
// funzione che genera le chiavi. Genera sia la chiave pubblica che la chiave privata e le restituisce in un unica struct
Keys gen() {    

    mpz_t p;       
    mpz_init(p);  
    mpz_t q;       
    mpz_init(q);

    clock_t tick;
    long seed;     

    time_t mytime = time(0);           // IL TEMPO ATTUALE NON BASTA PER AVERE UN SEED AFFIDABILE     IMPORTANTE !!!!!!
    tick = clock();
    seed = tick;          // fare combinazioni tra clock e time? 

    gmp_randstate_t state;
    gmp_randinit_default(state);         //diverse funzioni per Random State Initialization, provare anche le altre
    // gmp_randseed_ui(state,mytime);       
    gmp_randseed_ui(state,seed);    
    // gmp_randseed(state, p);     


    int n = 512;   //  int oppure mp_bitcnt_t    (per scegliere altro per ora modifico qua)
    // n = 18;     // n deve essere > 18 sennò non funziona (in python la stessa cosa)
    if (n == 512) {
        char str[] = "12948321689330283161097309069531008617676170438141861154869888117631594925133496804116121842848834853210714567795846339617837614889766598764879458136968853";
        mpz_set_str(q, str, 10);
        char strP[] = "6474160844665141580548654534765504308838085219070930577434944058815797462566748402058060921424417426605357283897923169808918807444883299382439729068484427";
        mpz_set_str(p, strP, 10);
    }else {
        int tmp_q;
        n--;    // n va diminuito di 1, serve  tra 2^(n-2) e 2^(n-1)   la funzione restituisce tra n-1 e n 
        do {
            mpz_rrandomb(p,state ,n );
            mpz_nextprime(p,p);   // così mi prende direttamente il primo numero primo dopo p. controllare se va bene ??
            mpz_mul_si(q,p,2);
            mpz_sub_ui(q,q,1);

            // ora dobbiamo controllare che q sia primo. Possiamo fare tante volte il test miller rabin
            tmp_q = mpz_probab_prime_p(q,25);    // il numero di volte potrebbe cambiare in base a n (?)
        } while (tmp_q == 0);  // se tmp = 0 allora sicuramente non è primo
    }
        
    // gmp_randinit_default(state);  
    // seed = clock();                  // serve inizializzarlo più volte?
    // gmp_randseed_ui(state,seed); 

    mpz_t d;       
    mpz_init(d); 
    int jacobiSymbol;    
    do {                  
        // d potrebbe essere uscito uguale a zero o 1, devo scartarli in quel caso. faccio fino a q+2 e sottraggo 2
        mpz_t tmpMax;
        mpz_init(tmpMax);       

        mpz_sub_ui(tmpMax,q,2);
        mpz_urandomm(d,state,tmpMax );
        mpz_add_ui(d,d,2);
        jacobiSymbol = mpz_jacobi(d, q);
    } while ( jacobiSymbol != -1 );  


    mpz_t g;       
    mpz_init(g); 

    mpz_t yG;       
    mpz_init(yG); 

    mpz_t xG;     
    mpz_t k;
    mpz_t xH;
    mpz_t yH;


    for (;;) {
        mpz_urandomm(yG,state,q );            // casuale da 0 a q-1 compresi
        mpz_t square;       
        mpz_init(square);  
        
        mpz_t tmpSquare;       
        mpz_init(tmpSquare);  

        mpz_mul(tmpSquare, yG, yG);   
        mpz_mod(tmpSquare,tmpSquare,q);  
        mpz_mul(tmpSquare, tmpSquare, d);    
        mpz_add_ui(tmpSquare, tmpSquare, 1);    
        
        mpz_mod(square,tmpSquare,q);

        if (mpz_jacobi(square, q) == 1) {
            // fare un esposnente random da 0 a 1 
            int max = 1;             // va bene sia 2 1 che  1 0                            
            int min = 0;
            srand(clock()); 
            int esponenteRandom = rand() % (max - min + 1) + min ;  
            int sign = -1;
            for(int i = 0; i < esponenteRandom; i++) {
                sign *= sign;
            }

            mpz_t tmpXg;       
            mpz_init(tmpXg);  
            modSqrt(tmpXg, square, q);
            mpz_mod(tmpXg,tmpXg,q);
            
            mpz_init(xG); 
            mpz_mul_si(xG, tmpXg, sign); 

            mpz_t tmpConic1;       
            mpz_init(tmpConic1);   
            mpz_t tmpConic2;       
            mpz_init(tmpConic2);
            
            mpz_t tmp;
            mpz_init(tmp);
            mpz_set_ui(tmp, 2 );        // Ho diversi tmp che inizializzo, potrei usarne di meno per avere meno istruzioni
            
            conic_pow(tmpConic1,tmpConic2, xG, yG, tmp, d, q);

            int cmpr1 = mpz_cmp_si(tmpConic1, 1);    // vale 0 se sono uguali
            int cmpr2 = mpz_cmp_si(tmpConic2, 0);

            if (cmpr1 != 0 || cmpr2 != 0) {
                conic_pow(tmpConic1,tmpConic2, xG, yG, p, d, q);

                cmpr1 = mpz_cmp_si(tmpConic1, 1);    
                cmpr2 = mpz_cmp_si(tmpConic2, 0);

                if (cmpr1 != 0 || cmpr2 != 0) {
                    
                    mpz_t tmpMax;
                    mpz_init(tmpMax); 
                    mpz_init(k);       

                    mpz_sub_ui(tmpMax,q,-1);
                    mpz_urandomm(k,state,tmpMax );
                    mpz_add_ui(k,k,2);             // k = randrange(2, q + 1),uguale a d ma con q+1 invece di q

                    mpz_init(xH); 
                    mpz_init(yH); 
                    conic_pow(xH,yH, xG, yG, k, d, q);

                    break;
                }
            }
        }
    } 


    PublicKey pk = {
        mpz_get_str(NULL,16,q),
        mpz_get_str(NULL,16,d),
        mpz_get_str(NULL,16,xG),
        mpz_get_str(NULL,16,yG),
        mpz_get_str(NULL,16,xH),
        mpz_get_str(NULL,16,yH)
    };

    SecretKey sk = {
        mpz_get_str(NULL,16,k)
    };

    Keys keys = {
        pk,sk
    };


    //vedere se usare o no clear delle variabili inutilizzate
    // mpz_clear (p);

    return keys;
}


