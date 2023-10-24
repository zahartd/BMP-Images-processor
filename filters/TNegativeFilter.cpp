#include "TNegativeFilter.h"

#include "exceptions.h"

namespace image_processor {

TNegativeFilter::TNegativeFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("Negative", 0, filter_params.size());
    }
}

void TNegativeFilter::FilterImpl(TImage::Channel& channel) const {
    for (auto& row : channel) {
        for (auto& px : row) {
            px = 1 - px;
        }
    }
}
}  // namespace image_processor
