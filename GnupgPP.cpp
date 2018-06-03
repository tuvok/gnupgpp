#include <GnupgPP.h>

#include <gpgme.h>

namespace gnupgpp
{


GnupgPP::GnupgPP()
{
    const char* version = gpgme_check_version(nullptr);

//    gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
//  #ifdef LC_MESSAGES
//    gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
//  #endif
}

GnupgPP::~GnupgPP()
{

}

gnupgpp::GpgContext GnupgPP::createContext()
{
    return GpgContext();
}


} /* namespace gnupgpp */


