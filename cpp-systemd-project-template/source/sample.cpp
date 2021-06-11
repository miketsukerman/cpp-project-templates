#include "sample.h"

#include <numeric>

#include <spdlog/spdlog.h>

SampleObject::SampleObject() {
    spdlog::info(__PRETTY_FUNCTION__);
}

SampleObject::~SampleObject() {
    spdlog::info(__PRETTY_FUNCTION__);
}

auto SampleObject::sum(const std::vector<int> & numbers) -> int 
{
    return std::accumulate(std::cbegin(numbers), std::cend(numbers), 0);
}