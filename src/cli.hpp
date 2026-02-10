#pragma once
#include <string>

namespace wttrbar::cli
{
    struct CliArgs
    {
        std::string mainIndicator = "temp_C";
        std::string location = "";
        bool verticalView = false;
        bool ampm = false;
        bool nerd = false;
        bool fahrenheit = false;
        bool mph = false;
        std::string lang = "en";
    };

    CliArgs parseArgs(int argc, char* argv[]);
}