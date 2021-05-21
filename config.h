/*
 * Minimal configuration rsa checking signatures
 */
#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

#define MBEDTLS_BIGNUM_C
#define MBEDTLS_OID_C

#define MBEDTLS_PKCS1_V21
#define MBEDTLS_PKCS1_V15

#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_FS_IO

#define MBEDTLS_BASE64_C
#define MBEDTLS_PEM_PARSE_C

#define MBEDTLS_MD_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_RSA_C


#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */
