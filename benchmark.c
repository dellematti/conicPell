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

// gcc benchmark.c -L./libs -lgmp -o benchmark -O3
// ./benchmark


// questo file è praticamente uguale a elGamalPell, esegue l istanza di elgamal ma non stampa i risultati
// serve per il benchmark dove non mi interessa contare il tempo della stampa



// benchmark sull intera esecuzione di un istanza di ElGamal con la conica di Pell (a 512 bit)    gen_enc_dec
int main() {


    // far girare il programma con solo un thread in esecuzione  todo
    float startTime = (float)clock()/CLOCKS_PER_SEC;

    /* Do work */




    Keys k = gen();
    PublicKey pk = k.pk;

    mpz_t msg;
    mpz_init(msg);                 // provo valori diversi?  magari la "i" che ho nel for fuori in bash
    mpz_set_ui(msg, 127);          // in teoria però la lunghezza del messaggio non influisce (?) TESTARLO  (shift O(1))
                                   
    CipherText ct = enc(msg, pk);

    mpz_t risultato;
    mpz_init(risultato);
    funzioneDec(risultato, ct, k);


    // int cmp = mpz_cmp(msg, risultato);
    // if (cmp != 0) {                       // nel benchmark controllo che sia giusto anche (?) ho provato tante volte
    //     break;                            // e non da mai errore
    // }






    float endTime = (float)clock()/CLOCKS_PER_SEC;

    float timeElapsed = endTime - startTime;
    printf("%f\n", timeElapsed);
}
