#pragma once

#include <exception>
#include <string>

#include "../exceptions.h"

namespace image_processor {
class BMPError : public ErrorWithMessage {
public:
    using ErrorWithMessage::ErrorWithMessage;
};

class NotBMPFileError : public BMPError {
public:
    explicit NotBMPFileError(const std::string filename, char filetype[2]);
};

class InvalidWidthBMPError : public BMPError {
public:
    explicit InvalidWidthBMPError(const std::string filename);
};

class InvalidBMPFormatError : public BMPError {
public:
    explicit InvalidBMPFormatError(const std::string filename);
};

class InvalidBMPBitCountError : public BMPError {
public:
    explicit InvalidBMPBitCountError(const std::string filename, uint16_t bit_count);
};

class NotSupportedBMPCompressionModeError : public BMPError {
public:
    explicit NotSupportedBMPCompressionModeError(const std::string filename, uint32_t compression);
};

class NotSupportedBMPColorTableError : public BMPError {
public:
    explicit NotSupportedBMPColorTableError(const std::string filename);
};

class BMPInvalidColorChannelCountError : public BMPError {
public:
    explicit BMPInvalidColorChannelCountError(size_t color_channel_count);
};

}  // namespace image_processor