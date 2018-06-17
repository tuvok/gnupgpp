#ifndef GNUPGPP_GPGKEY_H_
#define GNUPGPP_GPGKEY_H_

#include <GpgSubKey.h>
#include <GpgUID.h>

#include <gpgme.h>

#include <functional>
#include <string>
#include <vector>

namespace gnupgpp
{

class GpgContext;

class GpgKey
{
public:
    virtual ~GpgKey();

    GpgKey(const GpgKey& src);

    operator gpgme_key_t*();

    bool isRevoked() const;
    bool isExpired() const;
    bool isDisabled() const;
    bool isInvalid() const;
    bool canEncrypt() const;
    bool canSign() const;
    bool carCertify() const;
    bool canAuthenticate() const;
    bool isQualified() const;
    bool isSecret() const;

    gpgme_protocol_t getProtocol() const;
    gpgme_validity_t getOwnerTrust() const;
    std::vector<GpgSubKey> getSubkeys() const;
    std::vector<GpgUID> getUids() const;
    std::string getFingerprintOfPK() const;

private:
    friend class GpgContext;

    GpgKey(std::function<void(gpgme_key_t*)> init);

    gpgme_keylist_mode_t getKeylistMode() const;

    gpgme_key_t key;
};

} /* namespace gnupgpp */

#endif /* GNUPGPP_GPGKEY_H_ */
