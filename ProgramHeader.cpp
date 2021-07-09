//
// Created by yairko on 06/07/2021.
//
#include <cstring>
#include "ProgramHeader.h"
void ProgramHeader::loadHeader(char *ptr) {
    int current_offset = 0;
    memcpy(&this->p_type, &ptr[current_offset], sizeof(this->p_type));
    current_offset += sizeof(this->p_type);
    if(this->is32Bit()) {
        memcpy(&this->p_offset, &ptr[current_offset], sizeof(this->p_offset) / 2);
        current_offset += sizeof(this->p_offset) / 2;
        memcpy(&this->p_vaddr, &ptr[current_offset], sizeof(this->p_vaddr) / 2);
        current_offset += sizeof(this->p_vaddr) / 2;
        memcpy(&this->p_paddr, &ptr[current_offset], sizeof(this->p_paddr) / 2);
        current_offset += sizeof(this->p_paddr) / 2;
        memcpy(&this->p_filesz, &ptr[current_offset], sizeof(this->p_filesz) / 2);
        current_offset += sizeof(this->p_filesz) / 2;
        memcpy(&this->p_memsz, &ptr[current_offset], sizeof(this->p_memsz) / 2);
        current_offset += sizeof(this->p_memsz) / 2;
    } else {
        memcpy(&this->p_offset, &ptr[current_offset], sizeof(this->p_offset));
        current_offset += sizeof(this->p_offset);
        memcpy(&this->p_vaddr, &ptr[current_offset], sizeof(this->p_vaddr));
        current_offset += sizeof(this->p_vaddr);
        memcpy(&this->p_paddr, &ptr[current_offset], sizeof(this->p_paddr));
        current_offset += sizeof(this->p_paddr);
        memcpy(&this->p_filesz, &ptr[current_offset], sizeof(this->p_filesz));
        current_offset += sizeof(this->p_filesz);
        memcpy(&this->p_memsz, &ptr[current_offset], sizeof(this->p_memsz));
        current_offset += sizeof(this->p_memsz);
    }
    memcpy(&this->p_flags, &ptr[current_offset], sizeof(this->p_flags));
    current_offset += sizeof(this->p_flags);
    memcpy(&this->p_align, &ptr[current_offset], sizeof(this->p_align));
}