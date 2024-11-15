
# poi potrei cambiare i nomi, questo è il benchmark completo, gen_enc_dec
# quelli solo di enc e dec ha senso farli con le stesse chiavi fisse su python e qui
# quello di gen sarà invece chiaramente casuale e basta

# questi sono benchmark a 7680 bit,


# da terminale per far andare il file :
# bash benchmark7680.sh     


#!/bin/bash

# declare -i time=0
declare -i sum=0
# declare -i n=10000      
declare -i n=100


for ((i=0; i<n; i++))    
do
    time=$((./benchmark.out) 2>&1)
    # VAR=$((./benchmarkGen.out) 2>&1)
    # VAR=$((./benchmarkEnc.out) 2>&1)
    # VAR=$((./benchmarkDec.out) 2>&1)

    secondi=${time%.*} 
    millisecondi=${time#*.}
    millisecondi=$(echo $millisecondi | cut -c 1-3)
    
    tmp=$(echo $secondi 1000 | awk '{print $1*$2}')
    tmp=$(echo $tmp $millisecondi | awk '{print $1+$2}')
    # echo $millisecondi
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
    time=$((./benchmark.out) 2>&1)
    # VAR=$((./benchmarkGen.out) 2>&1)
    # VAR=$((./benchmarkEnc.out) 2>&1)
    # VAR=$((./benchmarkDec.out) 2>&1)

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


# media = 4965 millesimi di secondo
# varianza = 1179174.97
# deviazione starndard = 1085.9
# numero iterazioni = 100


# real	16m42.291s
# user	16m17.860s
# sys	0m24.481s









# media = 4970 millesimi di secondo
# varianza = 1419012.02
# deviazione starndard = 1191.22
# numero iterazioni = 100


# real	16m46.296s
# user	16m20.962s
# sys	0m25.424s