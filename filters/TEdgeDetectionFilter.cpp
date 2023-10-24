#include "TEdgeDetectionFilter.h"

#include "TGrayScaleFilter.h"
#include "TEdgeDetectionConvFilter.h"
#include "TThresholdFilter.h"
#include "exceptions.h"

namespace image_processor {
TEdgeDetectionFilter::TEdgeDetectionFilter(std::vector<std::string> filter_params) : TCompositeFilter({}) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Edge Detection", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        threshold_ = std::stof(filter_params[0]);
    } catch (std::invalid_argument const &error) {
        throw UnexpectedParamsTypeError("Edge Detection", {{"threshold", "floating-point number"}});
    } catch (std::out_of_range const &error) {
        throw UnexpectedParamsValueRangeError("Edge Detection", {{"threshold", {"0", "1"}}});
    }

    if (threshold_ < 0.0 || threshold_ > 1.0) {
        throw UnexpectedParamsValueRangeError("Edge Detection", {{"threshold", {"0", "1"}}});
    }
    AddFilter(std::make_unique<TGrayScaleFilter>());
    AddFilter(std::make_unique<TEdgeDetectionConvFilter>());
    AddFilter(std::make_unique<TThresholdFilter>(threshold_));
}

TEdgeDetectionFilter::TEdgeDetectionFilter(float threshold) : TCompositeFilter({}) {
    threshold_ = threshold;
    AddFilter(std::make_unique<TGrayScaleFilter>());
    AddFilter(std::make_unique<TEdgeDetectionConvFilter>());
    AddFilter(std::make_unique<TThresholdFilter>(threshold_));
}
}  // namespace image_processor