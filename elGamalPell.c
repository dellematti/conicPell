#include <stdio.h>
#include <stdlib.h>   // per il rand quando devo creare sign a +1 o -1
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

// gcc elGamalPell.c -L./libs -lgmp -o elGamalPell
// ./elGamalPell

// gcc elGamalPell.c -L./libs -lgmp -o elGamalPell -O3



// Vengono eseguite istanze su ElGamal con la conica di Pell 
int main() {

    Keys k = gen();
    // printf("%s\n", k.sk.k);     // stampa la chiave segreta

    PublicKey pk = k.pk;

    mpz_t msg;
    mpz_init(msg);
    mpz_set_ui(msg, 123456);
    // mpz_set_ui(msg, 56);
    // mpz_set_ui(msg, 123456871892281);

    
    printf("\nMessaggio iniziale :\n");
    mpz_out_str(stdout,10,msg);
    printf("\n\n");


    CipherText ct = enc(msg, pk);
    printf("Messaaggio cifrato :\n");
    printf("%s\n", ct.xC1);     
    printf("%s\n", ct.yC1);     
    printf("%s\n", ct.xC2);     
    printf("%s\n", ct.yC2);         
    // (sia chiave pubblica che segreta nella stessa struct ?)


    // decifro
    mpz_t risultato;
    mpz_init(risultato);
    funzioneDec(risultato, ct, k);

    printf("\n\nMessaggio decifrato :\n");
    mpz_out_str(stdout,10,risultato);
    printf("\n");

}
