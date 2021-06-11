#include "sample.h"

#include <spdlog/spdlog.h>

SampleObject::SampleObject() {
    spdlog::info(__PRETTY_FUNCTION__);
}

SampleObject::~SampleObject() {
    spdlog::info(__PRETTY_FUNCTION__);
}

auto SampleObject::sum(const int a,const int b) -> int {
    return a+b;
}