//
// Created by yairko on 06/07/2021.
//
#include "ELF.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
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
std::map<uint32_t, std::string> loadStringTable(char* buf, uint32_t len) {
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
void loadSectionHeaders(ELF* elf) {
    uint32_t offset_of_section_table = elf->e_header->e_shoff;
    FILE* f = fopen(elf->m_path.c_str(),"r");
    fseek(f,(int)offset_of_section_table,SEEK_SET);
    int i;
    for (i = 0; i < elf->e_header->e_shnum; ++i) {
        if (elf->is32Bit()) {
            elf->s_headers.push_back(new SectionHeader(BIT32));
        } else {
            elf->s_headers.push_back(new SectionHeader(BIT64));
        }
        char buf[elf->e_header->e_shentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        elf->s_headers[i]->loadHeader(buf);
    }
    fclose(f);
}
void loadProgramHeaders(ELF* elf) {
    FILE* f = fopen(elf->m_path.c_str(),"r");
    uint64_t offset_of_program_table = elf->e_header->e_phoff;
    fseek(f,(long)offset_of_program_table,SEEK_SET);
    int i;
    for(i = 0; i < elf->e_header->e_phnum; ++i) {
        if(elf->is32Bit()) {
            elf->p_headers.push_back(new ProgramHeader(BIT32));
        } else {
            elf->p_headers.push_back(new ProgramHeader(BIT64));
        }
        char buf[elf->e_header->e_phentsize];
        fread(buf,sizeof(char),sizeof(buf),f);
        elf->p_headers[i]->loadHeader(buf);
    }
    fclose(f);
}
void loadElfStringTable(ELF* elf) {
    FILE* f = fopen(elf->m_path.c_str(),"r");
    int i;
    SectionHeader* section_string_table = elf->s_headers[elf->e_header->e_shstrndx];
    fseek(f, (long)section_string_table->sh_offset, SEEK_SET);
    char buf[section_string_table->sh_size];
    fread(buf,sizeof(char),sizeof(buf),f);
    elf->string_table = loadStringTable(buf, (int)section_string_table->sh_size);
    for (i = 0; i < elf->e_header->e_shnum; ++i) {
        elf->s_headers[i]->name = elf->string_table[elf->s_headers[i]->sh_name];
    }
    fclose(f);
}
void loadElfSymbolTable(ELF* elf) {
    FILE* f = fopen(elf->m_path.c_str(),"r");
    SectionHeader* symbol_string_table_section = elf->getSectionHeader(".strtab");
    fseek(f,(long)symbol_string_table_section->sh_offset, SEEK_SET);
    char buf2[symbol_string_table_section->sh_size];
    fread(buf2,sizeof(char),sizeof(buf2),f);
    elf->symbol_string_table = loadStringTable(buf2, symbol_string_table_section->sh_size);
    fclose(f);
}
void loadDynamicSection(ELF* elf) {
    FILE* f = fopen(elf->m_path.c_str(),"r");
    SectionHeader* dynamic_section = elf->getSectionHeader(".dynamic");
    int size;
    if (elf->is32Bit()) {
        size = 8;
    } else {
        size = 16;
    }
    fseek(f,(long)dynamic_section->sh_offset, SEEK_SET);
    int i;
    for (i = 0; i < (int)dynamic_section->sh_size / size; ++i) {
        if (elf->is32Bit()) {
            elf->dynamic_tags.push_back(new DynamicTag(BIT32));
        } else {
            elf->dynamic_tags.push_back(new DynamicTag(BIT64));
        }
        char buf3[dynamic_section->sh_entsize];
        fread(buf3,sizeof(char),sizeof(buf3),f);
        elf->dynamic_tags[i]->loadTag(buf3);
    }
    fclose(f);
}
ELF::ELF(const std::string& path) : ELF(new ElfHeader(path)) {}

ELF::ELF(ElfHeader* e) {
    if (e == nullptr || !e->is_init()) {
        throw ElfNotInitializedException();
    }
    this->m_path = e->m_path;
    this->m_name = this->m_path.substr(this->m_path.find_last_of('/')+1,this->m_path.length() - 1);;
    this->e_header = e;
    //sections headers and string table should be joined because the other threads are using data they produce
    std::thread load_section_headers (loadSectionHeaders, this);
    load_section_headers.join();
    std::thread load_string_table (loadElfStringTable, this);
    load_string_table.join();
    std::thread load_program_headers (loadProgramHeaders, this);
    std::thread load_symbol_table (loadElfSymbolTable, this);
    std::thread load_dynamic_tags (loadDynamicSection, this);
    load_program_headers.join();
    load_symbol_table.join();
    load_dynamic_tags.join();
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
ELF::~ELF() {
    delete this->e_header;
    int i;
    for (i = 0; i < this->s_headers.size(); ++i) {
        delete this->s_headers[i];
    }
    for (i = 0; i < this->p_headers.size(); ++i) {
        delete this->p_headers[i];
    }
    for (i = 0; i < this->dynamic_tags.size(); ++i) {
        delete this->dynamic_tags[i];
    }
}
