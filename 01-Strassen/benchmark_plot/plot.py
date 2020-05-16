import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("benchmark_results.txt", sep ="\t",header=None, skiprows=1)
data.columns = ["n","Naive Alg.", "Strassen Alg.", "Improved Strassen", "Same result"]

fig = plt.figure(figsize=(12,8))
plt.ylabel("Time")
plt.xlabel("Size of Array")

ax = plt.subplot(111)

ax.plot(data["n"], data["Naive Alg."], label = "Naive Alg.")
ax.plot(data["n"], data["Strassen Alg."], label = "Strassen Alg.")
ax.plot(data["n"], data["Improved Strassen"], label = "Improved Strassen")

plt.title("Benchmark Results")
ax.legend()

plt.savefig("Benchmark_results.png")
plt.show("Benchmark_results.png")
