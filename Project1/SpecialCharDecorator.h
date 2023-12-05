#pragma once
#include <string>
#include "StringGenerator.h"
// ���ڷ����� Ŭ����: Ư�����ڸ� �߰��ϴ� ���ڷ�����
class SpecialCharDecorator : public StringGenerator {
protected:
    StringGenerator* generator;
public:
    SpecialCharDecorator(StringGenerator* generator) : generator(generator) {}

    std::string generateString() const override {
        return generator->generateString() + "!@#$%^&*()-_=+[]{};:,.<>?";
    }
};