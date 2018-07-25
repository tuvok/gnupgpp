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

void GpgContext::setArmor(bool armor)
{
    gpgme_set_armor(ctx, armor);
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

std::string GpgContext::decrypt(const std::string& data)
{
    gpgme_data_t cipherBuffer;
    if (gpg_err_code(gpgme_data_new_from_mem(&cipherBuffer, data.c_str(),
                data.length(), 0)) != GPG_ERR_NO_ERROR)
    {
        throw std::runtime_error("decrypt(): failed to create cipher buffer");
    }

    gpgme_data_t dataBuffer;
    if (gpg_err_code(gpgme_data_new(&dataBuffer)) != GPG_ERR_NO_ERROR)
    {
        gpgme_data_release(cipherBuffer);
        throw std::runtime_error("decrypt(): failed to create data buffer");
    }

    try
    {
        switch(gpg_err_code(gpgme_op_decrypt_verify(ctx, cipherBuffer, dataBuffer)))
        {
            case GPG_ERR_NO_ERROR:
                break;
            case GPG_ERR_INV_VALUE:
                throw std::runtime_error("decrypt(): invalid pointer[s] supplied");
            case GPG_ERR_NO_DATA:
                throw std::runtime_error("decrypt(): no data to decrypt");
            case GPG_ERR_DECRYPT_FAILED:
                throw std::runtime_error("decrypt(): decryption failed");
            case GPG_ERR_BAD_PASSPHRASE:
                throw std::runtime_error("decrypt(): invalid password");
            default:
                throw std::runtime_error("encrypt(): unknown problem");
        }

        size_t len = 0;
        char* buf = gpgme_data_release_and_get_mem(dataBuffer, &len);

        std::string decrypted(buf, len);

        gpgme_free(buf);
        gpgme_data_release(cipherBuffer);
        return decrypted;

    }
    catch (...)
    {
        gpgme_data_release(dataBuffer);
        gpgme_data_release(cipherBuffer);
        throw;
    }

    return std::string();

    // gpgme_op_decrypt_verify (gpgme_ctx_t ctx, gpgme_data_t cipher, gpgme_data_t plain)
}

std::string GpgContext::encrypt(const std::string& data, std::shared_ptr<GpgKey> key)
{
    gpgme_data_t dataBuffer;
    if (gpg_err_code(gpgme_data_new_from_mem(&dataBuffer, data.c_str(),
                data.length(), 0)) != GPG_ERR_NO_ERROR)
    {
        throw std::runtime_error("encrypt(): failed to create data buffer");
    }

    gpgme_data_t cipherBuffer;
    if (gpg_err_code(gpgme_data_new(&cipherBuffer)) != GPG_ERR_NO_ERROR)
    {
        gpgme_data_release(dataBuffer);
        throw std::runtime_error("encrypt(): failed to create cipher buffer");
    }

    gpgme_key_t keys[2] = {**key, 0};
    try
    {
        switch (gpg_err_code(gpgme_op_encrypt(ctx, keys, GPGME_ENCRYPT_NO_COMPRESS,
                    dataBuffer, cipherBuffer)))
        {
        case GPG_ERR_NO_ERROR:
            break;
        case GPG_ERR_INV_VALUE:
            throw std::runtime_error("encrypt(): invalid pointer[s] supplied");
        case GPG_ERR_UNUSABLE_PUBKEY:
            throw std::runtime_error("encrypt(): unusable public key");
        case GPG_ERR_BAD_PASSPHRASE:
            throw std::runtime_error("encrypt(): invalid passphrase");
        default:
            throw std::runtime_error("encrypt(): unknown problem");
        }

        size_t len = 0;
        char* buf = gpgme_data_release_and_get_mem(cipherBuffer, &len);

        std::string cipher(buf, len);

        gpgme_free(buf);
        gpgme_data_release(dataBuffer);

        return cipher;
    }
    catch (...)
    {
        gpgme_data_release(dataBuffer);
        gpgme_data_release(cipherBuffer);
        throw;
    }
}

} /* namespace gnupgpp */
