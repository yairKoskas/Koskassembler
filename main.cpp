#include <iostream>
#include "ELF.h"
#include "ElfParserUtil.h"
#include "Disassembler.h"
int main() {
    std::string path = "/home/yairko/Desktop/University/cs/OperatingSystems/ex4/a.out";
    ElfHeader* e = new ElfHeader(path);
    auto* elf = new ELF(e);
    elf->e_header->printHeaderInfo();
    std::cout << elf->securityCheck() << std::endl;
    for(auto & iter : elf->infoPLTFunctions()) {
        std::cout << iter << std::endl;
    }
    return 0;
}
