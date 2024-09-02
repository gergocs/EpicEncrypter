//
// Created by csger on 2024. 09. 02..
//

#include "BobTheArgParser.h"

namespace Encrypt {
    /**
     * @brief Constructor for the BobTheArgParser class
     * @param argc The argument count
     * @param argv The argument vector
     */
    BobTheArgParser::BobTheArgParser(int argc, char **argv) {
        if (argc < 3) {
            throw std::invalid_argument("Not enough arguments");
        }

        this->inputPath = std::filesystem::path(argv[1]);
        if (std::filesystem::exists(this->inputPath) && !std::filesystem::is_directory(this->inputPath)) {
            throw std::invalid_argument("Input path is not a directory");
        }
        try {
            auto tmp = std::stoi(argv[2]);

            if (tmp == -1) {
                this->threads = std::thread::hardware_concurrency();
            } else if (tmp < 1 || tmp > std::thread::hardware_concurrency()) {
                throw std::out_of_range("Thread count is less than 1 or more than the available threads");
            } else {
                this->threads = tmp;
            }
        } catch (std::invalid_argument &e) {
            throw std::invalid_argument("Thread count is not a number");
        }


        for (int i = 3; i < argc; ++i) {
            if (argv[i][0] != '.') {
                this->fileExtensions.insert("." + std::string(argv[i]));
                continue;
            }
            this->fileExtensions.insert(argv[i]);
        }
    }

    const std::filesystem::path &BobTheArgParser::getInputPath() const {
        return this->inputPath;
    }

    const std::set<std::string> &BobTheArgParser::getFileExtensions() const {
        return this->fileExtensions;
    }

    uint16_t BobTheArgParser::getThreads() const {
        return this->threads;
    }
} // Encrypter