#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TOilPaintFilter final : public IChannelWiseFilter {
public:
    ~TOilPaintFilter() override = default;
    explicit TOilPaintFilter(std::vector<std::string> filter_params);
    explicit TOilPaintFilter(int32_t radius);

protected:
    void FilterImpl(TImage::Channel &channel) const final;

private:
    int32_t radius_;
};
}  // namespace image_processor