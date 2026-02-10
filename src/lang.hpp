#pragma once
#include <string>
#include <stdexcept>

namespace wttrbar::lang
{
    enum LangCode {
        EN, DE, PL, RU, TR, FR, BE, ZH, ES, PT, IT, JA, UK, SV, DA, CS, SK, GA
    };

    class Lang {
    private:
        LangCode value;
    public:
        explicit Lang(LangCode v);
        static Lang fromString(const std::string& str);
        // std::string wttr_in_subdomain() const;
        std::string observationTime() const;
        std::string feelsLike() const;
        std::string humidity() const;
        std::string location() const;
        std::string today() const;
        std::string tomorrow() const;
        std::string fog() const;
        std::string frost() const;
        std::string overcast() const;
        std::string rain() const;
        std::string snow() const;
        std::string sunshine() const;
        std::string thunder() const;
        std::string wind() const;
        std::string weatherDescription() const;
        // std::string locale_str() const;
    };
}