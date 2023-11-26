#include <iostream>
#include <string>
#include "ghc/filesystem.hpp"

#define GET_EXTENSION(fileStr) fileStr.substr(fileStr.find_last_of(".") + 1)

namespace fs = ghc::filesystem;
using std::string;

using int64 = long long;

struct {
    size_t dirs;
    size_t files;
}index;

std::vector<string> suffixes = {
    " B",
    "KB",
    "MB",
    "GB",
    "TB",
    "EB",
    "ZB",
    "YB"
};

std::vector<fs::directory_entry> directories;
std::vector<fs::directory_entry> files;

void printLine(fs::directory_entry file, string message, string ext, bool b_ext) {
    string fileStr = file.path().filename().generic_string();
    if (
        ext == fileStr.substr(0, fileStr.find_last_of("."))
        ||
        ext == "*"
        ||
        (b_ext && ext == GET_EXTENSION(fileStr))
       ) {
        short sbyteUnits = 0;
        int64 fileSize = file.file_size();
        if (message == "Directory") {
            fileSize = file.file_size();
        }
        while (fileSize > 1023) {
            fileSize /= 1024;
            sbyteUnits++;
        }
        string spaces = "     "; // Five spaces
        int64 ifileSize = fileSize;
        while (ifileSize != 0) {
            ifileSize /= 10;
            spaces.pop_back();
        }
        if (fileSize > 0 || sbyteUnits > 1) spaces += "  "; // Checks if it's a file and adds 2 more spaces if true

        std::cout << message << spaces << fileSize
            << " " << suffixes[sbyteUnits] << "\t" // Prints the suffix
            << file.path().filename().string() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    index = { 0, 0 };
    string ext;
    bool b_ext = false;
    if (argc < 2) ext = "*";
    else {
        ext = argv[1];
        if (ext.find(".") != string::npos) {
            ext = ext.substr(ext.find_last_of(".") + 1);
            b_ext = true;
        }
    }
    fs::path path = fs::current_path();
    for (const fs::directory_entry& file : fs::directory_iterator(path)) {
        if (fs::is_directory(file)){
            directories.insert(directories.end(), file);
            index.dirs++;
        }
        else {
            files.insert(files.end(), file);
            index.files++;
        }
    }
    for (int i = 0; i < index.dirs; i++) {
        printLine(directories[i], "Directory", ext, b_ext);
    }
    for (int i = 0; i < index.files; i++) {
        printLine(files[i], "File\t", ext, b_ext);
    }
    return 0;
}
