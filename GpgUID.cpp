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
    if (uid->uid)
        return uid->uid;

    return {};
}

std::string GpgUID::getName() const
{
    if (uid->name)
        return uid->name;

    return {};
}

std::string GpgUID::getEmail() const
{
    if (uid->email)
        return uid->email;

    return {};
}

std::string GpgUID::getComment() const
{
    if (uid->comment)
        return uid->comment;

    return {};
}

/*std::string GpgUID::getAddress() const
{
    if (uid->address)
        return uid->address;

        }*/

} /* namespace gnupgpp */


