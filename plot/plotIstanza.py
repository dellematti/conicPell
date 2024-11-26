import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Media','Deviazione'] 
# valori a 512 bit
# c = [7.59,2.32] 
# python = [33.63,9.79] 

# valori a 7680 bit
c = [4970,1191.22] 
python = [50816.8,14031.653170243] 


  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, c, 0.4, label = 'C') 
plt.bar(X_axis + 0.2, python, 0.4, label = 'Python') 
  
plt.xticks(X_axis, X) 
#plt.xlabel("Tempi per le varie fasi dell algoritmo") 
plt.ylabel("Millisecondi") 
plt.title("Media e deviazione di un istanza completa") 
plt.legend() 
plt.show()
