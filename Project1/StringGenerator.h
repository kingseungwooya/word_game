#pragma once
#include <string>

// 문자열 생성을 위한 기본 클래스
class StringGenerator {
public:
    virtual std::string generateString() const = 0;
    virtual ~StringGenerator() = default;
};