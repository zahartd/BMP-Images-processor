#include "exceptions.h"

namespace image_processor {

MissingRequiredArgsError::MissingRequiredArgsError() : ParserError("Missing required arguments!") {
}
InvalidArgFormatError::InvalidArgFormatError() : ParserError("Invalid arguments format!") {
}
UnexpectedArgError::UnexpectedArgError() : ParserError("It provided not expected argument!") {
}
}  // namespace image_processor
