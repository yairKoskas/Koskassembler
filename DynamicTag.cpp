//
// Created by yairko on 10/07/2021.
//

#include "DynamicTag.h"
#include <cstring>
void DynamicTag::loadTag(char *buf) {
    int current_offset = 0;
    if (this->m_is32bit) {
        memcpy(&this->d_tag, &buf[current_offset], sizeof(this->d_tag) / 2);
        current_offset += sizeof(this->d_tag) / 2;
        switch(this->d_tag) {
            case DT_NULL:
                this->d_ptr = 0;
                break;
            case DT_NEEDED:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_PLTRELSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_PLTGOT:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_HASH:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_STRTAB:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_SYMTAB:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RELA:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RELASZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RELAENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_STRSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_SYMENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_INIT:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_FINI:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_SONAME:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RPATH:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_SYMBOLIC:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_REL:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RELSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RELENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_PLTREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_DEBUG:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_TEXTREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_JMPREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_BIND_NOW:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_RUNPATH:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_FLAGS:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
            case DT_FLAGS_1:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag) / 2);
                break;
        }
    } else {
        memcpy(&this->d_tag, &buf[current_offset], sizeof(this->d_tag));
        current_offset += sizeof(this->d_tag);
        switch (this->d_tag) {
            case DT_NULL:
                this->d_ptr = 0;
                break;
            case DT_NEEDED:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_PLTRELSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_PLTGOT:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_HASH:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_STRTAB:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_SYMTAB:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RELA:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RELASZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RELAENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_STRSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_SYMENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_INIT:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_FINI:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_SONAME:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RPATH:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_SYMBOLIC:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_REL:
                memcpy(&this->d_ptr, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RELSZ:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RELENT:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_PLTREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_DEBUG:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_TEXTREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_JMPREL:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_BIND_NOW:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_RUNPATH:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_FLAGS:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            case DT_FLAGS_1:
                memcpy(&this->d_val, &buf[current_offset], sizeof(this->d_tag));
                break;
            
        }
    }
}