//
// Created by yairko on 06/07/2021.
//

#ifndef KOSKASSEMBLER_ELFHEADER_H
#define KOSKASSEMBLER_ELFHEADER_H
#include <string>
#include <stdexcept>

#define EI_NIDENT 16
#define EI_MAG0 0x7f
#define EI_MAG1 'E'
#define EI_MAG2 'L'
#define EI_MAG3 'F'
#define ELFCLASS32 1
#define ELFCLASS64 2
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2
#define EV_CURRENT 1
#define ELFOSABI_SYSV 0
#define ELFOSABI_LINUX 3
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define EM_386 3
#define EM_x86_64 0x3e
#define SIZE_OF_ELF_HEADER 64
class ElfHeader{
    void loadHeader(const std::string& path);
public:
    std::string m_path;
    unsigned char e_ident[EI_NIDENT];
    uint16_t      e_type;
    uint16_t      e_machine;
    uint32_t      e_version;
    uint64_t      e_entry;
    uint64_t      e_phoff;
    uint64_t      e_shoff;
    uint32_t      e_flags;
    uint16_t      e_ehsize;
    uint16_t      e_phentsize;
    uint16_t      e_phnum;
    uint16_t      e_shentsize;
    uint16_t      e_shnum;
    uint16_t      e_shstrndx;
    void printHeaderInfo();
    void validateHeader();
    explicit ElfHeader(const std::string& path);
    bool is_init() {
        try {
            this->validateHeader();
        } catch (const std::runtime_error& e) {
            return false;
        }
        return true;
    }

    bool is32Bit() {
        return this->e_ident[4] == ELFCLASS32;
    }
};

ElfHeader* getHeader(const std::string& path);
#endif //KOSKASSEMBLER_ELFHEADER_H
