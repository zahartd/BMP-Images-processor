#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TMedianFilter final : public IChannelWiseFilter {
public:
    ~TMedianFilter() override = default;
    explicit TMedianFilter(std::vector<std::string> filter_params);
    explicit TMedianFilter(int32_t radius);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    int32_t radius_;
};
}  // namespace image_processor
