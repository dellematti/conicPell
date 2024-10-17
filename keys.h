#include <stdio.h>
#include "gmp-6.3.0/gmp.h"


typedef struct {
    char *q;
    char *d;
    char *xG;
    char *yG;
    char *xH;
    char *yH;
} PublicKey;


typedef struct {
    char * k;
} SecretKey;


typedef struct {
    PublicKey pk;
    SecretKey sk;
} Keys;

