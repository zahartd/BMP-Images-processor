#include "TGaussianBlurFilter.h"

#include <cmath>

#include "utils.h"
#include "exceptions.h"

namespace image_processor {
TGaussianBlurFilter::TGaussianBlurFilter(double sigma) : sigma_(sigma) {
}

TGaussianBlurFilter::TGaussianBlurFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.empty()) {
        sigma_ = DEFAULT_BLUR_SIGMA;
    } else if (filter_params.size() != 1) {
        throw UnexpectedParamsCountError("Blur", 1, filter_params.size());
    } else {
        // Convert and check that it correct
        try {
            sigma_ = std::stod(filter_params[0]);
        } catch (std::invalid_argument const &error) {
            throw UnexpectedParamsTypeError("Blur", {{"sigma", "floating-point number"}});
        } catch (std::out_of_range const &error) {
            throw UnexpectedParamsValueRangeError("Blur", {{"sigma", {"0", "inf"}}});
        }

        // Clamp parameters value
        if (sigma_ <= 0) {
            throw UnexpectedParamsValueRangeError("Blur", {{"sigma", {"0", "inf"}}});
        }
    }
}
void TGaussianBlurFilter::FilterImpl(TImage::Channel &channel) const {
    int32_t channel_height = static_cast<int32_t>(channel.size());
    int32_t channel_width = static_cast<int32_t>(channel[0].size());
    int32_t kernel_size = static_cast<int32_t>(std::ceil(sigma_ * 3)) * 2 + 1;
    int32_t kernel_radius = kernel_size / 2;

    // precompute coefficients
    std::vector<double> kernel_coefficients(kernel_size);
    double coefficients_sum = 0.0;
    for (int32_t i = 0; i < kernel_size; ++i) {
        double x = i - kernel_radius;
        double coefficient = std::exp(-std::pow(x, 2) / (2 * sigma_ * sigma_));
        kernel_coefficients[i] = coefficient;
        coefficients_sum += coefficient;
    }

    // normalize coefficients
    for (int32_t i = 0; i < kernel_size; ++i) {
        kernel_coefficients[i] /= coefficients_sum;
    }

    // horizontal pass
    TImage::Channel new_channel(channel_height, std::vector<double>(channel_width));
    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            double sum = 0.0;
            for (int32_t k = -kernel_radius; k < kernel_radius; ++k) {
                int32_t target_x = std::max(0, std::min(channel_width - 1, x + k));
                sum += channel[y][target_x] * kernel_coefficients[k + kernel_radius];
            }
            new_channel[y][x] = sum;
        }
    }

    // vertical pass
    for (int32_t y = 0; y < channel_height; ++y) {
        for (int32_t x = 0; x < channel_width; ++x) {
            double sum = 0.0;
            for (int32_t k = -kernel_radius; k < kernel_radius; ++k) {
                int32_t target_y = std::max(0, std::min(channel_height - 1, y + k));
                sum += new_channel[target_y][x] * kernel_coefficients[k + kernel_radius];
            }
            channel[y][x] = sum;
        }
    }
}
}  // namespace image_processor
