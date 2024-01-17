#pragma once




namespace marty_tr{

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

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(ELangTagFormat)

} // namespace marty_tr

