#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class FileSystemHandler {
public:
	vector<string> listDir(string directoryPath) {
		vector<string> directoryNames;
		struct dirent* entry;

		const char* dirName = directoryPath.c_str();
		DIR* dir = opendir(dirName);

		if (dir == nullptr) {
			return directoryNames;
		}

		while ((entry = readdir(dir)) != nullptr) {
			directoryNames.push_back(entry->d_name);
		}

		return directoryNames;
	}

	void saveToFile(string path, string content) {
		std::ofstream out(path);
		out << content;
		out.close();
	}

	string readFile(string path) {
		stringstream ss;
		string myText;
		ifstream MyReadFile(path);
		while (getline(MyReadFile, myText)) {
			ss << myText;
		}
		MyReadFile.close();
		return ss.str();
	}
};