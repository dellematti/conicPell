import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Media','Deviazione'] 
# valori a 512 bit
Ygirls = [7.59,2.32] 
Zboys = [33.63,9.79] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, Ygirls, 0.4, label = 'C') 
plt.bar(X_axis + 0.2, Zboys, 0.4, label = 'Python') 
  
plt.xticks(X_axis, X) 
#plt.xlabel("Tempi per le varie fasi dell algoritmo") 
plt.ylabel("Millisecondi") 
plt.title("Media e deviazione di un istanza completa") 
plt.legend() 
plt.show()

# a 512 bit