#include "TEmbossingConvFilter.h"

#include <vector>

#include "utils.h"
#include "exceptions.h"

namespace image_processor {
TEmbossingConvFilter::TEmbossingConvFilter(std::vector<std::string> filter_params)
    : TConvolutionFilter(EMBOSSING_FILTER_KERNEL) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("EmbossingConv", 0, filter_params.size());
    }
}
}  // namespace image_processor
