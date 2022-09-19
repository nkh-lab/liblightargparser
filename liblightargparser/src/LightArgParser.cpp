#include "LightArgParser.h"

#include <algorithm>

namespace nkhlab {
namespace lightargparser {

namespace impl {
class LightArgParserImpl
{
public:
    LightArgParserImpl(int argc, const char** argv)
        : argc{argc}
        , argv{argv}
    {
    }

    ~LightArgParserImpl() = default;

    bool Parse(Args_t& config_args, Args_t& data_args, std::string& bad_arg)
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
                if (key[1] == kConfigArgIdChar && key[2] != kConfigArgIdChar &&
                    key.size() >= kConfigArgLongFormMinSize)
                {
                    // Config argument in long form, e.g.: --ConfigKey1 or --ConfigKey2=ConfigData2
                    config_args.emplace(std::string{&key[2]}, val);
                }
                else if (key[1] != kConfigArgIdChar)
                {
                    if (key.size() == kConfigArgShortFormSingleSize)
                    {
                        // Config argument in short form single, e.g.: -x or -y=data
                        config_args.emplace(std::string{&key[1]}, val);
                    }
                    else if (val == std::string{})
                    {
                        // Config argument in short form complex, e.g.: -xyz
                        for (size_t i = 1; i < key.size(); ++i)
                            config_args.emplace(std::string{key[i]}, std::string{});
                    }
                    else
                    {
                        ret = false;
                        bad_arg = argv[i];
                        break;
                    }
                }
                else
                {
                    ret = false;
                    bad_arg = argv[i];
                    break;
                }
            }
            else
            {
                // Data argument
                data_args.emplace(key, val);
            }
        }

        if (!ret)
        {
            config_args.clear();
            data_args.clear();
        }

        return ret;
    }

private:
    const char* kKeyValueDelimiter = "=";
    const char kConfigArgIdChar = '-';
    const size_t kConfigArgLongFormMinSize = 4;
    const size_t kConfigArgShortFormSingleSize = 2;

    int argc;
    const char** argv;
};

} // namespace impl

LightArgParser::LightArgParser(int argc, const char** argv)
    : impl_{std::make_unique<impl::LightArgParserImpl>(argc, argv)}
{
}

LightArgParser::~LightArgParser()
{
}

bool LightArgParser::Parse(Args_t& config_args, Args_t& data_args, std::string& bad_arg)
{
    return impl_->Parse(config_args, data_args, bad_arg);
}

} // namespace lightargparser
} // namespace nkhlab