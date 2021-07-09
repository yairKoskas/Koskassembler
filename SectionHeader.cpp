//
// Created by yairko on 06/07/2021.
//

#include "SectionHeader.h"
#include "ElfParserUtil.h"
#include <cstring>
#include <iostream>

void SectionHeader::validateHeader() {

}
void SectionHeader::loadHeader(char* ptr) {
    int current_offset = 0;
    memcpy(&this->sh_name, &ptr[current_offset], sizeof(this->sh_name));
    current_offset += sizeof(this->sh_name);
    memcpy(&this->sh_type, &ptr[current_offset], sizeof(this->sh_type));
    current_offset += sizeof(this->sh_type);
    if (this->is32Bit()) {
        memcpy(&this->sh_flags, &ptr[current_offset], sizeof(this->sh_flags) / 2);
        current_offset += sizeof(this->sh_flags) / 2;
        memcpy(&this->sh_addr, &ptr[current_offset], sizeof(this->sh_addr) / 2);
        current_offset += sizeof(this->sh_addr) / 2;
        memcpy(&this->sh_offset, &ptr[current_offset], sizeof(this->sh_offset) / 2);
        current_offset += sizeof(this->sh_offset) / 2;
        memcpy(&this->sh_size, &ptr[current_offset], sizeof(this->sh_size) / 2);
        current_offset += sizeof(this->sh_size) / 2;
        memcpy(&this->sh_link, &ptr[current_offset], sizeof(this->sh_link));
        current_offset += sizeof(this->sh_link);
        memcpy(&this->sh_info, &ptr[current_offset], sizeof(this->sh_info) / 2);
        current_offset += sizeof(this->sh_info) / 2;
        memcpy(&this->sh_addralign, &ptr[current_offset], sizeof(this->sh_addralign) / 2);
        current_offset += sizeof(this->sh_addralign) / 2;
        memcpy(&this->sh_entsize, &ptr[current_offset], sizeof(this->sh_entsize) / 2);
    } else {
        memcpy(&this->sh_flags, &ptr[current_offset], sizeof(this->sh_flags));
        current_offset += sizeof(this->sh_flags);
        memcpy(&this->sh_addr, &ptr[current_offset], sizeof(this->sh_addr));
        current_offset += sizeof(this->sh_addr);
        memcpy(&this->sh_offset, &ptr[current_offset], sizeof(this->sh_offset));
        current_offset += sizeof(this->sh_offset);
        memcpy(&this->sh_size, &ptr[current_offset], sizeof(this->sh_size));
        current_offset += sizeof(this->sh_size);
        memcpy(&this->sh_link, &ptr[current_offset], sizeof(this->sh_link));
        current_offset += sizeof(this->sh_link);
        memcpy(&this->sh_info, &ptr[current_offset], sizeof(this->sh_info));
        current_offset += sizeof(this->sh_info);
        memcpy(&this->sh_addralign, &ptr[current_offset], sizeof(this->sh_addralign));
        current_offset += sizeof(this->sh_addralign);
        memcpy(&this->sh_entsize, &ptr[current_offset], sizeof(this->sh_entsize));
    }
    this->validateHeader();
}