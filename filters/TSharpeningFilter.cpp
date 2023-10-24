#include "TSharpeningFilter.h"

#include <vector>

#include "utils.h"
#include "exceptions.h"

namespace image_processor {
TSharpeningFilter::TSharpeningFilter(std::vector<std::string> filter_params)
    : TConvolutionFilter(SHARPENING_FILTER_KERNEL) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("Sharpening", 0, filter_params.size());
    }
}
}  // namespace image_processor
