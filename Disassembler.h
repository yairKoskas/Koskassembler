//
// Created by yairko on 07/07/2021.
//

#ifndef KOSKASSEMBLER_DISASSEMBLER_H
#define KOSKASSEMBLER_DISASSEMBLER_H
#include "ELF.h"

class Disassembler {
    ELF* m_elf;

public:
    explicit Disassembler(ELF* elf);
    std::string disassembleSection(const std::string& section_name);
};

#endif //KOSKASSEMBLER_DISASSEMBLER_H
