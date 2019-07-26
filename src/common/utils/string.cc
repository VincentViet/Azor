//
// Created by vice on 24/07/2019.
//

#include "string.h"

static std::vector<int> KMP_precomputed(const std::string& pattern){
    std::vector<int> pi;
    pi.push_back(-1);

    int k = -1;
    for (int q = 1; q < pattern.length(); ++q)
    {
        while (k > -1 && pattern[k + 1] != pattern[q])
            k = pi[k];
        if (pattern[k + 1] == pattern[q])
            k += 1;
        pi[q] = k;
    }

    return pi;
}

static std::vector<int> KMP_matcher(const std::string& text, const std::string& pattern){
    std::vector<int> result;
    std::vector<int> pi = KMP_precomputed(pattern);
    int q = -1;

    for (int i = 0; i < text.length(); ++i)
    {
        while (q > -1 && pattern[q + 1] != text[i])
            q = pi[q];
        if (pattern[q + 1] == text[i])
            q = q + 1;

        if (q == pattern.length() - 1)
        {
            result.push_back(i - pattern.length() + 1);
            q = pi[q];
        }
    }

    return result;
}

std::vector<std::string> string::split(const std::string &text, const std::string &separator)
{
    std::vector<int> shifts = KMP_matcher(text, separator);
    std::vector<std::string> result;
    int i = 0;
    for (auto j: shifts)
    {
        result.emplace_back(text.substr(i, j - i));
        i = j + separator.length();
    }
    result.emplace_back(text.substr(i));
    return result;
}