#include "TMaximumFilter.h"

#include "exceptions.h"

namespace image_processor {
TMaximumFilter::TMaximumFilter(int32_t radius) : radius_(radius) {
}
TMaximumFilter::TMaximumFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Maximum", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        radius_ = std::stoi(filter_params[0]);
    } catch (std::invalid_argument& error) {
        throw UnexpectedParamsTypeError("Maximum", {{"radius", "natural number"}});
    } catch (std::out_of_range const& error) {
        throw UnexpectedParamsValueRangeError("Maximum", {{"radius", {"1", "max(image_height, image_width)"}}});
    }

    // Clamp parameters value
    if (radius_ < 1) {
        throw UnexpectedParamsValueRangeError("Maximum", {{"radius", {"1", "max(image_height, image_width)"}}});
    }
}
void TMaximumFilter::FilterImpl(TImage::Channel& channel) const {
    const int32_t channel_height = static_cast<int32_t>(channel.size());
    const int32_t channel_width = static_cast<int32_t>(channel[0].size());

    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            double max_value = 0.0;
            for (int32_t k = -radius_; k <= radius_; ++k) {
                for (int32_t l = -radius_; l <= radius_; ++l) {
                    int32_t target_x = x + l;
                    int32_t target_y = y + k;
                    if (target_x < 0 || target_x >= channel_width || target_y < 0 || target_y >= channel_height) {
                        continue;
                    }
                    max_value = std::max(max_value, channel[target_y][target_x]);
                }
            }
            channel[y][x] = max_value;
        }
    }
}
}  // namespace image_processor
