#ifndef COLL_AOC_RUNNER_CRYPTO_MD5_HPP
#define COLL_AOC_RUNNER_CRYPTO_MD5_HPP

#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

namespace caoc {
  namespace crypto {
    inline std::string md5(const std::string& input) {
      unsigned char digest[EVP_MAX_MD_SIZE];
      unsigned int digest_len;

      EVP_MD_CTX* ctx = EVP_MD_CTX_new();
      if(ctx == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
      }

      if(EVP_DigestInit_ex(ctx, EVP_md5(), nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize digest");
      }

      if(EVP_DigestUpdate(ctx, input.c_str(), input.size()) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Failed to update digest");
      }

      if(EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize digest");
      }

      EVP_MD_CTX_free(ctx);

      std::stringstream ss;
      for(unsigned int i = 0; i < digest_len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
      }

      return ss.str();
      }
    }
  }

#endif
