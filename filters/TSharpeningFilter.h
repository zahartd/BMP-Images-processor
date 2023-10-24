#pragma once

#include "TConvolutionFilter.h"

namespace image_processor {
class TSharpeningFilter final : public TConvolutionFilter {
public:
    explicit TSharpeningFilter(std::vector<std::string> filter_params = {});
    ~TSharpeningFilter() override = default;
};
}  // namespace image_processor
