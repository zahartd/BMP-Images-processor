#include "TCrop.h"

#include "exceptions.h"

namespace image_processor {
TCrop::TCrop(int32_t width, int32_t height) : width_(width), height_(height) {
}

TCrop::TCrop(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (filter_params.size() < 2) {
        throw UnexpectedParamsCountError("Crop", 2, filter_params.size());
    }

    // Convert and check that it correct
    try {
        width_ = std::stoi(filter_params[0]);
        height_ = std::stoi(filter_params[1]);
    } catch (std::invalid_argument& error) {
        throw UnexpectedParamsTypeError("Crop", {{"width", "natural number"}, {"height", "natural number"}});
    } catch (std::out_of_range const& error) {
        throw UnexpectedParamsValueRangeError("Crop",
                                              {{"width", {"1", "image_width"}}, {"height", {"1", "image_height"}}});
    }

    // Clamp parameters value
    if (width_ <= 0 || height_ <= 0) {
        throw UnexpectedParamsValueRangeError("Crop",
                                              {{"width", {"1", "image_width"}}, {"height", {"1", "image_height"}}});
    }
}

void TCrop::FilterImpl(TImage::Channel& channel) const {
    channel.resize(std::min(height_, channel.size()));
    for (auto& image_channel_row : channel) {
        image_channel_row.resize(std::min(width_, image_channel_row.size()));
    }
}
}  // namespace image_processor
