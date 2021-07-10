//
// Created by yairko on 06/07/2021.
//
#include "ElfParserUtil.h"
#include "ElfHeader.h"
#include <iostream>
#include <iomanip>

std::string convertEndianessToString(unsigned char endianess) {
    if (endianess == 1) {
        return "2'S Complement, Little Endian";
    } else {
        return "2'S Complement, Big Endian";
    }
}

std::string convertABIToString(unsigned char ABI) {
    if (ABI == ELFOSABI_LINUX) {
        return "Linux";
    } else {
        return "UNIX - System V";
    }
}

std::string convertTypeToString(uint16_t e_type) {
    if (e_type == ET_REL) {
        return "Relocatable File";
    } else if (e_type == ET_EXEC) {
        return "Executable File";
    } else if (e_type == ET_DYN) {
        return "Shared Object File";
    } else {
        return "Core File";
    }
}

std::string convertMachineToString(uint16_t e_machine) {
    if (e_machine == EM_386) {
        return "Intel 80386";
    } else {
        return "AMD x86-64";
    }
}