#pragma once
#include <string>
#include "StringGenerator.h"
// 데코레이터 클래스: 특수문자를 추가하는 데코레이터
class SpecialCharDecorator : public StringGenerator {
protected:
    StringGenerator* generator;
public:
    SpecialCharDecorator(StringGenerator* generator) : generator(generator) {}

    std::string generateString() const override {
        return generator->generateString() + "!@#$%^&*()-_=+[]{};:,.<>?";
    }
};