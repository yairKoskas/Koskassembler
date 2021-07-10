//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_ARGPROCESSOR_H
#define KOSKASSEMBLER_ARGPROCESSOR_H
#include "ElfCommandFactory.h"
#include "Command.h"
#include <string>
#include <vector>
class ArgProcessor {
    std::vector<std::string> m_args;
    ElfCommandFactory* m_cf;
    ELF* m_elf;
public:
    ArgProcessor(std::vector<std::string> args, ELF* elf);
    void executeArgs();
};


#endif //KOSKASSEMBLER_ARGPROCESSOR_H
