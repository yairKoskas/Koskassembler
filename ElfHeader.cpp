//
// Created by yairko on 06/07/2021.
//

#include "ElfHeader.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include "ElfParserUtil.h"
class MagicELFException : public std::runtime_error {
public:
    explicit MagicELFException(char const* const message="Invalid Magic bits") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class ArchitectureException : public std::runtime_error {
public:
    explicit ArchitectureException(char const* const message="Invalid Architecture") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class EndianessException : public std::runtime_error {
public:
    explicit EndianessException(char const* const message="Invalid Endianness") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class VersionException : public std::runtime_error {
public:
    explicit VersionException(char const* const message="Invalid ELF Version") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class ABIException : public std::runtime_error {
public:
    explicit ABIException(char const* const message="Unsupported ABI") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};

class ElfTypeException : public std::runtime_error {
public:
    explicit ElfTypeException(char const* const message="Unsupported/Invalid Object File Type") noexcept :
        std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};

class ISAException : public std::runtime_error {
public:
    explicit ISAException(char const* const message="Unsupported/Invalid ISA") noexcept :
            std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};
void ElfHeader::validateHeader(){
    if (this->e_ident[0] != EI_MAG0
        || this->e_ident[1] != EI_MAG1
        || this->e_ident[2] != EI_MAG2
        || this->e_ident[3] != EI_MAG3) {
        throw MagicELFException();
    }
    if (this->e_ident[4] != ELFCLASS32 && this->e_ident[4] != ELFCLASS64) {
        throw ArchitectureException();
    }
    if (this->e_ident[5] != ELFDATA2LSB && this->e_ident[5] != ELFDATA2MSB) {
        throw EndianessException();
    }
    if (this->e_ident[6] != EV_CURRENT) {
        throw VersionException();
    }
    if (this->e_ident[7] != ELFOSABI_LINUX && this->e_ident[7] != ELFOSABI_SYSV) {
        throw ABIException();
    }
    // rest of e_ident doesn't have specific values, so we'll ignore it
    if (this->e_type != ET_REL && this->e_type != ET_EXEC && this->e_type != ET_DYN && this->e_type != ET_CORE) {
        throw ElfTypeException();
    }
    if ((this->e_ident[4] == ELFCLASS32 && this->e_machine != EM_386) ||
        (this->e_ident[4] == ELFCLASS64 && this->e_machine != EM_x86_64)) {
        throw ISAException();
    }
}

void ElfHeader::loadHeader(const std::string& path) {
    FILE* f = fopen(path.c_str(),"r");
    if (f == nullptr) {
        throw std::runtime_error("Error Opening File");
    }
    char *buf = new char[SIZE_OF_ELF_HEADER]; // this is the biggest buffer we'll need
    if (fread(buf,sizeof(char),SIZE_OF_ELF_HEADER,f) != SIZE_OF_ELF_HEADER) {
        throw std::runtime_error("Error Reading File");
    }
    fclose(f);
    int current_offset = 0;
    memcpy(this->e_ident, &buf[current_offset], sizeof(this->e_ident));
    current_offset += sizeof(this->e_ident);
    memcpy(&this->e_type, &buf[current_offset], sizeof(this->e_type));
    current_offset += sizeof(this->e_type);
    memcpy(&this->e_machine, &buf[current_offset], sizeof(this->e_machine));
    current_offset += sizeof(this->e_machine);
    memcpy(&this->e_version, &buf[current_offset], sizeof(this->e_version));
    current_offset += sizeof(this->e_version);
    if (this->is32Bit()) {
        memcpy(&this->e_entry, &buf[current_offset], sizeof(this->e_entry) / 2);
        current_offset += sizeof(this->e_entry) / 2;
        memcpy(&this->e_phoff, &buf[current_offset], sizeof(this->e_phoff) / 2);
        current_offset += sizeof(this->e_phoff) / 2;
        memcpy(&this->e_shoff, &buf[current_offset], sizeof(this->e_shoff) / 2);
        current_offset += sizeof(this->e_shoff) / 2;
    } else {
        memcpy(&this->e_entry, &buf[current_offset], sizeof(this->e_entry));
        current_offset += sizeof(this->e_entry);
        memcpy(&this->e_phoff, &buf[current_offset], sizeof(this->e_phoff));
        current_offset += sizeof(this->e_phoff);
        memcpy(&this->e_shoff, &buf[current_offset], sizeof(this->e_shoff));
        current_offset += sizeof(this->e_shoff);
    }
    memcpy(&this->e_flags, &buf[current_offset], sizeof(this->e_flags));
    current_offset += sizeof(this->e_flags);
    memcpy(&this->e_ehsize, &buf[current_offset], sizeof(this->e_ehsize));
    current_offset += sizeof(this->e_ehsize);
    memcpy(&this->e_phentsize, &buf[current_offset], sizeof(this->e_phentsize));
    current_offset += sizeof(this->e_phentsize);
    memcpy(&this->e_phnum, &buf[current_offset], sizeof(this->e_phnum));
    current_offset += sizeof(this->e_phnum);
    memcpy(&this->e_shentsize, &buf[current_offset], sizeof(this->e_shentsize));
    current_offset += sizeof(this->e_shentsize);
    memcpy(&this->e_shnum, &buf[current_offset], sizeof(this->e_shnum));
    current_offset += sizeof(this->e_shnum);
    memcpy(&this->e_shstrndx, &buf[current_offset], sizeof(this->e_shstrndx));
}
void ElfHeader::printHeaderInfo() {
    std::cout << std::endl << "---------------------ELF Header Info----------------------" << std::endl;
    std::cout <<  "ELF Magic                    7f 46 4c 45" << std::endl;
    std::cout <<  "Architecture                 64 Bit" << std::endl;
    std::cout <<  "Endianness                   " << convertEndianessToString(this->e_ident[5]) << std::endl;
    std::cout <<  "Version                      " << (char)(this->e_ident[6]+'0') << std::endl;
    std::cout <<  "OS/ABI                       " << convertABIToString(this->e_ident[7]) << std::endl;
    std::cout <<  "File Type                    " << convertTypeToString(this->e_type) << std::endl;
    std::cout <<  "Machine                      " << convertMachineToString(this->e_machine) << std::endl;
    std::cout <<  "Version                      " << intToHex(this->e_version) << std::endl;
    std::cout <<  "Entry Point                  " << intToHex(this->e_entry) << std::endl;
    std::cout <<  "Start Of Program Headers     " << intToHex(this->e_phoff) << std::endl;
    std::cout <<  "Start Of Section Headers     " << intToHex(this->e_shoff) << std::endl;
    std::cout <<  "Flags                        " << intToHex(this->e_flags) << std::endl;
    std::cout <<  "Size Of This Header          " << intToHex(this->e_ehsize) << std::endl;
    std::cout <<  "Size Of Program Headers      " << intToHex(this->e_phentsize) << std::endl;
    std::cout <<  "Number Of Program Headers    " << intToHex(this->e_phnum) << std::endl;
    std::cout <<  "Size Of Section Headers      " << intToHex(this->e_shentsize) << std::endl;
    std::cout <<  "Number Of Section Headers    " << intToHex(this->e_shnum) << std::endl;
    std::cout <<  "String Table Index           " << intToHex(this->e_shstrndx) << std::endl;
    std::cout << "---------------------ELF Header Info----------------------" << std::endl << std::endl;
}
ElfHeader::ElfHeader(const std::string& path) {
    this->m_path = path;
    this->loadHeader(path);
    this->validateHeader();
}