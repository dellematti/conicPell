
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 512 bit, potrei aggiungerne altri nello stesso file o crearne altri diversi



# da terminale per far andare il file :
# bash benchmark.sh     


#!/bin/bash

# declare -i time=0
declare -i sum=0
# declare -i n=10000      
declare -i n=3


for ((i=0; i<n; i++))    
do
    time=$((./benchmark.out) 2>&1)
    # VAR=$((./benchmarkGen.out) 2>&1)
    # VAR=$((./benchmarkEnc.out) 2>&1)
    # VAR=$((./benchmarkDec.out) 2>&1)

    secondi=${time%.*} 
    millisecondi=${time#*.}
    millisecondi=$(echo $millisecondi | cut -c 4-6)
    
    tmp=$(echo $secondi 1000 | awk '{print $1*$2}')
    sum=$(($tmp+$millisecondi + $sum))

    # echo $time            # il tempo è in millisecondi
done
# echo $time
# il risultato ora è in millesimi di secondo


media=$(echo "$sum $n" | awk '{printf "%.2f \n", $1/$2}') # media=$(($time/n))





################# VARIANZA


declare -i sum=0
for ((i=0; i<n; i++))    
do
    time=$((./benchmark.out) 2>&1)
    # time=$((./benchmarkGen.out) 2>&1)
    # time=$((./benchmarkEnc.out) 2>&1)
    # time=$((./benchmarkDec.out) 2>&1)

    # SUBSTRING=$(echo $VAR| cut -c 4-5)


    secondi=${time%.*} 
    millisecondi=${time#*.}
    millisecondi=$(echo $millisecondi | cut -c 4-6)
    
    tmp=$(echo $secondi 1000 | awk '{print $1*$2}')
    time=$(($tmp+$millisecondi))


    tmp=$(echo "$time $media" | awk '{print $1-$2}')
    echo $tmp
    tmp=$(echo $tmp $tmp | awk '{printf "%4.3f\n",$1*$2}')

    sum=$(echo "$sum $tmp" | tr . , | awk '{print $1+$2}')    # tr perché dovevo scambiare "." e ","
    # echo $i  
done

varianza=$(echo "$sum $n" | awk '{printf "%.2f \n", $1/$2}')   # divido per n o per n-1 ?
dev=$(echo "$varianza" | awk '{print sqrt($1)}')



printf "\nmedia = "$media" millesimi di secondo"
printf "\nvarianza = "$varianza
printf "\ndeviazione starndard = "$dev
printf "\nnumero iterazioni = "$n"\n\n"






# le varianze sono state ottenute dividendo per n ,non per n-1


###############################################à valori a 512 bit


