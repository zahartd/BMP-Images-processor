#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TMaximumFilter final : public IChannelWiseFilter {
public:
    ~TMaximumFilter() override = default;
    explicit TMaximumFilter(std::vector<std::string> filter_params);
    explicit TMaximumFilter(int32_t radius);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    int32_t radius_;
};
}  // namespace image_processor
