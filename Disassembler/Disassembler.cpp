//
// Created by yairko on 07/07/2021.
//

#include "Disassembler.h"
Disassembler::Disassembler(ELF *elf) {
    this->m_elf = elf;
    this->byteToInstruction.insert({0x40,"inc eax\n"});
    this->byteToInstruction.insert({0x41,"inc ecx\n"});
    this->byteToInstruction.insert({0x42,"inc edx\n"});
    this->byteToInstruction.insert({0x43,"inc ebx\n"});
    this->byteToInstruction.insert({0x44,"inc esp\n"});
    this->byteToInstruction.insert({0x45,"inc ebp\n"});
    this->byteToInstruction.insert({0x46,"inc esi\n"});
    this->byteToInstruction.insert({0x47,"inc edi\n"});
    this->byteToInstruction.insert({0x48,"dec eax\n"});
    this->byteToInstruction.insert({0x49,"dec ecx\n"});
    this->byteToInstruction.insert({0x4a,"dec edx\n"});
    this->byteToInstruction.insert({0x4b,"dec ebx\n"});
    this->byteToInstruction.insert({0x4c,"dec esp\n"});
    this->byteToInstruction.insert({0x4d,"dec ebp\n"});
    this->byteToInstruction.insert({0x4e,"dec esi\n"});
    this->byteToInstruction.insert({0x4f,"dec edi\n"});
    this->byteToInstruction.insert({0x50,"push rax\n"});
}
std::pair<std::string*,int> Disassembler::decodeOpcodex64(char* buf) {
    return {nullptr, 1};
}
std::pair<std::string*,int> Disassembler::decodeOpcodex86(char* buf) {
    std::string* s = new std::string(this->byteToInstruction[buf[0]]);
    if (((*s)[s->length()-1]) == '\n') {
        return {s,1};
    }
    return {s, 1};
}
std::string Disassembler::disassemblex86(char* buf, int size) {
    int i;
    std::string s;
    for (i = 0; i < size; ++i) {
        std::pair<std::string*, int> result = decodeOpcodex86(buf);
        if(!result.first->empty())
            s += (*result.first);
        buf += result.second;
    }
    return s;
}
std::string Disassembler::disassemblex64(char* buf, int size) {
    int i;
    std::string s;
    for (i = 0; i < size; ++i) {
        //s += decodeOpcodex64(buf);
        //buf += s.length();
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
        return this->disassemblex86(buf, sec->sh_size);
    }
    return this->disassemblex64(buf, sec->sh_size);
}