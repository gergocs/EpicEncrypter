//
// Created by csger on 2024. 09. 02..
//

#ifndef EPICENCRYPTER_ENCRYPTER_H
#define EPICENCRYPTER_ENCRYPTER_H

#include <set>
#include <filesystem>
#include <cassert>

namespace Encrypt {

    class Encrypter {
    public:
        Encrypter(const std::filesystem::path &inputPath, const std::set<std::string> &fileExtensions);

        [[nodiscard]] std::vector<std::filesystem::path> getFiles() const;

        static void encryptFile(const std::filesystem::path &file) ;

        void encryptFiles(uint16_t thread) const;
    private:
        std::vector<std::filesystem::path> files;
        static constexpr const int8_t key = 0b101010;
    };

} // Encrypt

#endif //EPICENCRYPTER_ENCRYPTER_H
