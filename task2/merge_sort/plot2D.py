#!/usr/bin/python3

import numpy as np
from matplotlib import pyplot as plt


threads    	 = [1, 		2, 		3, 		4, 		5, 		6, 		7, 		8]

# 1000000, depth 8
times = [0.737805, 0.200524, 0.208016, 0.213275, 0.220332, 0.222958, 0.232571, 0.237819]

# 10000, depth 8
# times = [0.009291, 0.007144, 0.013393, 0.018851, 0.022681, 0.032360, 0.037080, 0.043341]

speedup      = []
efficiency   = []

def main():

	fig, ax = plt.subplots(nrows=2, figsize=[12, 10]) 

	fig.suptitle(r"Speedup $S$ and Efficiency $E$ as functions of $p$", fontsize=20)


	for i in range(0, len(threads)):
		speedup.append(times[0] / times[i])
		efficiency.append(times[0] / times[i] / threads[i])

	ax[0].plot(threads, speedup,    label=f"n = 1000000")
	ax[1].plot(threads, efficiency, label=f"n = 1000000")

	ax[0].grid()
	ax[0].set_xlabel(r"Threads $t$", fontsize=18)
	ax[0].set_ylabel(r"Speedup $S$", fontsize=18)
	ax[0].legend(loc="best", fontsize=14)


	ax[1].grid()
	ax[1].set_xlabel(r"Threads $t$", fontsize=18)
	ax[1].set_ylabel(r"Efficiency $E$", fontsize=18)

	# plt.show()
	plt.savefig('image.png')


if __name__ == '__main__':
    main()
