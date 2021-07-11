//
// Created by yairko on 07/07/2021.
//

#ifndef KOSKASSEMBLER_DISASSEMBLER_H
#define KOSKASSEMBLER_DISASSEMBLER_H
#include "ELF.h"

class Disassembler {
    ELF* m_elf;
    std::map<char, std::string> byteToInstruction;
    std::string disassemblex86(char* buf, int size);
    std::string disassemblex64(char* buf, int size);
    std::string decodeOpcodex86(char* buf);
    std::string decodeOpcodex64(char* buf);
public:
    explicit Disassembler(ELF* elf);
    std::string disassembleSection(const std::string& section_name);
};

#endif //KOSKASSEMBLER_DISASSEMBLER_H
