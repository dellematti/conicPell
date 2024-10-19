
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 512 bit, potrei aggiungerne altri nello stesso file o crearne altri diversi



# da terminale per far andare il file :
# bash benchmark.sh     


#!/bin/bash

declare -i time=0
declare -i n=100      # poi sarà su 1000

for ((i=0; i<n; i++))    
do
    VAR=$((./benchmark) 2>&1)
    SUBSTRING=$(echo $VAR| cut -c 4-6)
    time=$((10#$SUBSTRING + time))    

done
time=$(($time/10))
# echo $time
# il risultato ora è in millesimi di secondo



media=$(($time/n))

printf "\n"
echo "media = "$media" millesimi di secondo"
printf "\n"
echo "numero iterazioni = "$n
printf "\n"




