#include "TEdgeDetectionConvFilter.h"

#include <vector>

#include "utils.h"
#include "exceptions.h"

namespace image_processor {
TEdgeDetectionConvFilter::TEdgeDetectionConvFilter(std::vector<std::string> filter_params)
    : TConvolutionFilter(EDGE_DETECTION_FILTER_KERNEL) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("EdgeDetectionConv", 0, filter_params.size());
    }
}
}  // namespace image_processor
