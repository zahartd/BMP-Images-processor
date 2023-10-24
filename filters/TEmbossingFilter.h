#pragma once

#include "TCompositeFilter.h"

namespace image_processor {
class TEmbossingFilter : public TCompositeFilter {
public:
    explicit TEmbossingFilter(std::vector<std::string> filter_params);
};
}  // namespace image_processor