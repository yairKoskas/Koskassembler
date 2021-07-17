//
// Created by yairko on 18/07/2021.
//

#ifndef KOSKASSEMBLER_ELFEXCEPTIONS_H
#define KOSKASSEMBLER_ELFEXCEPTIONS_H
class MagicELFException : public std::runtime_error {
public:
    explicit MagicELFException(char const* const message="Invalid Magic bits") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class ArchitectureException : public std::runtime_error {
public:
    explicit ArchitectureException(char const* const message="Invalid Architecture") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class EndianessException : public std::runtime_error {
public:
    explicit EndianessException(char const* const message="Invalid Endianness") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class VersionException : public std::runtime_error {
public:
    explicit VersionException(char const* const message="Invalid ELF Version") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override {
        return std::runtime_error::what();
    }
};

class ABIException : public std::runtime_error {
public:
    explicit ABIException(char const* const message="Unsupported ABI") noexcept : std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};

class ElfTypeException : public std::runtime_error {
public:
    explicit ElfTypeException(char const* const message="Unsupported/Invalid Object File Type") noexcept :
            std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};

class ISAException : public std::runtime_error {
public:
    explicit ISAException(char const* const message="Unsupported/Invalid ISA") noexcept :
            std::runtime_error(message) {}
    char const* what() const noexcept override{
        return std::runtime_error::what();
    }
};
#endif //KOSKASSEMBLER_ELFEXCEPTIONS_H
