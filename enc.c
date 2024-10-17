
// il messaggio che viene cifrato NON è una stringa ma un numero (uso un mpz anche qua come tipo)
// posso aggiungere la parte dove da stringa ottengo un numero 



// cifra il messaggio 'msg' utilizzando la chiave pubblica. 
CipherText enc(mpz_t msg, PublicKey pk ) {
    // come prima cosa devo ricavare gli mpz dai vari parametri nella public key
    // potrei durante gen, mettere nella struct sia la stringa esadecimale, sia l mpz(?)

    mpz_t q;
    mpz_init(q);
    mpz_t d;
    mpz_init(d);
    mpz_t xG;
    mpz_init(xG);
    mpz_t yG;
    mpz_init(yG);
    mpz_t xH;
    mpz_init(xH);
    mpz_t yH;
    mpz_init(yH);

    mpz_set_str(q, pk.q,16);
    mpz_set_str(d, pk.d,16);
    mpz_set_str(xG, pk.xG,16);
    mpz_set_str(yG, pk.yG,16);
    mpz_set_str(xH, pk.xH,16);
    mpz_set_str(yH, pk.yH,16);

    // mpz_out_str(stdout,10,q);
    // printf("\n");


    int n = mpz_sizeinbase (q, 2);   // per ora prove su 512
    // int var = n/16;               // C fa in automatico la floor division 
    mp_bitcnt_t var = n/16;

    // qua potrei fare un controllo sulla lunghezza massima del messaggio, TODO implementarlo 
    //   if msg.bit_length() > n - 1 - var:
    //     raise ValueError('msg longer than 15*n/16-1')


    long seed = clock();           // anche qua come in gen, controllare che clock vada bene per il seed   
    gmp_randstate_t state;
    gmp_randinit_default(state);   
    gmp_randseed_ui(state,seed);


    // il messaggio che viene cifrato NON è una stringa ma un numero
    mpz_t y;
    mpz_init(y);
    mpz_mul_2exp(y,msg,var);


    mpz_t stop;
    mpz_init(stop);
    mpz_set_ui(stop,1);  // per non dichiarare un mpz in più
    mpz_mul_2exp(stop,stop,var);


    mpz_t v;
    mpz_init(v);   // init da in automatico 0 come valore, non serve settarlo
    mpz_t square;       
    mpz_init(square);  
    while (mpz_cmp(v,stop) < 0) {

        // square = (1 + d * pow(y, 2, q)) % q
        mpz_mul(square, y, y);   
        mpz_mod(square,square,q);  
        mpz_mul(square, square, d);    
        mpz_add_ui(square, square, 1);    
        mpz_mod(square,square,q);

        if (mpz_jacobi(square, q) == 1) {
            break;
        }
        mpz_add_ui(y,y,1);

        mpz_add_ui(v,v,1);
    }

    // finito il ciclo ci sarebbe questo controllo in più da implementare TODO  (anche se già solo con n 512 non serve)
    // if j != 1:
    //   raise ValueError('x not found because 1+dy non-square')


    mpz_t x;
    mpz_init(x);
    modSqrt(x, square, q);


    // Classic ElGamal encryption
    mpz_t r;
    mpz_init(r);       
    mpz_t tmpMax;
    mpz_init(tmpMax); 

    mpz_sub_ui(tmpMax,q,-1);
    mpz_urandomm(r,state,tmpMax );
    mpz_add_ui(r,r,2);             // r = randrange(2, q + 1),uguale a k in gen


    mpz_t xC1;
    mpz_init(xC1);    
    mpz_t yC1;
    mpz_init(yC1);    

    conic_pow(xC1,yC1, xG, yG, r, d, q);

    mpz_t F1;
    mpz_init(F1);    
    mpz_t F2;
    mpz_init(F2); 

    conic_pow(F1,F2, xH, yH, r, d, q);

    mpz_t xC2;
    mpz_init(xC2);    
    mpz_t yC2;
    mpz_init(yC2); 

    conic_op(xC2, yC2, F1,F2, x,y,d,q);


    CipherText ct = {
        mpz_get_str(NULL,16,xC1),
        mpz_get_str(NULL,16,yC1),
        mpz_get_str(NULL,16,xC2),
        mpz_get_str(NULL,16,yC2)
    };

    return ct;
}

