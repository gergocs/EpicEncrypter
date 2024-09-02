#include <iostream>
#include "bobTheArgParser/BobTheArgParser.h"
#include "encrypter/Encrypter.h"

int main(int argc, char *argv[]) {
    try {
        Encrypt::BobTheArgParser parser(argc, argv);
        Encrypt::Encrypter encrypter(parser.getInputPath(), parser.getFileExtensions());
        std::cout << "Files to encrypt:" << std::endl;
        for (const auto &file: encrypter.getFiles()) {
            std::cout << file << std::endl;
        }

        encrypter.encryptFiles(parser.getThreads());
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
