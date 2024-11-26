

# questi sono benchmark a 2048 bit, il file è identico a quello a 7680 cambia solo il valore


# da terminale per far andare il file :
# bash benchmark2048.sh     


#!/bin/bash

# declare -i time=0
declare -i sum=0
# declare -i n=1000      
declare -i n=10


for ((i=0; i<n; i++))    
do
    time=$((./benchmark.out 2048) 2>&1)
    # time=$((./benchmarkGen.out) 2>&1)
    # time=$((./benchmarkEnc.out) 2>&1)
    # time=$((./benchmarkDec.out) 2>&1)

    secondi=${time%.*} 
    millisecondi=${time#*.}
    millisecondi=$(echo $millisecondi | cut -c 1-3)
    
    tmp=$(echo $secondi 1000 | awk '{print $1*$2}')
    tmp=$(echo $tmp $millisecondi | awk '{print $1+$2}')
    echo $millisecondi
    sum+=$(($tmp))

    # echo $tmp            # il tempo è in millisecondi
    # echo $sum    
done
# echo $time
# il risultato ora è in millesimi di secondo




media=$(echo "$sum $n" | awk '{printf "%.2f \n", $1/$2}') # media=$(($time/n))
# media=$(echo "$sum $n" | awk '{print $1/$2}') # media=$(($time/n))

media=$(echo $media| cut -c 1-4)


echo $media "media"



################# VARIANZA


declare -i sum=0
for ((i=0; i<n; i++))    
do
    time=$((./benchmark.out 2048) 2>&1)
    # time=$((./benchmarkGen.out) 2>&1)
    # time=$((./benchmarkEnc.out) 2>&1)
    # time=$((./benchmarkDec.out) 2>&1)

    secondi=${time%.*} 
    millisecondi=${time#*.}
    millisecondi=$(echo $millisecondi | cut -c 1-3)
    
    tmp=$(echo $secondi 1000 | awk '{print $1*$2}')
    tmp=$(echo $tmp $millisecondi | awk '{print $1+$2}')
   
    # echo "tempo"
    # echo $tmp            # il tempo è in millisecondi


    tmp=$(echo "$tmp $media" | awk '{print $1-$2}')

    # echo $tmp
    #tmp=$(echo $tmp $tmp | awk '{printf "%4.3f\n",$1*$2}')
    tmp=$(echo "$tmp $tmp" | awk '{print $1*$2}')


    sum+=$(($tmp))

    # sum=$(echo "$sum $tmp" | tr . , | awk '{print $1+$2}')    # tr perché dovevo scambiare "." e ","
    # echo $i  
done

varianza=$(echo "$sum $n" | awk '{printf "%.2f \n", $1/$2}')   # divido per n o per n-1 ?
dev=$(echo "$varianza" | awk '{print sqrt($1)}')



printf "\nmedia = "$media" millesimi di secondo"
printf "\nvarianza = "$varianza
printf "\ndeviazione starndard = "$dev
printf "\nnumero iterazioni = "$n"\n\n"






# le varianze sono state ottenute dividendo per n ,non per n-1


###############################################à valori a 7680 bit

# istanza completa





################
# generazione chiavi




###############
# enc




#############################################

# dec



