#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TCrop final : public IChannelWiseFilter {
public:
    explicit TCrop(std::vector<std::string> filter_params);
    TCrop(int32_t width, int32_t height);
    ~TCrop() override = default;

protected:
    void FilterImpl(TImage::Channel &channel) const override;

private:
    size_t width_;
    size_t height_;
};
}  // namespace image_processor
