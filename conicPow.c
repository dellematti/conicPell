

// nei parametri out1 e out2 verrà salvato il risultato dell operazione. Questi parametri al termine della funzione
// vengono quindi modificati
void conic_op (mpz_t out1, mpz_t out2,mpz_t x1,mpz_t y1, mpz_t x2, mpz_t y2, mpz_t d, mpz_t n) {

    mpz_t tmp;
    mpz_init(tmp);

    mpz_t tmp2;
    mpz_init(tmp2);


    mpz_mul ( tmp, x1, x2);
    mpz_mul ( tmp2, y1, y2);
    mpz_mul ( tmp2, tmp2, d);
    mpz_add(out1, tmp, tmp2);
    mpz_mod(out1,out1,n);

    mpz_mul ( tmp, x1, y2);
    mpz_mul ( tmp2, y1, x2);
    mpz_add(out2, tmp, tmp2); 

    mpz_mod(out2,out2,n);

    // mpz_clear(tmp);   

}



// nei parametri res1 e res2 verrà salvato il risultato dell operazione. Questi parametri al termine della funzione
// vengono quindi modificati
// i parametri che la funzione riceve devono essere già inizializzati
void conic_pow(mpz_t res1, mpz_t res2, mpz_t xG, mpz_t yG, mpz_t e, mpz_t d, mpz_t n) {
    // devo convertire il numero "e" in binario e iterare sopra
    // const void * p = (const void *)(void*)&e;    // ora p è il puntatore alla memoria dove si trova e
    char *p;
    p = mpz_get_str(NULL,2,e);         // p = mpz_get_str(NULL,10,e);

    mpz_set_ui(res1, 1);
    mpz_set_ui(res2, 0);

    int len = strlen(p);
    for (int i = 0; i<len; i++) {
        char bit = *(p+i);
        
        mpz_t out1;
        mpz_t out2;
        mpz_init(out1);
        mpz_init(out2);

        conic_op(out1,out2, res1, res2,res1,res2, d, n);
        mpz_set(res1, out1);
        mpz_set(res2, out2);
          

        if (bit == '1') {
            conic_op(out1,out2, res1,res2, xG,yG, d, n);
            mpz_set(res1, out1);
            mpz_set(res2, out2);
        }
    }

    // mpz_clear();
}



