//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_COMMANDFACTORY_H
#define KOSKASSEMBLER_COMMANDFACTORY_H
#include "Command.h"
#include <string>
#include <map>
class CommandFactory {
private:
    ELF* m_elf;
    std::map<std::string, Command*> m_mapping;
public:
    CommandFactory(ELF* elf);
    Command* getCommand(const std::string& name);
    ~CommandFactory();
};


#endif //KOSKASSEMBLER_COMMANDFACTORY_H
