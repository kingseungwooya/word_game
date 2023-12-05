#pragma once
#include <string>
#include "StringGenerator.h"
// 영어 알파벳 생성기
class AlphabetGenerator : public StringGenerator {
public:
    std::string generateString() const override {
        return "abcdefghijklmnopqrstuvwxyz";
    }
};