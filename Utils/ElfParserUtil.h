//
// Created by yairko on 06/07/2021.
//

#ifndef KOSKASSEMBLER_ELFPARSERUTIL_H
#define KOSKASSEMBLER_ELFPARSERUTIL_H
#include <string>
#include <iomanip>
std::string convertEndianessToString(unsigned char endianess);
std::string convertABIToString(unsigned char ABI);
std::string convertTypeToString(uint16_t e_type);
std::string convertMachineToString(uint16_t e_machine);
std::string covertSectionTypeToString(uint16_t s_type);
std::string covertSectionAttributesToString(uint16_t s_type);

template< typename T >
std::string intToHex( T i ) {
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0')
           << std::hex << i;
    return stream.str();
}
#endif //KOSKASSEMBLER_ELFPARSERUTIL_H
