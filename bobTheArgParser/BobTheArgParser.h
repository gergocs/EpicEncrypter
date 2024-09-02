//
// Created by csger on 2024. 09. 02..
//

#ifndef EPICENCRYPTER_BOBTHEARGPARSER_H
#define EPICENCRYPTER_BOBTHEARGPARSER_H

#include <filesystem>
#include <cstdint>
#include <set>

namespace Encrypt {

    class BobTheArgParser {
    public:
        BobTheArgParser(int argc, char * argv[]);
        [[nodiscard]] const std::filesystem::path &getInputPath() const;
        [[nodiscard]] const std::set<std::string> &getFileExtensions() const;
        [[nodiscard]] uint16_t getThreads() const;
    private:
        std::filesystem::path inputPath;
        std::set<std::string> fileExtensions;
        uint16_t threads; //Should be enough for the next 10 years
    };

} // Encrypter

#endif //EPICENCRYPTER_BOBTHEARGPARSER_H
