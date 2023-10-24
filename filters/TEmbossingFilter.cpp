#include "TEmbossingFilter.h"

#include "TEdgeDetectionFilter.h"
#include "TEmbossingConvFilter.h"
#include "utils.h"
#include "exceptions.h"

namespace image_processor {
TEmbossingFilter::TEmbossingFilter(std::vector<std::string> filter_params) : TCompositeFilter({}) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("Embossing", 0, filter_params.size());
    }
    AddFilter(std::make_unique<TEdgeDetectionFilter>(EMBOSSING_EDGE_DETECTION_THRESHOLD));
    AddFilter(std::make_unique<TEmbossingConvFilter>());
}
}  // namespace image_processor
