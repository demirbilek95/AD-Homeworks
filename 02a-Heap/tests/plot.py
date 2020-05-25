import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('default')

data = pd.read_csv("output.txt",sep="\t")

plt.tight_layout()
plt.figure(figsize=(10,6))
plt.plot(data["Number_of_Elements"], data["Times"])
plt.xlabel("Number of Elements")
plt.ylabel("Time")
plt.savefig("plot.png")

