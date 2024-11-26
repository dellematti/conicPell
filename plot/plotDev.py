import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Generazione','Encryption','Decryption'] 
# valori a 512 bit
c = [2.83,0.55,0.8] 
python = [10.23, 0.42, 0.3]

# valori a 7680 bit
c = [1076.29, 53.9585 , 17.3491] 
python = [12705.328 , 230.16 , 36.12 ]


X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, c, 0.4, label = 'C') 
plt.bar(X_axis + 0.2, python, 0.4, label = 'Python') 
  
plt.xticks(X_axis, X) 



#plt.xlabel("Tempi per le varie fasi dell algoritmo") 
plt.ylabel("Millisecondi") 
plt.title("Deviazione standard per le diverse fasi dell algoritmo") 
plt.legend() 
plt.show()