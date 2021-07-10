//
// Created by yairko on 10/07/2021.
//

#include "ArgProcessor.h"
void ArgProcessor::executeArgs() {
    for (auto & iter : this->m_args) {
        if (this->m_cf->getCommand(iter) != nullptr) {
            this->m_cf->getCommand(iter)->execute();
        } else {
            std::cout << "No Such Command: " << iter << std::endl;
        }
    }
}
ArgProcessor::ArgProcessor(std::vector<std::string> args, ELF* elf) {
    this->m_args = args;
    this->m_elf = elf;
    this->m_cf = new ElfCommandFactory(elf);
}