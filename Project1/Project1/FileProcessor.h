#pragma once
#include <iostream>
#include <string>
#include "SCode.h"
#include <fstream>
#include <unordered_map>
#include <sstream>

class FileProcessor
{
public:
    FileProcessor(const std::string& filepath);

    ~FileProcessor();

    void encodeFile();

    void decodeFile();

private:
    void readFile();
    SCode encode(const std::string& s1);
    std::string decode(const SCode& numbers);
    void writeVectorToFile(const SCode& numbers);
    SCode readVectorFromFile();
    void writeDecodingTextToFile(const std::string& s1);
    std::string _text;
    std::string _decodingText;
    SCode _encodedText;
    std::string _filepath;
};