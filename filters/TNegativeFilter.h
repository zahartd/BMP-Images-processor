#pragma once

#include "IChannelWiseFilter.h"

namespace image_processor {
class TNegativeFilter final : public IChannelWiseFilter {
public:
    explicit TNegativeFilter(std::vector<std::string> filter_params = {});
    ~TNegativeFilter() override = default;

protected:
    void FilterImpl(TImage::Channel &channel) const override;
};
}  // namespace image_processor
