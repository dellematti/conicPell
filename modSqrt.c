// #include <stdio.h>
// #include <stdlib.h>  
// #include <time.h>
// #include <string.h>
// #include <math.h>  

// #include "gmp-6.3.0/gmp.h"


// restituisce in "out" il valore della radice quadrata di a modulo p, ottenuta grazie all'algoritmo Tonelli-Shanks
void modSqrt(mpz_t out, mpz_t a, mpz_t p) {

    int jacobiSymbol = mpz_jacobi(a, p);
    if (jacobiSymbol != 1) {
        return; // 
    }
    int ris = mpz_cmp_si(a, 0);
    if (ris == 0) {
        mpz_set_ui(out, 0);
        return;
    }
    ris = mpz_cmp_si(p, 2);
    if (ris == 0) {
        mpz_set(out, p);
        return;
    }
    mpz_t tmp;
    mpz_init(tmp);
    mpz_mod_ui(tmp,p,4);   
    ris = mpz_cmp_si(tmp, 3);
    if (ris == 0) {
        mpz_add_ui(tmp,p,1);
        mpz_fdiv_q_ui(tmp,tmp, 4);  // la funzione Fdiv fa anche da floor
        mpz_powm(tmp, a, tmp, p);     
        mpz_set(out, tmp);
        return;
    }


    // p-1=q*2^s with q odd 
    mpz_t q;
    mpz_init(q);
    mpz_sub_ui(q,p,1);
    int s = 0;     

    mpz_mod_ui(tmp,q,2);
    ris = mpz_cmp_si(tmp, 0);


    while (ris == 0) {
        mpz_fdiv_q_ui(q,q, 2);
        s++;
        mpz_mod_ui(tmp,q,2);
        ris = mpz_cmp_si(tmp, 0);
    } 

    mpz_t z;            
    mpz_init(z);
    mpz_set_ui(z, 2 );


    jacobiSymbol = mpz_jacobi(p, z);  // anche senza la variabile
    while (jacobiSymbol != -1) {
        mpz_add_ui(z,z,1);
        jacobiSymbol = mpz_jacobi(p, z);
    }

    mpz_t r;             
    mpz_init(r);

    mpz_add_ui(tmp,q,1);
    mpz_fdiv_q_ui(tmp,tmp, 2);   
    mpz_powm(r, a, tmp, p); 

    mpz_t t;            
    mpz_init(t);
    mpz_powm(t, a, q, p); 

    mpz_t c;             
    mpz_init(c);
    mpz_powm(c, z, q, p); 


    for (;;) {
        int e;
        mpz_t t2e;             
        mpz_init(t2e);
        mpz_set(t2e, t );

        for (e = 0; e < s; e++) {
            ris = mpz_cmp_si(t2e, 1);
            if (ris == 0) {
                break;
            }
            mpz_powm_ui(t2e, t2e, 2, p); 
        }
        if (e == 0) {
            mpz_set(out, r);
            return;
        }

        mpz_t b;
        mpz_init(b);
        int esp = s-e-1;

        mpz_set_ui(tmp,2);
        mpz_pow_ui(tmp, tmp, esp);  
        mpz_powm(b, c, tmp,p); 

        s = e;     
        mpz_powm_ui(c, b, 2,p); 
        mpz_mul(t,t,c);
        mpz_mod(t,t,p);
        mpz_mul(r,r,b);
        mpz_mod(r,r,p);
    } 
}




