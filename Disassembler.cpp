//
// Created by yairko on 07/07/2021.
//

#include "Disassembler.h"
Disassembler::Disassembler(ELF *elf) {
    this->m_elf = elf;
}
std::string disassemblex86(char* buf) {
    return "xor esi,esi";
}
std::string disassemblex64(char* buf) {
    return "xor rsi,rsi";
}
std::string Disassembler::disassembleSection(std::string section_name) {
//    if (this->m_elf->is32Bit()) {
//        SectionHeaderx86* sec = this->m_elf->getSectionHeader(section_name).first;
//        FILE* f = fopen(this->m_elf->m_path.c_str(), "r");
//        fseek(f,sec->sh_offset,SEEK_SET);
//        char buf[sec->sh_size];
//        fread(buf,sizeof(char),sizeof(buf),f);
//        fclose(f);
//        return "Disassembly of section <"+section_name+">\n"+disassemblex86(buf);
//    } else {
//        FILE* f = fopen(this->m_elf->m_path.c_str(), "r");
//        SectionHeaderx64* sec = this->m_elf->getSectionHeader(section_name).second;
//        fseek(f,sec->sh_offset,SEEK_SET);
//        char buf[sec->sh_size];
//        fread(buf,sizeof(char),sizeof(buf),f);
//        fclose(f);
//        return "Disassembly of section <"+section_name+">\n"+disassemblex64(buf);
//    }
}