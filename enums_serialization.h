#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace marty_tr{

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ELangTagFormat, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langIdX             , "LangIdX"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langId              , "LangId"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::invalid             , "Invalid"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langTag             , "LangTag"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langTagNeutral      , "LangTagNeutral"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langIdFull          , "LangIdFull"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langTagNeutralAuto  , "LangTagNeutralAuto" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELangTagFormat::langIdFullX         , "LangIdFullX"        );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ELangTagFormat, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ELangTagFormat, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdX             , "lang-id-x"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdX             , "langidx"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdX             , "lang_id_x"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langId              , "lang-id"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langId              , "lang_id"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langId              , "langid"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::invalid             , "invalid"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTag             , "lang-tag"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTag             , "lang_tag"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTag             , "langtag"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutral      , "lang-tag-neutral"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutral      , "lang_tag_neutral"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutral      , "langtagneutral"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFull          , "lang-id-full"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFull          , "langidfull"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFull          , "lang_id_full"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutralAuto  , "lang-tag-neutral-auto" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutralAuto  , "lang_tag_neutral_auto" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langTagNeutralAuto  , "langtagneutralauto"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFullX         , "lang-id-full-x"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFullX         , "lang_id_full_x"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELangTagFormat::langIdFullX         , "langidfullx"           );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( ELangTagFormat, std::map, 1 )

} // namespace marty_tr

