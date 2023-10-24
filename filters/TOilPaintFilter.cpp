#include "TOilPaintFilter.h"

#include "exceptions.h"
#include "../image/utils.h"

namespace image_processor {
TOilPaintFilter::TOilPaintFilter(int32_t radius) : radius_(radius) {
}

TOilPaintFilter::TOilPaintFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Oil Paint", 1, filter_params.size());
    }

    // Convert and check that it correct
    try {
        radius_ = std::stoi(filter_params[0]);
    } catch (std::invalid_argument& error) {
        throw UnexpectedParamsTypeError("Oil Paint", {{"radius", "natural number"}});
    } catch (std::out_of_range const& error) {
        throw UnexpectedParamsValueRangeError("Oil Paint", {{"radius", {"1", "max(image_height, image_width)"}}});
    }

    // Clamp parameters value
    if (radius_ < 1) {
        throw UnexpectedParamsValueRangeError("Oil Paint", {{"radius", {"1", "max(image_height, image_width)"}}});
    }
}

void TOilPaintFilter::FilterImpl(TImage::Channel& channel) const {
    int32_t channel_height = static_cast<int32_t>(channel.size());
    int32_t channel_width = static_cast<int32_t>(channel[0].size());

    int32_t max_intensity_level = MAX_COLOR_CHANNEL_VALUE;

    TImage::Channel new_channel(channel);
    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            std::vector<int32_t> intensity_count(max_intensity_level, 0);
            std::vector<double> intensity_value(max_intensity_level, 0);

            for (int32_t i = -radius_; i <= radius_; ++i) {
                for (int32_t j = -radius_; j <= radius_; ++j) {
                    int32_t cur_x = x + i;
                    int32_t cur_y = y + j;
                    if (cur_x >= 0 && cur_x < channel_width && cur_y >= 0 && cur_y < channel_height) {
                        int32_t intensity = static_cast<int32_t>(channel[cur_y][cur_x] * (max_intensity_level - 1));
                        intensity_count[intensity]++;
                        intensity_value[intensity] += channel[cur_y][cur_x];
                    }
                }
            }

            size_t most_common_intensity = std::distance(
                intensity_count.begin(), std::max_element(intensity_count.begin(), intensity_count.end()));
            new_channel[y][x] = intensity_value[most_common_intensity] / intensity_count[most_common_intensity];
        }
    }

    channel = std::move(new_channel);
}
}  // namespace image_processor
