#pragma once
#include <string>
#include "StringGenerator.h"
// 데코레이터 클래스: 숫자를 추가하는 데코레이터
class NumberDecorator : public StringGenerator {
protected:
    StringGenerator* generator;
public:
    NumberDecorator(StringGenerator* generator) : generator(generator) {}

    std::string generateString() const override {
        return generator->generateString() + "0123456789";
    }
};