#include "autoMusic.cpp"
//Global Var
//const int ArrFolderSize = 100;

int main() {
	autoMusic Music;
	std::vector <std::string> songs; //vector of song names
	int i = 0;
	char old_val = '\\';
	char new_val = '/';
	//std ::string DsktFolders[ArrFolderSize]; //String of folder names for error checking
	std::string path; 
	std::string DsktFolder;
	std::string DesktopFolder = "/Music Files";
	std::string MusicFolder = "OGG"; // User's Music Folder on desktop 
	std::string desktop = Music.FindDir(old_val,new_val);
	//Get the directory name of User's music folder
	//std::cout << "Please enter the music folder name that is on your desktop. If folder doesn't exist, the program will crash\n";
	//getline(std::cin,MusicFolder);
	std::cout << "The desktop directory \"OGG\" will be used if available\n";
	MusicFolder.insert(0, "/");
	DsktFolder = desktop + DesktopFolder;
	path = desktop + MusicFolder; //Path to Music Files
	Music.ExtractMusic(songs, path);
	Music.Cleanstr(songs);
	// Creates directory Music Files on user desktop
	if (CreateDirectoryA(DsktFolder.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError()) {
	}
	else {
		std::cout << "Failed to create directory\n"; 	// Failed to create directory.
	}
	Music.Print(DsktFolder,songs);	// Create the asset and txt file for mods
	/*
	for (auto& i : songs) {
		std::cout << i << std::endl;
	}
	*/
	system("pause");
	return 0;
}
