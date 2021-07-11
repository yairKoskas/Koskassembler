//
// Created by yairko on 06/07/2021.
//
#include "ELF.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include "ElfUtil.h"
#define NO_RELRO 0
#define PARTIAL_RELRO 1
#define FULL_RELRO 2
#define PT_GNU_STACK 0x6474e551
#define PT_GNU_RELRO 0x6474e552
#define DT_FULL_RELRO 0x8
#define DT_PIE 0x8000001
bool isASCII (const std::string& s)
{
    return !std::any_of(s.begin(), s.end(), [](char c) {
        return static_cast<unsigned char>(c) > 127;
    });
}
class ElfNotInitializedException : public std::runtime_error {
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }

public:
    explicit ElfNotInitializedException(char const* const message="ELF Header Not Initialized") noexcept : std::runtime_error(message) {}
};
SectionHeader* ELF::getSectionHeader(std::string section_name) {
    for(SectionHeader *sh : this->s_headers) {
        if(sh->name == section_name) {
            return sh;
        }
    }
    return nullptr;
}
bool ELF::is32Bit() {
    return e_header->is32Bit();
}
std::map<uint32_t, std::string> loadStringTable(char* buf, int len) {
    int i;
    std::map<uint32_t,std::string> strings;
    ulong current_offset = 0;
    do {
        std::string s = std::string(buf);
        if (!s.empty())
            strings[current_offset] = s;
        buf += s.size() + 1;
        current_offset += s.size() + 1;
    } while (current_offset < len);
    return strings;
}
ELF::ELF(const std::string& path) {
    this->m_path = path;
    this->m_name = this->m_path.substr(this->m_path.find_last_of('/')+1,this->m_path.length() - 1);;
    this->e_header = new ElfHeader(path);
    uint32_t offset_of_section_table = this->e_header->e_shoff;
    FILE* f = fopen(path.c_str(),"r");
    fseek(f,(long)offset_of_section_table,SEEK_SET);
    // this->s_headers = new std::vector<SectionHeaderx86>[this->e_header->e_shnum];
    int i;
    for (i = 0; i < this->e_header->e_shnum; ++i) {
        if (this->is32Bit()) {
            this->s_headers.push_back(new SectionHeader(BIT32));
        } else {
            this->s_headers.push_back(new SectionHeader(BIT64));
        }
        char buf[this->e_header->e_shentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        this->s_headers[i]->loadHeader(buf);
    }
    uint32_t offset_of_program_table = this->e_header->e_phoff;
    fseek(f, (long)offset_of_program_table, SEEK_SET);
    for(i = 0; i < this->e_header->e_phnum; ++i) {
        if(this->is32Bit()) {
            this->p_headers.push_back(new ProgramHeader(BIT32));
        } else {
            this->p_headers.push_back(new ProgramHeader(BIT64));
        }
        char buf[this->e_header->e_phentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        this->p_headers[i]->loadHeader(buf);
    }
    SectionHeader* section_string_table = this->s_headers[this->e_header->e_shstrndx];
    fseek(f, (long)section_string_table->sh_offset, SEEK_SET);
    char buf[section_string_table->sh_size];
    fread(buf,sizeof(char),sizeof(buf),f);
    this->string_table = loadStringTable(buf, (int)section_string_table->sh_size);
    for (i = 0; i < this->e_header->e_shnum; ++i) {
        this->s_headers[i]->name = this->string_table[this->s_headers[i]->sh_name];
    }
    SectionHeader* symbol_string_table_section = this->getSectionHeader(".strtab");
    fseek(f, (long)symbol_string_table_section->sh_offset, SEEK_SET);
    char buf2[symbol_string_table_section->sh_size];
    fread(buf2,sizeof(char),sizeof(buf2),f);
    this->symbol_string_table = loadStringTable(buf2, symbol_string_table_section->sh_size);
    SectionHeader* dynamic_section = this->getSectionHeader(".dynamic");
    int size;
    if (this->is32Bit()) {
       size = 8;
    } else {
        size = 16;
    }
    fseek(f,(long)dynamic_section->sh_offset, SEEK_SET);
    for (i = 0; i < (int)dynamic_section->sh_size / size; ++i) {
        if (this->is32Bit()) {
            this->dynamic_tags.push_back(new DynamicTag(BIT32));
        } else {
            this->dynamic_tags.push_back(new DynamicTag(BIT64));
        }
        char buf3[dynamic_section->sh_entsize];
        fread(buf3,sizeof(char),sizeof(buf3),f);
        this->dynamic_tags[i]->loadTag(buf3);
    }
    fclose(f);
}
ELF::ELF(ElfHeader* e) {
    if (e == nullptr || e->is_init()) {
        throw ElfNotInitializedException();
    }
    this->m_path = e->m_path;
    this->m_name = this->m_path.substr(this->m_path.find_last_of('/')+1,this->m_path.length() - 1);;
    this->e_header = e;
    uint32_t offset_of_section_table = this->e_header->e_shoff;
    FILE* f = fopen(this->m_path.c_str(),"r");
    fseek(f,(int)offset_of_section_table,SEEK_SET);
    // this->s_headers = new std::vector<SectionHeaderx86>[this->e_header->e_shnum];
    int i;
    for (i = 0; i < this->e_header->e_shnum; ++i) {
        if (this->is32Bit()) {
            this->s_headers.push_back(new SectionHeader(BIT32));
        } else {
            this->s_headers.push_back(new SectionHeader(BIT64));
        }
        char buf[this->e_header->e_shentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        this->s_headers[i]->loadHeader(buf);
    }
    uint64_t offset_of_program_table = this->e_header->e_phoff;
    fseek(f,(long)offset_of_program_table,SEEK_SET);
    for(i = 0; i < this->e_header->e_phnum; ++i) {
        if(this->is32Bit()) {
            this->p_headers.push_back(new ProgramHeader(BIT32));
        } else {
            this->p_headers.push_back(new ProgramHeader(BIT64));
        }
        char buf[this->e_header->e_phentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        this->p_headers[i]->loadHeader(buf);
    }
    SectionHeader* section_string_table = this->s_headers[this->e_header->e_shstrndx];
    fseek(f, (long)section_string_table->sh_offset, SEEK_SET);
    char buf[section_string_table->sh_size];
    fread(buf,sizeof(char),sizeof(buf),f);
    this->string_table = loadStringTable(buf, (int)section_string_table->sh_size);
    for (i = 0; i < this->e_header->e_shnum; ++i) {
        this->s_headers[i]->name = this->string_table[this->s_headers[i]->sh_name];
    }
    SectionHeader* symbol_string_table_section = this->getSectionHeader(".strtab");
    fseek(f,(long)symbol_string_table_section->sh_offset, SEEK_SET);
    char buf2[symbol_string_table_section->sh_size];
    fread(buf2,sizeof(char),sizeof(buf2),f);
    this->symbol_string_table = loadStringTable(buf2, symbol_string_table_section->sh_size);
    SectionHeader* dynamic_section = this->getSectionHeader(".dynamic");
    int size;
    if (this->is32Bit()) {
        size = 8;
    } else {
        size = 16;
    }
    fseek(f,(long)dynamic_section->sh_offset, SEEK_SET);
    for (i = 0; i < (int)dynamic_section->sh_size / size; ++i) {
        if (this->is32Bit()) {
            this->dynamic_tags.push_back(new DynamicTag(BIT32));
        } else {
            this->dynamic_tags.push_back(new DynamicTag(BIT64));
        }
        char buf3[dynamic_section->sh_entsize];
        fread(buf3,sizeof(char),sizeof(buf3),f);
        this->dynamic_tags[i]->loadTag(buf3);
    }
    fclose(f);
}

std::string ELF::securityCheck() {
    bool nx = false;
    bool pie = false;
    bool canary = false;
    int relro = NO_RELRO;
    for (auto & iter : this->symbol_string_table) {
        if(iter.second.find("__stack_chk_fail") != std::string::npos) {
            canary = true;
            break;
        }
    }
    for (auto & iter : this->p_headers) {
        if (iter->p_type == PT_GNU_STACK && iter->p_flags % 2 == 0) {
            nx = true;
            break;
        }
    }
    int flag_debug = 0;
    int flag_now_pie = 0;
    for (auto & iter : this->p_headers) {
        if (iter->p_type == PT_GNU_RELRO) {
            relro = PARTIAL_RELRO;
            for (auto & dyn_iter : this->dynamic_tags) {
                if (dyn_iter->d_tag == DT_FLAGS && dyn_iter->d_val == DT_FULL_RELRO) {
                    relro = FULL_RELRO;
                }
                if (dyn_iter->d_tag == DT_DEBUG) {
                    flag_debug = 1;
                }
                if(dyn_iter->d_tag == DT_FLAGS_1 && dyn_iter->d_val == DT_PIE) {
                    flag_now_pie = 1;
                }
            }
        }
    }
    if(flag_debug && flag_now_pie) {
        pie = true;
    }
    std::string s;
    if (canary) {
        s += "Canary: Found\n";
    } else {
        s += "Canary: Not Found\n";
    }
    if (nx) {
        s += "NX: Enabled\n";
    } else {
        s += "NX: Disabled\n";
    }
    if (relro == NO_RELRO) {
        s += "RELRO: Disabled\n";
    } else if (relro == PARTIAL_RELRO) {
        s += "RELRO: Partial\n";
    } else {
        s += "RELRO: Full\n";
    }
    if (pie) {
        s += "PIE: Enabled\n";
    } else {
        s += "PIE: Disabled\n";
    }
    return s;
}
std::vector<std::string> ELF::infoPLTFunctions() {
    std::vector<std::string> plt_functions;
    for (auto & iter : this->symbol_string_table) {
        if (iter.second.find("@@") != std::string::npos) {
            plt_functions.push_back(iter.second.substr(0,iter.second.find("@@")));
        }
    }
    return plt_functions;
}