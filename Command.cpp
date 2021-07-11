//
// Created by yairko on 10/07/2021.
//

#include "Command.h"
#include "Disassembler.h"
void Help::execute()  {
    std::cout << "Display ELF file information:" << std::endl;
    std::cout << "Flag Options Are: " << std::endl;
    std::cout << "  --info-header:                       Display ELF Header Information" << std::endl;
    std::cout << "  --info-shstrtab/--info-string-table: Display String Table Entries" << std::endl;
    std::cout << "  --info-symtab/--info-symbol-table    Display Symbol Table Entries" << std::endl;
    std::cout << "  --info-plt                           Display Dynamically-Resolved Functions" << std::endl;
    std::cout << "  --checksec                           Display Security Attributes Information" << std::endl;
    std::cout << "  --disassemble                        Display Disassembly Of Text Section" << std::endl;
}
void SymbolTableInfo::execute() {
    for (auto & iter : this->m_elf->symbol_string_table) {
        if(!iter.second.empty())
            std::cout << iter.second << std::endl;
    }
    std::cout << std::endl;
}
void StringTableInfo::execute() {
    for (auto & iter : this->m_elf->string_table) {
        if(!iter.second.empty())
            std::cout << iter.second << std::endl;
    }
    std::cout << std::endl;
}
void InfoHeader::execute() {
    this->m_elf->e_header->printHeaderInfo();
}
void InfoPlt::execute() {
    for(auto & iter : this->m_elf->infoPLTFunctions())
        std::cout << iter << std::endl;
}
void Checksec::execute() {
    std::cout << this->m_elf->securityCheck() << std::endl;
}
void Disassemble::execute() {
    auto* d = new Disassembler(this->m_elf);
    std::cout << d->disassembleSection(".text") << std::endl;
    delete d;
}