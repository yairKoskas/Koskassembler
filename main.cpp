#include <iostream>
#include "ELF.h"
#include "ElfParserUtil.h"
#include "Disassembler.h"
#include "ArgProcessor.h"
int main(int argc, char* argv[]) {
    if (argc <= 1) {
       std::cout << "Usage: ./koskassembler [path] [flags]" << std::endl;
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
    return 0;
}
