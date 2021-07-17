//
// Created by yairko on 18/07/2021.
//
#include "x86OpcodeTable.h"
#include "OpcodeExceptions.h"
x86OpcodeTable* x86OpcodeTable::x86OpcodeTable_ = nullptr;
x86OpcodeTable* x86OpcodeTable::getInstance() {
    if (x86OpcodeTable_ == nullptr) {
        x86OpcodeTable_ = new x86OpcodeTable();
    }
    return x86OpcodeTable_;
}
x86OpcodeTable::x86OpcodeTable() {
    //todo: fill the opcode_table with x86 byte to opcodes
}
Opcode x86OpcodeTable::getOpcode(char* s) const{
    try {
        return this->opcode_table.at(s);
    } catch (std::out_of_range& e) {
        throw OpcodeNotFoundException();
    }
}

Opcode x86OpcodeTable::getOpcode(const char *s) const {
    try {
        return this->opcode_table.at(s);
    } catch (std::out_of_range& e) {
        throw OpcodeNotFoundException();
    }
}
