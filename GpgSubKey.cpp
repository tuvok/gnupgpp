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
}

bool GpgSubKey::isExpired() const
{
}

bool GpgSubKey::isDisabled() const
{
}

bool GpgSubKey::isInvalid() const
{
}

bool GpgSubKey::canEncrypt() const
{
}

bool GpgSubKey::canSign() const
{
}

bool GpgSubKey::canCertify() const
{
}

bool GpgSubKey::isSecret() const
{
}

bool GpgSubKey::canAuthenticate() const
{
}

bool GpgSubKey::isQualified() const
{
}

bool GpgSubKey::isCardkey() const
{
}

gpgme_pubkey_algo_t GpgSubKey::getPubkeyAlgo() const
{
}

unsigned int GpgSubKey::getLength() const
{
}

std::string GpgSubKey::getKeyId() const
{
}

std::string GpgSubKey::getFingerprint() const
{
}

long int GpgSubKey::getTimestamp() const
{
}

long int GpgSubKey::getExpirationTimestamp() const
{
}

std::string GpgSubKey::getCardNumber() const
{
}

std::string GpgSubKey::getCurve() const
{
}

std::string GpgSubKey::getKeygrip() const
{
}

} /* namespace gnupgpp */
