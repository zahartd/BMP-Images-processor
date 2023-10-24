file(GLOB filters filters/*.cpp)
file(GLOB image image/*.cpp)
file(GLOB cli cli/*.cpp)


set(LIB_SRC
        exceptions.cpp
        image/bmpexceptions.cpp
        image/exceptions.cpp
        utils.cpp
        ${filters}
        ${images}
        ${cli}
        image.cpp
        args_parser.cpp
        filter.cpp)

add_library(
        image_processor_lib OBJECT
        ${LIB_SRC}
)

add_executable(
        image_processor
        image_processor.cpp
)

add_catch(test_image_processor_filters image.cpp exceptions.cpp image/exceptions.cpp image/bmpexceptions.cpp filter.cpp filters/exceptions.cpp filters/IChannelWiseFilter.cpp
        filters/TCompositeFilter.cpp filters/TConvolutionFilter.cpp filters/utils.cpp filters/TCrop.cpp filters/TNegativeFilter.cpp filters/TGrayScaleFilter.cpp
        filters/TSharpeningFilter.cpp filters/TEdgeDetectionFilter.cpp filters/TGaussianBlurFilter.cpp filters/TMedianFilter.cpp filters/TGlassFilter.cpp
        filters/TThresholdFilter.cpp filters/TEdgeDetectionConvFilter.cpp tests/test_filters.cpp)
add_catch(test_image_processor_parser args_parser.cpp exceptions.cpp cli/utils.cpp cli/exceptions.cpp filters/utils.cpp tests/test_parser.cpp)
add_catch(test_image_processor_image image.cpp exceptions.cpp image/exceptions.cpp image/bmpexceptions.cpp tests/test_images.cpp)


target_link_libraries(image_processor image_processor_lib)

