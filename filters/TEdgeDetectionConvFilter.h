#pragma once

#include "TConvolutionFilter.h"

namespace image_processor {
class TEdgeDetectionConvFilter final : public TConvolutionFilter {
public:
    explicit TEdgeDetectionConvFilter(std::vector<std::string> filter_params = {});
    ~TEdgeDetectionConvFilter() override = default;
};
}  // namespace image_processor
