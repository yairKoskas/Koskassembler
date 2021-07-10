//
// Created by yairko on 10/07/2021.
//

#include "CommandFactory.h"
CommandFactory::CommandFactory(ELF* elf) {
    this->m_elf = elf;
    this->m_mapping.insert({"--checksec", new Checksec(m_elf)});
    this->m_mapping.insert({"--info-plt", new InfoPlt(m_elf)});
    this->m_mapping.insert({"--info-header", new InfoHeader(m_elf)});
    this->m_mapping.insert({"--info-shstrtab", new StringTableInfo(m_elf)});
    this->m_mapping.insert({"--info-string-table", new StringTableInfo(m_elf)});
    this->m_mapping.insert({"--info-symtab", new SymbolTableInfo(m_elf)});
    this->m_mapping.insert({"--info-symbol-table", new SymbolTableInfo(m_elf)});
    this->m_mapping.insert({"--help",new Help()});
}
Command * CommandFactory::getCommand(const std::string& name) {
    if (this->m_mapping.find(name) == this->m_mapping.end()) {
        return nullptr;
    }
    return this->m_mapping[name];
}