import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
from scipy.optimize import curve_fit

names = ["Gauss Method", "Overrelaxation Method with tau=0.500000",  "Seidel Method", "Jacobi Method", "Overrelaxation Method with tau=1.500000"]
len = 5

colors = {0: 'red', 2: 'black', 4: 'green', 8: 'yellow', 16: 'blue', 32: 'aqua', 64: 'c', 128: 'm', 256: 'brown', 512: 'violet', 1024: 'darkgreen'}


data = dict()
#data_collected
for i in range(len):
	data[i] = pd.read_csv("data/data_converged_"+names[i]+".txt", header = None, sep=' ');

for i in range(len):
	ax = plt.subplot()
	for k in range(10):
		n = 2**(k+1)
		data[i][data[i][2]==n].plot.scatter(x=0, y = 1, label = "mu = "+str(n),color=colors[n], ax=ax)

	plt.legend(loc=2, fontsize='xx-small')
	plt.grid(True)
	plt.xlabel('size of matrix')
	plt.ylabel('T, c')
	plt.title(names[i])
	plt.savefig("graph_python/"+names[i]+"Time(size of matrix).png", dpi=300)
	plt.clf()
