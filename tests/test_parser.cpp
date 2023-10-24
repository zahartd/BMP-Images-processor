#include <catch.hpp>
#include "../args_parser.h"

TEST_CASE("Parser: Parsing valid args") {
    char* argv[] = {const_cast<char*>("test"), const_cast<char*>("input.jpg"), const_cast<char*>("-filter"),  // NOLINT
                    const_cast<char*>("blur"), const_cast<char*>("-radius"),   const_cast<char*>("5"),        // NOLINT
                    const_cast<char*>("-v")};                                                                 // NOLINT

    image_processor::TArgParser::OptionsDescriptor options_descriptor = {
        {0, {}, true},
        {1, {"filter", "f"}, false},
        {2, {"radius", "r"}, false},
    };

    image_processor::TArgParser parser(options_descriptor);
    parser.Parse(7, argv);  // NOLINT
    auto user_query = parser.GetOptions();

    REQUIRE(user_query.required_options.size() == 1);
    REQUIRE(user_query.required_options[0] == "input.jpg");
    REQUIRE(user_query.optional_options.size() == 2);
    REQUIRE(user_query.optional_options[0].first == 1);
    REQUIRE(user_query.optional_options[0].second.size() == 1);
    REQUIRE(user_query.optional_options[0].second[0] == "blur");
    REQUIRE(user_query.optional_options[1].first == 2);
    REQUIRE(user_query.optional_options[1].second.size() == 1);
    REQUIRE(user_query.optional_options[1].second[0] == "5");
    REQUIRE(user_query.work_mode.is_need_verbose == true);
}

TEST_CASE("Parser: Missing required args") {
    char* argv[] = {const_cast<char*>("test"), const_cast<char*>("required_arg1"), const_cast<char*>("-arg"),  // NOLINT
                    const_cast<char*>("option1"), const_cast<char*>("option2")};                               // NOLINT

    image_processor::TArgParser::OptionsDescriptor options_descriptor = {
        {0, {}, true},
        {1, {}, true},
        {2, {"arg", "a"}, false},
    };

    image_processor::TArgParser parser(options_descriptor);

    REQUIRE_THROWS_WITH(parser.Parse(5, argv), "Missing required arguments!");
}

TEST_CASE("Parser: Invalid argument format") {
    char* argv[] = {const_cast<char*>("test"), const_cast<char*>("required_arg1"),  // NOLINT
                    const_cast<char*>("required_arg2"),                             // NOLINT
                    const_cast<char*>("invalid_arg")};                              // NOLINT

    image_processor::TArgParser::OptionsDescriptor options_descriptor = {
        {0, {}, true},
        {1, {}, true},
        {2, {"invalid_arg", "a"}, false},
    };

    image_processor::TArgParser parser(options_descriptor);

    REQUIRE_THROWS_WITH(parser.Parse(4, argv), "Invalid arguments format!");
}

TEST_CASE("Parser: Unexpected args") {
    char* argv[] = {const_cast<char*>("test"), const_cast<char*>("input.jpg"),  // NOLINT
                    const_cast<char*>("-unsupported_arg")};                     // NOLINT

    image_processor::TArgParser::OptionsDescriptor options_descriptor = {
        {0, {}, true},
    };

    image_processor::TArgParser parser(options_descriptor);

    REQUIRE_THROWS_WITH(parser.Parse(3, argv), "It provided not expected argument!");
}