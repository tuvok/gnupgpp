#ifndef GNUPGPP_GPGCONTEXT_H_
#define GNUPGPP_GPGCONTEXT_H_

#include <GpgKey.h>

#include <gpgme.h>

#include <memory>
#include <vector>

namespace gnupgpp
{

class GnupgPP;

class GpgContext
{
public:
    GpgContext(GpgContext&&) = default;
    virtual ~GpgContext();

    std::vector<GpgKey> listSecretKeys();
    std::shared_ptr<GpgKey> getKey(std::string fingerprint, bool secret = false);

private:
    GpgContext();
    GpgContext(const GpgContext&) = delete;

    friend class GnupgPP;

    gpgme_ctx_t ctx;
};

} /* namespace gnupgpp */

#endif /* GNUPGPP_GPGCONTEXT_H_ */
