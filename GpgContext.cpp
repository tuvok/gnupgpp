#include "GpgContext.h"

#include <stdexcept>
#include <string>

namespace gnupgpp
{

GpgContext::GpgContext()
{
    switch (gpg_err_code(gpgme_new(&ctx)))
    {
    case GPG_ERR_NO_ERROR:
        break;
    case GPG_ERR_INV_VALUE:
        throw std::runtime_error("GpgContext(): invalid ctx pointer");
    case GPG_ERR_ENOMEM:
        throw std::runtime_error("GpgContext(): out of memory");
    case GPG_ERR_NOT_OPERATIONAL:
        throw std::runtime_error("GpgContext(): GPGME not initialized");
    case GPG_ERR_SELFTEST_FAILED:
        throw std::runtime_error("GpgContext(): GPGME selftest failed");
    default:
        throw std::runtime_error("GpgContext(): unknown problem");
    }
}

GpgContext::~GpgContext()
{
    gpgme_release(ctx);
}

std::vector<GpgKey> GpgContext::listSecretKeys()
{

    std::vector<GpgKey> result;

    gpgme_err_code_t err = gpg_err_code(gpgme_op_keylist_start(ctx, nullptr, 1));
    if (err == GPG_ERR_INV_VALUE)
        throw std::runtime_error("listSecretKeys(): invalid ctx pointer");
    else if (err > 0)
        throw std::runtime_error("listSecretKeys(): error starting key listing: " + std::to_string(err));

    while (!err)
    {
        GpgKey key([this, &err] (gpgme_key_t* key) -> void
        {
            err = gpg_err_code(gpgme_op_keylist_next(ctx, key));
        });

        if (err == GPG_ERR_EOF)
            break;

        if (err > 0)
        {
            throw std::runtime_error("listSecretKeys(): error fetching key: " + std::to_string(err) +
                    ": " + std::string(gpgme_strerror(err)));
        }

        result.push_back(key);
    }

    return result;
}

std::shared_ptr<GpgKey> GpgContext::getKey(std::string fingerprint, bool secret)
{
    gpgme_err_code_t err;
    std::shared_ptr<GpgKey> result(new GpgKey(
        [this, &err, &fingerprint, &secret] (gpgme_key_t* key) -> void
        {
            err = gpg_err_code(gpgme_get_key(ctx, fingerprint.c_str(), key, secret));
        }));

    if (err != GPG_ERR_NO_ERROR)
        return nullptr;

    return result;
}

} /* namespace gnupgpp */
