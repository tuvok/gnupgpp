#ifndef GNUPGPP_GPGUID_H_
#define GNUPGPP_GPGUID_H_

#include <gpgme.h>

#include <string>

namespace gnupgpp
{

class GpgUID
{
public:
    GpgUID(gpgme_user_id_t uid_);
    virtual ~GpgUID();

    bool isRevoked() const;
    bool isInvalid() const;
    gpgme_validity_t getValidity() const;
    std::string getUid() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getComment() const;
    std::string getAddress() const;

private:
    gpgme_user_id_t uid;
};

} /* namespace gnupgpp */

#endif /* GNUPGPP_GPGUID_H_ */
