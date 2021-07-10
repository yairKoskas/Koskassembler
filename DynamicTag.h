//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_DYNAMICTAG_H
#define KOSKASSEMBLER_DYNAMICTAG_H
#include <cstdint>
#include <elf.h>
#include "ElfUtil.h"
class DynamicTag {
    bool m_is32bit;
public:
    uint64_t d_tag;
    union {
        uint64_t d_val;
        uint64_t d_ptr;
    };
    DynamicTag(architecture arch) {
        arch == BIT32 ? this->m_is32bit = true : this->m_is32bit = false;
    }
    void loadTag(char* buf);
};


#endif //KOSKASSEMBLER_DYNAMICTAG_H
