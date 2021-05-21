/*
 *  Program to check the RSA signature using pem public file,
 *  with code from mbedtls examples code.
 * 
 *  Copyright (c) 2021 Hewlett-Packard Development Company, L.P.
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.

 */

#include "mbedtls/config.h"

#include <stdio.h>
#include <stdlib.h>

#include "mbedtls/md.h"
#include "mbedtls/pem.h"
#include "mbedtls/pk.h"
#include "mbedtls/md.h"


int main( int argc, char *argv[] )
{
    FILE *f;
    int ret = 1;
    int exit_code = -1;
    size_t i;
    mbedtls_pk_context pk;
    unsigned char hash[32];
    unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
    char filename[512];

    mbedtls_pk_init( &pk );

    if( argc != 3 )
    {
        printf( "usage: %s <key_file> <filename>\n", argv[0] );
        goto exit;
    }

    printf( " . public key file: '%s' \n", argv[1] );

    if( ( ret = mbedtls_pk_parse_public_keyfile( &pk, argv[1] ) ) != 0 )
    {
        printf( " ! error reading the public key, error code %x \n\n", ret );
        goto exit;
    }

    if( !mbedtls_pk_can_do( &pk, MBEDTLS_PK_RSA ) )
    {
        printf( " ! error public key is not an RSA key\n", ret );
        goto exit;
    }

    /*
     * Extract the RSA signature from the file
     */
    snprintf( filename, 512, "%s.sig", argv[2] );
    printf( " . sig file '%s' \n", filename );

    if( ( f = fopen( filename, "rb" ) ) == NULL )
    {
        printf( " ! error opening file  %s\n\n", filename );
        goto exit;
    }

    i = fread( buf, 1, MBEDTLS_MPI_MAX_SIZE, f );

    fclose( f );

    /*
     * Compute the SHA-256 hash of the input file and
     * verify the signature
     */
    printf( " . Calculating hash....\n" );
    fflush( stdout );

    if( ( ret = mbedtls_md_file(
                    mbedtls_md_info_from_type( MBEDTLS_MD_SHA256 ),
                    argv[2], hash ) ) != 0 )
    {
        printf( " ! Error reading the file  %s\n\n", argv[2] );
        goto exit;
    }

    if( ( ret = mbedtls_pk_verify( &pk, MBEDTLS_MD_SHA256, hash, 0,
                           buf, i ) ) != 0 )
    {
        printf( " ! RSA verification failed\n");
        goto exit;
    }

    printf( " . RSA signature is valid\n" );

    exit_code = 0;

exit:
    mbedtls_pk_free( &pk );

    exit( exit_code );
}
