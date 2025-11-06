import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (AutoMinorLocator, MultipleLocator)



plt.rcParams["font.family"] = "monospace"

fig = plt.figure(2)

config = [(.25,1),
    (.5,1),
    (.75,1),
    (.25,2),
    (.5,2),
    (.75,2),
    (.25,3),
    (.5,3),
    (.75,3),
    (.25,5),
    (.5,5),
    (.75,5),
    (.25,10),
    (.5,10),
    (.75,10)
]
import os

for i in range(15):
    ax2 = fig.add_subplot(5,3,1+i)
    p,n = config[i]
    print(p,n)
    os.system(f"./star_free {n} {p}")
    if i < 3:
        ax2.set_title(f"p={p}",fontsize=12)
    if i%3 == 0:
        ax2.set_ylabel(f'w = {n}n',fontsize=12)
    # if i > 5:
    #     ax2.set_xlabel('Degree',fontsize=8)
    for i in range(25):
        G = nx.read_adjlist(f"graph{i}.adjlist")
        g = G.to_undirected()

        degree_sequence = sorted((d for n, d in g.degree()), reverse=True)
        dmax = max(degree_sequence)
        degree_freq = nx.degree_histogram(g)
        degrees = range(len(degree_freq))
        ax2.loglog(degrees, degree_freq,marker=".",ms=2.5,mew=.2,lw =0.1, label=f'p=0.75')




    plt.xticks(size = 4)
    plt.yticks(size = 4)

    ax2.grid(True,which="minor",ls=":",c=".1",alpha=.1)
    ax2.grid(True,which="major",ls="-",c=".1",alpha=.5)

# axins.get_xaxis().set_visible(False)
# axins.get_yaxis().set_visible(False)
fig.set_size_inches(8.27,11.69)
fig.tight_layout()
plt.savefig('output.pdf')
