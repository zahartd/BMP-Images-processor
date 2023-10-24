#include "TThresholdFilter.h"

#include "exceptions.h"

namespace image_processor {
TThresholdFilter::TThresholdFilter(float threshold) : threshold_(threshold) {
}
TThresholdFilter::TThresholdFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Threshold", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        threshold_ = std::stof(filter_params[0]);
    } catch (std::invalid_argument const &error) {
        throw UnexpectedParamsTypeError("Threshold", {{"threshold", "floating-point number"}});
    } catch (std::out_of_range const &error) {
        throw UnexpectedParamsValueRangeError("Threshold", {{"threshold", {"0", "1"}}});
    }

    // Clamp parameters value
    if (threshold_ < 0.0 || threshold_ > 1.0) {
        throw UnexpectedParamsValueRangeError("Threshold", {{"threshold", {"0", "1"}}});
    }
}

void TThresholdFilter::FilterImpl(TImage::Channel &channel) const {
    const int32_t image_height = static_cast<int32_t>(channel.size());
    const int32_t image_width = static_cast<int32_t>(channel[0].size());
    for (int32_t i = 0; i < image_height; ++i) {
        for (int32_t j = 0; j < image_width; ++j) {
            if (channel[i][j] > threshold_) {
                channel[i][j] = 1;
            } else {
                channel[i][j] = 0;
            }
        }
    }
}

}  // namespace image_processor