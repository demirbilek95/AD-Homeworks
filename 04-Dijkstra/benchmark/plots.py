import pandas as pd
import matplotlib.pyplot as plt

quick_vs_quickselect = pd.read_csv("output.txt",sep="\t")

plot = quick_vs_quickselect.plot(x="Size",title = "Comparison of Dijkstra Implementations",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('dijkstra_benc.png')

