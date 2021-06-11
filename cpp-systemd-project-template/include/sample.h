#pragma once 

#include <vector>

class SampleObject {
public:
    SampleObject();
    ~SampleObject();

    auto sum(const std::vector<int> & numbers) -> int;
};