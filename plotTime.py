import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Generazione','Encryption','Decryption'] 
# valori a 512 bit
Ygirls = [5.35,2.86,0.96] 
Zboys = [19.87,11.2,4.18] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, Ygirls, 0.4, label = 'C') 
plt.bar(X_axis + 0.2, Zboys, 0.4, label = 'Python') 
  
plt.xticks(X_axis, X) 
#plt.xlabel("Tempi per le varie fasi dell algoritmo") 
plt.ylabel("Millisecondi") 
plt.title("Tempi per le diverse fasi dell algoritmo") 
plt.legend() 
plt.show()

# a 512 bit