#include "TGrayScaleFilter.h"

#include "utils.h"
#include "exceptions.h"
#include "../image/bmpexceptions.h"

namespace image_processor {

TGrayScaleFilter::TGrayScaleFilter(std::vector<std::string> filter_params) {
    // Clamp parameters count
    if (!filter_params.empty()) {
        throw UnexpectedParamsCountError("Grayscale", 0, filter_params.size());
    }
}

void TGrayScaleFilter::ApplyFilter(TImage& image) const {
    TImage::Channels& image_channels = image.GetChannels();

    if (image_channels.size() == 1) {
        return;
    } else if (image_channels.size() == 3) {
        // iterate by px and luminance it
        for (size_t i = 0; i < image_channels[0].size(); ++i) {
            for (size_t j = 0; j < image_channels[0][0].size(); ++j) {
                image_channels[0][i][j] =
                    LuminancePx(image_channels[0][i][j], image_channels[1][i][j], image_channels[2][i][j]);
            }
        }
        // Delete channels
        image_channels.pop_back();
        image_channels.pop_back();
    } else {
        throw BMPInvalidColorChannelCountError(image_channels.size());
    }
}
}  // namespace image_processor
