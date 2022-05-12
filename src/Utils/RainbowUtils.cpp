#include "Utils/RainbowUtils.hpp"
#include "logging.hpp"

struct Gaydient
{
    static inline std::vector<Gaydient*> gaydients = {};
    static Gaydient& randomGaydient()
    {
        return *gaydients[rand() % gaydients.size()];
    }

    Gaydient() { gaydients.push_back(this); };
    virtual const char* nextPrefix() = 0;
};

template <int sz>
struct GaydientImpl : public Gaydient
{
    std::array<const char*, sz> colorPrefixes;
    int index = 0;

    GaydientImpl(std::array<const char*, sz> colorPrefixes) : Gaydient(), colorPrefixes(colorPrefixes){};
    const char* nextPrefix() override { return colorPrefixes[nextIndex()]; }
    int nextIndex() { return index = (index + 1) % sz; }
};

static GaydientImpl<12> rainbow{{"<color=#ff6060>",
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
                                 "<color=#ff60a0>"}};
static GaydientImpl<6> pride{{"<color=#e40303>",
                              "<color=#ff8c00>",
                              "<color=#ffed00>",
                              "<color=#008026>",
                              "<color=#004dff>",
                              "<color=#450787>"}};
static GaydientImpl<5> trans{{"<color=#59c9f4>",
                              "<color=#f1a5b5>",
                              "<color=#ffffff>",
                              "<color=#f1a5b5>",
                              "<color=#59c9f4>"}};
static GaydientImpl<5> lesbian{{"<color=#d52c01>",
                                "<color=#fd9a57>",
                                "<color=#ffffff>",
                                "<color=#d1619f>",
                                "<color=#a20161>"}};
static GaydientImpl<7> gay{{"<color=#078e70>",
                            "<color=#26ceaa>",
                            "<color=#98e8c1>",
                            "<color=#ffffff>",
                            "<color=#7bade2>",
                            "<color=#5049cb>",
                            "<color=#3d1a78>"}};
static GaydientImpl<5> bi{{"<color=#d0036d>",
                           "<color=#d0036d>",
                           "<color=#9a4f96>",
                           "<color=#0037a3>",
                           "<color=#0037a3>"}};
static GaydientImpl<4> ace{{"<color=#000000>",
                            "<color=#808080>",
                            "<color=#ffffff>",
                            "<color=#800080>"}};
static GaydientImpl<5> aro{{"<color=#3da542>",
                            "<color=#a8d379>",
                            "<color=#ffffff>",
                            "<color=#a9a9a9>",
                            "<color=#000000>"}};
static GaydientImpl<6> pan{{"<color=#f11a85>",
                            "<color=#f11a85>",
                            "<color=#ffd900>",
                            "<color=#ffd900>",
                            "<color=#1bb3ff>",
                            "<color=#1bb3ff>"}};
static GaydientImpl<4> nb{{"<color=#f9ee33>",
                           "<color=#000000>",
                           "<color=#9c59cf>",
                           "<color=#2d2d2d>"}};
static GaydientImpl<6> genderqueer{{"<color=#ac77d0>",
                                    "<color=#ac77d0>",
                                    "<color=#ffffff>",
                                    "<color=#ffffff>",
                                    "<color=#4b8124>",
                                    "<color=#4b8124>"}};

namespace Qosmetics::Core::RainbowUtils
{
    static constexpr int colorSegmentSize = 24;

    bool shouldRainbow(std::string_view name)
    {
        return toLower(std::string(name)).find("rainbow") != std::string::npos;
    }

    bool shouldRainbow(UnityEngine::Color& color)
    {
        return color.r >= 0.99f && color.g >= 0.99f && color.b >= 0.99f;
    }

    std::string rainbowify(std::string_view in)
    {
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

    std::string gayify(std::string_view in)
    {
        if (Gaydient::gaydients.size() < 1)
        {
            INFO("Not enough gaydients, using rainbowify instead");
            return rainbowify(in);
        }

        std::string result;
        int size = in.size();
        int finalSize = size * sizeof(char) * colorSegmentSize;
        result.resize(finalSize);
        auto& gaydient = Gaydient::randomGaydient();

        for (int i = 0; i < size; i++)
        {
            auto currentStart = &result[i * colorSegmentSize];
            memcpy(currentStart, gaydient.nextPrefix(), 15);
            currentStart[15] = in[i];
            memcpy(&currentStart[16], "</color>", 8);
        }
        return result;
    }

    std::string toLower(std::string in)
    {
        for (auto& c : in)
            c = tolower(c);
        return in;
    }
}