#include <GpgUID.h>

namespace gnupgpp
{

GpgUID::GpgUID(gpgme_user_id_t uid_) : uid(uid_)
{

}

GpgUID::~GpgUID()
{

}

bool GpgUID::isRevoked() const
{
    return uid->revoked;
}

bool GpgUID::isInvalid() const
{
    return uid->invalid;
}

gpgme_validity_t GpgUID::getValidity() const
{
    return uid->validity;
}

std::string GpgUID::getUid() const
{
    return uid->uid;
}

std::string GpgUID::getName() const
{
    return uid->name;
}

std::string GpgUID::getEmail() const
{
    return uid->email;
}

std::string GpgUID::getComment() const
{
    return uid->comment;
}

std::string GpgUID::getAddress() const
{
    return uid->address;
}

} /* namespace gnupgpp */


