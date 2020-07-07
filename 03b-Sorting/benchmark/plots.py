import pandas as pd
import matplotlib.pyplot as plt

quick_vs_quickselect = pd.read_csv("quickselect.txt",sep="\t")

plot = quick_vs_quickselect.plot(x="Size",title = "Comparison of Quick Sort and Quick Sort with Select",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('quickselect.png')

quick_vs_quickselect2 = pd.read_csv("quickselect2.txt",sep="\t")

plot = quick_vs_quickselect2.plot(x="Size",title = "Comparison of Quick Sort and Quick Sort with Select Higher Input Size",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('quickselect2.png')
