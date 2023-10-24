#include "TGlassFilter.h"

#include "exceptions.h"

namespace image_processor {
TGlassFilter::TGlassFilter(int32_t radius) : radius_(radius) {
}

TGlassFilter::TGlassFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Glass", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        radius_ = std::stoi(filter_params[0]);
    } catch (std::invalid_argument &error) {
        throw UnexpectedParamsTypeError("Glass", {{"radius", "natural number"}});
    } catch (std::out_of_range const &error) {
        throw UnexpectedParamsValueRangeError("Glass", {{"radius", {"1", "max(image_height, image_width)"}}});
    }

    // Clamp parameters value
    if (radius_ < 1) {
        throw UnexpectedParamsValueRangeError("Glass", {{"radius", {"1", "max(image_height, image_width)"}}});
    }
}

void TGlassFilter::FilterImpl(TImage::Channel &channel) const {
    int32_t channel_height = static_cast<int32_t>(channel.size());
    int32_t channel_width = static_cast<int32_t>(channel[0].size());
    TImage::Channel original_channel = channel;
    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            int32_t offset_x = std::rand() % (2 * radius_ + 1) - radius_;
            int32_t offset_y = std::rand() % (2 * radius_ + 1) - radius_;
            int32_t new_x = offset_x;
            int32_t new_y = offset_y;
            if (new_y < 0 || new_y >= channel_height || new_x < 0 || new_x >= channel_width) {
                continue;
            }
            channel[y][x] = original_channel[new_y][new_x];
        }
    }
}
}  // namespace image_processor
