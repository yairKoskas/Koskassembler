//
// Created by yairko on 18/07/2021.
//

#ifndef KOSKASSEMBLER_X86OPCODETABLE_H
#define KOSKASSEMBLER_X86OPCODETABLE_H
#include "Opcode.h"
#include <string>
#include <map>
class x86OpcodeTable {
private:
    std::map<const char*,Opcode> opcode_table;
    static x86OpcodeTable* x86OpcodeTable_;
    x86OpcodeTable();
public:
    static x86OpcodeTable* getInstance() ;
    Opcode getOpcode(char* s) const;
    Opcode getOpcode(const char* s) const;
};
#endif //KOSKASSEMBLER_X86OPCODETABLE_H
