#pragma once

#include <exception>
#include <string>

#include "../exceptions.h"

namespace image_processor {

class ParserError : public ErrorWithMessage {
public:
    using ErrorWithMessage::ErrorWithMessage;
};

class MissingRequiredArgsError : public ParserError {
public:
    explicit MissingRequiredArgsError();
};

class InvalidArgFormatError : public ParserError {
public:
    explicit InvalidArgFormatError();
};

class UnexpectedArgError : public ParserError {
public:
    explicit UnexpectedArgError();
};

}  // namespace image_processor
