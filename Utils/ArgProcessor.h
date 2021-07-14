//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_ARGPROCESSOR_H
#define KOSKASSEMBLER_ARGPROCESSOR_H
#include "CommandFactory.h"
#include "Command.h"
#include <string>
#include <vector>
class ArgProcessor {
    std::vector<std::string> m_args;
    CommandFactory* m_cf;
public:
    ArgProcessor(std::vector<std::string> args, ELF* elf);
    void executeArgs();
    ~ArgProcessor();
};


#endif //KOSKASSEMBLER_ARGPROCESSOR_H
