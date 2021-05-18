import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as st

file = open('rsq-random-ranges.txt', 'r')

number_of_elements = [100, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
                      150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000, 550000, 600000, 650000, 700000, 750000, 800000, 850000, 900000]
seconds = []
data = []
yerrormin = []
yerrormax = []

for line in file:
    line = line.replace("\n", "")
    if line != "---":
        data.append(float(line))
    else:
        print(len(data))
        sum = 0
        for num in data:
            sum += num
        sum = sum / len(data)
        seconds.append(sum)
        print(sum)

        error = st.t.interval(alpha=0.95, df=len(data) - 1, loc=np.mean(data), scale=st.sem(data))
        print(error)
        yerrormin.append(error[0])
        yerrormax.append(error[1])
        data = []
        sum = 0


# plt.xkcd()

fig = plt.figure(figsize=(23, 10))
ax1 = fig.add_subplot(111)

ax1.plot(number_of_elements, seconds, label="data")
ax1.scatter(number_of_elements, seconds)

ax1.set_xlabel("N, number of elements")
ax1.set_ylabel("T, nanoseconds")
ax1.set_title("RSQ (random ranges) - SEGMENT TREE")

yerror = [yerrormin, yerrormax]
# ax1.errorbar(number_of_elements, seconds, yerr=yerror, fmt=' ', capsize=3)
ax1.set_axisbelow(True)
ax1.scatter(number_of_elements, yerrormax, s=100, c='red', marker='_', linewidths=5)
ax1.scatter(number_of_elements, yerrormin, s=100, c='red', marker='_',  linewidths=5)

ax1.legend()
ax1.minorticks_on()
plt.grid(which="major", color='b', linestyle='-', linewidth=0.15)
plt.grid(which="minor", color='g', linestyle='--', linewidth=0.10)

plt.savefig("rsq-random-ranges-segment-tree-plot.png")

plt.show()
