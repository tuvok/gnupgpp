#ifndef GNUPGPP_GPGSUBKEY_H_
#define GNUPGPP_GPGSUBKEY_H_

#include <gpgme.h>

#include <string>

namespace gnupgpp
{

class GpgSubKey
{
public:
    GpgSubKey(gpgme_subkey_t skey_);
    virtual ~GpgSubKey();

    bool isRevoked() const;
    bool isExpired() const;
    bool isDisabled() const;
    bool isInvalid() const;
    bool canEncrypt() const;
    bool canSign() const;
    bool canCertify() const;
    bool isSecret() const;
    bool canAuthenticate() const;
    bool isQualified() const;
    bool isCardkey() const;

    gpgme_pubkey_algo_t getPubkeyAlgo() const;
    unsigned int getLength() const;
    std::string getKeyId() const;
    std::string getFingerprint() const;
    long int getTimestamp() const;
    long int getExpirationTimestamp() const;
    std::string getCardNumber() const;
    std::string getCurve() const;
    std::string getKeygrip() const;

private:
    gpgme_subkey_t skey;
};

} /* namespace gnupgpp */

#endif /* GNUPGPP_GPGSUBKEY_H_ */
