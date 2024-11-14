#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>

#include "gmp-6.3.0/gmp.h"

#include "modSqrt.c"
#include "conicPow.c"

#include "keys.h"
#include "ciphertext.h"

#include "gen.c"
#include "enc.c"
#include "dec.c"

// gcc benchmarkEnc.c -L./libs -lgmp -o benchmarkEnc.out -O3
// ./benchmark



// benchmark sull encryption di un istanza di ElGamal con la conica di Pell (a 512 bit)    enc
int main() {


    Keys k = gen(512);
    PublicKey pk = k.pk;




    mpz_t msg;
    mpz_init(msg);                 // provo valori diversi?  magari la "i" che ho nel for fuori in bash
    mpz_set_ui(msg, 127);          // in teoria però la lunghezza del messaggio non influisce (?) TESTARLO  (shift O(1))
    float startTime = (float)clock()/CLOCKS_PER_SEC;
                                   
    CipherText ct = enc(msg, pk);

    float endTime = (float)clock()/CLOCKS_PER_SEC;

    float timeElapsed = endTime - startTime;
    printf("%f\n", timeElapsed);
}
