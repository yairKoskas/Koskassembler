cmake_minimum_required(VERSION 3.17)
project(koskassembler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_executable(koskassembler main.cpp Elf/ElfHeader.cpp Elf/ElfHeader.h Utils/ElfParserUtil.h Utils/ElfParserUtil.cpp
        Elf/SectionHeader.cpp Elf/SectionHeader.h Elf/ELF.cpp Elf/ELF.h Elf/ProgramHeader.cpp Elf/ProgramHeader.h
        Disassembler/Disassembler.cpp Disassembler/Disassembler.h Elf/ElfUtil.h Elf/DynamicTag.cpp Elf/DynamicTag.h Utils/Command.cpp
        Utils/Command.h Utils/ArgProcessor.cpp Utils/ArgProcessor.h Utils/CommandFactory.cpp Utils/CommandFactory.h Disassembler/x86OpcodeTable.h Disassembler/x86OpcodeTable.cpp Disassembler/Opcode.cpp Disassembler/Opcode.h Elf/ElfExceptions.h Disassembler/OpcodeExceptions.h)