#include <iostream>
#include <map>
#include <string>
#include "ghc/filesystem.hpp"

std::map<int, std::string> byteUnits{
    {1, "B"},
    {2, "KB"},
    {3, "MB"},
    {4, "GB"},
    {5, "TB"},
    {6, "EB"},
    {7, "ZB"},
    {8, "YB"},
};

void dimReturn(long &fileSize, short &sbyteUnits) {
    if (fileSize > 999) {
        fileSize /= 1000;
        sbyteUnits++;
        dimReturn(fileSize, sbyteUnits);
    }
    return;
}

std::string printSpaces(int spaces) {
    std::string returned= "";
    for (int i = 0; i <= spaces; i++) {
        returned += " ";
    }
    return returned;
}

void printThing(ghc::filesystem::directory_entry file, std::string message, std::string ext, bool b_ext) {
    std::string fileStr = file.path().filename().generic_string();
    if (
        ext == fileStr.substr(0, fileStr.find_last_of(".")) ||
        ext == "*" || 
        (b_ext && ext == fileStr.substr(fileStr.find_last_of(".") + 1))
        ) {
        short sbyteUnits = 1;
        long fileSize = file.file_size();
        dimReturn(fileSize, sbyteUnits);

        int spaces = 5;
        long ifileSize = fileSize;
        while (ifileSize != 0) {
            ifileSize /= 10;
            spaces--;
        }
        if (fileSize > 0 || sbyteUnits > 1) spaces++;

        std::cout << message << printSpaces(spaces) << fileSize
            << " " << byteUnits[sbyteUnits] << "\t"
            << file.path().filename().string() << std::endl;
    }
}

int main (int argc, char *argv[]) {
    std::string ext;
    bool b_ext = false;
    if (argc < 2) ext = "*";
    else {
        ext = argv[1];
        if (ext.find(".") != std::string::npos) {
            ext = ext.substr(ext.find_last_of(".") + 1);
            b_ext = true;
        }
    }
    ghc::filesystem::path path = ghc::filesystem::current_path();
    for (const auto& file : ghc::filesystem::directory_iterator(path)) {
        if (ghc::filesystem::is_directory(file)) {
            printThing(file, "Directory\t", ext, b_ext);
        }
        else {
            printThing(file, "File\t\t", ext, b_ext);
        }
    }
    return 0;
}
