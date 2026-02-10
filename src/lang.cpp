
#include "lang.hpp"

namespace wttrbar::lang
{
    Lang::Lang(LangCode v) : value(v) {}

    Lang Lang::fromString(const std::string& str) {
        if (str == "en") return Lang(EN);
        else if (str == "de") return Lang(DE);
        else if (str == "pl") return Lang(PL);
        else if (str == "ru") return Lang(RU);
        else if (str == "tr") return Lang(TR);
        else if (str == "fr") return Lang(FR);
        else if (str == "be") return Lang(BE);
        else if (str == "zh") return Lang(ZH);
        else if (str == "es") return Lang(ES);
        else if (str == "pt") return Lang(PT);
        else if (str == "it") return Lang(IT);
        else if (str == "ja") return Lang(JA);
        else if (str == "uk") return Lang(UK);
        else if (str == "sv") return Lang(SV);
        else if (str == "da") return Lang(DA);
        else if (str == "cs") return Lang(CS);
        else if (str == "sk") return Lang(SK);
        else if (str == "ga") return Lang(GA);
        else throw std::invalid_argument("Unknown language code: " + str);
    }

    // std::string Lang::wttr_in_subdomain() const {
    //     switch (value) {
    //         case EN: return "wttr.in";
    //         case DE: return "de.wttr.in";
    //         case PL: return "pl.wttr.in";
    //         case RU: return "ru.wttr.in";
    //         case TR: return "tr.wttr.in";
    //         case FR: return "fr.wttr.in";
    //         case BE: return "be.wttr.in";
    //         case ZH: return "zh.wttr.in";
    //         case ES: return "es.wttr.in";
    //         case PT: return "pt.wttr.in";
    //         case IT: return "it.wttr.in";
    //         case JA: return "ja.wttr.in";
    //         case UK: return "uk.wttr.in";
    //         case SV: return "sv.wttr.in";
    //         case DA: return "da.wttr.in";
    //         case CS: return "cs.wttr.in";
    //         case SK: return "sk.wttr.in";
    //         case GA: return "ga.wttr.in";
    //         default: throw std::invalid_argument("Unknown Lang");
    //     }
    // }

    std::string Lang::observationTime() const {
        switch (value) {
            case EN: return "Observed at";
            case DE: return "Beobachtet um";
            case PL: return "Zaobserwowano o";
            case RU: return "Наблюдается в";
            case TR: return "Gözlemlendi";
            case FR: return "Observé à";
            case BE: return "Назірана ў";
            case ZH: return "观察时间";
            case ES: return "Observado en";
            case PT: return "Observado em";
            case IT: return "Osservato a";
            case JA: return "で観察されました";
            case UK: return "Спостерігається в";
            case SV: return "Observerat vid";
            case DA: return "Observeret kl";
            case CS: return "Změřeno v";
            case SK: return "Zmerané v";
            case GA: return "Feicthe ag";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::feelsLike() const {
        switch (value) {
            case EN: return "Feels Like";
            case DE: return "Gefühlt wie";
            case PL: return "Temperatura odczuwalna";
            case RU: return "Ощущается как";
            case TR: return "Hissedilen";
            case FR: return "Ressenti";
            case BE: return "Адчуваецца як";
            case ZH: return "体感温度";
            case ES: return "Sensación térmica";
            case PT: return "Sensação térmica";
            case IT: return "Sensazione Termica";
            case JA: return "体感温度";
            case UK: return "Відчувається як";
            case SV: return "Känns som";
            case DA: return "Føles som";
            case CS: return "Pocitově";
            case SK: return "Pocitovo";
            case GA: return "Mothaítear mar";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::humidity() const {
        switch (value) {
            case EN: return "Humidity";
            case DE: return "Luftfeuchtigkeit";
            case PL: return "Wilgotność";
            case RU: return "Влажность";
            case TR: return "Nem";
            case FR: return "Humidité";
            case BE: return "Вільготнасць";
            case ZH: return "湿度";
            case ES: return "Humedad";
            case PT: return "Umidade";
            case IT: return "Umidità";
            case JA: return "湿度";
            case UK: return "Вогкість";
            case SV: return "Luftfuktighet";
            case DA: return "Luftfugtighed";
            case CS: return "Vlhkost";
            case SK: return "Vlhkosť";
            case GA: return "Taise";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::location() const {
        switch (value) {
            case EN: return "Location";
            case DE: return "Standort";
            case PL: return "Lokalizacja";
            case RU: return "Местоположение";
            case TR: return "Konum";
            case FR: return "Lieu";
            case BE: return "Месцазнаходжанне";
            case ZH: return "地区";
            case ES: return "Ubicación";
            case PT: return "Localização";
            case IT: return "Posizione";
            case JA: return "地点";
            case UK: return "Розташування";
            case SV: return "Plats";
            case DA: return "Placering";
            case CS: return "Lokalita";
            case SK: return "Lokalita";
            case GA: return "Láthair";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::today() const {
        switch (value) {
            case EN: return "Today";
            case DE: return "Heute";
            case PL: return "Dzisiaj";
            case RU: return "Сегодня";
            case TR: return "Bugün";
            case FR: return "Aujourd'hui";
            case BE: return "Сёння";
            case ZH: return "今日天气";
            case ES: return "Hoy";
            case PT: return "Hoje";
            case IT: return "Oggi";
            case JA: return "今日";
            case UK: return "Сьогодні";
            case SV: return "Idag";
            case DA: return "I dag";
            case CS: return "Dnes";
            case SK: return "Dnes";
            case GA: return "Inniu";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::tomorrow() const {
        switch (value) {
            case EN: return "Tomorrow";
            case DE: return "Morgen";
            case PL: return "Jutro";
            case RU: return "Завтра";
            case TR: return "Yarın";
            case FR: return "Demain";
            case BE: return "Заўтра";
            case ZH: return "明日天气";
            case ES: return "Mañana";
            case PT: return "Amanhã";
            case IT: return "Domani";
            case JA: return "明日";
            case UK: return "Завтра";
            case SV: return "Imorgon";
            case DA: return "I morgen";
            case CS: return "Zítra";
            case SK: return "Zajtra";
            case GA: return "Amárach";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::fog() const {
        switch (value) {
            case EN: return "Fog";
            case DE: return "Nebel";
            case PL: return "Mgła";
            case RU: return "Туман";
            case TR: return "Sis";
            case FR: return "Brouillard";
            case BE: return "Туман";
            case ZH: return "雾";
            case ES: return "Niebla";
            case PT: return "Nevoeiro";
            case IT: return "Nebbia";
            case JA: return "霧";
            case UK: return "Туман";
            case SV: return "Dimma";
            case DA: return "Tåge";
            case CS: return "Mlha";
            case SK: return "Hmla";
            case GA: return "Ceo";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::frost() const {
        switch (value) {
            case EN: return "Frost";
            case DE: return "Frost";
            case PL: return "Mróz";
            case RU: return "Мороз";
            case TR: return "Don";
            case FR: return "Gel";
            case BE: return "Мароз";
            case ZH: return "霜";
            case ES: return "Escarcha";
            case PT: return "Geada";
            case IT: return "Gelo";
            case JA: return "霜";
            case UK: return "Мороз";
            case SV: return "Frost";
            case DA: return "Frost";
            case CS: return "Mráz";
            case SK: return "Mráz";
            case GA: return "Sioc";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::overcast() const {
        switch (value) {
            case EN: return "Overcast";
            case DE: return "Bewölkung";
            case PL: return "Zachmurzenie";
            case RU: return "Пасмурно";
            case TR: return "Bulutlu";
            case FR: return "Couvert";
            case BE: return "Хмурна";
            case ZH: return "多云";
            case ES: return "Nublado";
            case PT: return "Nublado";
            case IT: return "Nuvoloso";
            case JA: return "曇り";
            case UK: return "Похмуро";
            case SV: return "Mulet";
            case DA: return "Overskyet";
            case CS: return "Zataženo";
            case SK: return "Zamračené";
            case GA: return "Scamallach";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::rain() const {
        switch (value) {
            case EN: return "Rain";
            case DE: return "Regen";
            case PL: return "Deszcz";
            case RU: return "Дождь";
            case TR: return "Yağmur";
            case FR: return "Pluie";
            case BE: return "Дождж";
            case ZH: return "雨";
            case ES: return "Lluvia";
            case PT: return "Chuva";
            case IT: return "Pioggia";
            case JA: return "雨";
            case UK: return "Дощ";
            case SV: return "Regn";
            case DA: return "Regn";
            case CS: return "Déšť";
            case SK: return "Dážď";
            case GA: return "Fearthainn";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::snow() const {
        switch (value) {
            case EN: return "Snow";
            case DE: return "Schnee";
            case PL: return "Śnieg";
            case RU: return "Снег";
            case TR: return "Kar";
            case FR: return "Neige";
            case BE: return "Снег";
            case ZH: return "雪";
            case ES: return "Nieve";
            case PT: return "Neve";
            case IT: return "Neve";
            case JA: return "雪";
            case UK: return "Сніг";
            case SV: return "Snö";
            case DA: return "Sne";
            case CS: return "Sníh";
            case SK: return "Sneh";
            case GA: return "Sneachta";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::sunshine() const {
        switch (value) {
            case EN: return "Sunshine";
            case DE: return "Sonnenschein";
            case PL: return "Nasłonecznienie";
            case RU: return "Солнечно";
            case TR: return "Güneş ışığı";
            case FR: return "Ensoleillé";
            case BE: return "Сонечна";
            case ZH: return "晴";
            case ES: return "Soleado";
            case PT: return "Sol";
            case IT: return "Sole";
            case JA: return "晴れ";
            case UK: return "Сонячно";
            case SV: return "Solsken";
            case DA: return "Solskin";
            case CS: return "Jasno";
            case SK: return "Jasno";
            case GA: return "Grianmhar";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::thunder() const {
        switch (value) {
            case EN: return "Thunder";
            case DE: return "Donner";
            case PL: return "Burza";
            case RU: return "Гроза";
            case TR: return "Gök gürültüsü";
            case FR: return "Orages";
            case BE: return "Навальніца";
            case ZH: return "雷暴";
            case ES: return "Tormenta";
            case PT: return "Trovão";
            case IT: return "Tuono";
            case JA: return "雷";
            case UK: return "Гроза";
            case SV: return "Åska";
            case DA: return "Torden";
            case CS: return "Bouřka";
            case SK: return "Búrka";
            case GA: return "Toirneach";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::wind() const {
        switch (value) {
            case EN: return "Wind";
            case DE: return "Wind";
            case PL: return "Wiatr";
            case RU: return "Ветер";
            case TR: return "Rüzgar";
            case FR: return "Vent";
            case BE: return "Вецер";
            case ZH: return "风速";
            case ES: return "Viento";
            case PT: return "Vento";
            case IT: return "Vento";
            case JA: return "風速";
            case UK: return "Вітер";
            case SV: return "Vind";
            case DA: return "Vind";
            case CS: return "Vítr";
            case SK: return "Vietor";
            case GA: return "Gaoth";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    std::string Lang::weatherDescription() const {
        switch (value) {
            case EN: return "weatherDesc";
            case DE: return "lang_de";
            case PL: return "lang_pl";
            case RU: return "lang_ru";
            case TR: return "lang_tr";
            case FR: return "lang_fr";
            case BE: return "lang_be";
            case ZH: return "lang_zh";
            case ES: return "lang_es";
            case PT: return "lang_pt";
            case IT: return "lang_it";
            case JA: return "lang_ja";
            case UK: return "lang_uk";
            case SV: return "lang_sv";
            case DA: return "lang_da";
            case CS: return "lang_cs";
            case SK: return "lang_sk";
            case GA: return "lang_ga";
            default: throw std::invalid_argument("Unknown Lang");
        }
    }

    // std::string Lang::locale_str() const {
    //     switch (value) {
    //         case EN: return "en_US";
    //         case DE: return "de_DE";
    //         case PL: return "pl_PL";
    //         case RU: return "ru_RU";
    //         case TR: return "tr_TR";
    //         case FR: return "fr_FR";
    //         case BE: return "be_BY";
    //         case ZH: return "zh_CN";
    //         case ES: return "es_ES";
    //         case PT: return "pt_PT";
    //         case IT: return "it_IT";
    //         case JA: return "ja_JP";
    //         case UK: return "uk_UA";
    //         case SV: return "sv_SE";
    //         case DA: return "da_DK";
    //         case CS: return "cs_CZ";
    //         case SK: return "sk_SK";
    //         case GA: return "ga_IE";
    //         default: throw std::invalid_argument("Unknown Lang");
    //     }
    // }
}
