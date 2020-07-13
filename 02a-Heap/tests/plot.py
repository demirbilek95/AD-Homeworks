import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('default')

data = pd.read_csv("insert.txt",sep="\t")

plt.tight_layout()
plt.figure(figsize=(10,6))
plt.plot(data["Number_of_Elements"], data["Times"])
plt.title("Insert Elements")
plt.xlabel("Number of Elements")
plt.ylabel("Time")
plt.savefig("insert_plot.png")

import pandas as pd
delete_min = pd.read_csv("delete_min.txt",sep="\t")
plot = delete_min.plot(x="n",title = "Delete_min Comparasion",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('delete_min.png')


