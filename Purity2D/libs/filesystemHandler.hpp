#pragma once

#include <string>
#include <vector>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

class FileSystemHandler {
public:
	vector<string> listDir(string directoryPath) {
		vector<string> directoryNames;
		struct dirent* entry;

		const char* dirName = directoryPath.c_str();
		DIR* dir = opendir(dirName);

		if (dir = nullptr) {
			return;
		}

		while ((entry = readdir(dir)) != nullptr) {
			directoryNames.push_back(entry->d_name);
		}

		return directoryNames;
	}
};