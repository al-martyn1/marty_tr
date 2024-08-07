#pragma once

#include <cctype>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>


//----------------------------------------------------------------------------
#ifndef MARTY_ARG_USED

    //! Подавление варнинга о неиспользованном аргументе
    #define MARTY_ARG_USED(x)                   (void)(x)

#endif

//----------------------------------------------------------------------------



/*

: - in reference to macro perform a parameter substitution (like params in function call)
CALLED_MACRO := $(%0) $(%1) $(%2) $(%3)
                 ^ - number of passed args
usage
CALLED_MACRO(A:B) expands to '2 A B ' (trailing space included)
CALLED_MACRO(A:B:C) expands to '3 A B C' (no trailing space)


conditions
CONDITIONAL_TEST_EXISTENCE := $(SOME_MACRO_NAME?*A:B)
$(CONDITIONAL_TEST_EXISTENCE) expands to B (macro SOME_MACRO_NAME not exists)

CONDITIONAL_TEST_EXISTENCE := $(SOME_MACRO_NAME?*A:B)
SOME_MACRO_NAME:=
$(CONDITIONAL_TEST_EXISTENCE) expands to A (macro SOME_MACRO_NAME exists)

CONDITIONAL_TEST_EXISTENCE := $(SOME_MACRO_NAME?+A:B)
SOME_MACRO_NAME:=
$(CONDITIONAL_TEST_EXISTENCE) expands to B (macro SOME_MACRO_NAME exists, but empty)

CONDITIONAL_TEST_EXISTENCE := $(%1?+A:B)
SOME_MACRO_NAME:=C
$(CONDITIONAL_TEST_EXISTENCE:SOME_MACRO_NAME) expands to A %1 is a macro, its text is SOME_MACRO_NAME
$(CONDITIONAL_TEST_EXISTENCE:) expands to B

*/

// marty_tr::macros::
namespace marty_tr{
namespace macros{



// https://en.cppreference.com/w/cpp/language/type_alias
#if !defined(NDEBUG)

    // При отладке удобнее разглядывать std::map

    template<typename StringType>
    using StringStringMap = std::map<StringType,StringType>;

    template<typename StringType>
    using StringSet = std::set<StringType>;

#else

    // В релизе std::unordered_map быстрее
    template<typename StringType>
    using StringStringMap = std::unordered_map<StringType,StringType>;

    template<typename StringType>
    using StringSet = std::unordered_set<StringType>;

    template<typename StringType>
    using StringSet = std::unordered_set<StringType>;

#endif



// subst macros flags
const int smf_Default                         = 0x0000;
const int smf_ArgsAllowed                     = 0x0001;
const int smf_ConditionAllowed                = 0x0002;
const int smf_AppendVarValueAllowed           = 0x0004;
const int smf_SetVarValueSubstitutionAllowed  = 0x0008;
const int smf_changeDot                       = 0x0010;
const int smf_changeSlash                     = 0x0020;
const int smf_uppercaseNames                  = 0x0040;
const int smf_lowercaseNames                  = 0x0080;
const int smf_DisableRecursion                = 0x0200;
const int smf_KeepUnknownVars                 = 0x0400;
// const int smf_EnvVarsAllowed                  = 0x0100;


// subst macros flags
const int substFlagsDefault                   = smf_Default                        ;
const int argsAllowed                         = smf_ArgsAllowed                    ;
const int conditionAllowed                    = smf_ConditionAllowed               ;
const int appendVarValueAllowed               = smf_AppendVarValueAllowed          ;
const int setVarValueSubstitutionAllowed      = smf_SetVarValueSubstitutionAllowed ;
const int changeDot                           = smf_changeDot                      ;
const int changeSlash                         = smf_changeSlash                    ;
const int uppercaseNames                      = smf_uppercaseNames                 ;
const int lowercaseNames                      = smf_lowercaseNames                 ;
const int disableRecursion                    = smf_DisableRecursion               ;
const int keepUnknownVars                     = smf_KeepUnknownVars                ;
// const int smf_EnvVarsAllowed                  = envVarsAllowed                ;




//----------------------------------------------------------------------------
template<typename StringType>
struct IMacroTextGetter
{

    virtual bool operator()(const StringType &name, StringType &text) const = 0;
};

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
namespace util{




//-----------------------------------------------------------------------------
//! Возвращает отрицание функционального объекта-предиката
/*!
    \tparam ActualPred Тип предиката
    \tparam ParamType  Тип аргумента предиката
    \return Отрицание предиката
 */

template<typename ActualPred, typename ParamType>
struct not_pred
{
    const ActualPred &actualPred; //!< Ссылка на предикат для отрицания его результата
    //! Конструктор предиката отрицания
    not_pred( const ActualPred &a /*!< предикат для отрицания */ ) : actualPred(a) {}
    //! Оператор функционального объекта
    bool operator()( ParamType ch ) const { return !actualPred(ch); }
};
//-----------------------------------------------------------------------------
//! Создаёт строку StringType из std::wstring (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const std::wstring &str )
{
    StringType res;
    for( std::wstring::const_iterator it = str.begin(); it != str.end(); ++it)
        res.append(1, (typename StringType::value_type)*it );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из std::string (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const std::string &str )
{
    StringType res;
    for( std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        res.append(1, (typename StringType::value_type)*it );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из const wchar_t* (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const wchar_t *str )
{
    StringType res;
    for(; *str; str++)
        res.append(1, (typename StringType::value_type)*str );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из const char* (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const char *str )
{
    StringType res;
    for(; *str; str++)
        res.append(1, (typename StringType::value_type)*str );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из sz wchar_t'ов (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( wchar_t ch, size_t sz = 1 )
{
    StringType res;
    res.append(sz, (typename StringType::value_type)ch );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из sz char'ов (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( char ch, size_t sz = 1 )
{
    StringType res;
    res.append(sz, (typename StringType::value_type)ch );
    return res;
}

//-----------------------------------------------------------------------------
//! Левый inplace trim с предикатом
/*! \tparam StringType Тип входной строки (std::basic_string)
    \tparam TrimPred   Предикат. Должен возвращать true для тех символов, которые необходимо обрезать
    \param s           Входная строка
    \param pred        Экземпляр предиката
 */
template <typename StringType, typename TrimPred> inline void ltrim( StringType &s, const TrimPred &pred )
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_pred<TrimPred, typename StringType::value_type>(pred) ));
}

//-----------------------------------------------------------------------------
//! Правый inplace trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred > inline void rtrim(StringType &s, const TrimPred &pred)
{
    s.erase( std::find_if(s.rbegin(), s.rend(), not_pred<TrimPred,typename StringType::value_type>(pred) ).base(), s.end());
}

//-----------------------------------------------------------------------------
//! Двусторонний inplace trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred> inline void trim(StringType &s, const TrimPred &pred)
{
    ltrim(s,pred); rtrim(s,pred);
}

//-----------------------------------------------------------------------------
//! Левый inplace trim. Обрезает пробелы и табы
/*! \tparam StringType Тип входной строки (std::basic_string)
    \param s           Входная строка
 */
template <typename StringType> inline void ltrim(StringType &s)
{
    ltrim(s, whitespace_pred<typename StringType::value_type>());
}

//-----------------------------------------------------------------------------
//! Правый inplace trim. Обрезает пробелы и табы
/*! \tparam StringType Тип входной строки (std::basic_string)
 */
template <typename StringType> inline void rtrim(StringType &s)
{
    rtrim(s, whitespace_pred<typename StringType::value_type>());
}

//-----------------------------------------------------------------------------
//! Двусторонний inplace trim. Обрезает пробелы и табы
/*! \tparam StringType Тип входной строки (std::basic_string)
 */
template <typename StringType> inline void trim(StringType &s)
{
    trim(s,whitespace_pred<typename StringType::value_type>());
}

//-----------------------------------------------------------------------------
//! Левый copy trim с предикатом
/*! \tparam StringType Тип входной и результирующей строки (std::basic_string)
    \tparam TrimPred   Предикат. Должен возвращать true для тех символов, которые необходимо обрезать
    \param s           Входная строка
    \param pred        Экземпляр предиката
    \returns           Обрезанную строку
 */
template <typename StringType, typename TrimPred> inline StringType ltrim_copy(StringType s, const TrimPred &pred)
{
    ltrim(s,pred); return s;
}

//-----------------------------------------------------------------------------
//! Правый copy trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred> inline StringType rtrim_copy(StringType s, const TrimPred &pred)
{
    rtrim(s,pred); return s;
}

//-----------------------------------------------------------------------------
//! Двусторонний copy trim с предикатом
/*! \copydetails ltrim */
template <typename StringType, typename TrimPred> inline StringType trim_copy(StringType s, const TrimPred &pred)
{
    trim(s,pred); return s;
}

//-----------------------------------------------------------------------------
//! Левый copy trim
/*! \tparam StringType Тип входной и результирующей строки (std::basic_string)
    \param s           Входная строка
    \returns           Обрезанную строку
 */
template <typename StringType> inline StringType ltrim_copy(StringType s)
{
    return ltrim_copy(s,whitespace_pred<typename StringType::value_type>());
}

//-----------------------------------------------------------------------------
//! Правый copy trim с предикатом
/*! \tparam StringType Тип входной и результирующей строки (std::basic_string)
    \param s           Входная строка
    \returns           Обрезанную строку
 */
template <typename StringType> inline StringType rtrim_copy(StringType s)
{
    return rtrim_copy(s,whitespace_pred<typename StringType::value_type>());
}

//-----------------------------------------------------------------------------
//! Двусторонний copy trim
/*! \tparam StringType Тип входной и результирующей строки (std::basic_string)
    \param s           Входная строка
    \returns           Обрезанную строку
 */
template <typename StringType> inline StringType trim_copy(StringType s)
{
    return trim_copy(s,whitespace_pred<typename StringType::value_type>());
}

//----------------------------------------------------------------------------
//! Находит символ Ch, которые не заключен в скобки startBr/endBr
template < char startBr
         , char endBr
         , char Ch
         , typename CharType
         , typename Traits
         , typename Allocator
         > inline
typename ::std::basic_string<CharType, Traits, Allocator>::size_type
findChar(const ::std::basic_string<CharType, Traits, Allocator> &str, typename ::std::basic_string<CharType, Traits, Allocator>::size_type pos = 0)
{
    int depth = 0;
    typename ::std::basic_string<CharType, Traits, Allocator>::size_type size = str.size();
    for(; pos<size; ++pos)
    {
        if (str[pos]==(CharType)startBr) { ++depth; continue; }
        if (str[pos]==(CharType)endBr)   { --depth; continue; }
        if (!depth && str[pos]==(CharType)Ch) return pos;
    }
    return ::std::basic_string<CharType, Traits, Allocator>::npos;
}

//----------------------------------------------------------------------------
//!
template < typename CharType
         , typename Traits
         , typename Allocator
         > inline
::std::basic_string<CharType, Traits, Allocator>
prepareMacroName( ::std::basic_string<CharType, Traits, Allocator> name, int flags )
   {
    if (flags&smf_uppercaseNames)
    {
       for(auto &ch : name)
       {
           ch = (CharType)std::toupper(ch);
       }

       return name;
    }
    else if (flags&smf_lowercaseNames)
    {
       for(auto &ch : name)
       {
           ch = (CharType)std::tolower(ch);
       }

       return name;
    }
    return name;
   }

//-----------------------------------------------------------------------------
template < typename CharType
         , typename Traits
         , typename Allocator
         > inline
::std::basic_string<CharType, Traits, Allocator> filterDotsSlashes(const ::std::basic_string<CharType, Traits, Allocator> &str, int flags )
   {

    ::std::basic_string<CharType, Traits, Allocator> res = str;
    //res.reserve(str.size());
    for(typename ::std::basic_string<CharType, Traits, Allocator>::iterator it = res.begin(); it!=res.end(); ++it)
       {
        if ((*it==(CharType)'\\' || *it==(CharType)'/') && (flags&changeSlash))
           {
            *it = (CharType)'_';
            continue;
           }
        if (*it==(CharType)'.' && (flags&changeDot))
           {
            *it = (CharType)'_';
            continue;
           }
       }
    return res;
   }

//-----------------------------------------------------------------------------
template<typename StringType /* , typename OrgGetter */ >
struct MacroTextGetterProxy : public IMacroTextGetter<StringType>
{
    const StringStringMap<StringType>     &m;
    //const OrgGetter                       &orgGetter;
    const IMacroTextGetter<StringType>    &orgGetter;

    MacroTextGetterProxy( const StringStringMap<StringType>     &_m
                        , const IMacroTextGetter<StringType>    &_orgGetter
                        ) : m(_m), orgGetter(_orgGetter) {}

    virtual bool operator()(const StringType &name, StringType &text) const override
    {
        // что-то от старой версии, пусть пока полежит
        // if (getMacroTextFromMap(m, name, text))
        //     return true;

        StringStringMap<StringType>::const_iterator it = m.find(name);
        if (it!=m.end())
        {
            text = it->second;
            return true;
        }

        return orgGetter(name, text);
    }

}; // struct MacroTextGetterProxy

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
template<typename StringType, typename IntType> inline
StringType toString(IntType i)
{
    if constexpr (sizeof(typename StringType::value_type)>sizeof(char)) // is wide version?
        return std::to_wstring(i);
    else
        return std::to_string(i);

}

//-----------------------------------------------------------------------------




} // namespace util

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
template < typename CharType
         , typename Traits
         , typename Allocator
         >
::std::basic_string<CharType, Traits, Allocator>
substMacros( const ::std::basic_string<CharType, Traits, Allocator>                          &str
           , const IMacroTextGetter< ::std::basic_string<CharType, Traits, Allocator> >      &getMacroText
           , int                                                                             flags
           , StringSet< ::std::basic_string<CharType, Traits, Allocator> >                   &usedMacros
           )
   {
    namespace util = ::marty_tr::macros::util;

    typedef ::std::basic_string<CharType, Traits, Allocator> StringType;

    StringType percentZero(1, (CharType)'%'); percentZero.append(1, (CharType)'0');

    typename StringType::const_iterator it = str.begin(), mstartIt = str.end();
    StringType res; res.reserve(str.size());
    //bool prevSlash = false;

    for(; it!=str.end(); ++it)
       {
        if (*it!=(CharType)'$')
           res.append(1, *it);
        else
           {
            mstartIt = it;
            ++it;
            if (it==str.end()) continue;

            if (*it==(CharType)'$')
               {
                res.append(1, *it);
                continue;
               }

            if (*it!=(CharType)'(')
               {
                res.append(1, (CharType)'$');
                res.append(1, *it);
                continue;
               }

            ++it;
            if (it==str.end()) continue;

            typename StringType::const_iterator start = it;
            int brCnt = 1;
            for(; it!=str.end(); ++it)
               {
                if (*it==(CharType)'(') { ++brCnt; continue; }
                if (*it==(CharType)')')
                   {
                    --brCnt;
                    if (!brCnt) break;
                   }
               }

            if (it==str.end())
               {
                res.append(start, it);
                continue;
               }

            StringType macroName = StringType(start, it);
            //std::string::size_type qPos = macroName.find('?', 0);
            typename StringType::size_type qPos = util::findChar<'(', ')', '?'>(macroName);
            //findChar(const std::string str)
            // ? not found, not an conditional
            if (qPos==StringType::npos)
               {
                std::vector< StringType > parts;
                typename StringType::size_type startPos = 0, nextPos = util::findChar<'(', ')', ':'>(macroName, 0);
                do {
                    if (nextPos!=StringType::npos)
                       {
                        parts.push_back(StringType(macroName, startPos, nextPos-startPos));
                        startPos = nextPos+1;
                        nextPos = util::findChar<'(', ')', ':'>(macroName, startPos);
                       }
                    else
                       {
                        parts.push_back(StringType(macroName, startPos));
                        break;
                       }

                   } while(1);

                //
                if (parts.size()<=1)
                   {
                    StringType
                           macroNameChanged = util::prepareMacroName(util::filterDotsSlashes(macroName, flags), flags);
                    if (usedMacros.find(macroNameChanged)!=usedMacros.end())
                       continue; // allready used

                    StringType macroText;
                    if (!getMacroText(macroNameChanged, macroText))
                       {
                        if (flags&smf_KeepUnknownVars)
                           {
                            typename StringType::const_iterator endIt = it;
                            ++endIt;
                            res.append(mstartIt,endIt);
                           }
                        continue; // macro not found
                       }

                    StringSet< StringType > usedMacrosCopy = usedMacros;
                    usedMacrosCopy.insert(macroNameChanged);
                    res.append((flags&smf_DisableRecursion) ? macroText : substMacros(macroText, getMacroText, flags, usedMacrosCopy));
                    continue;
                   }
                else
                   {
                    if (!(flags&smf_ArgsAllowed))
                       {
                        throw std::runtime_error("Parametrized macros not allowed");
                       }

                    StringType macroNameChanged = util::prepareMacroName(util::filterDotsSlashes(parts[0], flags), flags);

                    if (usedMacros.find(macroNameChanged)!=usedMacros.end())
                       continue; // allready used

                    StringType macroText;
                    if (!getMacroText(macroNameChanged, macroText))
                       continue; // macro not found

                    StringSet< StringType > usedMacrosCopy = usedMacros;
                    usedMacrosCopy.insert(macroNameChanged);

                    StringStringMap<StringType> tmpMacros; // = macros;

                    typename StringType::size_type pi = 1, piSize = parts.size();

                    for(; pi<piSize; ++pi)
                       {
                        StringSet< StringType > usedMacrosCopy2 = usedMacrosCopy;
                        parts[pi] = substMacros(parts[pi], getMacroText, flags, usedMacrosCopy2);
                       }

                    tmpMacros[percentZero] = util::toString<StringType>(int(parts.size()) - 1);
                        // util::intToStr< CharType, ::std::char_traits<CharType>, ::std::allocator<CharType> >(int(parts.size())-1);
                    pi = 1;

                    for(; pi<piSize; ++pi)
                       {
                        StringType idxStr = util::toString<StringType>(int(pi)); // ( util::intToStr< CharType, ::std::char_traits<CharType>, ::std::allocator<CharType> >(int(pi)));
                        StringType paramMacroName(1, (CharType)'%'); paramMacroName.append(idxStr);
                        tmpMacros[ paramMacroName ] = parts[pi];
                       }

                    #if 1
                        //!!! Чего-то с прокси не срослось - компилятор помирает от вложенности шаблонов
                        // Порешал, сделав getter нешаблонным параметром с виртуальным оператором ()
                        res.append(substMacros(macroText, util::MacroTextGetterProxy<StringType>(tmpMacros, getMacroText), flags, usedMacrosCopy));
                    #else
                        //!!! Пока не будем ничего делать, потом разберёмся
                        res.append(macroText);
                    #endif
                    continue;
                   }
               }

            //flags = smf_ArgsAllowed|smf_ConditionAllowed
            if (!(flags&smf_ConditionAllowed))
               {
                throw std::runtime_error("Conditional macros not allowed");
               }

            StringType macroNameCond = util::filterDotsSlashes(StringType(macroName, 0, qPos), flags);
            macroNameCond = util::prepareMacroName(macroNameCond, flags);
            ++qPos;
            if (qPos>=macroName.size())
               {
                continue; // no true or false branches
               }

            if (macroName[qPos]!='*' && macroName[qPos]!='+')
               {
                throw std::runtime_error( ::std::string("Conditional macro inclusion (body: '")
                                        + util::make_string<::std::string>(macroName) // MARTY_CON_NS str2con(macroName)
                                        + ::std::string("') - invalid condition, ?* nor ?+ used")
                                        );
                //std::cout<<"Conditional macro inclusion (body: '"<<macroName<<"') - invalid condition, ?* nor ?+ used\n";
                continue;
               }

            bool onlyExist = macroName[qPos]=='*';
            typename StringType::size_type truthBranchStart = ++qPos;
            if (truthBranchStart>=macroName.size())
               {
                continue; // no true or false branches
               }

            typename StringType::size_type colonPos = util::findChar<'(', ')', ':'>(macroName, truthBranchStart);

            StringType truthPart, falsePart;
            if (colonPos==StringType::npos || colonPos>=macroName.size())
               {
                truthPart = StringType(macroName, truthBranchStart);
               }
            else
               {
                typename StringType::size_type truthBranchLen = colonPos-truthBranchStart;
                truthPart = StringType(macroName, truthBranchStart, truthBranchLen);
                falsePart = StringType(macroName, truthBranchStart + truthBranchLen+1);
               }

            bool cond = false;
            StringType macroText;
            if (getMacroText(macroNameCond, macroText))
               { // macro exist
                if (onlyExist)
                   cond = true;
                else
                   {
                    #if 0
                    if (! /* ::boost::algorithm:: */ ::marty::util::trim_copy(macroText, ::marty::util::CIsSpace<CharType>()).empty())
                    #endif
                    //if (!util::trim_copy(macroText, util::space_pred<typename StringType::value_type>()).empty())
                    if (!util::trim_copy( macroText
                                        , [&](typename StringType::value_type ch)
                                          {
                                              typedef typename StringType::value_type CharType;
                                              return (ch==(CharType)' ' || ch==(CharType)'\t' || ch==(CharType)'\n' || ch==(CharType)'\r');
                                          }
                                        ).empty()
                       )
                       cond = true;
                   }
               }

            macroText = cond ? truthPart : falsePart;
            StringType
                str = (flags&smf_DisableRecursion) ? macroText : substMacros(macroText, getMacroText, flags, usedMacros);
            res.append(str);
           }
       }

    return res;
   }

//-----------------------------------------------------------------------------
template < typename MacroTextGetter
         , typename CharType
         , typename Traits
         , typename Allocator
         >
::std::basic_string<CharType, Traits, Allocator>
substMacros( const ::std::basic_string<CharType, Traits, Allocator> &str
           , const MacroTextGetter                                  &getMacroText
           , int                                                     flags = smf_KeepUnknownVars // smf_ArgsAllowed|smf_ConditionAllowed
           )
   {
    StringSet< ::std::basic_string<CharType, Traits, Allocator> > usedMacros;
    return substMacros(str, getMacroText, flags, usedMacros);
   }





} // namespace macros
} // namespace marty_tr


// marty_tr::macros::



