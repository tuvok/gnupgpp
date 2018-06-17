#include <GpgSubKey.h>

namespace gnupgpp
{

GpgSubKey::GpgSubKey(gpgme_subkey_t skey_) : skey(skey_)
{

}

GpgSubKey::~GpgSubKey()
{

}

bool GpgSubKey::isRevoked() const
{
    return skey->revoked;
}

bool GpgSubKey::isExpired() const
{
    return skey->expired;
}

bool GpgSubKey::isDisabled() const
{
    return skey->disabled;
}

bool GpgSubKey::isInvalid() const
{
    return skey->invalid;
}

bool GpgSubKey::canEncrypt() const
{
    return skey->can_encrypt;
}

bool GpgSubKey::canSign() const
{
    return skey->can_sign;
}

bool GpgSubKey::canCertify() const
{
    return skey->can_certify;
}

bool GpgSubKey::isSecret() const
{
    return skey->secret;
}

bool GpgSubKey::canAuthenticate() const
{
    return skey->can_authenticate;
}

bool GpgSubKey::isQualified() const
{
    return skey->is_qualified;
}

bool GpgSubKey::isCardkey() const
{
    return skey->is_cardkey;
}

gpgme_pubkey_algo_t GpgSubKey::getPubkeyAlgo() const
{
    return skey->pubkey_algo;
}

unsigned int GpgSubKey::getLength() const
{
    return skey->length;
}

std::string GpgSubKey::getKeyId() const
{
    if (skey->keyid)
        return skey->keyid;

    return {};
}

std::string GpgSubKey::getFingerprint() const
{
    if (skey->fpr)
        return skey->fpr;

    return {};
}

long int GpgSubKey::getTimestamp() const
{
    return skey->timestamp;
}

long int GpgSubKey::getExpirationTimestamp() const
{
    return skey->expires;
}

std::string GpgSubKey::getCardNumber() const
{
    if (skey->card_number)
        return skey->card_number;

    return {};
}

std::string GpgSubKey::getCurve() const
{
    if (skey->curve)
        return skey->curve;

    return {};
}

std::string GpgSubKey::getKeygrip() const
{
    if (skey->keygrip)
        return skey->keygrip;

    return {};
}

} /* namespace gnupgpp */
