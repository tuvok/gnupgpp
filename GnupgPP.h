#ifndef GNUPGPP_GNUPGPP_H_
#define GNUPGPP_GNUPGPP_H_

#include <GpgContext.h>

namespace gnupgpp
{

class GnupgPP
{
public:
    GnupgPP();
    virtual ~GnupgPP();

    gnupgpp::GpgContext createContext();

};

} /* namespace gnupgpp */

#endif /* GNUPGPP_GNUPGPP_H_ */
