//
// Created by yairko on 06/07/2021.
//

#ifndef KOSKASSEMBLER_ELF_H
#define KOSKASSEMBLER_ELF_H
#include "ElfHeader.h"
#include "ProgramHeader.h"
#include "SectionHeader.h"
#include "DynamicTag.h"
#include <vector>
#include <map>
class ELF {
public:
    std::string m_name;
    std::string m_path;
    ElfHeader* e_header;
    std::vector<SectionHeader*> s_headers;
    std::vector<ProgramHeader*> p_headers;
    std::vector<DynamicTag*> dynamic_tags;
    std::map<uint32_t,std::string> string_table;
    std::map<uint32_t,std::string> symbol_string_table;
    SectionHeader* getSectionHeader(std::string section_name);
    ELF(std::string path);
    ELF(ElfHeader* e);
    std::string securityCheck();
    std::vector<std::string> infoPLTFunctions();
    bool is32Bit();
};
#endif //KOSKASSEMBLER_ELF_H
