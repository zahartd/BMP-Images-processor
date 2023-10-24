#include <catch.hpp>
#include "image.h"
#include "image/bmpexceptions.h"

TEST_CASE("TImage: Open valid file without throw") {
    image_processor::TImage img;

    const std::string no_throw_image =
        "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag.bmp";
    REQUIRE_NOTHROW(img.LoadFromBMP(no_throw_image));
}

TEST_CASE("TImage: Write valid file without throw") {
    image_processor::TImage img;

    const std::string read_image = "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/flag.bmp";
    const std::string write_image = "/home/hexinf/projects/hse-course/tasks/image_processor/test_script/data/new.bmp";

    img.LoadFromBMP(read_image);

    // Test SaveToBMP
    REQUIRE_NOTHROW(img.SaveToBMP(write_image));
}
