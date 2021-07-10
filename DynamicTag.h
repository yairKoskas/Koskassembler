//
// Created by yairko on 10/07/2021.
//

#ifndef KOSKASSEMBLER_DYNAMICTAG_H
#define KOSKASSEMBLER_DYNAMICTAG_H
#include <cstdint>
#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH	15
#define DT_SYMBOLIC	16
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define	DT_BIND_NOW	24
#define DT_RUNPATH	29
#define DT_FLAGS	30
#define DT_FLAGS_1	0x6ffffffb
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
