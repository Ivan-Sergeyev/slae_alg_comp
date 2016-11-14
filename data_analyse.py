import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
from scipy.optimize import curve_fit

names = {"gauss": "data_converged_Gauss Method.txt", "over05":"data_converged_Overrelaxation Method with tau=0.500000.txt",  "seidel": "data_converged_Seidel Method.txt", "jacobi_con":"data_converged_Jacobi Method.txt",  "over15":"data_converged_Overrelaxation Method with tau=1.500000.txt", "jacobi_div":"data_diverged_Jacobi Method.txt"}

gauss = pd.read_csv("data/"+names["gauss"], header = None, sep=' ');

gauss.plot.scatter(x=0, y = 1)
plt.savefig("graph_python/gauss_n.png", dpi=300)


seidel = pd.read_csv("data/"+names["seidel"], header = None, sep=' ');
seidel.fillna(0,inplace=True)

ax = plt.subplot();

colors = {0: 'red', 2: 'black', 4: 'green', 8: 'yellow', 16: 'blue', 32: 'aqua', 64: 'c', 128: 'm', 256: 'brown', 512: 'violet', 1024: 'darkgreen'}

#seidel[seidel[2]==0].plot.scatter(x=0, y = 1,label = "without mu",color=colors[0], ax=ax);
for i in range(10):
	n = 2**(i+1)
	seidel[seidel[2]==n].plot.scatter(x=0, y = 1, label = "mu = "+str(n),color=colors[n], ax=ax)

plt.legend(loc=2, fontsize='xx-small')
plt.grid(True)
plt.xlabel('size of matrix')
plt.ylabel('T, c')
plt.savefig("graph_python/seidel_n.png", dpi=300)
