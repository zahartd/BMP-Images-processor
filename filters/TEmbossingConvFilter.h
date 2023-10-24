#pragma once

#include "TConvolutionFilter.h"

namespace image_processor {
class TEmbossingConvFilter final : public TConvolutionFilter {
public:
    explicit TEmbossingConvFilter(std::vector<std::string> filter_params = {});
    ~TEmbossingConvFilter() override = default;
};
}  // namespace image_processor