cmake_minimum_required(VERSION 3.29)
project(EpicEncrypter)

set(CMAKE_CXX_STANDARD 20)

add_executable(EpicEncrypter main.cpp
        bobTheArgParser/BobTheArgParser.cpp
        bobTheArgParser/BobTheArgParser.h
        encrypter/Encrypter.cpp
        encrypter/Encrypter.h)
