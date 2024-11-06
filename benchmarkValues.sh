
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 512 bit, potrei aggiungerne altri nello stesso file o crearne altri diversi



# da terminale per far andare il file :
# bash benchmarkValues.sh     


# script che esegue n volte il benchmark a 512 bit e salva i risultati in un file 


#!/bin/bash

declare -i time=0
declare -i n=10000      
# declare -i n=100 

rm time512bit.txt
touch -f time512bit.txt

for ((i=0; i<n; i++))    
do
    VAR=$((./benchmark.out) 2>&1)
    SUBSTRING=$(echo $VAR| cut -c 4-6)
    time=$((10#$SUBSTRING))    
    echo -e $((time / 10)) >> time512bit.txt   # il risultato è in millesimi di secondo
done



