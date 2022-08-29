#include "LightArgParserHelper.h"

#include <algorithm>

namespace nlab {

class LightArgParserHelperImpl
{
public:
    LightArgParserHelperImpl(const Args_t& args)
        : args{args}
    {
    }

    ~LightArgParserHelperImpl() = default;

    bool KeyExists(const ArgKey_t& key) { return args.find(key) == args.end() ? false : true; }

    bool AnyKeyExists(const std::vector<ArgKey_t>& keys)
    {
        if (args.size())
        {
            for (auto key : keys)
                if (args.find(key) == args.end()) return true;
        }
        return false;
    }

    std::vector<ArgKey_t> GetKeys()
    {
        std::vector<ArgKey_t> keys;

        for (auto a : args) keys.emplace_back(a.first);

        return keys;
    }

private:
    const Args_t& args;
};

LightArgParserHelper::LightArgParserHelper(const Args_t& args)
    : impl{std::make_unique<LightArgParserHelperImpl>(args)}
{
}

LightArgParserHelper::~LightArgParserHelper()
{
}

bool LightArgParserHelper::KeyExists(const ArgKey_t& key)
{
    return impl->KeyExists(key);
}

bool LightArgParserHelper::AnyKeyExists(const std::vector<ArgKey_t>& keys)
{
    return impl->AnyKeyExists(keys);
}

std::vector<ArgKey_t> LightArgParserHelper::GetKeys()
{
    return impl->GetKeys();
}

} // namespace nlab