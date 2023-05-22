#include "marty_tr/marty_tr.h"

#include <iostream>

 


int main( int argc, char* argv[] )
{

    auto addLocaleInfoTranslation = [&]( const marty_tr::LocaleInfo &li)
    {
        std::string locationType = li.location;

        marty_tr::tr_add(li.lang, li.lang, "marty-tr/language-name"    , "en-US");
        if (!locationType.empty())
            marty_tr::tr_add(locationType, locationType, "marty-tr/language-location", "en-US");
    };

    marty_tr::forEachLocaleInfo(addLocaleInfoTranslation);
    marty_tr::tr_add("_", "", "marty-tr/language-location", "en-US");
    marty_tr::tr_add("-", "", "marty-tr/language-location", "en-US");

    std::cout << marty_tr::tr_serialize_translations(marty_tr::tr_get_all_translations());

    return 0;
}

