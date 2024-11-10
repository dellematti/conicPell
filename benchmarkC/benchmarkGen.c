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

// gcc benchmarkGen.c -L./libs -lgmp -o benchmarkGen.out -O3
// ./benchmarkGen.out


// questo file è praticamente uguale a elGamalPell, esegue l istanza di elgamal ma non stampa i risultati
// serve per il benchmark dove non mi interessa contare il tempo della stampa



// benchmark sulla generazione chiavi di un istanza di ElGamal con la conica di Pell (a 512 bit)    gen_enc_dec
int main() {

    float startTime = (float)clock()/CLOCKS_PER_SEC;
    Keys k = gen();
    float endTime = (float)clock()/CLOCKS_PER_SEC;

    float timeElapsed = endTime - startTime;
    printf("%f\n", timeElapsed);
}
