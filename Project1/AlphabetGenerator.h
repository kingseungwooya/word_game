#pragma once
#include <string>
#include "StringGenerator.h"
// ���� ���ĺ� ������
class AlphabetGenerator : public StringGenerator {
public:
    std::string generateString() const override {
        return "abcdefghijklmnopqrstuvwxyz";
    }
};