import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Generazione','Encryption','Decryption'] 
Ygirls = [2.83,0.55,0.8] 
Zboys = [10.23, 0.42, 0.3] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, Ygirls, 0.4, label = 'C') 
plt.bar(X_axis + 0.2, Zboys, 0.4, label = 'Python') 
  
plt.xticks(X_axis, X) 



#plt.xlabel("Tempi per le varie fasi dell algoritmo") 
plt.ylabel("Millisecondi") 
plt.title("Deviazione standard per le diverse fasi dell algoritmo") 
plt.legend() 
plt.show()