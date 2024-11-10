
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 512 bit, potrei aggiungerne altri nello stesso file o crearne altri diversi



# da terminale per far andare il file :
# bash benchmark.sh     


#!/bin/bash

declare -i time=0
declare -i n=10000      
# declare -i n=1000

for ((i=0; i<n; i++))    
do
    # VAR=$((./benchmark.out) 2>&1)
    # VAR=$((./benchmarkGen.out) 2>&1)
    # VAR=$((./benchmarkEnc.out) 2>&1)
    VAR=$((./benchmarkDec.out) 2>&1)

    SUBSTRING=$(echo $VAR| cut -c 4-6)
    time=$((10#$SUBSTRING + time))    
    echo $(echo $VAR| cut -c 4-6)

done
time=$(($time/10))
# echo $time
# il risultato ora è in millesimi di secondo



media=$(echo "$time $n" | awk '{printf "%.2f \n", $1/$2}') # media=$(($time/n))





################# VARIANZA


declare -i sum=0
for ((i=0; i<n; i++))    
do
    # VAR=$((./benchmark.out) 2>&1)
    # VAR=$((./benchmarkGen.out) 2>&1)
    # VAR=$((./benchmarkEnc.out) 2>&1)
    VAR=$((./benchmarkDec.out) 2>&1)

    SUBSTRING=$(echo $VAR| cut -c 4-5)
    tmp=$(echo "$SUBSTRING $media" | awk '{print $1-$2}')
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


# con benchmark.out     cioè istanza completa

# media = 7.59
# varianza = 5.40
# deviazione starndard = 2.32379
# numero iterazioni = 10000


# media = 7.68
# varianza = 5.60
# deviazione starndard = 2.36643
# numero iterazioni = 10000



#######################################


# con benchmarkgen    generazione chiavi

# media = 5.39
# varianza = 8.50
# deviazione starndard = 2.91548
# numero iterazioni = 10000



# media = 5.35
# varianza = 8.05
# deviazione starndard = 2.83725
# numero iterazioni = 10000



####################################


# con benchmarkEnc     

# media = 2.88
# varianza = 0.31
# deviazione starndard = 0.556776
# numero iterazioni = 10000



# media = 2.86
# varianza = 0.30
# deviazione starndard = 0.547723
# numero iterazioni = 10000



####################################


# con benchmarkDec

# media = 0.96
# varianza = 0.75
# deviazione starndard = 0.866025
# numero iterazioni = 100


# media = 1.07
# varianza = 0.76
# deviazione starndard = 0.87178
# numero iterazioni = 10000
