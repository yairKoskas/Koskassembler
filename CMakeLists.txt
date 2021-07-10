cmake_minimum_required(VERSION 3.19)
project(koskassembler)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_executable(koskassembler main.cpp ElfHeader.cpp ElfHeader.h ElfParserUtil.h ElfParserUtil.cpp
               SectionHeader.cpp SectionHeader.h ELF.cpp ELF.h ProgramHeader.cpp ProgramHeader.h
               Disassembler.cpp Disassembler.h ElfUtil.h DynamicTag.cpp DynamicTag.h Command.cpp
               Command.h ArgProcessor.cpp ArgProcessor.h ElfCommandFactory.cpp ElfCommandFactory.h)