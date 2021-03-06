/* maip.cpp */
#include "main_help.h"

std::vector<bool> keys;

int main(int argc, char *argv[]) {
	clock_t t0 = clock();
	std::map<std::string, int> fileNames;
	std::map<std::string, int>::iterator finder;
	keys = {false, false, false, false, false, false, false, false, false};
//			c	   d	  k		 l		r	   t	  1		 9		a
	for (int i = 1; i < argc; ++i) {
		std::string keyFile;
		std::stringstream tmp(argv[i]);
		tmp >> keyFile;
		if (keyFile[0] == '-') {//ключ(и)
			if (!KeyManager(keyFile)) {
				return -1;
			}
		}
		else {// файлы и папки
			bool got = false;
			if (keyFile.size() > 2) {
				if (keyFile[0] == '.' && keyFile[1] == '/') {
					keyFile.erase(0, 2);
				}
			}
			finder = fileNames.find(keyFile);
			if (finder != fileNames.end()) {//для избежания работы над одним и тем же файлом несколько раз
				got = true;
			}
			if (!got) {
				fileNames.insert({keyFile, i});
			}
		}
	}
	if (fileNames.empty()) {
		std::cout << "Compressed data not written to a terminal." << std::endl;
		return 0;
	}
	//проверка на файлы и папки и дальнейшая работа с ними
	for (finder = fileNames.begin(); finder != fileNames.end(); ++finder) {
		bool directory = IsDirectory(finder->first, false);
		if (!keys[4] && directory) {
			std::cout << finder->first << " is a directory -- ignored" << std::endl;
		}
		else if (directory) {
			WorkWithDirectory(finder->first);
		}
		else if (finder->first == "main") {
			continue;
		}
		else {
			if (errno == ENOTDIR) {
				WorkWithFile(finder->first);
			}
			else {
				PrintDirectoryErrors(finder->first);
			}
		}
	}
	clock_t t1 = clock();//TODO
	if (keys[8]) {
		std::cout << std::endl << ((double) t1 - t0) / CLOCKS_PER_SEC << " секунд" << std::endl;
	}
	return 0;
}
