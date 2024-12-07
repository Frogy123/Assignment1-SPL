#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Auxiliary{
    public:
        static std::vector<std::string> parseArguments(const std::string& line);
        static int minElement(std::vector<int>& nums);
        static int maxElement(std::vector<int>& nums);
};
