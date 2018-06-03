#include <GpgKey.h>

namespace gnupgpp
{

GpgKey::GpgKey(const GpgKey& src)
{
    key = src.key;
    gpgme_key_ref(key);
}

GpgKey::GpgKey(std::function<void(gpgme_key_t*)> init)
{
    init(&key);
}

GpgKey::~GpgKey()
{
    gpgme_key_unref(key);
}

GpgKey::operator gpgme_key_t*()
{
    return &key;
}

bool GpgKey::isRevoked() const
{
    return key->revoked;
}

bool GpgKey::isExpired() const
{
    return key->expired;
}

bool GpgKey::isDisabled() const
{
    return key->disabled;
}

bool GpgKey::isInvalid() const
{
    return key->invalid;
}

bool GpgKey::canEncrypt() const
{
    return key->can_encrypt;
}

bool GpgKey::canSign() const
{
    return key->can_sign;
}

bool GpgKey::carCertify() const
{
    return key->can_certify;
}

bool GpgKey::canAuthenticate() const
{
    return key->can_authenticate;
}

bool GpgKey::isQualified() const
{
    return key->is_qualified;
}

bool GpgKey::isSecret() const
{
    return key->secret;
}

gpgme_protocol_t GpgKey::getProtocol() const
{
    return key->protocol;
}

gpgme_validity_t GpgKey::getOwnerTrust() const
{
    return key->owner_trust;
}

std::vector<GpgSubKey> GpgKey::getSubkeys() const
{
}

std::vector<GpgUID> GpgKey::getUids() const
{
    std::vector<GpgUID> result;

    gpgme_user_id_t uid = key->uids;
    while(uid)
    {
        result.push_back(uid);
        uid = uid->next;
    }

    return result;
}

std::string GpgKey::getFingerprintOfPK() const
{
    return key->fpr;
}

gpgme_keylist_mode_t GpgKey::getKeylistMode() const
{
    return key->keylist_mode;
}

} /* namespace gnupgpp */


