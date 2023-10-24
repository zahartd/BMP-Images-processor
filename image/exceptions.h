#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <string_view>

#include "../exceptions.h"

namespace image_processor {
class FileError : public ErrorWithMessage {
public:
    using ErrorWithMessage::ErrorWithMessage;
};

class FileOpenError : public FileError {
public:
    explicit FileOpenError(std::string filename);
};

class FileCloseError : public FileError {
public:
    explicit FileCloseError(std::string filename);
};

class InvalidFileFormatError : public FileError {
public:
    explicit InvalidFileFormatError(std::string filename, std::string file_format);
};
}  // namespace image_processor