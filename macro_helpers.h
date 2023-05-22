#pragma once

#include "macros.h"

#include <map>
#include <string>
#include <unordered_map>


//----------------------------------------------------------------------------
// marty_tr::macros::
namespace marty_tr{
namespace macros{



//----------------------------------------------------------------------------
template<typename StringType>
bool getMacroTextFromMap(const StringStringMap<StringType> &m, const StringType &name, StringType &text)
{
    StringStringMap<StringType>::const_iterator it = m.find(name);
    if (it==m.end())
        return false;

    text = it->second;

    return true;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template<typename StringType>
struct MacroTextFromMap : public IMacroTextGetter<StringType>
{
    StringStringMap<StringType> m;

    MacroTextFromMap(const StringStringMap<StringType> &_m) : m(_m) {}

    virtual bool operator()(const StringType &name, StringType &text) const override
    {
        return getMacroTextFromMap(m, name, text);
    }

    const char* getName() const { return "MacroTextFromMap"; }

}; // struct MacroTextFromMap

//------------------------------
template<typename StringType>
struct MacroTextFromMapRef : public IMacroTextGetter<StringType>
{
    const StringStringMap<StringType> &m;

    MacroTextFromMapRef(const StringStringMap<StringType> &_m) : m(_m) {}

    virtual bool operator()(const StringType &name, StringType &text) const override
    {
        return getMacroTextFromMap(m, name, text);
    }

    const char* getName() const { return "MacroTextFromMapRef"; }

}; // struct MacroTextFromMapRef

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template<typename StreamType, typename StringType>
StreamType& printMacros( StreamType &oss, const StringType &prefix, const StringStringMap<StringType> &macros )
{
    StringStringMap<StringType>::const_iterator it = macros.begin();

    std::size_t maxName = 0;

    // Scan for max name len

    for(; it!=macros.end(); ++it)
    {
        if (it->first.size()>maxName)
            maxName = it->first.size();
    }


    it = macros.begin();

    for(; it!=macros.end(); ++it)
    {
        auto fillStr = StringType( maxName - it->first.size() + 1, ' ');
        oss << prefix << it->first << fillStr << " : " << it->second << "\n";
    }

    return oss;
}


//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

} // namespace macros
} // namespace marty_tr

// marty_tr::macros::



