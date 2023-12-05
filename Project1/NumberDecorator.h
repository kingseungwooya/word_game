#pragma once
#include <string>
#include "StringGenerator.h"
// ���ڷ����� Ŭ����: ���ڸ� �߰��ϴ� ���ڷ�����
class NumberDecorator : public StringGenerator {
protected:
    StringGenerator* generator;
public:
    NumberDecorator(StringGenerator* generator) : generator(generator) {}

    std::string generateString() const override {
        return generator->generateString() + "0123456789";
    }
};