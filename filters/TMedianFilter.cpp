#include "TMedianFilter.h"

#include "exceptions.h"

namespace image_processor {
TMedianFilter::TMedianFilter(int32_t radius) : radius_(radius) {
}

TMedianFilter::TMedianFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Median", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        radius_ = std::stoi(filter_params[0]);
    } catch (std::invalid_argument& error) {
        throw UnexpectedParamsTypeError("Median", {{"radius", "natural number"}});
    } catch (std::out_of_range const& error) {
        throw UnexpectedParamsValueRangeError("Median", {{"radius", {"1", "max(image_height, image_width)"}}});
    }

    // Clamp parameters value
    if (radius_ < 1) {
        throw UnexpectedParamsValueRangeError("Median", {{"radius", {"1", "max(image_height, image_width)"}}});
    }
}

void TMedianFilter::FilterImpl(TImage::Channel& channel) const {
    const int32_t channel_height = static_cast<int32_t>(channel.size());
    const int32_t channel_width = static_cast<int32_t>(channel[0].size());

    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            std::vector<double> target_pxs;
            for (int32_t k = -radius_; k <= radius_; ++k) {
                for (int32_t l = -radius_; l <= radius_; ++l) {
                    int32_t target_x = x + l;
                    int32_t target_y = y + k;
                    if (target_x < 0 || target_x >= channel_width || target_y < 0 || target_y >= channel_height) {
                        continue;
                    }
                    target_pxs.push_back(channel[target_y][target_x]);
                }
            }

            const int32_t mid = static_cast<int32_t>(target_pxs.size() / 2);
            std::nth_element(target_pxs.begin(), target_pxs.begin() + mid, target_pxs.end());
            const double median = target_pxs[mid];

            channel[y][x] = median;
        }
    }
}
}  // namespace image_processor
