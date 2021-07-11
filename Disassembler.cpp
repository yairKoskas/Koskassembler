//
// Created by yairko on 07/07/2021.
//

#include "Disassembler.h"
Disassembler::Disassembler(ELF *elf) {
    this->m_elf = elf;
}
std::string decodeOpcodex86(char* buf) {
    std::string s;
    
}
std::string disassemblex86(char* buf, int size) {
    int i;
    std::string s;
    for (i = 0; i < size; ++i) {
        s += decodeOpcodex86(buf);
        buf += s.length();
    }
    return s;
}
std::string disassemblex64(char* buf, int size) {
    int i;
    std::string s;
    for (i = 0; i < size; ++i) {
        s += decodeOpcodex64(buf);
        buf += s.length();
    }
    return s;
}
std::string Disassembler::disassembleSection(const std::string& section_name) {
    FILE* f = fopen(this->m_elf->m_path.c_str(), "r");
    SectionHeader* sec = this->m_elf->getSectionHeader(section_name);
    fseek(f,(long)sec->sh_offset,SEEK_SET);
    char buf[sec->sh_size];
    fread(buf,sizeof(char),sizeof(buf),f);
    if(this->m_elf->is32Bit()) {
        return disassemblex86(buf, sec->sh_size);
    }
    return disassemblex64(buf, sec->sh_size);
}