#include "exceptions.h"

namespace image_processor {

FileOpenError::FileOpenError(std::string filename) : FileError("Unable to open file " + filename + ".") {
}

FileCloseError::FileCloseError(std::string filename) : FileError("Unable to close file " + filename + ".") {
}
InvalidFileFormatError::InvalidFileFormatError(std::string filename, std::string file_format)
    : FileError("File " + filename + " have unsupported file format, it expected: " + file_format) {
}
}  // namespace image_processor