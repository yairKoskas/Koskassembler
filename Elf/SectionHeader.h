//
// Created by yairko on 06/07/2021.
//

#ifndef KOSKASSEMBLER_SECTIONHEADER_H
#define KOSKASSEMBLER_SECTIONHEADER_H
#include <cstdint>
#include <string>
#include "ElfUtil.h"
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_NUM 19
#define SHF_WRITE 1
#define SHF_ALLOC 2
#define SHF_EXECINSTR 4
#define SHF_MERGE 16
#define SHF_STRINGS 32
#define SHF_INFO_LINK 64
#define SHF_LINK_ORDER 128
#define SHF_OS_NONCONFORMING 256
#define SHF_GROUP 512
#define SHF_TLS 1024
class SectionHeader {
    bool m_is32Bit;
public:
    std::string name;
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint64_t   sh_size;
    uint64_t   sh_flags;
    uint64_t   sh_addralign;
    uint64_t   sh_entsize;
    uint64_t   sh_addr;
    uint64_t   sh_offset;
    SectionHeader(architecture e) {
        e == BIT32 ? this->m_is32Bit = true : this->m_is32Bit = false;
    }
    void loadHeader(char* ptr);
    void validateHeader();
    bool is32Bit() const {
        return this->m_is32Bit;
    }
};
#endif //KOSKASSEMBLER_SECTIONHEADER_H
