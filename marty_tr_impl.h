#pragma once

#include "enums_decl.h"
#include "locales.h"

#include "marty_yaml_toml_json/json_utils.h"
#include "marty_yaml_toml_json/yaml_json.h"

#include <nlohmann/json.hpp>

#include <exception>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>



//----------------------------------------------------------------------------
#ifndef MARTY_ARG_USED

    //! Подавление варнинга о неиспользованном аргументе
    #define MARTY_ARG_USED(x)                   (void)(x)

#endif

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
namespace marty_tr {



//----------------------------------------------------------------------------

// https://en.cppreference.com/w/cpp/language/type_alias
#if defined(DEBUG) || defined(_DEBUG)

    // При отладке удобнее разглядывать std::map

    template<typename StringType>
    using StringStringMap = std::map<StringType,StringType>;

    template<typename StringType>
    using StringSet = std::set<StringType>;

    typedef StringStringMap<std::string>                                    translations_map_t;
    typedef std::map<std::string,translations_map_t>                        category_translations_map_t;
    typedef std::map<std::string,category_translations_map_t>               all_translations_map_t;

#else

    // В релизе std::unordered_map быстрее
    template<typename StringType>
    using StringStringMap = std::unordered_map<StringType,StringType>;

    template<typename StringType>
    using StringSet = std::unordered_set<StringType>;

    template<typename StringType>
    using StringSet = std::unordered_set<StringType>;

    typedef StringStringMap<std::string>                                    translations_map_t;
    typedef std::unordered_map<std::string,translations_map_t>              category_translations_map_t;
    typedef std::unordered_map<std::string,category_translations_map_t>     all_translations_map_t;

#endif



//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
enum class MsgNotFound
{
    msg,
    cat,
    lang
};


inline
std::string to_string(MsgNotFound m)
{
    switch(m)
    {
        case MsgNotFound::msg : return "message";
        case MsgNotFound::cat : return "category";
        case MsgNotFound::lang: return "language";
        default:            return "";
    }
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
std::string to_ascii(const char* str)
{
    return str ? std::string(str) : std::string();
}

inline
std::string to_ascii(const std::string &str)
{
    return str;
}

inline
std::string to_ascii(const std::wstring &str)
{
    std::string strRes; strRes.reserve(str.size());
    for (auto ch : str)
    {
        strRes.append(1, (char)(unsigned char)ch);
    }
    return strRes;
}

inline
std::string to_ascii(const wchar_t* str)
{
    return str ? to_ascii(std::wstring(str)) : std::string();
}

//------------------------------
inline
std::wstring to_wide(const wchar_t* str)
{
    return str ? std::wstring(str) : std::wstring();
}

inline
std::wstring to_wide(const std::wstring &str)
{
    return str;
}

inline
std::wstring to_wide(const std::string &str)
{
    std::wstring strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (wchar_t)(unsigned char)ch);
    return strRes;
}

inline
std::wstring to_wide(const char* str)
{
    return str ? to_wide(std::string(str)) : std::wstring();
}

//------------------------------
template<typename ResultStringType, typename StringType>
ResultStringType to_string_type(StringType s)
{
    if constexpr (sizeof(typename ResultStringType::value_type)>1)
        return to_wide(s);
    else
        return to_ascii(s);
}


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct IErrReportHandler
{
    virtual ~IErrReportHandler() {}
    virtual void messageNotFound(MsgNotFound what, const std::string& msg, const std::string& catId, const std::string& langId) = 0;

    //! return true if overwriting prev value allowed
    virtual bool translationAlreadyExist(const std::string& msgId, const std::string& msgPrev, const std::string& msgNew, const std::string& catId, const std::string& langId) = 0;

    //! Сообщение не полностью переведено
    virtual void messageNotFullyTranslated(const std::string& catId, const std::string& msgId) = 0;

    virtual void messageMissingTranslation(const std::string& lang, const std::string& langTag) = 0;

};

typedef IErrReportHandler* IErrReportHandlerPtr;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DefaultMessageNotFoundHandler
{
    void operator()(MsgNotFound what, const std::string& msg, const std::string& catId, const std::string& langId) const
    {
        MARTY_ARG_USED(what);
        MARTY_ARG_USED(msg);
        MARTY_ARG_USED(catId);
        MARTY_ARG_USED(langId);
    }
};

//------------------------------
struct DefaultTranslationAlreadyExistHandler
{
    bool operator()(const std::string& msgId, const std::string& msgPrev, const std::string& msgNew, const std::string& catId, const std::string& langId) const
    {
        MARTY_ARG_USED(msgId);
        MARTY_ARG_USED(msgPrev);
        MARTY_ARG_USED(msgNew);
        MARTY_ARG_USED(catId);
        MARTY_ARG_USED(langId);
        return true; // allow overwite
    }
};

//------------------------------
struct DefaultMessageNotFullyTranslatedHandler
{
    void operator()(const std::string& catId, const std::string& msgId) const
    {
        MARTY_ARG_USED(catId);
        MARTY_ARG_USED(msgId);
    }
};

//------------------------------
struct DefaultMessageMissingTranslationHandler
{
    void operator()(const std::string& lang, const std::string& langTag) const
    {
        MARTY_ARG_USED(lang);
        MARTY_ARG_USED(langTag);
    }
};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template< typename MessageNotFoundHandler
        , typename TranslationAlreadyExistHandler
        , typename MessageNotFullyTranslatedHandler
        , typename MessageMissingTranslationHandler
        >
struct ErrReportHandler : public IErrReportHandler
{
    MessageNotFoundHandler             messageNotFoundHandler;
    TranslationAlreadyExistHandler     translationAlreadyExistHandler;
    MessageNotFullyTranslatedHandler   messageNotFullyTranslatedHandler;
    MessageMissingTranslationHandler   messageMissingTranslationHandler;

    ErrReportHandler( MessageNotFoundHandler            mnfHandler
                    , TranslationAlreadyExistHandler    taeHandler
                    , MessageNotFullyTranslatedHandler  mnftHandler
                    , MessageMissingTranslationHandler  mmtHandler
                    )
    : messageNotFoundHandler(mnfHandler)
    , translationAlreadyExistHandler(taeHandler)
    , messageNotFullyTranslatedHandler(mnftHandler)
    , messageMissingTranslationHandler(mmtHandler)
    {}

    virtual void messageNotFound(MsgNotFound what, const std::string& msg, const std::string& catId, const std::string& langId) override
    {
        messageNotFoundHandler(what, msg, catId, langId);
    }

    virtual bool translationAlreadyExist(const std::string& msgId, const std::string& msgPrev, const std::string& msgNew, const std::string& catId, const std::string& langId) override
    {
        return translationAlreadyExistHandler(msgId, msgPrev, msgNew, catId, langId);
    }

    virtual void messageNotFullyTranslated(const std::string& catId, const std::string& msgId) override
    {
        messageNotFullyTranslatedHandler(catId, msgId);
    }
     
    virtual void messageMissingTranslation(const std::string& lang, const std::string& lanfTag) override
    {
        messageMissingTranslationHandler(lang, lanfTag);
    }


};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template< typename MessageNotFoundHandler             = DefaultMessageNotFoundHandler
        , typename TranslationAlreadyExistHandler     = DefaultTranslationAlreadyExistHandler
        , typename MessageNotFullyTranslatedHandler   = DefaultMessageNotFullyTranslatedHandler
        , typename MessageMissingTranslationHandler   = DefaultMessageMissingTranslationHandler
        > inline
ErrReportHandler< MessageNotFoundHandler
                , TranslationAlreadyExistHandler
                , MessageNotFullyTranslatedHandler
                , MessageMissingTranslationHandler
                > 
makeErrReportHandler( MessageNotFoundHandler           mnfHandler   = DefaultMessageNotFoundHandler()
                    , TranslationAlreadyExistHandler   taeHandler   = DefaultTranslationAlreadyExistHandler()
                    , MessageNotFullyTranslatedHandler mnftHandler  = DefaultMessageNotFullyTranslatedHandler()
                    , MessageMissingTranslationHandler mmtHandler   = DefaultMessageMissingTranslationHandler()
                    )
{
    return ErrReportHandler< MessageNotFoundHandler
                           , TranslationAlreadyExistHandler
                           , MessageNotFullyTranslatedHandler
                           , MessageMissingTranslationHandler
                           >
                           (mnfHandler, taeHandler, mnftHandler, mmtHandler);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace impl_helpers {

inline
IErrReportHandlerPtr& tr_get_err_handler()
{
    static IErrReportHandlerPtr ph = 0;
    return ph;
}

inline
ELangTagFormat& tr_get_lang_tag_format()
{
    static ELangTagFormat fmt = ELangTagFormat::langIdFull; // 0409
    return fmt;
}


} // namespace impl_helpers

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
IErrReportHandlerPtr tr_get_err_handler()
{
    IErrReportHandlerPtr ph = impl_helpers::tr_get_err_handler();
    return ph;
}

inline
IErrReportHandlerPtr tr_set_err_handler(IErrReportHandlerPtr newPh)
{
    auto ph = impl_helpers::tr_get_err_handler();
    impl_helpers::tr_get_err_handler() = newPh;
    return ph;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
ELangTagFormat tr_get_lang_tag_format()
{
    return impl_helpers::tr_get_lang_tag_format();
}

inline
ELangTagFormat tr_set_lang_tag_format(ELangTagFormat newFmt)
{
    auto res = impl_helpers::tr_get_lang_tag_format();
    if (newFmt!=ELangTagFormat::langTagNeutral && newFmt!=ELangTagFormat::langTagNeutralAuto)
    {
        impl_helpers::tr_get_lang_tag_format() = newFmt;
    }
    return res;
}

inline
std::string tr_fix_lang_tag_format(const std::string &langTagOrId)
{
    return formatLangTag(langTagOrId, tr_get_lang_tag_format());
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
std::string tr_fix_category(const std::string &catId)
{
    std::string newCatId; newCatId.reserve(catId.size());

    for(auto ch : catId)
    {
        if (ch=='\\' || ch==':' || ch=='.')
            ch = '/';

        if (ch=='/' && !newCatId.empty() && newCatId.back()=='/')
            continue; // skip double separators

        newCatId.append(1, ch);
    }

    return newCatId;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
all_translations_map_t tr_parse_translations_data(const std::string &trJson)
{
    std::string errMsg;
    std::string tmpJson;
    marty::json_utils::FileFormat detectedFormat = marty::json_utils::FileFormat::unknown;
    nlohmann::json jAll = marty::json_utils::parseJsonOrYaml( trJson, true /* allowComments */ , &errMsg, &tmpJson, &detectedFormat );

    if (detectedFormat==marty::json_utils::FileFormat::unknown)
    {
        std::ostringstream oss;
        oss <<  /* encodingApi.encode(fileName) << ":  */ "error: " << errMsg << "\n";
        if (!tmpJson.empty())
        {
            oss << "JSON:" << "\n";
            oss << tmpJson << "\n";
        }
        
        throw std::runtime_error(oss.str());
    }


    all_translations_map_t  all_translations_map;

    for (nlohmann::json::iterator jitLang=jAll.begin(); jitLang!=jAll.end(); ++jitLang)
    {
        std::string langId  = jitLang.key();
        auto &jCategory     = jitLang.value();

        langId = tr_fix_lang_tag_format(langId);

        category_translations_map_t  category_translations_map;

        for(nlohmann::json::iterator jitCat=jCategory.begin(); jitCat!=jCategory.end(); ++jitCat)
        {
            std::string catId  = jitCat.key();
            auto &jTranslation = jitCat.value();

            catId = tr_fix_category(catId);

            translations_map_t  translations_map;

            for(nlohmann::json::iterator jitTr=jTranslation.begin(); jitTr!=jTranslation.end(); ++jitTr)
            {
                const auto &msgId  = jitTr.key();
                auto &jMsg         = jitTr.value();
                auto msgText       = jMsg.get<std::string>();
                translations_map[msgId] = msgText;
            }

            category_translations_map[catId] = translations_map;
        }

        all_translations_map[langId] = category_translations_map;
    }

    return all_translations_map;
}

//----------------------------------------------------------------------------
inline
std::string tr_serialize_translations(const all_translations_map_t &trMap, unsigned indent=2)
{
    nlohmann::json jLang; // = nlohmann::json::object();

    if (indent>8)
        indent = 8;

    for(const auto &langKvp : trMap)
    {
        const auto &langId  = langKvp.first;
        const auto &catMap  = langKvp.second;
        nlohmann::json jCat; // = nlohmann::json::object();

        for(const auto &catKvp : catMap)
        {
            const auto &catId   = catKvp.first;
            const auto &msgMap  = catKvp.second;
            nlohmann::json jMsg; // = nlohmann::json::object();

            for(const auto &msgKvp : msgMap)
            {
                const auto &msgId   = msgKvp.first;
                const auto &msgText = msgKvp.second;
                // ...
                jMsg[msgId] = msgText;
            }

            jCat[catId] = jMsg;
        }

        jLang[langId] = jCat;
    }

    std::string strFromJ = jLang.dump((int)indent);

    return strFromJ;
}


//----------------------------------------------------------------------------
inline
all_translations_map_t& tr_get_all_translations()
{
    static all_translations_map_t m;
    return m;
}

//----------------------------------------------------------------------------
inline 
void tr_init_all_translations(const std::string &trJson)
{
    tr_get_all_translations() = tr_parse_translations_data(trJson);
}

//----------------------------------------------------------------------------
inline
void tr_add_custom_translations(const all_translations_map_t &customTrMap)
{
    all_translations_map_t& trAllMap = tr_get_all_translations();

    IErrReportHandlerPtr errHandler = tr_get_err_handler();
    auto handleTranslationAlreadyExist = [&](const std::string& msgId, const std::string& msgPrev, const std::string& msgNew, const std::string& catId, const std::string& langId) -> bool
    {
        if (!errHandler)
            return true; // allow overwrite

        return errHandler->translationAlreadyExist(msgId, msgPrev, msgNew, catId, langId);
    };


    for(const auto &langKvp : customTrMap)
    {
        const auto &langId  = langKvp.first;
        const auto &catMap  = langKvp.second;

        for(const auto &catKvp : catMap)
        {
            const auto &catId  = catKvp.first;
            const auto &msgMap = catKvp.second;

            for(const auto &msgKvp : msgMap)
            {
                const auto &msgId   = msgKvp.first;
                const auto &msgText = msgKvp.second;

                translations_map_t &trMap = trAllMap[langId][catId];
                translations_map_t::iterator it = trMap.find(msgId);

                bool existNotSame = false;
                if (it!=trMap.end())
                {
                    if (it->second!=msgText)
                        existNotSame = true;
                }

                if (!existNotSame || handleTranslationAlreadyExist(msgId, it->second, msgText, catId, langId))
                {
                    trMap[msgId] = msgText; // overwrite prev or add new
                }

                //trMap[langId][catId][msgId] = msgText;
                //trMap[msgId] = msgText;
            }
        }
    }
}

//----------------------------------------------------------------------------
inline
void tr_add_custom_translations(const std::string &trJson)
{
    all_translations_map_t customTrMap = tr_parse_translations_data(trJson);
    tr_add_custom_translations(customTrMap);
}

// typedef std::unordered_map<std::string,std::string>                     translations_map_t;
// typedef std::unordered_map<std::string,translations_map_t>              category_translations_map_t;
// typedef std::unordered_map<std::string,category_translations_map_t>     all_translations_map_t;

//----------------------------------------------------------------------------
inline
bool tr_has_category(const all_translations_map_t &trMap, std::string catId)
{
    catId = tr_fix_category(catId);

    for(const auto &langKvp : trMap)
    {
        // const std::string &langId                      = langKvp.first; // not used
        const category_translations_map_t &catMap      = langKvp.second;
        category_translations_map_t::const_iterator it = catMap.find(catId);
        if (it!=catMap.end())
            return true; // category found
    }

    return false;
}

//----------------------------------------------------------------------------
inline
bool tr_replace_category(all_translations_map_t &trMap, std::string prevCatId, std::string newCatId)
{
    prevCatId = tr_fix_category(prevCatId);
    newCatId  = tr_fix_category(newCatId);

    // Надо проверить, есть ли уже такая категория
    // Потому что при переименовании будет производится замена имени существующей категории, и новое имя может
    // совпадать с каким-то уже имеющися, а переименование не подразумевает слияния

    if (tr_has_category(trMap, newCatId))
        return false;

    for(auto &langKvp : trMap)
    {
        // const std::string &langId                       = langKvp.first; // not used
        category_translations_map_t &catMap             = langKvp.second;
        category_translations_map_t::const_iterator nit = catMap.find(prevCatId);
        if (nit!=catMap.end())
        {
            auto nh  = catMap.extract(nit);
            nh.key() = newCatId;
            catMap.insert(std::move(nh));
        }
    }

    return true; // Переименование прошло без ошибок (возможно, по факту ничего не было сделано, так как искомой prevCatId категории нет, но это не важно)
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
namespace impl_helpers {

inline
std::string& tr_get_def_category()
{
    static std::string n = "common";
    return n;
}

inline
std::string& tr_get_def_lang()
{
    #if defined(WIN32) || defined(_WIN32)
        static std::string n = "0409";
    #else
        static std::string n = "en-US";
    #endif

    return n;
}

inline
bool& tr_get_msg_not_found_decorate_mode()
{
    static bool mode = true;
    return mode;
}

inline
bool& tr_get_empty_msg_not_exist()
{
    static bool mode = false;
    return mode;
}



} // namespace impl_helpers

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
std::string tr_get_def_category()
{
    return impl_helpers::tr_get_def_category();
}

//----------------------------------------------------------------------------
inline
std::string tr_set_def_category(const std::string &c)
{
    std::string res = impl_helpers::tr_get_def_category();
    impl_helpers::tr_get_def_category() = c;
    return res;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
std::string tr_get_def_lang()
{
    return impl_helpers::tr_get_def_lang();
}

//----------------------------------------------------------------------------
inline
std::string tr_set_def_lang(const std::string &l)
{
    std::string res = impl_helpers::tr_get_def_lang();
    impl_helpers::tr_get_def_lang() = l;
    return res;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
bool tr_get_msg_not_found_decorate_mode()
{
    return impl_helpers::tr_get_msg_not_found_decorate_mode();
}

//----------------------------------------------------------------------------
inline
bool tr_set_msg_not_found_decorate_mode(bool newMode)
{
    bool res = impl_helpers::tr_get_msg_not_found_decorate_mode();
    impl_helpers::tr_get_msg_not_found_decorate_mode() = newMode;
    return res;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
bool tr_get_empty_msg_not_exist()
{
    return impl_helpers::tr_get_empty_msg_not_exist();
}

//----------------------------------------------------------------------------
inline
bool tr_set_empty_msg_not_exist(bool mode)
{
    bool res = impl_helpers::tr_get_empty_msg_not_exist();
    impl_helpers::tr_get_empty_msg_not_exist() = mode;
    return res;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// Main functionality
//----------------------------------------------------------------------------


// enum class MsgNotFound
// {
//     msg,
//     cat,
//     lang
// };


//----------------------------------------------------------------------------
// std::string tr_fix_lang_tag_format(const std::string &langTagOrId)
// std::string tr_fix_category(const std::string &catId)

inline
std::string tr(const std::string &msgId, std::string catId, std::string langId)
{
    const all_translations_map_t& trAllMap = tr_get_all_translations();

    catId  = tr_fix_category(catId);
    langId = tr_fix_lang_tag_format(langId);

    auto reportTrNotFound = [=](MsgNotFound what) // 0 - msg, 1 - cat, 2 - lang
        {
            // lambda [=] - похоже захватывает по константе или как-то так (хотя вроде должно по значению)
            // Делаем руцками копию
            // Лениво разбираться чо как

            std::string msgId_   = msgId;
            std::string catId_   = catId;
            std::string langId_  = langId;

            // auto orgMsg = msg;
            auto handler = tr_get_err_handler();
            if (handler)
            {
                switch(what)
                {
                    case MsgNotFound::msg : msgId_  =  /* std::string("!") +  */ msgId_ ; break;
                    case MsgNotFound::cat : catId_  =  /* std::string("!") +  */ catId_ ; break;
                    case MsgNotFound::lang: langId_ =  /* std::string("!") +  */ langId_; break;
                }
                handler->messageNotFound(what, msgId_, catId_, langId_);
            }

            if (!tr_get_msg_not_found_decorate_mode())
               return msgId; // orgMsg;

            return "![" + msgId + "]";
        };

    all_translations_map_t::const_iterator lit = trAllMap.find(langId);
    if (lit==trAllMap.end())
        return reportTrNotFound(MsgNotFound::lang);


    const category_translations_map_t &catMap = lit->second;

    category_translations_map_t::const_iterator cit = catMap.find(catId);
    if (cit==catMap.end())
        return reportTrNotFound(MsgNotFound::cat);


    const translations_map_t &trMap = cit->second;

    translations_map_t::const_iterator mit = trMap.find(msgId);
    if (mit==trMap.end())
        return reportTrNotFound(MsgNotFound::msg);

    if (tr_get_empty_msg_not_exist() && mit->second.empty())
        return reportTrNotFound(MsgNotFound::msg);

    return mit->second;
}

//----------------------------------------------------------------------------
inline
bool tr_has_msg(const std::string &msgId, std::string catId, std::string langId)
{
    const all_translations_map_t& trAllMap = tr_get_all_translations();

    catId  = tr_fix_category(catId);
    langId = tr_fix_lang_tag_format(langId);

    all_translations_map_t::const_iterator lit = trAllMap.find(langId);
    if (lit==trAllMap.end())
    {
        return false;
    }

    const category_translations_map_t &catMap = lit->second;

    category_translations_map_t::const_iterator cit = catMap.find(catId);
    if (cit==catMap.end())
    {
        return false;
    }

    const translations_map_t &trMap = cit->second;

    translations_map_t::const_iterator mit = trMap.find(msgId);
    //if (mit==trMap.end())
    if (mit==trMap.end())
    {
        return false;
    }

    if (tr_get_empty_msg_not_exist() && mit->second.empty())
    {
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------
inline
bool tr_has_msg(const std::string &msgId, std::string catId)
{
    return tr_has_msg(msgId, catId, tr_get_def_lang());
}

//----------------------------------------------------------------------------
inline
bool tr_has_msg(const std::string &msgId)
{
    return tr_has_msg(msgId, tr_get_def_category(), tr_get_def_lang());
}

//----------------------------------------------------------------------------
// inline
// bool tr_has_message(const all_translations_map_t &trMap, std::string msgId, std::string catId)
// {
//     catId = tr_fix_category(catId);
//  
//     for(const auto &langKvp : trMap)
//     {
//         // const std::string &langId                      = langKvp.first; // not used
//         const category_translations_map_t &catMap      = langKvp.second;
//         category_translations_map_t::const_iterator it = catMap.find(catId);
//         if (it!=catMap.end())
//             return true; // category found
//     }
//  
//     return false;
// }


//----------------------------------------------------------------------------
inline
std::string tr(const std::string &msgId, const std::string &catId)
{
    return tr(msgId, catId, tr_get_def_lang());
}

//----------------------------------------------------------------------------
inline
std::string tr(const std::string &msgId)
{
    return tr(msgId, tr_get_def_category(), tr_get_def_lang());
}

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
inline
void tr_add(const std::string &msgId, const std::string &msgText, std::string catId, std::string langId)
{
    all_translations_map_t& trAllMap = tr_get_all_translations();

    catId  = tr_fix_category(catId);
    langId = tr_fix_lang_tag_format(langId);

    trAllMap[langId][catId][msgId] = msgText;
}

//------------------------------
inline
void tr_add(const std::string &msgId, const std::string &msgText, const std::string &catId)
{
    tr_add(msgId, msgText, catId, tr_get_def_lang());
}

//------------------------------
inline
void tr_add(const std::string &msgId, const std::string &msgText)
{
    tr_add(msgId, msgText, tr_get_def_category(), tr_get_def_lang());
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
void tr_add_if_empty(const std::string &msgId, const std::string &msgText, std::string catId, std::string langId)
{
    if (tr_has_msg(msgId, catId, langId))
    {
        return;
    }

    all_translations_map_t& trAllMap = tr_get_all_translations();

    catId  = tr_fix_category(catId);
    langId = tr_fix_lang_tag_format(langId);

    trAllMap[langId][catId][msgId] = msgText;
}

//------------------------------
inline
void tr_add_if_empty(const std::string &msgId, const std::string &msgText, const std::string &catId)
{
    tr_add_if_empty(msgId, msgText, catId, tr_get_def_lang());
}

//------------------------------
inline
void tr_add_if_empty(const std::string &msgId, const std::string &msgText)
{
    tr_add_if_empty(msgId, msgText, tr_get_def_category(), tr_get_def_lang());
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename THandler> inline
void tr_enumerate_msgids(THandler handler, std::string catId, std::string langId)
{
    all_translations_map_t& trAllMap = tr_get_all_translations();

    catId  = tr_fix_category(catId);
    langId = tr_fix_lang_tag_format(langId);

    all_translations_map_t::const_iterator lit = trAllMap.find(langId);
    if (lit==trAllMap.end())
        return; // No lang found


    const category_translations_map_t &catMap = lit->second;

    category_translations_map_t::const_iterator cit = catMap.find(catId);
    if (cit==catMap.end())
        return;


    const translations_map_t &trMap = cit->second;
    translations_map_t::const_iterator mit = trMap.begin();
    for(; mit!=trMap.end(); ++mit)
    {
        handler(mit->first);
    }
}

//----------------------------------------------------------------------------
// Тут отличие от остального API - вместо установленного по дефолту языка используем 
// всегда en-US для перечисления сообщений в категории, считая, что en-US - эталонная
// трансляция и там всё есть
template<typename THandler> inline
void tr_enumerate_msgids(THandler handler, std::string catId)
{
    tr_enumerate_msgids(handler, catId, "en-US");
}

//----------------------------------------------------------------------------
inline
std::vector<std::string> tr_get_msgids(std::string catId, std::string langId)
{
    std::vector<std::string> res; res.reserve(32);

    tr_enumerate_msgids( [&](const std::string &msgId)
                         {
                             res.emplace_back(msgId);
                         }
                       , catId, langId
                       );
    return res;
}

//----------------------------------------------------------------------------
inline
std::vector<std::string> tr_get_msgids(std::string catId)
{
    std::vector<std::string> res; res.reserve(32);

    tr_enumerate_msgids( [&](const std::string &msgId)
                         {
                             res.emplace_back(msgId);
                         }
                       , catId
                       );
    return res;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
bool tr_check_translation_completeness()
{
    unsigned errCnt = 0;

    auto allTrMap = marty_tr::tr_get_all_translations();

    std::set<std::string>                          foundLangs;
    std::map<std::string, std::set<std::string> >  msgLangs;

    IErrReportHandlerPtr errHandler = tr_get_err_handler();
    auto handleNotFullyTranslated = [&](const std::string& catId, const std::string& msgId)
    {
        if (!errHandler)
            return;

        return errHandler->messageNotFullyTranslated(catId, msgId);
    };

    auto handleMissingTranslation = [&](const std::string& lang, const std::string& langTag)
    {
        if (!errHandler)
            return;

        return errHandler->messageMissingTranslation(lang, langTag);
    };

    // Пробегаемся по всем языкам, для каждого языка пробегаемся по категориям и сообщениям.

    for(const auto &langKvp : allTrMap)
    {
        const auto &langId  = langKvp.first;
        const auto &catMap  = langKvp.second;

        foundLangs.insert(langId);

        for(const auto &catKvp : catMap)
        {
            const auto &catId  = catKvp.first;
            const auto &msgMap = catKvp.second;

            for(const auto &msgKvp : msgMap)
            {
                const auto &msgId   = msgKvp.first;
                // const auto &msgText = msgKvp.second; // not used

                // Склеиваем категорию:сообщение в ключ, и инкрементируем элемент map по этому ключу.

                std::string msgFullId = catId + std::string(":") + msgId;

                msgLangs[msgFullId].insert(langId); // add found translation
            }

        } // cat

    } // lang


    for(const auto &msgCatKvp : msgLangs)
    {
        const auto &msgCat   = msgCatKvp.first;
        const auto &msgLangs2 = msgCatKvp.second;

        if (msgLangs2.size()!=foundLangs.size())
        {
            ++errCnt;

            std::string::size_type sepPos = msgCat.find(':');
            if (sepPos==msgCat.npos)
                handleNotFullyTranslated(msgCat, std::string());
            else
                handleNotFullyTranslated(std::string(msgCat, 0, sepPos), std::string(msgCat, sepPos+1));


            // iterate through all found langs
            for(const auto &lang : foundLangs)
            {
                std::set<std::string>::const_iterator it = msgLangs2.find(lang);
                if (it==msgLangs2.end()) // если язык не найден для данного сообщения, то выводим сообщение
                {
                    auto langTag = marty_tr::formatLangTag(lang, marty_tr::ELangTagFormat::langTag);
                    handleMissingTranslation(lang,langTag);
                }

            } // for(const auto &lang : foundLangs)
        
        } // if (msgLangs2.size()!=foundLangs.size())

    } // for(const auto &msgCatKvp : msgLangs2)

    return errCnt==0;
}




//----------------------------------------------------------------------------


} // namespace marty_tr



//----------------------------------------------------------------------------



