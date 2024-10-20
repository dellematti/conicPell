
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 512 bit, potrei aggiungerne altri nello stesso file o crearne altri diversi



# da terminale per far andare il file :
# bash benchmark.sh     


#!/bin/bash

declare -i time=0
declare -i n=10000      

for ((i=0; i<n; i++))    
do
    VAR=$((./benchmark.out) 2>&1)
    SUBSTRING=$(echo $VAR| cut -c 4-6)
    time=$((10#$SUBSTRING + time))    
    # echo $i

done
time=$(($time/10))
# echo $time
# il risultato ora è in millesimi di secondo



media=$(echo "$time $n" | awk '{printf "%.2f \n", $1/$2}') # media=$(($time/n))





################# VARIANZA


declare -i sum=0
for ((i=0; i<n; i++))    
do
    VAR=$((./benchmark) 2>&1)
    SUBSTRING=$(echo $VAR| cut -c 4-5)
    # potrei salvare anche i valori minimi e massimi? (per il grafico)
    # e oltre al grafico di media e deviazione, potrei fare uno scatter plot

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


# media = 15.08
# varianza = 12.17
# deviazione starndard = 3.48855
# numero iterazioni = 10000


# media = 14.92
# varianza = 13.71
# deviazione starndard = 3.7027
# numero iterazioni = 10000


# media = 14.53
# varianza = 15.77
# deviazione starndard = 3.97115
# numero iterazioni = 10000


# media = 15.69
# varianza = 13.20
# deviazione starndard = 3.63318
# numero iterazioni = 10000



# media = 15.46
# varianza = 15.86
# deviazione starndard = 3.98246
# numero iterazioni = 10000






# input grande                       # ho messo in carica il pc mentre andava lo script (?)

# media = 13.16
# varianza = 30.36
# deviazione starndard = 5.50999
# numero iterazioni = 100000




# il pc in carica aumenta di così tanto le prestazioni (?)

# media = 7.59
# varianza = 5.40
# deviazione starndard = 2.32379
# numero iterazioni = 10000


# media = 7.68
# varianza = 5.60
# deviazione starndard = 2.36643
# numero iterazioni = 10000



# ora ho tolto il pc dalla carica

# media = 15.60
# varianza = 12.99
# deviazione starndard = 3.60416
# numero iterazioni = 10000


# infatti siamo tornati ai valori di prima




