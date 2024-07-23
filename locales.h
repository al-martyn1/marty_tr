#pragma once

#include "enums_decl.h"

#include <algorithm>
#include <cstdint>
#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



//----------------------------------------------------------------------------
#ifndef MARTY_ARG_USED

    //! Подавление варнинга о неиспользованном аргументе
    #define MARTY_ARG_USED(x)                   (void)(x)

#endif

//----------------------------------------------------------------------------



namespace marty_tr {


/*
Language Identifiers
+-------------------------+-------------------------+
|     SubLanguage ID      |   Primary Language ID   |
+-------------------------+-------------------------+
15                    10  9                         0   bit
        6 bit                       10 bit

        0x3F max                    0x3FF max
*/

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4623) // warning C4623: 'class': default constructor was implicitly defined as deleted
#endif

struct LocaleInfo
{
    const char* const    lang    ;
    const char* const    location; // or type
    unsigned    const    langId  ; // Windows Language Identifier (Language ID, which is a part of the Windows Language Code Identifier - LCID)
    const char* const    ltag    ; // Language tag (locale name), en-US etc...
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


struct StringLocaleInfo
{
    std::string          lang    ;
    std::string          location; // or type
    unsigned             langId  ; // Windows Language Identifier (Language ID, which is a part of the Windows Language Code Identifier - LCID)
    std::string          ltag    ; // Language tag (locale name), en-US etc...

    StringLocaleInfo(const LocaleInfo &li)
    {
        if (li.lang)
            lang = li.lang;

        if (li.location)
            location = li.location;

        if (li.ltag)
            ltag = li.ltag;

        langId = li.langId;
    }

    StringLocaleInfo() = default;
    StringLocaleInfo(const StringLocaleInfo&) = default;
    StringLocaleInfo& operator=(const StringLocaleInfo&) = default;
    StringLocaleInfo(StringLocaleInfo&&) = default;
    StringLocaleInfo& operator=(StringLocaleInfo&&) = default;



};



// Locale names that are valid but not associated with a given LCID MAY be assigned the LCID Language ID 0x1000, if an LCID is requested by the application


#define MARTY_TR_LOCALEINFO_MAKE(lng, locType, id, nm, releaseStr)    { lng, locType, id, nm    }

#define MARTY_TR_LOCALEINFO_MAKES(lng, locType, id, nm, releaseStr)   { #lng, #locType, id, #nm }

const LocaleInfo* getLocalesInfo( std::size_t *pSize )
{
    static LocaleInfo localeInfo[] =
    {
        /*
            Release key      Supported versions
            Release A        First available in Windows NT 3.51. Supported in all later versions.
            Release B        First available in Windows NT Server 4.0 operating system. Supported in all later versions.
            Release C        First available in Windows 2000. Supported in all later versions.
            Release D        First available in Windows XP and Windows Server 2003. Supported in all later versions.
            Release E1       First available in Windows XP ELK v1 for Windows XP SP2, Windows Server 2003, Windows Vista, and Windows Server 2008. Supported in all later client and server versions of Windows.
            Release E2       First available in Windows XP ELK v2 for Windows XP SP2, Windows Server 2003, Windows Vista, and Windows Server 2008. Supported in all later client and server versions of Windows.
            Release V        First available in Windows Server 2008 and Windows Vista. Supported in all later versions.
            Release 7        First available in Windows 7 and Windows Server 2008 R2. Supported in all later versions.
            Release 8        First available in Windows 8 and Windows Server 2012. Supported in all later versions
            Release 8.1      First available in Windows 8.1 and Windows Server 2012 R2. Supported in all later versions.
            Release 10       First available in Windows 10 and Windows Server 2016. Supported in all later versions.
            Release 10.1     First available in Windows 10 v1607 operating system and Windows Server 2016. Supported in all later versions.
            Release 10.2     First available in Windows 10 v1703 operating system. Supported in all later versions.
            Release 10.3     First available in Windows 10 v1709 operating system and Windows Server operating system. Supported in all later versions.
            Release 10.4     First available in Windows 10 v1903 operating system and Windows Server v1903 operating system. Supported in all later versions.
        */

        //                                                                                                                  Language Language        Supported
        //                                  Language                                      Location (or type)                   ID      tag            version
        MARTY_TR_LOCALEINFO_MAKES(Afar                                  ,                                                 _, 0x1000, aa            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Afar                                  ,                                          Djibouti, 0x1000, aa-DJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Afar                                  ,                                           Eritrea, 0x1000, aa-ER         , Release 10 Afar ),
        MARTY_TR_LOCALEINFO_MAKES(Ethiopia                              ,                                                 _, 0x1000, aa-ET         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Afrikaans                             ,                                                 _, 0x0036, af            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Afrikaans                             ,                                           Namibia, 0x1000, af-NA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Afrikaans                             ,                                      South Africa, 0x0436, af-ZA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Aghem                                 ,                                                 _, 0x1000, agq           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Aghem                                 ,                                          Cameroon, 0x1000, agq-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Akan                                  ,                                                 _, 0x1000, ak            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Akan                                  ,                                             Ghana, 0x1000, ak-GH         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Albanian                              ,                                                 _, 0x001C, sq            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Albanian                              ,                                           Albania, 0x041C, sq-AL         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Albanian                              ,                                   North Macedonia, 0x1000, sq-MK         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Alsatian                              ,                                                 _, 0x0084, gsw           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Alsatian                              ,                                            France, 0x0484, gsw-FR        , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Alsatian                              ,                                     Liechtenstein, 0x1000, gsw-LI        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Alsatian                              ,                                       Switzerland, 0x1000, gsw-CH        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Amharic                               ,                                                 _, 0x005E, am            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Amharic                               ,                                          Ethiopia, 0x045E, am-ET         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                                 _, 0x0001, ar            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Algeria, 0x1401, ar-DZ         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Bahrain, 0x3C01, ar-BH         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                              Chad, 0x1000, ar-TD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Comoros, 0x1000, ar-KM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                          Djibouti, 0x1000, ar-DJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Egypt, 0x0c01, ar-EG         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Eritrea, 0x1000, ar-ER         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                              Iraq, 0x0801, ar-IQ         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                            Israel, 0x1000, ar-IL         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                            Jordan, 0x2C01, ar-JO         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                            Kuwait, 0x3401, ar-KW         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Lebanon, 0x3001, ar-LB         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Libya, 0x1001, ar-LY         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                        Mauritania, 0x1000, ar-MR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Morocco, 0x1801, ar-MA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                              Oman, 0x2001, ar-OM         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                             Palestinian Authority, 0x1000, ar-PS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Qatar, 0x4001, ar-QA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                      Saudi Arabia, 0x0401, ar-SA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Somalia, 0x1000, ar-SO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                       South Sudan, 0x1000, ar-SS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Sudan, 0x1000, ar-SD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Syria, 0x2801, ar-SY         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                           Tunisia, 0x1C01, ar-TN         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                            U.A.E., 0x3801, ar-AE         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             World, 0x1000, ar-001        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Arabic                                ,                                             Yemen, 0x2401, ar-YE         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Armenian                              ,                                                 _, 0x002B, hy            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Armenian                              ,                                           Armenia, 0x042B, hy-AM         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Assamese                              ,                                                 _, 0x004D, as            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Assamese                              ,                                             India, 0x044D, as-IN         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Asturian                              ,                                                 _, 0x1000, ast           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Asturian                              ,                                             Spain, 0x1000, ast-ES        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Asu                                   ,                                                 _, 0x1000, asa           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Asu                                   ,                                          Tanzania, 0x1000, asa-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Azerbaijani (Cyrillic)                ,                                                 _, 0x742C, az-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Azerbaijani (Cyrillic)                ,                                        Azerbaijan, 0x082C, az-Cyrl-AZ    , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Azerbaijani (Latin)                   ,                                                 _, 0x002C, az            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Azerbaijani (Latin)                   ,                                                 _, 0x782C, az-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Azerbaijani (Latin)                   ,                                        Azerbaijan, 0x042C, az-Latn-AZ    , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Bafia                                 ,                                                 _, 0x1000, ksf           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bafia                                 ,                                          Cameroon, 0x1000, ksf-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bamanankan                            ,                                                 _, 0x1000, bm            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bamanankan (Latin)                    ,                                              Mali, 0x1000, bm-Latn-ML    , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bangla                                ,                                                 _, 0x0045, bn            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bangla                                ,                                        Bangladesh, 0x0845, bn-BD         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Bangla                                ,                                             India, 0x0445, bn-IN         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Basaa                                 ,                                                 _, 0x1000, bas           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Basaa                                 ,                                          Cameroon, 0x1000, bas-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bashkir                               ,                                                 _, 0x006D, ba            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bashkir                               ,                                            Russia, 0x046D, ba-RU         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Basque                                ,                                                 _, 0x002D, eu            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Basque                                ,                                             Spain, 0x042D, eu-ES         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Belarusian                            ,                                                 _, 0x0023, be            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Belarusian                            ,                                           Belarus, 0x0423, be-BY         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Bemba                                 ,                                                 _, 0x1000, bem           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bemba                                 ,                                            Zambia, 0x1000, bem-ZM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bena                                  ,                                                 _, 0x1000, bez           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bena                                  ,                                          Tanzania, 0x1000, bez-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Blin                                  ,                                                 _, 0x1000, byn           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Blin                                  ,                                           Eritrea, 0x1000, byn-ER        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bodo                                  ,                                                 _, 0x1000, brx           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bodo                                  ,                                             India, 0x1000, brx-IN        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Bosnian (Cyrillic)                    ,                                                 _, 0x641A, bs-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bosnian (Cyrillic)                    ,                            Bosnia and Herzegovina, 0x201A, bs-Cyrl-BA    , Release         ),
        MARTY_TR_LOCALEINFO_MAKES(E1 Bosnian (Latin)                    ,                                                 _, 0x681A, bs-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bosnian (Latin)                       ,                                                 _, 0x781A, bs            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bosnian (Latin)                       ,                            Bosnia and Herzegovina, 0x141A, bs-Latn-BA    , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Breton                                ,                                                 _, 0x007E, br            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Breton                                ,                                            France, 0x047E, br-FR         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Bulgarian                             ,                                                 _, 0x0002, bg            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Bulgarian                             ,                                          Bulgaria, 0x0402, bg-BG         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Burmese                               ,                                                 _, 0x0055, my            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Burmese                               ,                                           Myanmar, 0x0455, my-MM         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Catalan                               ,                                                 _, 0x0003, ca            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Catalan                               ,                                           Andorra, 0x1000, ca-AD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Catalan                               ,                                            France, 0x1000, ca-FR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Catalan                               ,                                             Italy, 0x1000, ca-IT         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Catalan                               ,                                             Spain, 0x0403, ca-ES         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Cebuano                               ,                                                 _, 0x1000, ceb           , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Cebuan (Latin)                        ,                                                 _, 0x1000, ceb-Latn      , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Cebuan (Latin)                        ,                                       Philippines, 0x1000, ceb-Latn-PH   , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Central Atlas Tamazight (Latin)       ,                                           Morocco, 0x1000, tzm-Latn-MA   , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Central Kurdish                       ,                                                 _, 0x0092, ku            , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Central Kurdish                       ,                                                 _, 0x7c92, ku-Arab       , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Central Kurdish                       ,                                              Iraq, 0x0492, ku-Arab-IQ    , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Chakma                                ,                                                 _, 0x1000, ccp           , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Chakma                                ,                                            Chakma, 0x1000, ccp-Cakm      , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Chakma                                ,                                        Bangladesh, 0x1000, ccp-Cakm-BD   , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Chakma                                ,                                             India, 0x1000, ccp-Cakm-IN   , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Chechen                               ,                                            Russia, 0x1000, ce-RU         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Cherokee                              ,                                                 _, 0x005C, chr           , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Cherokee                              ,                                                 _, 0x7c5C, chr-Cher      , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Cherokee                              ,                                     United States, 0x045C, chr-Cher-US   , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Chiga                                 ,                                                 _, 0x1000, cgg           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Chiga                                 ,                                            Uganda, 0x1000, cgg-UG        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Simplified)                  ,                                                 _, 0x0004, zh-Hans       , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Simplified)                  ,                                                 _, 0x7804, zh            , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKE ("Chinese (Simplified)"                ,                      "People's Republic of China", 0x0804, "zh-CN"       , "Release A"     ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Simplified)                  ,                                         Singapore, 0x1004, zh-SG         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Traditional)                 ,                                                 _, 0x7C04, zh-Hant       , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Traditional)                 ,                                  Hong Kong S.A.R., 0x0C04, zh-HK         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Traditional)                 ,                                      Macao S.A.R., 0x1404, zh-MO         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Chinese (Traditional)                 ,                                            Taiwan, 0x0404, zh-TW         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Church Slavic                         ,                                            Russia, 0x1000, cu-RU         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Congo Swahili                         ,                                                 _, 0x1000, swc           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Congo Swahili                         ,                                         Congo DRC, 0x1000, swc-CD        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Cornish                               ,                                                 _, 0x1000, kw            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Cornish                               ,                                    United Kingdom, 0x1000, kw-GB         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Corsican                              ,                                                 _, 0x0083, co            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Corsican                              ,                                            France, 0x0483, co-FR         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Croatian                              ,                                                 _, 0x001A, hr            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Croatian                              ,                                           Croatia, 0x041A, hr-HR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Croatian (Latin)                      ,                            Bosnia and Herzegovina, 0x101A, hr-BA         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Czech                                 ,                                                 _, 0x0005, cs            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Czech                                 ,                                    Czech Republic, 0x0405, cs-CZ         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Danish                                ,                                                 _, 0x0006, da            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Danish                                ,                                           Denmark, 0x0406, da-DK         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Danish                                ,                                         Greenland, 0x1000, da-GL         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dari                                  ,                                                 _, 0x008C, prs           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Dari                                  ,                                       Afghanistan, 0x048C, prs-AF        , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Divehi                                ,                                                 _, 0x0065, dv            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Divehi                                ,                                          Maldives, 0x0465, dv-MV         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Duala                                 ,                                                 _, 0x1000, dua           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Duala                                 ,                                          Cameroon, 0x1000, dua-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                                 _, 0x0013, nl            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                             Aruba, 0x1000, nl-AW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                           Belgium, 0x0813, nl-BE         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKE ("Dutch"                               ,                "Bonaire, Sint Eustatius and Saba", 0x1000, "nl-BQ"       , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                           Curacao, 0x1000, nl-CW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                       Netherlands, 0x0413, nl-NL         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                      Sint Maarten, 0x1000, nl-SX         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dutch                                 ,                                          Suriname, 0x1000, nl-SR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dzongkha                              ,                                                 _, 0x1000, dz            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Dzongkha                              ,                                            Bhutan, 0x0C51, dz-BT         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Embu                                  ,                                                 _, 0x1000, ebu           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Embu                                  ,                                             Kenya, 0x1000, ebu-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                                 _, 0x0009, en            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                    American Samoa, 0x1000, en-AS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Anguilla, 0x1000, en-AI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                               Antigua and Barbuda, 0x1000, en-AG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Australia, 0x0C09, en-AU         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Austria, 0x1000, en-AT         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Bahamas, 0x1000, en-BS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Barbados, 0x1000, en-BB         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Belgium, 0x1000, en-BE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Belize, 0x2809, en-BZ         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Bermuda, 0x1000, en-BM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Botswana, 0x1000, en-BW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                    British Indian Ocean Territory, 0x1000, en-IO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                            British Virgin Islands, 0x1000, en-VG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Burundi, 0x1000, en-BI         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Cameroon, 0x1000, en-CM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Canada, 0x1009, en-CA         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Caribbean, 0x2409, en-029        , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                    Cayman Islands, 0x1000, en-KY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                  Christmas Island, 0x1000, en-CX         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                           Cocos [Keeling] Islands, 0x1000, en-CC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                      Cook Islands, 0x1000, en-CK         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Cyprus, 0x1000, en-CY         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Denmark, 0x1000, en-DK         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Dominica, 0x1000, en-DM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Eritrea, 0x1000, en-ER         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Europe, 0x1000, en-150        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                  Falkland Islands, 0x1000, en-FK         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Finland, 0x1000, en-FI         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                              Fiji, 0x1000, en-FJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Gambia, 0x1000, en-GM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Germany, 0x1000, en-DE         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Ghana, 0x1000, en-GH         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Gibraltar, 0x1000, en-GI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Grenada, 0x1000, en-GD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                              Guam, 0x1000, en-GU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Guernsey, 0x1000, en-GG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Guyana, 0x1000, en-GY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Hong Kong, 0x3C09, en-HK         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             India, 0x4009, en-IN         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Ireland, 0x1809, en-IE         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       Isle of Man, 0x1000, en-IM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Israel, 0x1000, en-IL         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Jamaica, 0x2009, en-JM         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Jersey, 0x1000, en-JE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Kenya, 0x1000, en-KE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Kiribati, 0x1000, en-KI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Lesotho, 0x1000, en-LS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Liberia, 0x1000, en-LR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Macao SAR, 0x1000, en-MO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                        Madagascar, 0x1000, en-MG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Malawi, 0x1000, en-MW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Malaysia, 0x4409, en-MY         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Malta, 0x1000, en-MT         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                  Marshall Islands, 0x1000, en-MH         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Mauritius, 0x1000, en-MU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                        Micronesia, 0x1000, en-FM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                        Montserrat, 0x1000, en-MS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Namibia, 0x1000, en-NA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Nauru, 0x1000, en-NR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       Netherlands, 0x1000, en-NL         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       New Zealand, 0x1409, en-NZ         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Nigeria, 0x1000, en-NG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                              Niue, 0x1000, en-NU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                    Norfolk Island, 0x1000, en-NF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                          Northern Mariana Islands, 0x1000, en-MP         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Pakistan, 0x1000, en-PK         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Palau, 0x1000, en-PW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                  Papua New Guinea, 0x1000, en-PG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                  Pitcairn Islands, 0x1000, en-PN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       Puerto Rico, 0x1000, en-PR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                       Republic of the Philippines, 0x3409, en-PH         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Rwanda, 0x1000, en-RW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                             Saint Kitts and Nevis, 0x1000, en-KN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       Saint Lucia, 0x1000, en-LC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                  Saint Vincent and the Grenadines, 0x1000, en-VC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Samoa, 0x1000, en-WS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                        Seychelles, 0x1000, en-SC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                      Sierra Leone, 0x1000, en-SL         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Singapore, 0x4809, en-SG         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                      Sint Maarten, 0x1000, en-SX         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Slovenia, 0x1000, en-SI         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                   Solomon Islands, 0x1000, en-SB         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                      South Africa, 0x1C09, en-ZA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       South Sudan, 0x1000, en-SS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("English"                             ,          "St Helena, Ascension, Tristan da Cunha", 0x1000, "en-SH"       , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Sudan, 0x1000, en-SD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                         Swaziland, 0x1000, en-SZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Sweden, 0x1000, en-SE         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                       Switzerland, 0x1000, en-CH         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Tanzania, 0x1000, en-TZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Tokelau, 0x1000, en-TK         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             Tonga, 0x1000, en-TO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                               Trinidad and Tobago, 0x2c09, en-TT         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                          Turks and Caicos Islands, 0x1000, en-TC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Tuvalu, 0x1000, en-TV         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Uganda, 0x1000, en-UG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                              United Arab Emirates, 0x4C09, en-AE         , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                    United Kingdom, 0x0809, en-GB         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                     United States, 0x0409, en-US         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                         US Minor Outlying Islands, 0x1000, en-UM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                 US Virgin Islands, 0x1000, en-VI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                           Vanuatu, 0x1000, en-VU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                             World, 0x1000, en-001        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                            Zambia, 0x1000, en-ZM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(English                               ,                                          Zimbabwe, 0x3009, en-ZW         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Esperanto                             ,                                                 _, 0x1000, eo            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Esperanto                             ,                                             World, 0x1000, eo-001        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Estonian                              ,                                                 _, 0x0025, et            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Estonian                              ,                                           Estonia, 0x0425, et-EE         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Ewe                                   ,                                                 _, 0x1000, ee            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ewe                                   ,                                             Ghana, 0x1000, ee-GH         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ewe                                   ,                                              Togo, 0x1000, ee-TG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ewondo                                ,                                                 _, 0x1000, ewo           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ewondo                                ,                                          Cameroon, 0x1000, ewo-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Faroese                               ,                                                 _, 0x0038, fo            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Faroese                               ,                                           Denmark, 0x1000, fo-DK         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Faroese                               ,                                     Faroe Islands, 0x0438, fo-FO         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Filipino                              ,                                                 _, 0x0064, fil           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Filipino                              ,                                       Philippines, 0x0464, fil-PH        , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Finnish                               ,                                                 _, 0x000B, fi            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Finnish                               ,                                           Finland, 0x040B, fi-FI         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                                 _, 0x000C, fr            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Algeria, 0x1000, fr-DZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Belgium, 0x080C, fr-BE         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Benin, 0x1000, fr-BJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                      Burkina Faso, 0x1000, fr-BF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Burundi, 0x1000, fr-BI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                          Cameroon, 0x2c0C, fr-CM         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                            Canada, 0x0c0C, fr-CA         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                          Central African Republic, 0x1000, fr-CF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                              Chad, 0x1000, fr-TD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Comoros, 0x1000, fr-KM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Congo, 0x1000, fr-CG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("French"                              ,                                      "Congo, DRC", 0x240C, "fr-CD"       , "Release 8.1"   ),
        MARTY_TR_LOCALEINFO_MAKE ("French"                              ,                                   "Cote d'Ivoire", 0x300C, "fr-CI"       , "Release 8.1"   ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                          Djibouti, 0x1000, fr-DJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                 Equatorial Guinea, 0x1000, fr-GQ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                            France, 0x040C, fr-FR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                     French Guiana, 0x1000, fr-GF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                  French Polynesia, 0x1000, fr-PF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Gabon, 0x1000, fr-GA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Guadeloupe, 0x1000, fr-GP         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                            Guinea, 0x1000, fr-GN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Haiti, 0x3c0C, fr-HT         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Luxembourg, 0x140C, fr-LU         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Madagascar, 0x1000, fr-MG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                              Mali, 0x340C, fr-ML         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Martinique, 0x1000, fr-MQ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Mauritania, 0x1000, fr-MR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                         Mauritius, 0x1000, fr-MU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Mayotte, 0x1000, fr-YT         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Morocco, 0x380C, fr-MA         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                     New Caledonia, 0x1000, fr-NC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Niger, 0x1000, fr-NE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                            Principality of Monaco, 0x180C, fr-MC         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Reunion, 0x200C, fr-RE         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                            Rwanda, 0x1000, fr-RW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                  Saint Barthelemy, 0x1000, fr-BL         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                      Saint Martin, 0x1000, fr-MF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                         Saint Pierre and Miquelon, 0x1000, fr-PM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Senegal, 0x280C, fr-SN         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                        Seychelles, 0x1000, fr-SC         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                       Switzerland, 0x100C, fr-CH         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                             Syria, 0x1000, fr-SY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                              Togo, 0x1000, fr-TG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Tunisia, 0x1000, fr-TN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                           Vanuatu, 0x1000, fr-VU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(French                                ,                                 Wallis and Futuna, 0x1000, fr-WF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Frisian                               ,                                                 _, 0x0062, fy            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Frisian                               ,                                       Netherlands, 0x0462, fy-NL         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Friulian                              ,                                                 _, 0x1000, fur           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Friulian                              ,                                             Italy, 0x1000, fur-IT        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                                 _, 0x0067, ff            , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                                 _, 0x7C67, ff-Latn       , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                      Burkina Faso, 0x1000, ff-Latn-BF    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                          Cameroon, 0x1000, ff-CM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                          Cameroon, 0x1000, ff-Latn-CM    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                            Gambia, 0x1000, ff-Latn-GM    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                             Ghana, 0x1000, ff-Latn-GH    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                            Guinea, 0x1000, ff-GN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                            Guinea, 0x1000, ff-Latn-GN    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                     Guinea-Bissau, 0x1000, ff-Latn-GW    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                           Liberia, 0x1000, ff-Latn-LR    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                        Mauritania, 0x1000, ff-MR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                        Mauritania, 0x1000, ff-Latn-MR    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                             Niger, 0x1000, ff-Latn-NE    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                           Nigeria, 0x1000, ff-NG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                           Nigeria, 0x1000, ff-Latn-NG    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah                                 ,                                           Senegal, 0x0867, ff-Latn-SN    , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Fulah (Latin)                         ,                                      Sierra Leone, 0x1000, ff-Latn-SL    , Release 10.4    ),
        MARTY_TR_LOCALEINFO_MAKES(Galician                              ,                                                 _, 0x0056, gl            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Galician                              ,                                             Spain, 0x0456, gl-ES         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Ganda                                 ,                                                 _, 0x1000, lg            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ganda                                 ,                                            Uganda, 0x1000, lg-UG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Georgian                              ,                                                 _, 0x0037, ka            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Georgian                              ,                                           Georgia, 0x0437, ka-GE         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                                 _, 0x0007, de            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                           Austria, 0x0C07, de-AT         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                           Belgium, 0x1000, de-BE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                           Germany, 0x0407, de-DE         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                             Italy, 0x1000, de-IT         , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                     Liechtenstein, 0x1407, de-LI         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                        Luxembourg, 0x1007, de-LU         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(German                                ,                                       Switzerland, 0x0807, de-CH         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Greek                                 ,                                                 _, 0x0008, el            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Greek                                 ,                                            Cyprus, 0x1000, el-CY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Greek                                 ,                                            Greece, 0x0408, el-GR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Greenlandic                           ,                                                 _, 0x006F, kl            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Greenlandic                           ,                                         Greenland, 0x046F, kl-GL         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Guarani                               ,                                                 _, 0x0074, gn            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Guarani                               ,                                          Paraguay, 0x0474, gn-PY         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Gujarati                              ,                                                 _, 0x0047, gu            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Gujarati                              ,                                             India, 0x0447, gu-IN         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Gusii                                 ,                                                 _, 0x1000, guz           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Gusii                                 ,                                             Kenya, 0x1000, guz-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Hausa (Latin)                         ,                                                 _, 0x0068, ha            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Hausa (Latin)                         ,                                                 _, 0x7C68, ha-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Hausa (Latin)                         ,                                             Ghana, 0x1000, ha-Latn-GH    , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Hausa (Latin)                         ,                                             Niger, 0x1000, ha-Latn-NE    , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Hausa (Latin)                         ,                                           Nigeria, 0x0468, ha-Latn-NG    , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Hawaiian                              ,                                                 _, 0x0075, haw           , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Hawaiian                              ,                                     United States, 0x0475, haw-US        , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Hebrew                                ,                                                 _, 0x000D, he            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Hebrew                                ,                                            Israel, 0x040D, he-IL         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Hindi                                 ,                                                 _, 0x0039, hi            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Hindi                                 ,                                             India, 0x0439, hi-IN         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Hungarian                             ,                                                 _, 0x000E, hu            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Hungarian                             ,                                           Hungary, 0x040E, hu-HU         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Icelandic                             ,                                                 _, 0x000F, is            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Icelandic                             ,                                           Iceland, 0x040F, is-IS         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Igbo                                  ,                                                 _, 0x0070, ig            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Igbo                                  ,                                           Nigeria, 0x0470, ig-NG         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Indonesian                            ,                                                 _, 0x0021, id            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Indonesian                            ,                                         Indonesia, 0x0421, id-ID         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Interlingua                           ,                                                 _, 0x1000, ia            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Interlingua                           ,                                            France, 0x1000, ia-FR         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Interlingua                           ,                                             World, 0x1000, ia-001        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Inuktitut (Latin)                     ,                                                 _, 0x005D, iu            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Inuktitut (Latin)                     ,                                                 _, 0x7C5D, iu-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Inuktitut (Latin)                     ,                                            Canada, 0x085D, iu-Latn-CA    , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Inuktitut (Syllabics)                 ,                                                 _, 0x785D, iu-Cans       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Inuktitut (Syllabics)                 ,                                            Canada, 0x045d, iu-Cans-CA    , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Irish                                 ,                                                 _, 0x003C, ga            , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Irish                                 ,                                           Ireland, 0x083C, ga-IE         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Italian                               ,                                                 _, 0x0010, it            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Italian                               ,                                             Italy, 0x0410, it-IT         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Italian                               ,                                        San Marino, 0x1000, it-SM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Italian                               ,                                       Switzerland, 0x0810, it-CH         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Italian                               ,                                      Vatican City, 0x1000, it-VA         , Release 10.3    ),
        MARTY_TR_LOCALEINFO_MAKES(Japanese                              ,                                                 _, 0x0011, ja            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Japanese                              ,                                             Japan, 0x0411, ja-JP         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Javanese                              ,                                                 _, 0x1000, jv            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Javanese Latin                        ,                                                 _, 0x1000, jv-Latn       , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Javanese Latin                        ,                                         Indonesia, 0x1000, jv-Latn-ID    , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Jola-Fonyi                            ,                                                 _, 0x1000, dyo           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Jola-Fonyi                            ,                                           Senegal, 0x1000, dyo-SN        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kabuverdianu                          ,                                                 _, 0x1000, kea           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kabuverdianu                          ,                                        Cabo Verde, 0x1000, kea-CV        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kabyle                                ,                                                 _, 0x1000, kab           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kabyle                                ,                                           Algeria, 0x1000, kab-DZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kako                                  ,                                                 _, 0x1000, kkj           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kako                                  ,                                          Cameroon, 0x1000, kkj-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kalenjin                              ,                                                 _, 0x1000, kln           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kalenjin                              ,                                             Kenya, 0x1000, kln-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kamba                                 ,                                                 _, 0x1000, kam           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kamba                                 ,                                             Kenya, 0x1000, kam-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kannada                               ,                                                 _, 0x004B, kn            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Kannada                               ,                                             India, 0x044B, kn-IN         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Kashmiri                              ,                                                 _, 0x0060, ks            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kashmiri                              ,                                      Perso-Arabic, 0x0460, ks-Arab       , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kashmiri                              ,                                      Perso-Arabic, 0x1000, ks-Arab-IN    , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kazakh                                ,                                                 _, 0x003F, kk            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Kazakh                                ,                                        Kazakhstan, 0x043F, kk-KZ         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Khmer                                 ,                                                 _, 0x0053, km            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Khmer                                 ,                                          Cambodia, 0x0453, km-KH         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKE ("K'iche"                              ,                                               "_", 0x0086, "quc"         , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKE ("K'iche"                              ,                                       "Guatemala", 0x0486, "quc-Latn-GT" , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(Kikuyu                                ,                                                 _, 0x1000, ki            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kikuyu                                ,                                             Kenya, 0x1000, ki-KE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kinyarwanda                           ,                                                 _, 0x0087, rw            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Kinyarwanda                           ,                                            Rwanda, 0x0487, rw-RW         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Kiswahili                             ,                                                 _, 0x0041, sw            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Kiswahili                             ,                                             Kenya, 0x0441, sw-KE         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Kiswahili                             ,                                          Tanzania, 0x1000, sw-TZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kiswahili                             ,                                            Uganda, 0x1000, sw-UG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Konkani                               ,                                                 _, 0x0057, kok           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Konkani                               ,                                             India, 0x0457, kok-IN        , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Korean                                ,                                                 _, 0x0012, ko            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Korean                                ,                                             Korea, 0x0412, ko-KR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Korean                                ,                                       North Korea, 0x1000, ko-KP         , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Koyra Chiini                          ,                                                 _, 0x1000, khq           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Koyra Chiini                          ,                                              Mali, 0x1000, khq-ML        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Koyraboro Senni                       ,                                                 _, 0x1000, ses           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Koyraboro Senni                       ,                                              Mali, 0x1000, ses-ML        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kwasio                                ,                                                 _, 0x1000, nmg           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kwasio                                ,                                          Cameroon, 0x1000, nmg-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Kyrgyz                                ,                                                 _, 0x0040, ky            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Kyrgyz                                ,                                        Kyrgyzstan, 0x0440, ky-KG         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKE ("Kurdish"                             ,                              "Perso-Arabic, Iran", 0x1000, "ku-Arab-IR"  , "Release 10.1"  ),
        MARTY_TR_LOCALEINFO_MAKES(Lakota                                ,                                                 _, 0x1000, lkt           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lakota                                ,                                     United States, 0x1000, lkt-US        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Langi                                 ,                                                 _, 0x1000, lag           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Langi                                 ,                                          Tanzania, 0x1000, lag-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lao                                   ,                                                 _, 0x0054, lo            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Lao                                   ,                                        Lao P.D.R., 0x0454, lo-LA         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Latvian                               ,                                                 _, 0x0026, lv            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Latvian                               ,                                            Latvia, 0x0426, lv-LV         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Lingala                               ,                                                 _, 0x1000, ln            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lingala                               ,                                            Angola, 0x1000, ln-AO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lingala                               ,                          Central African Republic, 0x1000, ln-CF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lingala                               ,                                             Congo, 0x1000, ln-CG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lingala                               ,                                         Congo DRC, 0x1000, ln-CD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Lithuanian                            ,                                                 _, 0x0027, lt            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Lithuanian                            ,                                         Lithuania, 0x0427, lt-LT         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Low German                            ,                                                 _, 0x1000, nds           , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Low German                            ,                                           Germany, 0x1000, nds-DE        , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Low German                            ,                                       Netherlands, 0x1000, nds-NL        , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Lower Sorbian                         ,                                                 _, 0x7C2E, dsb           , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Lower Sorbian                         ,                                           Germany, 0x082E, dsb-DE        , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Luba-Katanga                          ,                                                 _, 0x1000, lu            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Luba-Katanga                          ,                                         Congo DRC, 0x1000, lu-CD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Luo                                   ,                                                 _, 0x1000, luo           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Luo                                   ,                                             Kenya, 0x1000, luo-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Luxembourgish                         ,                                                 _, 0x006E, lb            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Luxembourgish                         ,                                        Luxembourg, 0x046E, lb-LU         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Luyia                                 ,                                                 _, 0x1000, luy           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Luyia                                 ,                                             Kenya, 0x1000, luy-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Macedonian                            ,                                                 _, 0x002F, mk            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Macedonian                            ,                                   North Macedonia, 0x042F, mk-MK         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Machame                               ,                                                 _, 0x1000, jmc           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Machame                               ,                                          Tanzania, 0x1000, jmc-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Makhuwa-Meetto                        ,                                                 _, 0x1000, mgh           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Makhuwa-Meetto                        ,                                        Mozambique, 0x1000, mgh-MZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Makonde                               ,                                                 _, 0x1000, kde           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Makonde                               ,                                          Tanzania, 0x1000, kde-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Malagasy                              ,                                                 _, 0x1000, mg            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Malagasy                              ,                                        Madagascar, 0x1000, mg-MG         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Malay                                 ,                                                 _, 0x003E, ms            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Malay                                 ,                                 Brunei Darussalam, 0x083E, ms-BN         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Malay                                 ,                                          Malaysia, 0x043E, ms-MY         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Malayalam                             ,                                                 _, 0x004C, ml            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Malayalam                             ,                                             India, 0x044C, ml-IN         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Maltese                               ,                                                 _, 0x003A, mt            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Maltese                               ,                                             Malta, 0x043A, mt-MT         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Manx                                  ,                                                 _, 0x1000, gv            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Manx                                  ,                                       Isle of Man, 0x1000, gv-IM         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Maori                                 ,                                                 _, 0x0081, mi            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Maori                                 ,                                       New Zealand, 0x0481, mi-NZ         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Mapudungun                            ,                                                 _, 0x007A, arn           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Mapudungun                            ,                                             Chile, 0x047A, arn-CL        , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Marathi                               ,                                                 _, 0x004E, mr            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Marathi                               ,                                             India, 0x044E, mr-IN         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Masai                                 ,                                                 _, 0x1000, mas           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Masai                                 ,                                             Kenya, 0x1000, mas-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Masai                                 ,                                          Tanzania, 0x1000, mas-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Mazanderani                           ,                                              Iran, 0x1000, mzn-IR        , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Meru                                  ,                                                 _, 0x1000, mer           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Meru                                  ,                                             Kenya, 0x1000, mer-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("Meta'"                               ,                                               "_", 0x1000, "mgo"         , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKE ("Meta'"                               ,                                        "Cameroon", 0x1000, "mgo-CM"      , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(Mohawk                                ,                                                 _, 0x007C, moh           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Mohawk                                ,                                            Canada, 0x047C, moh-CA        , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Mongolian (Cyrillic)                  ,                                                 _, 0x0050, mn            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Mongolian (Cyrillic)                  ,                                                 _, 0x7850, mn-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Mongolian (Cyrillic)                  ,                                          Mongolia, 0x0450, mn-MN         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Mongolian (Traditional Mongolian)     ,                                                 _, 0x7C50, mn-Mong       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKE ("Mongolian (Traditional Mongolian)"   ,                      "People's Republic of China", 0x0850, "mn-Mong-CN"  , "Release V"     ),
        MARTY_TR_LOCALEINFO_MAKES(Mongolian (Traditional Mongolian)     ,                                          Mongolia, 0x0C50, mn-Mong-MN    , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Morisyen                              ,                                                 _, 0x1000, mfe           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Morisyen                              ,                                         Mauritius, 0x1000, mfe-MU        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Mundang                               ,                                                 _, 0x1000, mua           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Mundang                               ,                                          Cameroon, 0x1000, mua-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("N'ko"                                ,                                               "_", 0x1000, "nqo"         , "Release 8.1"   ),
        MARTY_TR_LOCALEINFO_MAKE ("N'ko"                                ,                                          "Guinea", 0x1000, "nqo-GN"      , "Release 8.1"   ),
        MARTY_TR_LOCALEINFO_MAKES(Nama                                  ,                                                 _, 0x1000, naq           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nama                                  ,                                           Namibia, 0x1000, naq-NA        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nepali                                ,                                                 _, 0x0061, ne            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Nepali                                ,                                             India, 0x0861, ne-IN         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Nepali                                ,                                             Nepal, 0x0461, ne-NP         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Ngiemboon                             ,                                                 _, 0x1000, nnh           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ngiemboon                             ,                                          Cameroon, 0x1000, nnh-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ngomba                                ,                                                 _, 0x1000, jgo           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ngomba                                ,                                          Cameroon, 0x1000, jgo-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Northern Luri                         ,                                              Iraq, 0x1000, lrc-IQ        , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Northern Luri                         ,                                              Iran, 0x1000, lrc-IR        , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(North Ndebele                         ,                                                 _, 0x1000, nd            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(North Ndebele                         ,                                          Zimbabwe, 0x1000, nd-ZW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian (Bokmal)                    ,                                                 _, 0x0014, no            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian (Bokmal)                    ,                                                 _, 0x7C14, nb            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian (Bokmal)                    ,                                            Norway, 0x0414, nb-NO         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian (Nynorsk)                   ,                                                 _, 0x7814, nn            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian (Nynorsk)                   ,                                            Norway, 0x0814, nn-NO         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Norwegian Bokmal                      ,                            Svalbard and Jan Mayen, 0x1000, nb-SJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nuer                                  ,                                                 _, 0x1000, nus           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nuer                                  ,                                             Sudan, 0x1000, nus-SD        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nuer                                  ,                                       South Sudan, 0x1000, nus-SS        , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Nyankole                              ,                                                 _, 0x1000, nyn           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Nyankole                              ,                                            Uganda, 0x1000, nyn-UG        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Occitan                               ,                                                 _, 0x0082, oc            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Occitan                               ,                                            France, 0x0482, oc-FR         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Odia                                  ,                                                 _, 0x0048, or            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Odia                                  ,                                             India, 0x0448, or-IN         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Oromo                                 ,                                                 _, 0x0072, om            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Oromo                                 ,                                          Ethiopia, 0x0472, om-ET         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Oromo                                 ,                                             Kenya, 0x1000, om-KE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ossetian                              ,                                                 _, 0x1000, os            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ossetian Cyrillic                     ,                                           Georgia, 0x1000, os-GE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ossetian Cyrillic                     ,                                            Russia, 0x1000, os-RU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Pashto                                ,                                                 _, 0x0063, ps            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Pashto                                ,                                       Afghanistan, 0x0463, ps-AF         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Pashto                                ,                                          Pakistan, 0x1000, ps-PK         , Release 10.5    ),
        MARTY_TR_LOCALEINFO_MAKES(Persian                               ,                                                 _, 0x0029, fa            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Persian                               ,                                       Afghanistan, 0x1000, fa-AF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Persian                               ,                                              Iran, 0x0429, fa-IR         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Polish                                ,                                                 _, 0x0015, pl            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Polish                                ,                                            Poland, 0x0415, pl-PL         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                                 _, 0x0016, pt            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                            Angola, 0x1000, pt-AO         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                            Brazil, 0x0416, pt-BR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                        Cabo Verde, 0x1000, pt-CV         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                 Equatorial Guinea, 0x1000, pt-GQ         , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                     Guinea-Bissau, 0x1000, pt-GW         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                        Luxembourg, 0x1000, pt-LU         , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                         Macao SAR, 0x1000, pt-MO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                        Mozambique, 0x1000, pt-MZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                          Portugal, 0x0816, pt-PT         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                             Sao Tome and Principe, 0x1000, pt-ST         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                       Switzerland, 0x1000, pt-CH         , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Portuguese                            ,                                       Timor-Leste, 0x1000, pt-TL         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Prussian                              ,                                                 _, 0x1000, prg-001       , Release 10.1    ),
        MARTY_TR_LOCALEINFO_MAKES(Pseudo Language Pseudo locale for east Asian/complex script localization testing,       _, 0x05FE, qps-ploca     , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Pseudo Language Pseudo locale used for localization testing                     ,       _, 0x0501, qps-ploc      , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Pseudo Language Pseudo locale used for localization testing of mirrored locales ,       _, 0x09FF, qps-plocm     , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Punjabi                               ,                                                 _, 0x0046, pa            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Punjabi                               ,                                                 _, 0x7C46, pa-Arab       , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Punjabi                               ,                                             India, 0x0446, pa-IN         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Punjabi                               ,                      Islamic Republic of Pakistan, 0x0846, pa-Arab-PK    , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Quechua                               ,                                                 _, 0x006B, quz           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Quechua                               ,                                           Bolivia, 0x046B, quz-BO        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Quechua                               ,                                           Ecuador, 0x086B, quz-EC        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Quechua                               ,                                              Peru, 0x0C6B, quz-PE        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Ripuarian                             ,                                                 _, 0x1000, ksh           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Ripuarian                             ,                                           Germany, 0x1000, ksh-DE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Romanian                              ,                                                 _, 0x0018, ro            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Romanian                              ,                                           Moldova, 0x0818, ro-MD         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Romanian                              ,                                           Romania, 0x0418, ro-RO         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Romansh                               ,                                                 _, 0x0017, rm            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Romansh                               ,                                       Switzerland, 0x0417, rm-CH         , Release E2      ),
        MARTY_TR_LOCALEINFO_MAKES(Rombo                                 ,                                                 _, 0x1000, rof           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Rombo                                 ,                                          Tanzania, 0x1000, rof-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Rundi                                 ,                                                 _, 0x1000, rn            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Rundi                                 ,                                           Burundi, 0x1000, rn-BI         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                                 _, 0x0019, ru            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                           Belarus, 0x1000, ru-BY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                        Kazakhstan, 0x1000, ru-KZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                        Kyrgyzstan, 0x1000, ru-KG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                           Moldova, 0x0819, ru-MD         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                            Russia, 0x0419, ru-RU         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Russian                               ,                                           Ukraine, 0x1000, ru-UA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Rwa                                   ,                                                 _, 0x1000, rwk           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Rwa                                   ,                                          Tanzania, 0x1000, rwk-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Saho                                  ,                                                 _, 0x1000, ssy           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Saho                                  ,                                           Eritrea, 0x1000, ssy-ER        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sakha                                 ,                                                 _, 0x0085, sah           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sakha                                 ,                                            Russia, 0x0485, sah-RU        , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Samburu                               ,                                                 _, 0x1000, saq           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Samburu                               ,                                             Kenya, 0x1000, saq-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Inari)                          ,                                                 _, 0x703B, smn           , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Inari)                          ,                                           Finland, 0x243B, smn-FI        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Lule)                           ,                                                 _, 0x7C3B, smj           , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Lule)                           ,                                            Norway, 0x103B, smj-NO        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Lule)                           ,                                            Sweden, 0x143B, smj-SE        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Northern)                       ,                                                 _, 0x003B, se            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Northern)                       ,                                           Finland, 0x0C3B, se-FI         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Northern)                       ,                                            Norway, 0x043B, se-NO         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Northern)                       ,                                            Sweden, 0x083B, se-SE         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Skolt)                          ,                                                 _, 0x743B, sms           , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Skolt)                          ,                                           Finland, 0x203B, sms-FI        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Southern)                       ,                                                 _, 0x783B, sma           , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Southern)                       ,                                            Norway, 0x183B, sma-NO        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sami (Southern)                       ,                                            Sweden, 0x1C3B, sma-SE        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Sango                                 ,                                                 _, 0x1000, sg            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sango                                 ,                          Central African Republic, 0x1000, sg-CF         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sangu                                 ,                                                 _, 0x1000, sbp           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sangu                                 ,                                          Tanzania, 0x1000, sbp-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sanskrit                              ,                                                 _, 0x004F, sa            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sanskrit                              ,                                             India, 0x044F, sa-IN         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Scottish Gaelic                       ,                                                 _, 0x0091, gd            , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Scottish Gaelic                       ,                                    United Kingdom, 0x0491, gd-GB         , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sena                                  ,                                                 _, 0x1000, seh           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Sena                                  ,                                        Mozambique, 0x1000, seh-MZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Cyrillic)                    ,                                                 _, 0x6C1A, sr-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Cyrillic)                    ,                            Bosnia and Herzegovina, 0x1C1A, sr-Cyrl-BA    , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Cyrillic)                    ,                                        Montenegro, 0x301A, sr-Cyrl-ME    , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Cyrillic)                    ,                                            Serbia, 0x281A, sr-Cyrl-RS    , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Cyrillic)                    ,                    Serbia and Montenegro (Former), 0x0C1A, sr-Cyrl-CS    , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                                                 _, 0x701A, sr-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                                                 _, 0x7C1A, sr            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                            Bosnia and Herzegovina, 0x181A, sr-Latn-BA    , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                                        Montenegro, 0x2c1A, sr-Latn-ME    , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                                            Serbia, 0x241A, sr-Latn-RS    , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Serbian (Latin)                       ,                    Serbia and Montenegro (Former), 0x081A, sr-Latn-CS    , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Sesotho sa Leboa                      ,                                                 _, 0x006C, nso           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sesotho sa Leboa                      ,                                      South Africa, 0x046C, nso-ZA        , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Setswana                              ,                                                 _, 0x0032, tn            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Setswana                              ,                                          Botswana, 0x0832, tn-BW         , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Setswana                              ,                                      South Africa, 0x0432, tn-ZA         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Shambala                              ,                                                 _, 0x1000, ksb           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Shambala                              ,                                          Tanzania, 0x1000, ksb-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Shona                                 ,                                                 _, 0x1000, sn            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Shona                                 ,                                             Latin, 0x1000, sn-Latn       , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Shona                                 ,                                          Zimbabwe, 0x1000, sn-Latn-ZW    , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Sindhi                                ,                                                 _, 0x0059, sd            , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Sindhi                                ,                                                 _, 0x7C59, sd-Arab       , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Sindhi                                ,                      Islamic Republic of Pakistan, 0x0859, sd-Arab-PK    , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Sinhala                               ,                                                 _, 0x005B, si            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Sinhala                               ,                                         Sri Lanka, 0x045B, si-LK         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Slovak                                ,                                                 _, 0x001B, sk            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Slovak                                ,                                          Slovakia, 0x041B, sk-SK         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Slovenian                             ,                                                 _, 0x0024, sl            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Slovenian                             ,                                          Slovenia, 0x0424, sl-SI         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Soga                                  ,                                                 _, 0x1000, xog           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Soga                                  ,                                            Uganda, 0x1000, xog-UG        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Somali                                ,                                                 _, 0x0077, so            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Somali                                ,                                          Djibouti, 0x1000, so-DJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Somali                                ,                                          Ethiopia, 0x1000, so-ET         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Somali                                ,                                             Kenya, 0x1000, so-KE         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Somali                                ,                                           Somalia, 0x0477, so-SO         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Sotho                                 ,                                                 _, 0x0030, st            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Sotho                                 ,                                      South Africa, 0x0430, st-ZA         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(South Ndebele                         ,                                                 _, 0x1000, nr            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(South Ndebele                         ,                                      South Africa, 0x1000, nr-ZA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Southern Sotho                        ,                                        Lesotho  _, 0x1000, st-LS         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                                 _, 0x000A, es            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                         Argentina, 0x2C0A, es-AR         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                            Belize, 0x1000, es-BZ         , Release 10.3    ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                  Bolivarian Republic of Venezuela, 0x200A, es-VE         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                           Bolivia, 0x400A, es-BO         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                            Brazil, 0x1000, es-BR         , Release 10.2    ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                             Chile, 0x340A, es-CL         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                          Colombia, 0x240A, es-CO         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                        Costa Rica, 0x140A, es-CR         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                              Cuba, 0x5c0A, es-CU         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                Dominican Republic, 0x1c0A, es-DO         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                           Ecuador, 0x300A, es-EC         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                       El Salvador, 0x440A, es-SV         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                 Equatorial Guinea, 0x1000, es-GQ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                         Guatemala, 0x100A, es-GT         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                          Honduras, 0x480A, es-HN         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                     Latin America, 0x580A, es-419        , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                            Mexico, 0x080A, es-MX         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                         Nicaragua, 0x4C0A, es-NI         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                            Panama, 0x180A, es-PA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                          Paraguay, 0x3C0A, es-PY         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                              Peru, 0x280A, es-PE         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                       Philippines, 0x1000, es-PH         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                       Puerto Rico, 0x500A, es-PR         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                             Spain, 0x040A, es-ES_tradnl  , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                             Spain, 0x0c0A, es-ES         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                     United States, 0x540A, es-US         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Spanish                               ,                                           Uruguay, 0x380A, es-UY         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Standard Moroccan Tamazight           ,                                                 _, 0x1000, zgh           , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Standard Moroccan Tamazight           ,                                           Morocco, 0x1000, zgh-Tfng-MA   , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Standard Moroccan Tamazight           ,                                          Tifinagh, 0x1000, zgh-Tfng      , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Swati                                 ,                                                 _, 0x1000, ss            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Swati                                 ,                                      South Africa, 0x1000, ss-ZA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Swati                                 ,                                         Swaziland, 0x1000, ss-SZ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Swedish                               ,                                                 _, 0x001D, sv            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Swedish                               ,                                     Aland Islands, 0x1000, sv-AX         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Swedish                               ,                                           Finland, 0x081D, sv-FI         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Swedish                               ,                                            Sweden, 0x041D, sv-SE         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Syriac                                ,                                                 _, 0x005A, syr           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Syriac                                ,                                             Syria, 0x045A, syr-SY        , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Tachelhit                             ,                                                 _, 0x1000, shi           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tachelhit                             ,                                          Tifinagh, 0x1000, shi-Tfng      , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("Tachelhit"                           ,                               "Tifinagh, Morocco", 0x1000, "shi-Tfng-MA" , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(Tachelhit (Latin)                     ,                                                 _, 0x1000, shi-Latn      , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tachelhit (Latin)                     ,                                           Morocco, 0x1000, shi-Latn-MA   , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Taita                                 ,                                                 _, 0x1000, dav           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Taita                                 ,                                             Kenya, 0x1000, dav-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tajik (Cyrillic)                      ,                                                 _, 0x0028, tg            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tajik (Cyrillic)                      ,                                                 _, 0x7C28, tg-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tajik (Cyrillic)                      ,                                        Tajikistan, 0x0428, tg-Cyrl-TJ    , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamazight (Latin)                     ,                                                 _, 0x005F, tzm           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamazight (Latin)                     ,                                                 _, 0x7C5F, tzm-Latn      , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamazight (Latin)                     ,                                           Algeria, 0x085F, tzm-Latn-DZ   , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamil                                 ,                                                 _, 0x0049, ta            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamil                                 ,                                             India, 0x0449, ta-IN         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Tamil                                 ,                                          Malaysia, 0x1000, ta-MY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tamil                                 ,                                         Singapore, 0x1000, ta-SG         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tamil                                 ,                                         Sri Lanka, 0x0849, ta-LK         , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Tasawaq                               ,                                                 _, 0x1000, twq           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tasawaq                               ,                                             Niger, 0x1000, twq-NE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tatar                                 ,                                                 _, 0x0044, tt            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tatar                                 ,                                            Russia, 0x0444, tt-RU         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Telugu                                ,                                                 _, 0x004A, te            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Telugu                                ,                                             India, 0x044A, te-IN         , Release D       ),
        MARTY_TR_LOCALEINFO_MAKES(Teso                                  ,                                                 _, 0x1000, teo           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Teso                                  ,                                             Kenya, 0x1000, teo-KE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Teso                                  ,                                            Uganda, 0x1000, teo-UG        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Thai                                  ,                                                 _, 0x001E, th            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Thai                                  ,                                          Thailand, 0x041E, th-TH         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Tibetan                               ,                                                 _, 0x0051, bo            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Tibetan                               ,                                             India, 0x1000, bo-IN         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("Tibetan"                             ,                      "People's Republic of China", 0x0451, "bo-CN"       , "Release V"     ),
        MARTY_TR_LOCALEINFO_MAKES(Tigre                                 ,                                                 _, 0x1000, tig           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tigre                                 ,                                           Eritrea, 0x1000, tig-ER        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tigrinya                              ,                                                 _, 0x0073, ti            , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Tigrinya                              ,                                           Eritrea, 0x0873, ti-ER         , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Tigrinya                              ,                                          Ethiopia, 0x0473, ti-ET         , Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Tongan                                ,                                                 _, 0x1000, to            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tongan                                ,                                             Tonga, 0x1000, to-TO         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Tsonga                                ,                                                 _, 0x0031, ts            , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Tsonga                                ,                                      South Africa, 0x0431, ts-ZA         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Turkish                               ,                                                 _, 0x001F, tr            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Turkish                               ,                                            Cyprus, 0x1000, tr-CY         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Turkish                               ,                                            Turkey, 0x041F, tr-TR         , Release A       ),
        MARTY_TR_LOCALEINFO_MAKES(Turkmen                               ,                                                 _, 0x0042, tk            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Turkmen                               ,                                      Turkmenistan, 0x0442, tk-TM         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Ukrainian                             ,                                                 _, 0x0022, uk            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Ukrainian                             ,                                           Ukraine, 0x0422, uk-UA         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Upper Sorbian                         ,                                                 _, 0x002E, hsb           , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Upper Sorbian                         ,                                           Germany, 0x042E, hsb-DE        , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Urdu                                  ,                                                 _, 0x0020, ur            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Urdu                                  ,                                             India, 0x0820, ur-IN         , Release 8.1     ),
        MARTY_TR_LOCALEINFO_MAKES(Urdu                                  ,                      Islamic Republic of Pakistan, 0x0420, ur-PK         , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Uyghur                                ,                                                 _, 0x0080, ug            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKE ("Uyghur"                              ,                      "People's Republic of China", 0x0480, "ug-CN"       , "Release V"     ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek                                 ,                                      Perso-Arabic, 0x1000, uz-Arab       , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKE ("Uzbek"                               ,                       "Perso-Arabic, Afghanistan", 0x1000, "uz-Arab-AF"  , "Release 10"    ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek (Cyrillic)                      ,                                                 _, 0x7843, uz-Cyrl       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek (Cyrillic)                      ,                                        Uzbekistan, 0x0843, uz-Cyrl-UZ    , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek (Latin)                         ,                                                 _, 0x0043, uz            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek (Latin)                         ,                                                 _, 0x7C43, uz-Latn       , Windows 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Uzbek (Latin)                         ,                                        Uzbekistan, 0x0443, uz-Latn-UZ    , Release C       ),
        MARTY_TR_LOCALEINFO_MAKES(Vai                                   ,                                                 _, 0x1000, vai           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vai                                   ,                                                 _, 0x1000, vai-Vaii      , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vai                                   ,                                           Liberia, 0x1000, vai-Vaii-LR   , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vai (Latin)                           ,                                           Liberia, 0x1000, vai-Latn-LR   , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vai (Latin)                           ,                                                 _, 0x1000, vai-Latn      , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Valencian                             ,                                             Spain, 0x0803, ca-ES-valencia, Release 8       ),
        MARTY_TR_LOCALEINFO_MAKES(Venda                                 ,                                                 _, 0x0033, ve            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Venda                                 ,                                      South Africa, 0x0433, ve-ZA         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vietnamese                            ,                                                 _, 0x002A, vi            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Vietnamese                            ,                                           Vietnam, 0x042A, vi-VN         , Release B       ),
        MARTY_TR_LOCALEINFO_MAKES(Volapuk                               ,                                                 _, 0x1000, vo            , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Volapuk                               ,                                             World, 0x1000, vo-001        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vunjo                                 ,                                                 _, 0x1000, vun           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Vunjo                                 ,                                          Tanzania, 0x1000, vun-TZ        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Walser                                ,                                                 _, 0x1000, wae           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Walser                                ,                                       Switzerland, 0x1000, wae-CH        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Welsh                                 ,                                                 _, 0x0052, cy            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Welsh                                 ,                                    United Kingdom, 0x0452, cy-GB         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Wolaytta                              ,                                                 _, 0x1000, wal           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Wolaytta                              ,                                          Ethiopia, 0x1000, wal-ET        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Wolof                                 ,                                                 _, 0x0088, wo            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Wolof                                 ,                                           Senegal, 0x0488, wo-SN         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Xhosa                                 ,                                                 _, 0x0034, xh            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Xhosa                                 ,                                      South Africa, 0x0434, xh-ZA         , Release E1      ),
        MARTY_TR_LOCALEINFO_MAKES(Yangben                               ,                                                 _, 0x1000, yav           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Yangben                               ,                                          Cameroon, 0x1000, yav-CM        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Yi                                    ,                                                 _, 0x0078, ii            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKE ("Yi"                                  ,                      "People's Republic of China", 0x0478, "ii-CN"       , "Release V"     ),
        MARTY_TR_LOCALEINFO_MAKES(Yoruba                                ,                                                 _, 0x006A, yo            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Yoruba                                ,                                             Benin, 0x1000, yo-BJ         , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Yoruba                                ,                                           Nigeria, 0x046A, yo-NG         , Release V       ),
        MARTY_TR_LOCALEINFO_MAKES(Zarma                                 ,                                                 _, 0x1000, dje           , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Zarma                                 ,                                             Niger, 0x1000, dje-NE        , Release 10      ),
        MARTY_TR_LOCALEINFO_MAKES(Zulu                                  ,                                                 _, 0x0035, zu            , Release 7       ),
        MARTY_TR_LOCALEINFO_MAKES(Zulu                                  ,                                      South Africa, 0x0435, zu-ZA         , Release E1      )

    };

    if (pSize)
    {
        *pSize = sizeof(localeInfo) / sizeof(localeInfo[0]);
    }

    return &localeInfo[0];
}


template<typename Handler> inline
void forEachLocaleInfo(Handler handler)
{
    static const char *emptyStr = "";
    static const std::string emptyLocation = "_";
    std::size_t localesTotal = 0;
    const LocaleInfo* pLocales = getLocalesInfo( &localesTotal );

    for(auto i=0u; i!=localesTotal; ++i)
    {
        if (pLocales[i].langId==0x1000)
            continue; // skip unassigned

        const char *pStrLocation = emptyStr; // pLocales[i].location;
        if (pLocales[i].location)
        {
            if (emptyLocation==pLocales[i].location)
            {
            }
            else
            {
                pStrLocation = pLocales[i].location;
            }
        }

        LocaleInfo localeInfoCopy = MARTY_TR_LOCALEINFO_MAKE( pLocales[i].lang, pStrLocation, pLocales[i].langId, pLocales[i].ltag, "");

        handler(localeInfoCopy);
    }
}

inline
std::map<std::string, StringLocaleInfo> getStringLocaleInfoMap()
{
    std::map<std::string, StringLocaleInfo> m;

    forEachLocaleInfo( [&](const LocaleInfo li)
                       {
                           auto sli = StringLocaleInfo(li);
                           if (!sli.ltag.empty())
                           {
                               m[sli.ltag] = sli;
                           }
                       }
                     );

    return m;
}



// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-lcid/0adad5d7-edb6-4649-849f-12825721630e

inline
std::string correctLanguageTag(std::string t)
{
    for(auto &ch : t)
    {
        if (ch=='_')
            ch = '-';
    }

    return t;
}

inline
std::string getLanguageTagNeutral(std::string t)
{
    t = correctLanguageTag(t);
    auto sepPos = t.find('-');
    if (sepPos==t.npos)
        return t;
    return std::string(t, 0, sepPos);
}

inline
std::string getLanguageTagTypeLocation(std::string t)
{
    t = correctLanguageTag(t);
    auto sepPos = t.find('-');
    if (sepPos==t.npos)
        return std::string();
    return std::string(t, sepPos+1, t.npos);
}


// Цифры - всегда в верхнем регистре, префикс 0x - в нижнем
inline
std::string formatLangId(unsigned langId, bool addPrefix = false, bool noLeadingZeros = false)
{
    std::string res;
    for(auto i=0; i!=4; ++i, langId>>=4)
    {
        unsigned d = langId & 0x0F;
        if (d<10)
            res.append(1, '0'+(char)d);
        else
            res.append(1, 'A'+ (char)d);
    }

    if (noLeadingZeros)
    {
        while(res.size()>1 && res.back()=='0')
        {
            res.erase(res.size()-1, res.npos);
        }
    }

    if (addPrefix)
    {
        res.append("x0");
    }



    std::reverse(res.begin(), res.end());

    return res;

}

inline
bool isNumericLanguageTag(const std::string &langTag)
{
    if (langTag.size()<1)
        return false;

    if (langTag.size()>2 && langTag[0]=='0' && (langTag[1]=='x' || langTag[1]=='X')) // Число с префиксом 0x
        return true;

    if (langTag=="ceb")
        return false;

    auto i = 0u;
    for(; i!=langTag.size(); ++i)
    {
        char ch = langTag[i];

        if (ch>='0' && ch<='9')
            continue;

        if (ch>='A' && ch<='F')
            continue;

        if (ch>='a' && ch<='f')
            continue;

        return false;
    }

    // Как будто бы число

    // aa, ae - это строковые тэги локалей, но похожи на числа. Но таких коротких чисел не должно быть

    if (langTag.size()<=2)
        return false;

    return true;

}





namespace impl_helpers {


inline bool    isLower( char ch )     { return (ch>='a' && ch<='z'); }
inline bool    isUpper( char ch )     { return (ch>='A' && ch<='Z'); }

inline bool    isLower( wchar_t ch )  { return (ch>=L'a' && ch<=L'z'); }
inline bool    isUpper( wchar_t ch )  { return (ch>=L'A' && ch<=L'Z'); }

inline char    toLower( char ch )     { return (char)(isUpper(ch) ? ch-'A'+'a' : ch); }
inline char    toUpper( char ch )     { return (char)(isLower(ch) ? ch-'a'+'A' : ch); }

inline wchar_t toLower( wchar_t ch )  { return (wchar_t)(isUpper(ch) ? ch-L'A'+L'a' : ch); }
inline wchar_t toUpper( wchar_t ch )  { return (wchar_t)(isLower(ch) ? ch-L'a'+L'A' : ch); }

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toLower( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr; resStr.reserve(str.size());
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toLower(*it) );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toUpper( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr; resStr.reserve(str.size());
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toUpper(*it) );
    }

    return resStr;
}




inline
std::unordered_map<std::string, std::string>& getLanguageTagSpecificByNeutralMap()
{
    static std::unordered_map<std::string, std::string> m =
    {
        //{"", ""}, //
        { "af", "af-ZA" }, // Afrikaans (South Africa)
        { "am", "am-ET" }, // Amharic (Ethiopia)
        { "ar", "ar-SA" }, // !!! ar-DZ Arabic (Algeria)
        { "arn", "arn-CL" }, // Mapudungun (Chile)
        { "as", "as-IN" }, // Assamese (India)
        { "az", "az-Latn" }, // !!! az-Cyrl Azerbaijani (Cyrillic) (_)
        { "ba", "ba-RU" }, // Bashkir (Russia)
        { "be", "be-BY" }, // Belarusian (Belarus)
        { "bg", "bg-BG" }, // Bulgarian (Bulgaria)
        { "bn", "bn-BD" }, // Bangla (Bangladesh)
        { "bo", "bo-CN" }, // Tibetan (People's Republic of China)
        { "br", "br-FR" }, // Breton (France)
        { "bs", "bs-Cyrl" }, // Bosnian (Cyrillic) (_)
        { "ca", "ca-ES" }, // Catalan (Spain)
        { "chr", "chr-Cher-US" }, // !!! chr-Cher Cherokee (_)
        { "co", "co-FR" }, // Corsican (France)
        { "cs", "cs-CZ" }, // Czech (Czech Republic)
        { "cy", "cy-GB" }, // Welsh (United Kingdom)
        { "da", "da-DK" }, // Danish (Denmark)
        { "de", "de-DE" }, // !!! de-AT German (Austria)
        { "dsb", "dsb-DE" }, // Lower Sorbian (Germany)
        { "dv", "dv-MV" }, // Divehi (Maldives)
        { "dz", "dz-BT" }, // Dzongkha (Bhutan)
        { "el", "el-GR" }, // Greek (Greece)
        { "en", "en-US" }, // !!! en-AU English (Australia)
        { "es", "es-AR" }, // Spanish (Argentina)
        { "et", "et-EE" }, // Estonian (Estonia)
        { "eu", "eu-ES" }, // Basque (Spain)
        { "fa", "fa-IR" }, // Persian (Iran)
        { "ff", "ff-Latn" }, // Fulah (Latin) (_)
        { "fi", "fi-FI" }, // Finnish (Finland)
        { "fil", "fil-PH" }, // Filipino (Philippines)
        { "fo", "fo-FO" }, // Faroese (Faroe Islands)
        { "fr", "fr-BE" }, // French (Belgium)
        { "fy", "fy-NL" }, // Frisian (Netherlands)
        { "ga", "ga-IE" }, // Irish (Ireland)
        { "gd", "gd-GB" }, // Scottish Gaelic (United Kingdom)
        { "gl", "gl-ES" }, // Galician (Spain)
        { "gn", "gn-PY" }, // Guarani (Paraguay)
        { "gsw", "gsw-FR" }, // Alsatian (France)
        { "gu", "gu-IN" }, // Gujarati (India)
        { "ha", "ha-Latn" }, // Hausa (Latin) (_)
        { "haw", "haw-US" }, // Hawaiian (United States)
        { "he", "he-IL" }, // Hebrew (Israel)
        { "hi", "hi-IN" }, // Hindi (India)
        { "hr", "hr-HR" }, // Croatian (Croatia)
        { "hsb", "hsb-DE" }, // Upper Sorbian (Germany)
        { "hu", "hu-HU" }, // Hungarian (Hungary)
        { "hy", "hy-AM" }, // Armenian (Armenia)
        { "id", "id-ID" }, // Indonesian (Indonesia)
        { "ig", "ig-NG" }, // Igbo (Nigeria)
        { "ii", "ii-CN" }, // Yi (People's Republic of China)
        { "is", "is-IS" }, // Icelandic (Iceland)
        { "it", "it-IT" }, // Italian (Italy)
        { "iu", "iu-Latn" }, // Inuktitut (Latin) (_)
        { "ja", "ja-JP" }, // Japanese (Japan)
        { "ka", "ka-GE" }, // Georgian (Georgia)
        { "kk", "kk-KZ" }, // Kazakh (Kazakhstan)
        { "kl", "kl-GL" }, // Greenlandic (Greenland)
        { "km", "km-KH" }, // Khmer (Cambodia)
        { "kn", "kn-IN" }, // Kannada (India)
        { "ko", "ko-KR" }, // Korean (Korea)
        { "kok", "kok-IN" }, // Konkani (India)
        { "ks", "ks-Arab" }, // Kashmiri (Perso-Arabic)
        { "ku", "ku-Arab" }, // Central Kurdish (_)
        { "ky", "ky-KG" }, // Kyrgyz (Kyrgyzstan)
        { "lb", "lb-LU" }, // Luxembourgish (Luxembourg)
        { "lo", "lo-LA" }, // Lao (Lao P.D.R.)
        { "lt", "lt-LT" }, // Lithuanian (Lithuania)
        { "lv", "lv-LV" }, // Latvian (Latvia)
        { "mi", "mi-NZ" }, // Maori (New Zealand)
        { "mk", "mk-MK" }, // Macedonian (North Macedonia)
        { "ml", "ml-IN" }, // Malayalam (India)
        { "mn", "mn-Cyrl" }, // Mongolian (Cyrillic) (_)
        { "moh", "moh-CA" }, // Mohawk (Canada)
        { "mr", "mr-IN" }, // Marathi (India)
        { "ms", "ms-BN" }, // Malay (Brunei Darussalam)
        { "mt", "mt-MT" }, // Maltese (Malta)
        { "my", "my-MM" }, // Burmese (Myanmar)
        { "nb", "nb-NO" }, // Norwegian (Bokmal) (Norway)
        { "ne", "ne-IN" }, // Nepali (India)
        { "nl", "nl-BE" }, // Dutch (Belgium)
        { "nn", "nn-NO" }, // Norwegian (Nynorsk) (Norway)
        { "nso", "nso-ZA" }, // Sesotho sa Leboa (South Africa)
        { "oc", "oc-FR" }, // Occitan (France)
        { "om", "om-ET" }, // Oromo (Ethiopia)
        { "or", "or-IN" }, // Odia (India)
        { "pa", "pa-Arab" }, // Punjabi (_)
        { "pl", "pl-PL" }, // Polish (Poland)
        { "prs", "prs-AF" }, // Dari (Afghanistan)
        { "ps", "ps-AF" }, // Pashto (Afghanistan)
        { "pt", "pt-BR" }, // Portuguese (Brazil)
        { "qps", "qps-ploca" }, // Pseudo Language Pseudo locale for east Asian/complex script localization testing (_)
        { "quc", "quc-Latn-GT" }, // K'iche (Guatemala)
        { "quz", "quz-BO" }, // Quechua (Bolivia)
        { "rm", "rm-CH" }, // Romansh (Switzerland)
        { "ro", "ro-MD" }, // Romanian (Moldova)
        { "ru", "ru-RU" }, // !!! ru-MD Russian (Moldova)
        { "rw", "rw-RW" }, // Kinyarwanda (Rwanda)
        { "sa", "sa-IN" }, // Sanskrit (India)
        { "sah", "sah-RU" }, // Sakha (Russia)
        { "sd", "sd-Arab" }, // Sindhi (_)
        { "se", "se-FI" }, // Sami (Northern) (Finland)
        { "si", "si-LK" }, // Sinhala (Sri Lanka)
        { "sk", "sk-SK" }, // Slovak (Slovakia)
        { "sl", "sl-SI" }, // Slovenian (Slovenia)
        { "sma", "sma-NO" }, // Sami (Southern) (Norway)
        { "smj", "smj-NO" }, // Sami (Lule) (Norway)
        { "smn", "smn-FI" }, // Sami (Inari) (Finland)
        { "sms", "sms-FI" }, // Sami (Skolt) (Finland)
        { "so", "so-SO" }, // Somali (Somalia)
        { "sq", "sq-AL" }, // Albanian (Albania)
        { "sr", "sr-Cyrl" }, // Serbian (Cyrillic) (_)
        { "st", "st-ZA" }, // Sotho (South Africa)
        { "sv", "sv-FI" }, // Swedish (Finland)
        { "sw", "sw-KE" }, // Kiswahili (Kenya)
        { "syr", "syr-SY" }, // Syriac (Syria)
        { "ta", "ta-IN" }, // Tamil (India)
        { "te", "te-IN" }, // Telugu (India)
        { "tg", "tg-Cyrl" }, // Tajik (Cyrillic) (_)
        { "th", "th-TH" }, // Thai (Thailand)
        { "ti", "ti-ER" }, // Tigrinya (Eritrea)
        { "tk", "tk-TM" }, // Turkmen (Turkmenistan)
        { "tn", "tn-BW" }, // Setswana (Botswana)
        { "tr", "tr-TR" }, // Turkish (Turkey)
        { "ts", "ts-ZA" }, // Tsonga (South Africa)
        { "tt", "tt-RU" }, // Tatar (Russia)
        { "tzm", "tzm-Latn" }, // Tamazight (Latin) (_)
        { "ug", "ug-CN" }, // Uyghur (People's Republic of China)
        { "uk", "uk-UA" }, // Ukrainian (Ukraine)
        { "ur", "ur-IN" }, // Urdu (India)
        { "uz", "uz-Cyrl" }, // Uzbek (Cyrillic) (_)
        { "ve", "ve-ZA" }, // Venda (South Africa)
        { "vi", "vi-VN" }, // Vietnamese (Vietnam)
        { "wo", "wo-SN" }, // Wolof (Senegal)
        { "xh", "xh-ZA" }, // Xhosa (South Africa)
        { "yo", "yo-NG" }, // Yoruba (Nigeria)
        { "zh", "zh-Hans" }, // Chinese (Simplified) (_)
        { "zu", "zu-ZA" } // Zulu (South Africa)

    };

    return m;
}

} // namespace impl_helpers

//TODO: !!! Это не совсем безопасно, но если считать, что все настройки будут в однопотоке при запуске проги и потом не меняются, то норм
// Вообще подразумевается, что они никогда не будут меняться, что и так всё хорошо настроено

inline
void setLanguageTagSpecificByNeutral(const std::string &tneutral, const std::string &t)
{
    impl_helpers::getLanguageTagSpecificByNeutralMap()[getLanguageTagNeutral(tneutral)] = t;
}

inline
std::string getLanguageTagSpecificByNeutral(std::string tneutral)
{
    const std::unordered_map<std::string, std::string> &m = impl_helpers::getLanguageTagSpecificByNeutralMap();
    std::unordered_map<std::string, std::string>::const_iterator it = m.find(getLanguageTagNeutral(tneutral));
    if (it==m.end())
        return std::string();
    return it->second;
}



namespace impl_helpers {


inline
void makeLangMaps( std::unordered_map<unsigned   , std::size_t>  *idToIndexMap
                 , std::unordered_map<std::string, std::size_t>  *tagToIndexMap
                 )
{
    std::size_t localesTotal = 0;
    const LocaleInfo* pLocales = getLocalesInfo( &localesTotal );

    for(auto i=0u; i!=localesTotal; ++i)
    {
        if (idToIndexMap && pLocales[i].langId!=0x1000)
        {
            (*idToIndexMap)[pLocales[i].langId] = i; // мапим виндовый LangID на индекс в массиве локалей
        }

        if (tagToIndexMap)
        {
            (*tagToIndexMap)[pLocales[i].ltag] = i; // мапим lang tag на индекс в массиве локалей

            if (pLocales[i].langId!=0x1000)
            {
                // Также хотим, чтобы мапились виндовые локали вида 0xNNNN/0XNNNN/0xNNN/0XNNN/NNNN/NNN в строковом представлении
                                                                      // addPrefix  noLeadingZeros
                if (pLocales[i].langId>=0x100)
                {
                    std::string strLangId1 = formatLangId(pLocales[i].langId, false, false); //   0409
                    std::string strLangId2 = formatLangId(pLocales[i].langId, false, true ); //    409
                    (*tagToIndexMap)[toUpper(strLangId1)] = i;
                    (*tagToIndexMap)[        strLangId1 ] = i;
                    (*tagToIndexMap)[toUpper(strLangId2)] = i;
                    (*tagToIndexMap)[        strLangId2 ] = i;
                }

                std::string strLangId3 = formatLangId(pLocales[i].langId, true , false); // 0x0409
                std::string strLangId4 = formatLangId(pLocales[i].langId, true , true ); //  0x409
                (*tagToIndexMap)[toUpper(strLangId3)] = i;
                (*tagToIndexMap)[        strLangId3 ] = i;
                (*tagToIndexMap)[toUpper(strLangId4)] = i;
                (*tagToIndexMap)[        strLangId4 ] = i;
            }
        }
    }
}

inline
std::unordered_map<unsigned, std::size_t> makeIdToIndexMap()
{
    std::unordered_map<unsigned, std::size_t> idToIndexMap;
    makeLangMaps(&idToIndexMap, 0);
    return idToIndexMap;
}

inline
std::unordered_map<std::string, std::size_t> makeTagToIndexMap()
{
    std::unordered_map<std::string, std::size_t> tagToIndexMap;
    makeLangMaps(0, &tagToIndexMap);
    return tagToIndexMap;
}

inline
const std::unordered_map<unsigned, std::size_t>& getIdToIndexMap()
{
    static std::unordered_map<unsigned, std::size_t> m = makeIdToIndexMap();
    return m;
}

inline
const std::unordered_map<std::string, std::size_t>& getTagToIndexMap()
{
    static std::unordered_map<std::string, std::size_t> m = makeTagToIndexMap();
    return m;
}

inline
const LocaleInfo* getLocaleInfoByIndex( std::size_t idx )
{
    std::size_t size = 0;
    const LocaleInfo* pInfos = getLocalesInfo(&size);
    if (idx>=size)
        return 0;

    return &pInfos[idx];
}


} // namespace impl_helpers





inline
const LocaleInfo* getLocaleInfo( unsigned langId )
{
    const std::unordered_map<unsigned, std::size_t> &m = impl_helpers::getIdToIndexMap();
    std::unordered_map<unsigned, std::size_t>::const_iterator it = m.find(langId);
    if (it==m.end())
        return 0;

    return impl_helpers::getLocaleInfoByIndex(it->second);
}

// LCID          Language tag (string name)     Type
// 0x00000075    haw                            neutral locale
// 0x00000409    en-US                          specific locale
// 0x00010407    de-DE_phoneb                   alternate sort for locale

inline
const LocaleInfo* getLocaleInfo( std::string langTag, bool neutralAllowed = false )
{
    langTag = correctLanguageTag(langTag);

    const std::unordered_map<std::string, std::size_t> &tagMap = impl_helpers::getTagToIndexMap();
    std::unordered_map<std::string, std::size_t>::const_iterator it = tagMap.end();

    // Для числовых langTag'ов просто - если найден, то там то, что нужно
    if (isNumericLanguageTag(langTag))
    {
        it = tagMap.find(impl_helpers::toUpper(langTag));
        if (it==tagMap.end())
            return 0;
        return impl_helpers::getLocaleInfoByIndex(it->second);
    }

    // language tag: nlang-LOCATION, en-US etc
    // nlang       : language neutral, en etc

    /* Если находим по language tag, что ему нет ассоциированных Language ID, то вырезаем nlang часть, и ищем по ней.
       Если находим по nlang, что ему нет ассоциированных Language ID, то ищем подходящий не нейтральный

     */

    const LocaleInfo* pli = 0;

    it = tagMap.find(langTag);

    while (it!=tagMap.end())
    {
        // Что-то нашлось
        pli = impl_helpers::getLocaleInfoByIndex(it->second);
        if (!pli)
            throw std::runtime_error("marty_tr::getLocaleInfo(std::string) - something goes wrong (1)");

        if (pli->langId==0x1000)
            break; // Not assigned, продолжаем поиск

        if (pli->langId<0x100 && !neutralAllowed)
            break; // Neutral, not allowed, продолжаем поиск

        return pli;
    }

    std::string nlang = getLanguageTagNeutral(langTag);

    std::string langTagNext = getLanguageTagSpecificByNeutral(nlang);

    if (langTagNext.empty())
        return 0;

    it = tagMap.find(langTagNext);

    while (it!=tagMap.end())
    {
        // Что-то нашлось
        pli = impl_helpers::getLocaleInfoByIndex(it->second);
        if (!pli)
            throw std::runtime_error("marty_tr::getLocaleInfo(std::string) - something goes wrong (2)");

        if (pli->langId==0x1000)
            break; // Not assigned, продолжаем поиск

        if (pli->langId<0x100 && !neutralAllowed)
            break; // Neutral, not allowed, продолжаем поиск

        return pli;
    }

    return 0;
}

inline
std::string getLocaleLanguageTag( unsigned langId )
{
    const LocaleInfo* pli = getLocaleInfo(langId);
    if (pli)
        return pli->ltag;
    return std::string();
}

inline
std::string getLocaleLanguageTag( std::string langTag, bool neutralAllowed = false )
{
    const LocaleInfo* pli = getLocaleInfo(langTag, neutralAllowed);
    if (pli)
        return pli->ltag;
    return std::string();
}


inline
std::string formatLangTag(const std::string &langTagOrId, ELangTagFormat fmt)
{
    switch(fmt)
    {
        case ELangTagFormat::langTag: // full
             return getLocaleLanguageTag( langTagOrId, false /* neutralAllowed */);

        case ELangTagFormat::langTagNeutral: // Force neutral
             {
                 std::string tagTmp = getLocaleLanguageTag( langTagOrId, true /* neutralAllowed */);
                 return getLanguageTagNeutral(tagTmp);
             }

        case ELangTagFormat::langTagNeutralAuto:
             return getLocaleLanguageTag( langTagOrId, true /* neutralAllowed */);

        case ELangTagFormat::langId:
        case ELangTagFormat::langIdFull:
        case ELangTagFormat::langIdX:
        case ELangTagFormat::langIdFullX:
             {
                 const LocaleInfo* pLocInfo = getLocaleInfo( langTagOrId, false /* neutralAllowed */);
                 if (!pLocInfo)
                     break; // что-то пошло не так

                                                      //      bool addPrefix, bool noLeadingZeros
                 switch(fmt)
                 {
                      case ELangTagFormat::langId:      // 409 (no leading zeros)
                           return formatLangId(pLocInfo->langId, false, true );

                      case ELangTagFormat::langIdFull:  // 0409
                           return formatLangId(pLocInfo->langId, false, false);

                      case ELangTagFormat::langIdX:     // 0x409
                           return formatLangId(pLocInfo->langId, true , true );

                      case ELangTagFormat::langIdFullX: // 0x0409
                           return formatLangId(pLocInfo->langId, true , false);

                      case ELangTagFormat::invalid           : [[fallthrough]];
                      case ELangTagFormat::langTag           : [[fallthrough]];
                      case ELangTagFormat::langTagNeutral    : [[fallthrough]];
                      case ELangTagFormat::langTagNeutralAuto: [[fallthrough]];

                      default: {}
                 }
             }

        case ELangTagFormat::invalid: [[fallthrough]];

        default: return std::string();
    }

    return std::string();

}

inline
std::string formatLangTag(unsigned langId, ELangTagFormat fmt)
{
    const LocaleInfo* pLocInfo = getLocaleInfo( langId );
    if (!pLocInfo)
        return std::string();

    switch(fmt)
    {
        case ELangTagFormat::langTag: // full
             {
                 std::string langTag = pLocInfo->ltag;
                 std::string locType = getLanguageTagTypeLocation(langTag);
                 if (locType.empty())
                 {
                     std::string full = getLanguageTagSpecificByNeutral(langTag);
                     if (!full.empty())
                         return full;
                 }
                 return langTag;
             }

        case ELangTagFormat::langTagNeutral: // Force neutral
             return getLanguageTagNeutral(pLocInfo->ltag);

        case ELangTagFormat::langTagNeutralAuto:
             return pLocInfo->ltag;

        case ELangTagFormat::langId:      // 409 (no leading zeros)
             return formatLangId(pLocInfo->langId, false, true );

        case ELangTagFormat::langIdFull:  // 0409
             return formatLangId(pLocInfo->langId, false, false);

        case ELangTagFormat::langIdX:     // 0x409
             return formatLangId(pLocInfo->langId, true , true );

        case ELangTagFormat::langIdFullX: // 0x0409
             return formatLangId(pLocInfo->langId, true , false);

        case ELangTagFormat::invalid: [[fallthrough]];

        default: return std::string();

    }

}

#if 0
enum class ELangTagFormat
{
    invalid              = -1,
    langTag              = 0 /*!< 'en-US' */,
    langTagNeutral       = 1 /*!< Force 'en' */,
    langTagNeutralAuto   = 2 /*!< 'en' or 'en-US', depending on input */,
    langId               = 3 /*!< 409 (no leading zeros) */,
    langIdFull           = 4 /*!< 0409 */,
    langIdX              = 5 /*!< 0x409 */,
    langIdFullX          = 6 /*!< 0x0409 */

}; // enum class ELangTagFormat
#endif


// struct LocaleInfo
// {
//     const char* const    lang    ;
//     const char* const    location; // or type
//     unsigned    const    langId  ; // Windows Language Identifier (Language ID, which is a part of the Windows Language Code Identifier - LCID)
//     const char* const    ltag    ; // Language tag (locale name), en-US etc...
// };


// ISO 3166-1:2020
// Codes for the representation of names of countries and their subdivisions — Part 1: Country code
// https://www.iso.org/standard/72482.html
// https://en.wikipedia.org/wiki/ISO_3166-1

// [ISO-639] International Organization for Standardization, "Codes for the representation of names of languages -- Part 2: Alpha-3 code", ISO 639-2:1998,
//    https://en.wikipedia.org/wiki/ISO_639

// [RFC5646] Phillips, A, and Davis, M., "Tags for Identifying Languages", BCP 47, RFC 4646, September 2006, http://www.rfc-editor.org/rfc/bcp/bcp47.txt







// neutral locale
// 0x0100

















} // namespace marty_tr

