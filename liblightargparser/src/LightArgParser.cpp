#include "LightArgParser.h"

#include <algorithm>

namespace nlab {

class LightArgParserImpl
{
public:
    LightArgParserImpl(int argc, const char** argv)
        : argc{argc}
        , argv{argv}
    {
    }

    ~LightArgParserImpl() = default;

    bool Parse(std::map<ArgKey_t, ArgVal_t>& config, std::map<ArgKey_t, ArgVal_t>& data)
    {
        bool ret = true;

        for (int i = 1; i < argc; ++i)
        {
            std::string s{argv[i]};
            std::string key = s;
            std::string val;
            size_t delimiter_pos = s.find_first_of(kKeyValueDelimiter);

            if (delimiter_pos != std::string::npos)
            {
                key = s.substr(0, delimiter_pos);
                val = s.substr(delimiter_pos + 1);
            }

            if (key[0] == kConfigArgIdChar)
            {
                if ((key[1] != kConfigArgIdChar && key.size() == kConfigArgShortFormSize) ||
                    (key[1] == kConfigArgIdChar && key.size() >= kConfigArgLongFormMinSize))
                {
                    key.erase(
                        std::remove(key.begin(), key.begin() + 2, kConfigArgIdChar), key.begin() + 2);

                    if (key[0] == kConfigArgIdChar)
                    {
                        ret = false;
                        break;
                    }
                }
                else
                {
                    ret = false;
                    break;
                }

                config.emplace(key, val);
            }
            else
            {
                data.emplace(key, val);
            }
        }

        if (!ret)
        {
            config.clear();
            data.clear();
        }

        return ret;
    }

private:
    const char* kKeyValueDelimiter = "=";
    const char kConfigArgIdChar = '-';
    const size_t kConfigArgShortFormSize = 2;
    const size_t kConfigArgLongFormMinSize = 4;

    int argc;
    const char** argv;
};

LightArgParser::LightArgParser(int argc, const char** argv)
    : impl{std::make_unique<LightArgParserImpl>(argc, argv)}
{
}

LightArgParser::~LightArgParser()
{
}

bool LightArgParser::Parse(std::map<ArgKey_t, ArgVal_t>& config, std::map<ArgKey_t, ArgVal_t>& data)
{
    return impl->Parse(config, data);
}

} // namespace nlab