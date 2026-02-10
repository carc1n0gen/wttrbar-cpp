#include "cli.hpp"

#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>

#include "utils.hpp"

namespace wttrbar::cli
{
    namespace po = boost::program_options;

    CliArgs parseArgs(int argc, char* argv[])
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("main-indicator", po::value<std::string>(), "Set the main weather indicator (default: temp_C)")
            ("location", po::value<std::string>(), "Specify the location for weather data")
            ("vertical-view", po::bool_switch(), "Use vertical view mode")
            ("ampm", po::bool_switch(), "Use 12-hour format with AM/PM")
            ("nerd", po::bool_switch(), "Use nerd icons for weather symbols")
            ("fahrenheit", po::bool_switch(), "Use Fahrenheit for temperature")
            ("mph", po::bool_switch(), "Use miles per hour for wind speed")
            ("lang", po::value<std::string>(), "Set the language for output (default: en)")
            ("help,h", "show this help message");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        CliArgs args;

        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            std::exit(0);
        }

        if (vm.count("main-indicator"))
        {
            args.mainIndicator = vm["main-indicator"].as<std::string>();
        }

        if (vm.count("location"))
        {
            args.location = vm["location"].as<std::string>();
        }

        if (vm["vertical-view"].as<bool>())
        {
            args.verticalView = true;
        }

        if (vm["ampm"].as<bool>())
        {
            args.ampm = true;
        }

        if (vm["nerd"].as<bool>())
        {
            args.nerd = true;
        }

        if (vm["fahrenheit"].as<bool>())
        {
            args.fahrenheit = true;
        }

        if (vm["mph"].as<bool>())
        {
            args.mph = true;
        }

        if (vm.count("lang"))
        {
            args.lang = vm["lang"].as<std::string>();
        }

        return args;
    }
}