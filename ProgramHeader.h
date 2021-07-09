//
// Created by yairko on 06/07/2021.
//

#ifndef KOSKASSEMBLER_PROGRAMHEADER_H
#define KOSKASSEMBLER_PROGRAMHEADER_H
#include <stdint.h>
#include <string>
#include "ElfUtil.h"
class ProgramHeader {
    bool m_is32Bit;
public:
    std::string name;
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
    void loadHeader(char* ptr);
    ProgramHeader(architecture e) {
        e == BIT32 ? this->m_is32Bit = true : this->m_is32Bit = false;
    }
    bool is32Bit() {
        return this->m_is32Bit;
    }
};
#endif //KOSKASSEMBLER_PROGRAMHEADER_H
