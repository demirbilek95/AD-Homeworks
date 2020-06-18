import pandas as pd
import matplotlib.pyplot as plt

all_data = pd.read_csv("all.txt",sep="\t")

plot = all_data.plot(x="Size",title = "Comparison of Sorting Algorithms",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('all.png')

insertion_data = pd.read_csv("insertion.txt",sep="\t")

plot = insertion_data.plot(x="Size",title = "Insertion Sort",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('insertion.png')

quick_data = pd.read_csv("quick_sort.txt",sep="\t")

plot = quick_data.plot(x="Size",title = "Quick Sort",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('quick.png')

quick_data = pd.read_csv("quick_vs_heap.txt",sep="\t")

plot = quick_data.plot(x="Size",title = "Quick Sort vs Heap Sort",figsize=(10,6))
plot.set_ylabel("Time")
fig = plot.get_figure()
fig.savefig('quick_vs_heap.png')
