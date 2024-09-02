//
// Created by csger on 2024. 09. 02..
//

#include <iostream>
#include <fstream>
#include "Encrypter.h"

namespace Encrypt {
    /**
     * @brief Encrypter constructor
     * @param inputPath The path to the directory to encrypt
     * @param fileExtensions The file extensions to encrypt
     */
    Encrypter::Encrypter(const std::filesystem::path &inputPath, const std::set<std::string> &fileExtensions) {
        assert(std::filesystem::exists(inputPath) && std::filesystem::is_directory(inputPath));

        for (const auto &entry: std::filesystem::recursive_directory_iterator(inputPath)) {
            if (entry.is_regular_file() &&
                (fileExtensions.empty() || fileExtensions.contains(entry.path().extension().generic_string()))) {
                this->files.push_back(entry.path());
            }
        }
    }

    std::vector<std::filesystem::path> Encrypter::getFiles() const {
        return this->files;
    }

    /**
     * @brief Encrypts a file
     * @param file The file to encrypt
     */
    void Encrypter::encryptFile(const std::filesystem::path &file) {
        std::fstream fileStream(file, std::ios::in | std::ios::out | std::ios::binary);

        char byte;
        uint8_t idx = 0;
        while (fileStream.get(byte)) {
            byte ^= key;
            auto prev = fileStream.tellg();
            fileStream.seekp(idx, std::ios::beg);
            fileStream.put(byte);
            fileStream.seekg(prev);
            idx++;
        }
        fileStream.close();
    }

    /**
     * @brief Encrypts the files
     * @param thread The number of threads to use
     */
    void Encrypter::encryptFiles(uint16_t thread) const {
        auto func = [this](size_t begin, size_t end) {
            for (auto i = begin; i < std::min(end, this->files.size()); ++i) {
                encryptFile(this->files[i]);
            }
        };

        std::vector<std::jthread> threads;
        threads.reserve(thread);
        size_t step = this->files.size() / thread;
        if (step == 0) {
            step = 1;
        }
        size_t begin = 0;
        size_t end = step;
        for (uint16_t i = 0; i < thread; ++i) {
            if (i == thread - 1) {
                end = this->files.size();
            }

            if (end > this->files.size()) {
                break;
            }

            threads.emplace_back(func, begin, end);
            begin = end;
            end += step;
        }
    }
} // Encrypt