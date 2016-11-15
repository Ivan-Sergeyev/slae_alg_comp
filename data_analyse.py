import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
from scipy.optimize import curve_fit

fit = 2
def f(x, a, b, c): 
	if (fit == 2): return 1.0*a*x**2+b*x
	if (fit == 3): return 1.0*a*x**3+b*x**2+c*x

names = ["Gauss Method", "Overrelaxation Method with tau=0.500000",  "Seidel Method", "Overrelaxation Method with tau=1.500000", "Jacobi Method"]
len = 5

colors = {0: 'red', 1: 'black', 2: 'green', 3: 'yellow', 4: 'blue', 5: 'aqua', 6: 'c', 7: 'm', 8: 'brown', 9: 'violet', 10: 'darkgreen'}


data = dict()
ax = dict()
x = dict()
y = dict()
#data_collected
for i in range(len-1):
	data[i] = pd.read_csv("data/data_converged_"+names[i]+".txt", header = None, sep=' ')
	data[i] = data[i].rename(columns={0:"n", 1:"t", 2:"mu"})

data[len-1] = pd.read_csv("data/data_diverged_"+names[len-1]+".txt", header = None, sep=' ') # Jacobi Method
data[len-1] = data[len-1].rename(columns={0:"n", 1:"t", 2:"mu"})

for i in range(len):
	ax[i] = plt.subplot()
	
	x[i] = np.arange(0, data[i].n.max(), 1)
	if (i!= 0) : fit = 2
	else: fit = 3
	coeff, covar = curve_fit(f, data[i].n.values, data[i].t.values)
	
	data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)

	coeff, covar = curve_fit(f, data[i].n.values, data[i].t.values)
	y[i] = f(x[i], coeff[0], coeff[1], coeff[2])

	for k in range(10):
		n = 2**(k+1)
		data[i][(data[i].mu==n)].plot(x='n', y = 't', kind='scatter',label = "mu = "+str(n),color=colors[k+1], ax=ax[i], s = 10) #  & (data[i].bad != True)
	plt.plot(x[i],y[i], linewidth = 0.5)
	plt.legend(loc=2, fontsize='xx-small')
	plt.grid(True)
	plt.xlabel('size of matrix')
	plt.ylabel('T, c')
	plt.title(names[i])
	#if (fit == 2): plt.text(data[i].n.max()/2, data[i].t.max()/3, "T = " + str(coeff[0])+r"$\cdot x^2$ + " + str(coeff[1]) + r"$\cdot x$")
	plt.savefig("graph_python/"+names[i]+"Time(size of matrix).png", dpi=500)
	plt.clf()


com = plt.subplot();
for i in range(len-2):
	k = i+1;
	data[k].plot(x='n', y = 't',kind = 'scatter', label = names[k], color=colors[k], ax=com, s = 10)
	plt.plot(x[k], y[k], label = names[k]+"line", linewidth = 0.5)
plt.legend(loc=2, fontsize='xx-small')
plt.grid(True)
plt.xlabel('size of matrix')
plt.ylabel('T, c')
plt.title("Methods")
plt.savefig("graph_python/All Method.png", dpi=500)
plt.clf()
	# data[i].plot.scatter(x=2, y = 1)
	# plt.grid(True)
	# plt.xlabel('number of conditionality')
	# plt.ylabel('T, c')
	# plt.title(names[i])
	# plt.savefig("graph_python/"+names[i]+"Time(number of conditionality).png", dpi=300)
	# plt.clf()
