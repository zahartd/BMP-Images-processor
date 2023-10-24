#pragma once

#include "TCompositeFilter.h"

namespace image_processor {
class TEdgeDetectionFilter : public TCompositeFilter {
public:
    explicit TEdgeDetectionFilter(float threshold);
    explicit TEdgeDetectionFilter(std::vector<std::string> filter_params);
    ~TEdgeDetectionFilter() override = default;

private:
    float threshold_;
};
}  // namespace image_processor
