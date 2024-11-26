#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>

#include "../gmp-6.3.0/gmp.h"


#include "../modSqrt.c"
#include "../conicPow.c"

#include "../keys.h"
#include "../ciphertext.h"

#include "../gen.c"
#include "../enc.c"
#include "../dec.c"

// gcc benchmark.c -L../libs -lgmp -o benchmark.out -O3   (due punti prima di libs)
// ./benchmark.out      e la lunghezza della chiave


// questo file è praticamente uguale a elGamalPell, esegue l istanza di elgamal ma non stampa i risultati
// serve per il benchmark dove non mi interessa contare il tempo della stampa



// benchmark sull intera esecuzione di un istanza di ElGamal con la conica di Pell (a 512 bit)    gen_enc_dec
int main(int argc, char *argv[]) {

    int keyLen = atoi(argv[1]);

    // da cancellare durante i benchmark
    printf("\ndimensione chiave :\n");
    printf("%d\n", keyLen);
    printf("\n\ntempo impiegato :\n");


    float startTime = (float)clock()/CLOCKS_PER_SEC;

    Keys k = gen(keyLen);
    PublicKey pk = k.pk;

    mpz_t msg;
    mpz_init(msg);                 // provo valori diversi?  magari la "i" che ho nel for fuori in bash
    mpz_set_ui(msg, 127);          // in teoria però la lunghezza del messaggio non influisce (?) TESTARLO  (shift O(1))
                                   
    CipherText ct = enc(msg, pk);

    mpz_t risultato;
    mpz_init(risultato);
    funzioneDec(risultato, ct, k);


    float endTime = (float)clock()/CLOCKS_PER_SEC;

    float timeElapsed = endTime - startTime;
    printf("%f\n", timeElapsed);


    // da cancellare durante i benchmark:
    
    printf("\nMessaggio iniziale :\n");
    mpz_out_str(stdout,10,msg);
    printf("\n\n");

    printf("Messaaggio cifrato :\n");
    printf("%s\n", ct.xC1);     
    printf("%s\n", ct.yC1);     
    printf("%s\n", ct.xC2);     
    printf("%s\n", ct.yC2);  

    printf("\n\nMessaggio decifrato :\n");
    mpz_out_str(stdout,10,risultato);
    printf("\n");
}
