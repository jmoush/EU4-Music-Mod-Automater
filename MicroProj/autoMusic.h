#pragma once
#include <string>
#include <vector>

#ifndef autoMusic_H
#define autoMusic_H
        class autoMusic{
        public:
             std::string FindDir(char oldVal, char newVal);
             void ExtractMusic(std::vector <std::string>& songs, std::string& filepath);
             void Cleanstr(std::vector <std::string>& songs);
             void Print(std::string& Desktop, std::vector <std::string>& songs);
                ;
        private:
        };
#endif
