import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import commands, os, string

import subprocess as sb

fit = 2

def f(x, a, b, c):
	global fit
	if (fit == 2): 
		return 1.0*a*x**2+b*x
	if (fit == 3): 
		return 1.0*a*x**3+b*x**2+c*x

tau_str = ["0.500000","0.600000","0.800000", "1.000000", "1.200000","1.250000","1.400000", "1.500000","1.750000"] 
tau_num = []
for i in range(len(tau_str)): tau_num.append(float(tau_str[i]))

tau_len = len(tau_str)
names = ["Gauss Method fast", "Overrelaxation Method with tau=0.500000", "Overrelaxation Method with tau=1.250000", "Overrelaxation Method with tau=1.500000", "Overrelaxation Method with tau=1.750000", "Seidel Method",  "Jacobi Method"]
len = 7
python_names = ["Overrelaxation Method with tau=0.500000", "Overrelaxation Method with tau=1.500000", "Seidel Method", "Jacobi Method"]
python_len = 4

slow_names = ["Gauss Method", "Overrelaxation Method with tau=0.500000",   "Overrelaxation Method with tau=1.250000", "Overrelaxation Method with tau=1.500000", "Overrelaxation Method with tau=1.750000",  "Seidel Method",  "Jacobi Method"]
slow_len = 7
colors = {0: 'red', 1: 'black', 2: 'green', 3: 'y', 4: 'blue', 5: 'aqua', 6: 'slateblue', 7: 'm', 8: 'brown', 9: 'violet', 10: 'darkgreen', 11: 'darkred', 12: 'lime', 13: 'grey' , 14: 'indigo'}


mu_len = 7
data = dict()
ax = dict()
mu = dict()
x = dict()
x_slow = dict()
x_py = dict()
y = dict()
y_slow = dict()
y_py = dict()
coeff = dict()
coeff_sl = dict()
coeff_py = dict()

data_python = dict()
data_slow = dict()
#data_collected
for i in range(len):
	data[i] = pd.read_csv("temp_data/data_converged_"+names[i]+".txt", header = None, sep=' ')
	data[i] = data[i].rename(columns={0:"n", 1:"t", 2:"mu"})

for i in range(python_len):
	data_python[i] = pd.read_csv("temp_data/python/data_converged_"+python_names[i]+".txt", header = None, sep=' ')
	data_python[i] = data_python[i].rename(columns={0:"n", 1:"t"})

for i in range(slow_len):
	data_slow[i] = pd.read_csv("temp_data/slow/data_converged_"+slow_names[i]+".txt", header = None, sep=' ')
	data_slow[i] = data_slow[i].rename(columns={0:"n", 1:"t", 2:"mu"})

data_tau = dict()

for i in range(tau_len):
	data_tau[i] = pd.read_csv("temp_data/data_converged_Overrelaxation Method with tau="+tau_str[i]+".txt", header = None, sep=' ')
	data_tau[i] = data_tau[i].rename(columns={0:"n", 1:"t", 2:"mu"})
#data[len-1] = pd.read_csv("temp_data/data_diverged_"+names[len-1]+".txt", header = None, sep=' ') # Jacobi Method
#data[len-1] = data[len-1].rename(columns={0:"n", 1:"t", 2:"mu"})

#print all program in one graph
def all_methods(): 
	global fit
	print "\n\nAll Methods: \n"
	for i in range(len):
		ax[i] = plt.subplot()

		if (i!= 0) : fit = 2
		else: fit = 3
		maxT = data[i].t.max()
		print "| - ", names[i], ":"
		
		print "| - - fast"
		#full graph
		for k in range(mu_len):

			n = 10**k
			print "| - - - mu =", n
			#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
			x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
			coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
			y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])
			data[i][(data[i].mu==n)].plot(x='n', y = 't', kind='scatter',label = "mu = "+str(n),color=colors[k+1], ax=ax[i], s = 5, marker = 'o') #  & (data[i].bad != True)
			ax[i].plot(x[k+i*mu_len],y[k+i*mu_len],color=colors[k+1], linewidth = 0.5)

		if (i >= 0):

			print "| - - slow"
			maxT = max(data_slow[i].t.max(), maxT)
			for k in range(mu_len):
				n = 10**k
				print "| - - - mu =", n
				#data_slow[i].drop(data_slow[i][((data_slow[i].t-f(data_slow[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i]_slow.t*0.2)].index, axis=0, inplace = True)
				x_slow[k+i*mu_len] = np.arange(0, data_slow[i].n.max(), 1)
				coeff_sl[k+i*mu_len], covar = curve_fit(f, data_slow[i][(data_slow[i].mu==n)].n.values, data_slow[i][(data_slow[i].mu==n)].t.values)
				y_slow[k+i*mu_len] = f(x_slow[k+i*mu_len], coeff_sl[k+i*mu_len][0], coeff_sl[k+i*mu_len][1], coeff_sl[k+i*mu_len][2])
				data_slow[i][(data_slow[i].mu==n)].plot(x='n', y = 't', kind='scatter',label = "slow methods with mu = "+str(n),color=colors[k+1], ax=ax[i], s = 5, marker = 's') #  & (data[i].bad != True)
				ax[i].plot(x_slow[k+i*mu_len],y_slow[k+i*mu_len],color=colors[k+1], linewidth = 0.5)


			m = -1
			for l in range(python_len):
				if (python_names[l] == names[i]): m = l

			if  (m >= 0):

				maxT = max(data_python[m].t.max(),maxT)
				print "| - - python"
				#data_python[m].drop(data_python[m][((data_python[m].t-f(data_python[m].n*1.0, coeff[0], coeff[1], coeff[2])) > data_python[m].t*0.2)].index, axis=0, inplace = True)
				x_py[m] = np.arange(0, data_python[m].n.max(), 1)
				coeff_py, covar = curve_fit(f, data_python[m].n.values, data_python[m].t.values)
				y_py[m] = f(x_py[m], coeff_py[0], coeff_py[1], coeff_py[2])
				data_python[m].plot(x='n', y = 't', kind='scatter',label = "python" , ax=ax[i], s = 5, marker = "x") #  & (data[i].bad != True)
				ax[i].plot(x_py[m],y_py[m], linewidth = 1)
		maxT = int(maxT/10)*10+10
		if (i > 0): plt.axis([0,6000, 0, maxT])
		else : plt.axis([0,3000, 0, maxT])
		plt.legend(loc=2, fontsize='xx-small')
		plt.grid(True)
		plt.xlabel('size of matrix')
		plt.ylabel('T, c')
		plt.title(names[i]+ "(methods on python,\nuse finction to get value in class (slow method), forward get value)")
		#if (fit == 2): plt.text(data[i].n.max()/2, data[i].t.max()/3, "T = " + str(coeff[0])+r"$\cdot x^2$ + " + str(coeff[1]) + r"$\cdot x$")
		plt.savefig("temp_graphs/all/"+names[i]+" Full.png", dpi=500)
		plt.clf()

#print only latest fast program in graph
def only_fast_methods():
	global fit
	print "\n\nOnly fast methods:\n"
	for i in range(len):

		if (i!= 0) : 
			fit = 2
		else: 
			fit = 3

		ax[i] = plt.subplot()
		print "| - ", names[i], ":"

		for k in range(mu_len):
			n = 10**k
			print "| - - mu =", n
			#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
			x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
			coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
			y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])
			data[i][(data[i].mu==n)].plot(x='n', y = 't', kind='scatter',label = "mu = "+str(n),color=colors[k+1], ax=ax[i], s = 5, marker = 'o') #  & (data[i].bad != True)
			ax[i].plot(x[k+i*mu_len],y[k+i*mu_len],color=colors[k+1], linewidth = 0.5)

		maxT = data[i].t.max()
		maxT = int(maxT/10)*10+10
		if (i > 0): plt.axis([0,6000, 0, maxT])
		else : plt.axis([0,3000, 0, maxT])
			
		plt.legend(loc=2, fontsize='xx-small')
		plt.grid(True)
		plt.xlabel('size of matrix')
		plt.ylabel('T, c')
		plt.title(names[i] + "(only fast method)")
		#if (fit == 2): plt.text(data[i].n.max()/2, data[i].t.max()/3, "T = " + str(coeff[0])+r"$\cdot x^2$ + " + str(coeff[1]) + r"$\cdot x$")
		plt.savefig("temp_graphs/fast/"+names[i]+" only fast.png", dpi=500)
		plt.close()

#print only latest fast program and every mu for every graph
def for_all_mu():
	print "\n\nfor all mu:\n"
	global fit
	for i in range(len):

		if (i!= 0) : 
			fit = 2
		else:
			fit = 3
		print "| - ", names[i], ":"
		#aproximate
		for k in range(mu_len):

			ax[i] = plt.subplot()
			n = 10**k
			print "| - - mu = ", n
			#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
			x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
			coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
			y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])
			data[i][(data[i].mu==n)].plot(x='n', y = 't', kind='scatter',label = "mu = "+str(n),color=colors[k+1], ax=ax[i], s = 5, marker = 'o') #  & (data[i].bad != True)
			ax[i].plot(x[k+i*mu_len],y[k+i*mu_len],color=colors[k+1], linewidth = 0.5)

			maxT = data[i][(data[i].mu==n)].t.max()
			maxT = int(maxT/10)*10+10
			if (i > 0): plt.axis([0,6000, 0, maxT])
			else : plt.axis([0,3000, 0, maxT])

			
			plt.legend(loc=2, fontsize='xx-small')
			plt.grid(True)
			plt.xlabel('size of matrix')
			plt.ylabel('T, c')
			plt.title(names[i] + " (mu =" + str(n) + ")")
			plt.savefig("temp_graphs/for_all_mu/"+names[i]+" mu = " + str(n) + ".png", dpi=500)
			plt.close()


def a_mu():
	global fit
	print "\n\na(mu):\n"
	for i in range(len):
		ax[i] = plt.subplot()

		if (i!= 0) : fit = 2
		else: fit = 3

		
		print "| - ", names[i], ":"		
		
		print "| - - approximate"
		#aproximate
		for k in range(mu_len):

			ax[i] = plt.subplot()

			n = 10**k
			print "| - - - mu =", n
			#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
			x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
			coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
			y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])

		# a(mu)
		print "| -- plotting"
		mu_mas = []
		mu[i] = plt.subplot()
		for k in range(mu_len):
			n = 10**k
			print "| - - - mu: ", n
			mu[i].plot([k],[coeff[k+i*mu_len][0]],'rx')
			mu_mas.append(coeff[k+i*mu_len][0])

		mu[i].plot(range(mu_len), mu_mas, 'r-')
		plt.grid(True)
		plt.xlabel('number of conditionality')
		if (i > 0): plt.ylabel(r'$a$ in $a\cdot x^2 + b\cdot x + c$')
		else: plt.ylabel(r'$a$ in $a\cdot x^3 + b\cdot x^2 + c*x + d$')
		plt.title(names[i] + "\n" + r"$\log_{10}$(number of conditionality)")
		#if (fit == 2): plt.text(data[i].n.max()/2, data[i].t.max()/3, "T = " + str(coeff[0])+r"$\cdot x^2$ + " + str(coeff[1]) + r"$\cdot x$")
		plt.savefig("temp_graphs/mu/"+names[i]+" mu.png", dpi=500)
		plt.clf()

def plot_all_in_one():
	global fit
	print "\n\nplot all methods:\n"
	com = plt.subplot();
	maxT = 0

	for i in range(1, len):

		ax[i] = plt.subplot()

		if (i!= 0) : fit = 2
		else: fit = 3

		print "| - ", names[i], ":"		
		
		x[i*mu_len] = np.arange(0, data[i].n.max(), 1)
		coeff[i*mu_len], covar = curve_fit(f, data[i].n.values, data[i].t.values)
		y[i*mu_len] = f(x[i*mu_len], coeff[i*mu_len][0], coeff[i*mu_len][1], coeff[i*mu_len][2])

		data[i].plot(x='n', y = 't',kind = 'scatter', label = names[i], color=colors[i], ax=com, s = 5)
		com.plot(x[i*mu_len], y[i*mu_len], label = names[i]+" line", linewidth = 0.5, color=colors[i])
		maxT = max(data[i].t.max(), maxT)

	# for i in range(tau_len):
	# 	poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
	# 	x_tau = np.arange(0, data[i].n.max(), 1)
	# 	y_tau = f(x_tau, coeff[i*mu_len][0], coeff[i*mu_len][1], coeff[i*mu_len][2])

	# 	data_tau[i].plot(x='n', y = 't',kind = 'scatter', label = names[i], color=colors[i], ax=com, s = 5)
	# 	com.plot(x_tau, y_tau, label = "Overrelaxation Method with tau="+tau_str[i]+"line", linewidth = 0.5, color=colors[i])

	maxT = int(maxT/10)*10+10
	if (i > 0): plt.axis([0,6000, 0, maxT])
	else : plt.axis([0,3000, 0, maxT])
		
	plt.legend(loc=2, fontsize='xx-small')
	plt.grid(True)
	plt.xlabel('size of matrix')
	plt.ylabel('T, c')
	plt.title("Methods")
	plt.savefig("temp_graphs/All Methods.png", dpi=500)
	plt.clf()

	print "without point:"

	com = plt.subplot();
	
	maxT = 0
	i = len-1

	ax[i] = plt.subplot()

	if (i!= 0) : fit = 2
	else: fit = 3

	
	print "| - ", names[i], ":"		
	
	print "| - - approximate"
	#aproximate
	for k in range(mu_len):
		n = 10**k
		print "| - - - mu =", n
		#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
		x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
		coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
		y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])
	maxT = max(data[i].t.max(), maxT)

	com.plot(x[i*mu_len], y[i*mu_len], label = names[i]+" line", linewidth = 1, color=colors[i])

	for i in range(tau_len):
		poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
		x_tau = np.arange(0, data_tau[i].n.max(), 1)
		y_tau = f(x_tau, poeff[0], poeff[1], poeff[2])
		maxT = max(data_tau[i].t.max(), maxT)
		com.plot(x_tau, y_tau, label = "Overrelaxation Method with tau="+tau_str[i]+" line", linewidth = 1, color=colors[i+1])

	maxT = int(maxT/10)*10+10
	if (i > 0): plt.axis([0,6000, 0, maxT])
	else : plt.axis([0,3000, 0, maxT])
		
	plt.legend(loc=2, fontsize='xx-small')
	plt.grid(True)
	plt.xlabel('size of matrix')
	plt.ylabel('T, c')
	plt.title("Methods")
	plt.savefig("temp_graphs/All Methods (without point).png", dpi=500)
	plt.clf()

def plot_over_gif():
	global fit
	print "\n\nplot overrelaxation gif:\n"

	for i in range(tau_len):
		com = plt.subplot();
		plt.axis([0,6000, 0, 20])
		poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
		x_tau = np.arange(0, data_tau[i].n.max(), 1)
		y_tau = f(x_tau, poeff[0], poeff[1], poeff[2])

		data_tau[i].plot(x='n', y = 't',kind = 'scatter', label = tau_str[i], color=colors[i], ax=com, s = 5)
		com.plot(x_tau, y_tau, label = "Overrelaxation Method with tau="+tau_str[i]+"\t line", linewidth = 0.5, color=colors[i])
		plt.text(2000, 10, str(float(tau_str[i])), fontsize=20, fontweight='bold')
		plt.legend(loc=2, fontsize='xx-small')
		plt.grid(True)
		plt.xlabel('size of matrix')
		plt.ylabel('T, c')
		plt.title("Methods")
		plt.savefig("temp_graphs/gif_tau/"+str(i)+".png", dpi=500)
		plt.clf()
	sb.Popen(['convert', '-background', 'white', '-alpha', 'remove', '-layers', 'OptimizePlus', '-delay', '50', 'temp_graphs/gif_tau/*.png', '-loop', '1', 'temp_graphs/tau.gif'])

	# print "without point:"

	# com = plt.subplot();
	
	# for i in range(1, len):

	# 	ax[i] = plt.subplot()

	# 	if (i!= 0) : fit = 2
	# 	else: fit = 3

		
	# 	print "| - ", names[i], ":"		
		
	# 	print "| - - approximate"
	# 	#aproximate
	# 	for k in range(mu_len):
	# 		n = 10**k
	# 		print "| - - - mu =", n
	# 		#data[i].drop(data[i][((data[i].t-f(data[i].n*1.0, coeff[0], coeff[1], coeff[2])) > data[i].t*0.2)].index, axis=0, inplace = True)
	# 		x[k+i*mu_len] = np.arange(0, data[i].n.max(), 1)
	# 		coeff[k+i*mu_len], covar = curve_fit(f, data[i][(data[i].mu==n)].n.values, data[i][(data[i].mu==n)].t.values)
	# 		y[k+i*mu_len] = f(x[k+i*mu_len], coeff[k+i*mu_len][0], coeff[k+i*mu_len][1], coeff[k+i*mu_len][2])

	# 	com.plot(x[i*mu_len], y[i*mu_len], label = names[i]+" line", linewidth = 1, color=colors[i])

	# # for i in range(tau_len):
	# # 	poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
	# # 	x_tau = np.arange(0, data_tau[i].n.max(), 1)
	# # 	y_tau = f(x_tau, poeff[0], poeff[1], poeff[2])

	# # 	com.plot(x_tau, y_tau, label = "Overrelaxation Method with tau="+tau_str[i]+" line", linewidth = 1, color=colors[i+len])

	# plt.legend(loc=2, fontsize='xx-small')
	# plt.grid(True)
	# plt.xlabel('size of matrix')
	# plt.ylabel('T, c')
	# plt.title("Methods")
	# plt.savefig("temp_graphs/All Methods (without point and shot).png", dpi=500)
	# plt.clf()

#work with tau
def tau_dependense():
	global fit
	fit = 2
	print "\n\nplot overrelaxation methods:\n"
	coeff_tau = []

	for i in range(tau_len):
		poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
		coeff_tau.append(poeff[0])
	#seidel (tau = 1)
	i = tau_len
	data_tau[i] = pd.read_csv("temp_data/data_converged_Seidel Method.txt", header = None, sep=' ')
	data_tau[i] = data_tau[i].rename(columns={0:"n", 1:"t", 2:"mu"})
	poeff, povar = curve_fit(f, data_tau[i].n.values, data_tau[i].t.values)
	coeff_tau.append(poeff[0])
	tau_num.append(1.0)

	tau_plt = plt.subplot();


	pd_tau = pd.DataFrame(tau_num)
	pd_tau[1] = coeff_tau

	pd_tau.sort(columns = 0, inplace = True)

	tau_plt.plot(pd_tau[0].values, pd_tau[1].values, 'rx')
	tau_plt.plot(pd_tau[0].values, pd_tau[1].values, 'r-')

	print pd_tau
	#plt.legend(loc=2, fontsize='xx-small')
	plt.grid(True)
	plt.xlabel(r'$\tau$')
	plt.ylabel('coeff')
	plt.title("Overrelaxation Methods")
	plt.savefig("temp_graphs/Overrelaxation Methods.png", dpi=500)
	plt.clf()

all_methods()
only_fast_methods()
for_all_mu()
a_mu()
plot_all_in_one()
plot_over_gif()
tau_dependense()
