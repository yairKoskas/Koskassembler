//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_COMMAND_H
#define KOSKASSEMBLER_COMMAND_H

#include <iostream>
#include "ELF.h"

class Command {
public:
    virtual void execute() = 0;
};
class ElfCommand : public Command {
protected:
    ELF* m_elf;
public:
    virtual void execute() = 0;
};
class Checksec : public ElfCommand {
public:
    Checksec(ELF* elf) {
        this->m_elf = elf;
    }
    void execute() override {
        std::cout << this->m_elf->securityCheck() << std::endl;
    }
};
class InfoPlt : public ElfCommand {
public:
    InfoPlt(ELF* elf) {
        this->m_elf = elf;
    }
    void execute() override {
        for(auto & iter : this->m_elf->infoPLTFunctions())
        std::cout << iter << std::endl;
    }
};
class InfoHeader : public ElfCommand {
public:
    InfoHeader(ELF* elf) {
        this->m_elf = elf;
    }
    void execute() override {
        this->m_elf->e_header->printHeaderInfo();
    }
};

#endif //KOSKASSEMBLER_COMMAND_H
