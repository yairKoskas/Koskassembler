//
// Created by yairko on 18/07/2021.
//

#ifndef KOSKASSEMBLER_OPCODEEXCEPTIONS_H
#define KOSKASSEMBLER_OPCODEEXCEPTIONS_H
class OpcodeNotFoundException : public std::runtime_error {
public:
    explicit OpcodeNotFoundException(char const* const message="Invalid Magic bits") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};
#endif //KOSKASSEMBLER_OPCODEEXCEPTIONS_H
