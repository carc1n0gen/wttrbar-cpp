#include <format>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <boost/json.hpp>
#include <boost/algorithm/string.hpp>

#include "cli.hpp"
#include "lang.hpp"
#include "utils.hpp"
#include "constants.hpp"

using namespace std;
using namespace wttrbar;

int main(int argc, char* argv[])
{
    cli::CliArgs args = cli::parseArgs(argc, argv);
    lang::Lang lang = lang::Lang::fromString(args.lang);
    string cacheFilePath = filesystem::temp_directory_path() / format("wttrbar-{}-{}.json", args.location, args.lang);

    cout << R"({"text":"⏳", "tooltip":"Loading...", "class":"loading"})" << endl;
    
    boost::json::value weather;
    if (utils::isCacheRecent(cacheFilePath))
    {
        ifstream cache(cacheFilePath);
        stringstream buffer;
        buffer << cache.rdbuf();
        weather = boost::json::parse(buffer.str());
    }
    else
    {
        int attempts = 0;
        const int maxAttempts = 20;
        while (true)
        {
            try
            {
                utils::Response response = utils::request(format("https://wttr.in/{}?format=j1&lang={}", args.location, args.lang));
                try
                {
                    weather = boost::json::parse(response.body);
                    ofstream cache(cacheFilePath);
                    cache << response.body;
                    break;
                }
                catch (const std::exception& parseException)
                {
                    cout << R"({"text":"⛓️‍💥", "tooltip":"Invalid wttr.in response", "class":"error"})" << endl;
                    return 0;
                }
            }
            catch (const std::exception& requestException)
            {
                attempts++;
                this_thread::sleep_for(chrono::milliseconds(500 * attempts));

                if (attempts >= maxAttempts)
                {
                    cout << R"({"text":"⛓️‍💥", "tooltip":"Error reaching wttr.in", "class":"error"})" << endl;
                    return 0;
                }
            }
        }
    }

    const boost::json::object& currentConditions = weather.as_object()["current_condition"].as_array()[0].as_object();
    const string& weatherCode = currentConditions.at("weatherCode").as_string().c_str();
    const string& feelsLike = args.fahrenheit ? currentConditions.at("FeelsLikeF").as_string().c_str() : currentConditions.at("FeelsLikeC").as_string().c_str();
    const string& temperature = args.fahrenheit ? currentConditions.at("temp_F").as_string().c_str() : currentConditions.at("temp_C").as_string().c_str();
    const string& windSpeed = args.mph ? currentConditions.at("windspeedMiles").as_string().c_str() : currentConditions.at("windspeedKmph").as_string().c_str();
    const boost::json::object& nearestArea = weather.as_object().at("nearest_area").as_array()[0].as_object();
    const unordered_map<std::string, std::string>& weatherIcons = args.nerd ? constants::WEATHER_ICONS_NERD : constants::WEATHER_ICONS;
    const chrono::sys_time<chrono::seconds> observationTime = utils::chronoDateFromString(currentConditions.at("localObsDateTime").as_string().c_str(), "%Y-%m-%d %H:%M %p");
    const string& weatherDescription = currentConditions.at(lang.weatherDescription()).as_array()[0].as_object().at("value").as_string().c_str();

    string indicatorKey;
    if (args.mainIndicator.empty())
    {
        indicatorKey = args.fahrenheit ? "temp_F" : "temp_C";
    }
    else
    {
        indicatorKey = args.mainIndicator;
    }

    boost::json::object output = {};
    output["text"] = format("{} {}", weatherIcons.at(weatherCode), currentConditions.at(indicatorKey).as_string().c_str());

    string tooltip = format("<b>{}</b> {}°\n", weatherDescription, temperature);
    tooltip.append(format("{}: {}°\n", lang.feelsLike(), feelsLike));
    tooltip.append(format("{}: {} {}\n", lang.wind(), windSpeed, args.mph ? "mph" : "km/h"));
    tooltip.append(format("{}: {}%\n", lang.humidity(), currentConditions.at("humidity").as_string().c_str()));
    tooltip.append(format("{}: {}, {}, {}\n",
        lang.location(),
        nearestArea.at("areaName").as_array()[0].as_object().at("value").as_string().c_str(),
        nearestArea.at("region").as_array()[0].as_object().at("value").as_string().c_str(),
        nearestArea.at("country").as_array()[0].as_object().at("value").as_string().c_str()
    ));
    
    tooltip.append(format("{}: ", lang.observationTime()));
    if (args.ampm)
    {
        tooltip.append(format("{:%I:%M %p}\n", observationTime));
    }
    else
    {
        tooltip.append(format("{:%H:%M}\n", observationTime));
    }

    chrono::sys_time<chrono::seconds> today = chrono::floor<chrono::seconds>(chrono::system_clock::now());
    boost::json::array forecast = {};
    for (const auto& day : weather.as_object().at("weather").as_array())
    {
        chrono::sys_time<chrono::seconds> dayDate = utils::chronoDateFromString(day.as_object().at("date").as_string().c_str(), "%Y-%m-%d");
        if (dayDate >= today)
        {
            forecast.push_back(day);
        }
    }

    for (size_t i = 0; i < forecast.size(); i++)
    {
        auto day = forecast[i].as_object();
        tooltip.append("\n<b>");

        if (i == 0)
        {
            tooltip.append(format("{}, ", lang.today()));
        }
        else if (i == 1)
        {
            tooltip.append(format("{}, ", lang.tomorrow()));
        }

        // TODO: potentially need to localize the date
        tooltip.append(format("{}</b>\n", day.at("date").as_string().c_str()));
        
        string min, max;
        if (args.fahrenheit)
        {
            min = day.at("mintempF").as_string().c_str();
            max = day.at("maxtempF").as_string().c_str();
        }
        else
        {
            min = day.at("mintempC").as_string().c_str();
            max = day.at("maxtempC").as_string().c_str();
        }

        if (args.nerd)
        {
            tooltip.append(format("󰳡 {}° 󰳛  {}° ", min, max));
        }
        else
        {
            tooltip.append(format("⬆️ {}° ⬇️  {}° ", min, max));
        }

        string sunrise, sunset;
        if (args.ampm)
        {
            sunrise = day.at("astronomy").as_array()[0].as_object().at("sunrise").as_string().c_str();
            sunset = day.at("astronomy").as_array()[0].as_object().at("sunset").as_string().c_str();
        }
        else
        {
            sunrise = format("{:%H:%M}", utils::chronoTimeFromString(day.at("astronomy").as_array()[0].as_object().at("sunrise").as_string().c_str(), "%I:%M %p")).c_str();
            sunset = format("{:%H:%M}", utils::chronoTimeFromString(day.at("astronomy").as_array()[0].as_object().at("sunset").as_string().c_str(), "%I:%M %p")).c_str();
        }

        if (args.nerd)
        {
            tooltip.append(format("󰖜 {} 󰖛 {}\n", sunrise, sunset));
        }
        else
        {
            tooltip.append(format("🌅 {} 🌇 {}\n", sunrise, sunset));
        }

        const boost::json::array& hourly = day.at("hourly").as_array();
        for (const boost::json::value& hour: hourly)
        {
            string timeString = hour.as_object().at("time").as_string().c_str();
            timeString = boost::algorithm::replace_all_copy(timeString, "00", "");
            chrono::hh_mm_ss<std::chrono::seconds> time = utils::chronoTimeFromString(timeString, "%H");
            
            string outputHour;
            if (args.ampm)
            {
                outputHour = format("{:%I %p}", time).c_str();
            }
            else
            {
                outputHour = format("{:%H:%M}", time).c_str();
            }

            string hourIcon = weatherIcons.at(hour.as_object().at("weatherCode").as_string().c_str());
            string hourTemp = args.fahrenheit ? hour.as_object().at("tempF").as_string().c_str() : hour.as_object().at("tempC").as_string().c_str();
            string hourFeelsLike = args.fahrenheit ? hour.as_object().at("FeelsLikeF").as_string().c_str() : hour.as_object().at("FeelsLikeC").as_string().c_str();
            string hourDescription = hour.as_object().at(lang.weatherDescription()).as_array()[0].as_object().at("value").as_string().c_str();
            tooltip.append(format("{} {} {}° / {}° {}\n", outputHour, hourIcon, hourTemp, hourFeelsLike, hourDescription));
        }
    }

    output["tooltip"] = tooltip;

    output["class"] = [&weatherDescription]() {
        string s = weatherDescription;
        boost::algorithm::to_lower(s);
        boost::algorithm::replace_all(s, " ", "_");

        vector<string> parts;
        boost::algorithm::split(parts, s, boost::algorithm::is_any_of(","));
        return parts[0];
    }();

    cout << boost::json::serialize(output) << endl;
    return 0;
}
