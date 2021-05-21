# OpenBMC RSA signature verification tool
This tool is used to verify the signature of any file using
a public RSA key.

## Build dependencies.
This tool use the library [mbedtls](https://github.com/ARMmbed/mbedtls), that is fetched at build
time by CMake.

## Compile
```shell
mkdir build && cd build
cmake ..
cmake --build .
```

### Usage example
```shell
./check_signature  test/public.pem test/image-kernel
```
**output**
```
 . public key file: 'test/public.pem'
 . sig file 'test/image-kernel.sig'
 . Calculating hash....
 . RSA signature is valid
```
