#include <stdio.h>
#include <stdlib.h>
#include "crc.h"
#include "aes.h"
#include "sha1.h"
#include "sha256.h"
#include "sha512.h"
#include "sha3.h"

int main(int argc, char* argv[])
{
    crc();
    aes();
    sha1();
    sha256();
    sha512();
    sha3();
    return EXIT_SUCCESS;
}
