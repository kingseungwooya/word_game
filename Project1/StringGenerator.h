#pragma once
#include <string>

// ���ڿ� ������ ���� �⺻ Ŭ����
class StringGenerator {
public:
    virtual std::string generateString() const = 0;
    virtual ~StringGenerator() = default;
};