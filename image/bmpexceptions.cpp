#include "bmpexceptions.h"

namespace image_processor {
NotBMPFileError::NotBMPFileError(const std::string filename, char filetype[2])
    : BMPError("Is not a BMP format image " + filename + ". It have type: " + filetype[0] + filetype[1] +
               ", but should be BM.") {
}

InvalidBMPFormatError::InvalidBMPFormatError(const std::string filename)
    : BMPError("File" + filename + "have invalid for BMP info size!") {
}

InvalidBMPBitCountError::InvalidBMPBitCountError(const std::string filename, uint16_t bit_count)
    : BMPError(filename + " have not supported bit count, it have " + std::to_string(bit_count) +
               ". Keep in mind that only 24-bit BMPs are supported!") {
}
NotSupportedBMPCompressionModeError::NotSupportedBMPCompressionModeError(const std::string filename,
                                                                         uint32_t compression)
    : BMPError("File " + filename + " have not supported compression mode, it have " + std::to_string(compression) +
               ". Keep in mind that isn't supported BMP with compression!") {
}
NotSupportedBMPColorTableError::NotSupportedBMPColorTableError(const std::string filename)
    : BMPError("File " + filename +
               " have not supported color table. Keep in mind that BMPs with color tables are not supported!") {
}
BMPInvalidColorChannelCountError::BMPInvalidColorChannelCountError(size_t color_channel_count)
    : BMPError("It have invalid color channel: " + std::to_string(color_channel_count)) {
}
InvalidWidthBMPError::InvalidWidthBMPError(const std::string filename)
    : BMPError("File " + filename + " have negative pixmap width but that BMP not supported!") {
}
}  // namespace image_processor
