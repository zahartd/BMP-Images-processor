#include "TConvolutionFilter.h"

namespace image_processor {
TConvolutionFilter::TConvolutionFilter(const std::vector<std::vector<double>>& matrix) : kernel_(matrix) {
}
void TConvolutionFilter::FilterImpl(TImage::Channel& channel) const {
    int32_t channel_height = static_cast<int32_t>(channel.size());
    int32_t channel_width = static_cast<int32_t>(channel[0].size());

    TImage::Channel new_channel(channel_height, std::vector<double>(channel_width));

    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            double sum = 0.0;
            for (int32_t i = -kernel_radius_y_; i <= kernel_radius_y_; ++i) {
                for (int32_t j = -kernel_radius_x_; j <= kernel_radius_x_; ++j) {
                    int32_t target_x = std::max(0, std::min(channel_width - 1, x + j));
                    int32_t target_y = std::max(0, std::min(channel_height - 1, y + i));
                    sum += channel[target_y][target_x] * kernel_[i + kernel_radius_y_][j + kernel_radius_x_];
                }
            }
            new_channel[y][x] = std::min(1.0, std::max(0.0, sum));
        }
    }

    channel = std::move(new_channel);
}
}  // namespace image_processor
