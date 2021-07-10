//
// Created by yairko on 10/07/2021.
//

#include "ElfCommandFactory.h"
ElfCommandFactory::ElfCommandFactory(ELF* elf) {
    this->m_elf = elf;
    this->m_mapping.insert({"--checksec", new Checksec(m_elf)});
    this->m_mapping.insert({"--info-plt", new InfoPlt(m_elf)});
    this->m_mapping.insert({"--info-header", new InfoHeader(m_elf)});
}
Command * ElfCommandFactory::getCommand(const std::string& name) {
    if (this->m_mapping.find(name) == this->m_mapping.end()) {
        return nullptr;
    }
    return this->m_mapping[name];
}