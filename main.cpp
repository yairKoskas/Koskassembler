#include <iostream>
#include "Elf/ELF.h"
#include "Disassembler/Disassembler.h"
#include "Utils/ArgProcessor.h"
int main(int argc, char* argv[]) {
    if (argc <= 2) {
       std::cout << "Usage: ./koskassembler [path-to-elf] [flags]" << std::endl;
       std::cout << "For more information, try ./koskassembler --help" << std::endl;
       return 0;
    }
    std::string path = argv[1];
    std::vector<std::string> args;
    int i;
    for (i = 2; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    auto* elf = new ELF(path);
    auto* ap = new ArgProcessor(args, elf);
    ap->executeArgs();
    delete elf;
    delete ap;
    return 0;
}
