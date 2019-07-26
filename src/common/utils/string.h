//
// Created by vice on 24/07/2019.
//

#ifndef AZOR_SRC_COMMON_UTILS_STRING_H_
#define AZOR_SRC_COMMON_UTILS_STRING_H_

#include <vector>
#include <string>

namespace string{
    // string split utils function base on Knuth–Morris–Pratt string searching algorithm
    std::vector<std::string> split(const std::string& text, const std::string& separator);
}

#endif //AZOR_SRC_COMMON_UTILS_STRING_H_
