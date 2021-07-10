//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_ELFCOMMANDFACTORY_H
#define KOSKASSEMBLER_ELFCOMMANDFACTORY_H
#include "Command.h"
#include <string>
#include <map>
class ElfCommandFactory {
private:
    ELF* m_elf;
    std::map<std::string, Command*> m_mapping;
public:
    ElfCommandFactory(ELF* elf);
    Command* getCommand(const std::string& name);
};


#endif //KOSKASSEMBLER_ELFCOMMANDFACTORY_H
