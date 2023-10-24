#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>

namespace image_processor {

class TArgParser {
public:
    struct OptionSignature {
        int id = 0;
        std::vector<std::string> names = {};
        // If true, it is added to a special queue of required arguments and such
        // options are expected in advisory order in the arguments
        bool is_required = false;
    };

    struct ResultOptions {
        // {..., required_option, ...}
        using RequiredOptions = std::vector<std::string>;
        // {..., (option_id, option_args), ...}
        using OptionalOptions = std::vector<std::pair<int, std::vector<std::string>>>;

        struct {
            bool is_need_verbose = false;
        } work_mode;

        RequiredOptions required_options = {};
        OptionalOptions optional_options = {};
    };
    using OptionsDescriptor = std::vector<OptionSignature>;

    explicit TArgParser(OptionsDescriptor options_descriptor);
    ~TArgParser() = default;

    void Parse(int argc, char** argv);
    ResultOptions GetOptions() const;

    static void PrintHelp();

private:
    OptionsDescriptor options_descriptor_ = {};
    ResultOptions result_options_ = {};
    int64_t require_args_count_ = 0;
    std::unordered_map<std::string, int> supported_args_to_id_ = {};
};

}  // namespace image_processor
