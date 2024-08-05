#include "Utils/RainbowUtils.hpp"
#include "logging.hpp"

struct Gaydient {
    static inline std::vector<Gaydient*> gaydients = {};
    static Gaydient& randomGaydient() {
        return *gaydients[rand() % gaydients.size()];
    }

    Gaydient() { gaydients.push_back(this); };
    virtual const char* nextPrefix() = 0;
    virtual const std::string& rawGradient() const = 0;
};

template <int sz>
struct GaydientImpl : public Gaydient {
    std::array<const char*, sz> colorPrefixes;
    std::string gradient;
    int index = 0;

    GaydientImpl(std::array<const char*, sz> colorPrefixes, std::string gradient) : Gaydient(), colorPrefixes(colorPrefixes), gradient(gradient){};
    const char* nextPrefix() override { return colorPrefixes[nextIndex()]; }
    const std::string& rawGradient() const override { return gradient; };
    int nextIndex() { return index = (index + 1) % sz; }
};

static GaydientImpl<12> rainbow {
    {
        "<color=#ff6060>",
        "<color=#ffa060>",
        "<color=#ffff60>",
        "<color=#a0ff60>",
        "<color=#60ff60>",
        "<color=#60ffa0>",
        "<color=#60ffff>",
        "<color=#60a0ff>",
        "<color=#6060ff>",
        "<color=#a060ff>",
        "<color=#ff60ff>",
        "<color=#ff60a0>"
    },
    "#ff6060;#ffa060;#ffff60;#a0ff60;#60ff60;#60ffa0;#60ffff;#60a0ff;#6060ff;#a060ff;#ff60ff;#ff60a0;#ff6060"
};

static GaydientImpl<6> pride {
    {
        "<color=#e40303>",
        "<color=#ff8c00>",
        "<color=#ffed00>",
        "<color=#008026>",
        "<color=#004dff>",
        "<color=#450787>"
    },
    "#e40303;#ff8c00;#ffed00;#008026;#004dff;#450787;#e40303"
};

static GaydientImpl<5> trans {
    {
        "<color=#59c9f4>",
        "<color=#f1a5b5>",
        "<color=#ffffff>",
        "<color=#f1a5b5>",
        "<color=#59c9f4>"
    },
    "#59c9f4;#f1a5b5;#ffffff;#f1a5b5;#59c9f4"
};

static GaydientImpl<5> lesbian {
    {
        "<color=#d52c01>",
        "<color=#fd9a57>",
        "<color=#ffffff>",
        "<color=#d1619f>",
        "<color=#a20161>"
    },
    "#d52c01;#fd9a57;#ffffff;#d1619f;#a20161;#d52c01"
};

static GaydientImpl<7> gay {
    {
        "<color=#078e70>",
        "<color=#26ceaa>",
        "<color=#98e8c1>",
        "<color=#ffffff>",
        "<color=#7bade2>",
        "<color=#5049cb>",
        "<color=#3d1a78>"
    },
    "#078e70;#26ceaa;#98e8c1;#ffffff;#7bade2;#5049cb;#3d1a78;#078e70"
};
static GaydientImpl<5> bi {
    {
        "<color=#d0036d>",
        "<color=#d0036d>",
            "<color=#9a4f96>",
            "<color=#0037a3>",
            "<color=#0037a3>"
    },
    "#d0036d;#d0036d;#9a4f96;#0037a3;#0037a3;#d0036d"
};

static GaydientImpl<4> ace {
    {
        "<color=#000000>",
        "<color=#808080>",
        "<color=#ffffff>",
        "<color=#800080>"
    },
    "#000000;#808080;#ffffff;#800080;#000000"
};

static GaydientImpl<5> aro {
    {
        "<color=#3da542>",
        "<color=#a8d379>",
        "<color=#ffffff>",
        "<color=#a9a9a9>",
        "<color=#000000>"
    },
    "#3da542;#a8d379;#ffffff;#a9a9a9;#000000;#3da542"
};

static GaydientImpl<6> pan {
    {
        "<color=#f11a85>",
        "<color=#f11a85>",
        "<color=#ffd900>",
        "<color=#ffd900>",
        "<color=#1bb3ff>",
        "<color=#1bb3ff>"
    },
    "#f11a85;#f11a85;#ffd900;#ffd900;#1bb3ff;#1bb3ff;#f11a85"
};

static GaydientImpl<4> nonbinary {
    {
        "<color=#f9ee33>",
        "<color=#000000>",
        "<color=#9c59cf>",
        "<color=#2d2d2d>"
    },
    "#f9ee33;#000000;#9c59cf;#2d2d2d;#f9ee33"
};

static GaydientImpl<6> genderqueer {
    {
        "<color=#ac77d0>",
        "<color=#ac77d0>",
        "<color=#ffffff>",
        "<color=#ffffff>",
        "<color=#4b8124>",
        "<color=#4b8124>"
    },
    "#ac77d0;#ac77d0;#ffffff;#ffffff;#4b8124;#4b8124;#ac77d0"
};

static GaydientImpl<5> genderfluid {
    {
        "<color=#ff75a2>",
        "<color=#f5f5f5>",
        "<color=#be18d6>",
        "<color=#2c2c2c>",
        "<color=#333ebd>"
    },
    "#ff75a2;#f5f5f5;#be18d6;#2c2c2c;#333ebd;#ff75a2"
};

static GaydientImpl<7> agender {
    {
        "<color=#000000>",
        "<color=#bcc4c6>",
        "<color=#ffffff>",
        "<color=#b9f480>",
        "<color=#ffffff>",
        "<color=#bcc4c6>",
        "<color=#000000>"
    },
    "#000000;#bcc4c6;#ffffff;#b9f480;#ffffff;#bcc4c6;#000000"
};

namespace Qosmetics::Core::RainbowUtils {
    static constexpr int colorSegmentSize = 24;

    bool shouldRainbow(std::string_view name) {
        return toLower(std::string(name)).find("rainbow") != std::string::npos;
    }

    bool shouldRainbow(UnityEngine::Color& color) {
        return color.r >= 0.99f && color.g >= 0.99f && color.b >= 0.99f;
    }

    std::string rainbowify(std::string_view in) {
        std::string result;
        int size = in.size();
        int finalSize = size * sizeof(char) * colorSegmentSize;
        result.resize(finalSize);

        for (int i = 0; i < size; i++)
        {
            auto currentStart = &result[i * colorSegmentSize];
            memcpy(currentStart, rainbow.nextPrefix(), 15);
            currentStart[15] = in[i];
            memcpy(&currentStart[16], "</color>", 8);
        }
        return result;
    }

    const std::string_view rainbowGradient() { return rainbow.rawGradient(); }

    const std::string_view randomGradient() { return Gaydient::randomGaydient().rawGradient(); }

    std::string gayify(std::string_view in) {
        if (Gaydient::gaydients.size() < 1) {
            INFO("Not enough gaydients, using rainbowify instead");
            return rainbowify(in);
        }

        std::string result;
        int size = in.size();
        int finalSize = size * sizeof(char) * colorSegmentSize;
        result.resize(finalSize);
        auto& gaydient = Gaydient::randomGaydient();

        for (int i = 0; i < size; i++) {
            auto currentStart = &result[i * colorSegmentSize];
            memcpy(currentStart, gaydient.nextPrefix(), 15);
            currentStart[15] = in[i];
            memcpy(&currentStart[16], "</color>", 8);
        }

        return result;
    }

    std::string toLower(std::string in) {
        std::transform(in.begin(), in.end(), in.begin(), tolower);
        return in;
    }
}
