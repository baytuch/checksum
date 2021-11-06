/*
 * This is a modified version of:
 *
 * https://github.com/joyeecheung/md5
 */

#ifndef MD5_HPP
#define MD5_HPP

#include <stdint.h>
#include <string>

class MD5
{
public:
    MD5();
    ~MD5();

    MD5& update(const unsigned char *in, size_t inputLen);
    MD5& update(const char *in, size_t inputLen);
    MD5& finalize();
    std::string getDigest() const;
    std::string toString() const;

private:

    void transform(const uint8_t block[64]);

private:
    uint8_t buffer[64];  // buffer of the raw data
    uint8_t digest[16];  // result hash, little endian

    uint32_t state[4];  // state (ABCD)
    uint32_t lo, hi;    // number of bits, modulo 2^64 (lsb first)
    bool finalized;  // if the context has been finalized
};


#endif
