//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_COMMAND_H
#define KOSKASSEMBLER_COMMAND_H

#include <iostream>
#include "../Elf/ELF.h"

class Command {
public:
    virtual void execute() = 0;
};
class ElfCommand : public Command {
protected:
    ELF* m_elf;
    explicit ElfCommand(ELF* elf) : m_elf(elf) {};
public:
    void execute() override = 0;
};
class Checksec : public ElfCommand {
    void execute() override;

public:
    explicit Checksec(ELF *elf) : ElfCommand(elf) {}
};
class InfoPlt : public ElfCommand {
    void execute() override;

public:
    explicit InfoPlt(ELF *elf) : ElfCommand(elf) {}
};
class InfoHeader : public ElfCommand {
    void execute() override;

public:
    explicit InfoHeader(ELF *elf) : ElfCommand(elf) {}
};
class StringTableInfo : public ElfCommand {
    void execute() override;

public:
    explicit StringTableInfo(ELF *elf) : ElfCommand(elf) {}
};
class SymbolTableInfo : public ElfCommand {
    void execute() override;

public:
    explicit SymbolTableInfo(ELF *elf) : ElfCommand(elf) {}
};
class Disassemble : public ElfCommand {
    void execute() override;

public:
    explicit Disassemble(ELF *elf) : ElfCommand(elf) {}
};
class Help : public Command {
    void execute() override;

public:
    explicit Help() : Command() {}
};
#endif //KOSKASSEMBLER_COMMAND_H
