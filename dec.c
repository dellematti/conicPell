

void funzioneDec(mpz_t output, CipherText ct, Keys keys) {

    mpz_t xC1;
    mpz_init(xC1);
    mpz_t yC1;
    mpz_init(yC1);
    mpz_t xC2;
    mpz_init(xC2);
    mpz_t yC2;
    mpz_init(yC2);

    mpz_set_str(xC1, ct.xC1,16);
    mpz_set_str(yC1, ct.yC1,16);
    mpz_set_str(xC2, ct.xC2,16);
    mpz_set_str(yC2, ct.yC2,16);


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

    mpz_set_str(q, keys.pk.q,16);       // più efficiente a fare ogni volta keys.pk oppure inizializzo un pk?
    mpz_set_str(d, keys.pk.d,16);
    mpz_set_str(xG, keys.pk.xG,16);
    mpz_set_str(yG, keys.pk.yG,16);
    mpz_set_str(xH, keys.pk.xH,16);
    mpz_set_str(yH, keys.pk.yH,16);


    mpz_t k;
    mpz_init(k);
    mpz_set_str(k, keys.sk.k,16);


    int n = mpz_sizeinbase (q, 2);   
    // int var = n/16;               // C fa in automatico la floor division (vale per tutte le versioni di C ??? TODO )
    mp_bitcnt_t var = n/16;


    mpz_t xF;
    mpz_init(xF);    
    mpz_t yF;
    mpz_init(yF);    

    conic_pow(xF,yF, xC1, yC1, k, d, q);


    // M = conic_op((xF, - yF % q), (xC2, yC2), d, q)
    mpz_t tmp;
    mpz_init(tmp);
    mpz_sub(tmp,tmp,yF);

    // mpz_out_str(stdout,10,tmp);
    // printf("\n");

    mpz_mod(tmp,tmp,q);  

    mpz_t M1;
    mpz_init(M1);
    mpz_t M2;
    mpz_init(M2);
    conic_op(M1, M2, xF, tmp, xC2, yC2, d, q); 


    // msg = M[1] >> var
    mpz_init(output);
    mpz_fdiv_q_2exp(output,M2, var);

}