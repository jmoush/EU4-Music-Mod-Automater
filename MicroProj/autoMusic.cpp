#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <shlobj.h>
#include "autoMusic.h"

namespace fs = std::filesystem;
std::string autoMusic::FindDir(char oldVal, char newVal) {
	int i;
	//Find user desktop
	char* buff = new char[512];
	SHGetSpecialFolderPathA(HWND_DESKTOP, buff, CSIDL_DESKTOPDIRECTORY, FALSE);
	std::string desktop = buff;
	delete[] buff;
	//Replaces backslashs with forward slashes and disk drive to work with ofstream
	for (i = 0; i < desktop.size(); i++) {
		if (desktop[i] == oldVal) {
			desktop[i] = newVal;
		}
		else {}
	}
	desktop.erase(desktop.begin(), desktop.begin() + 2); //Erase the disk drive from the file name easily
	return desktop;
}

void autoMusic::ExtractMusic(std::vector <std::string>& songs, std::string& filepath) {
	// This structure would distinguish a file from a directory
	struct stat sb;

	// Looping until all the items of the directory are exhausted
	for (const auto& entry : std::filesystem::directory_iterator(filepath)) {

		// Converting the path to const char * in the subsequent lines
		fs::path outfilename = entry.path();
		std::string outfilename_str = outfilename.string();
		const char* path = outfilename_str.c_str();
		//Debugging weird file names that break code
		//std::cout << outfilename_str <<std::endl;
		//Erase path to only have file names

		// Testing whether the path points to a
		// non-directory or not If it does, displays path
		if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
			//std::cout << path << std::endl;
			songs.push_back(path);
		}
	}
}

//Clean up strings to only contain file names.
 void autoMusic::Cleanstr(std::vector <std::string>& songs) {
	int i = 0;
	std::size_t found;
	for (i = 0; i < songs.size(); i++) {
		found = songs[i].find('\\');
		if (found != songs[i].find('\\')) {}
		else {
			songs[i].erase(songs[i].begin(), songs[i].begin() + (found + 1));
			songs[i].erase(songs[i].end() - 4, songs[i].end()); //remove .ogg or any three letter music file extension
		}
	}
}
 void autoMusic::Print(std::string& Desktop, std::vector<std::string>& songs){
	 std::ofstream AssetGen(Desktop + "/test.asset");
	 for (auto& i : songs) {
		 AssetGen << "\nmusic = {\n\tname = \"" << i << "\"\n\tfile = \"" << i << ".ogg\"\n}\n";
	 }
	 AssetGen.close();
	 std::ofstream TxtGen(Desktop + "/test.txt");
	 for (auto& i : songs) {
		 TxtGen << "\nsong = {\n\t name = \"" << i << "\"\n\t chance = {\n\t\t modifier = { factor = 1 }\n\t} \n}\n";
	 }
	 TxtGen.close();
	 std::cout << "Asset and txt file have been created.\nThank you for using this tool\n";
 }
