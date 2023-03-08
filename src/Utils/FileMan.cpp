#include "FileMan.h"

string FileMan::fileToString(const string& filePath) { // draft
    ifstream inFile(filePath);
    string fileText;
    string temp;

    if (!inFile) {
        return "File not found";
    }
    int i = 0;
    while (getline(inFile, temp)) {
        if (i++ == 0) continue;
        fileText += temp + "\n";
    }

    inFile.close();

    return fileText;
}


