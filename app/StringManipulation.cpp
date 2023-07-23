//
// Created by sdlig on 7/21/2023.
//

#include "StringManipulation.hpp"
#include <sstream>

std::vector<std::string> StringManipulation::splice(std::string str, const char separator) {
    std::string strData = str;
    std::vector<std::string>  outputArray;
    std::stringstream streamData(strData);
    std::string val;
    while (std::getline(streamData, val, separator)) {
        outputArray.push_back(val);
    }
    return outputArray;
}
