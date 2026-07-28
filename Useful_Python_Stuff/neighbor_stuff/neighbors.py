import re
import numpy as np

adj = np.zeros((48, 48), dtype=int)
tp2cell = {}
lines = open("neighbors.txt").read().strip().splitlines()

# first pass: TP id -> cell number
for line in lines:
    m = re.match(r"TP (\d+) \(cell (\d+), mod 0\)", line)
    if m:
        tp2cell[int(m.group(1))] = int(m.group(2))

# second pass: fill matrix
for line in lines:
    m = re.match(r"TP (\d+) \(cell \d+, mod 0\) neighbors:(.*)", line)
    if not m:
        continue
    cell = tp2cell[int(m.group(1))]
    for tp in map(int, m.group(2).split()):
        if tp in tp2cell:  # skip neighbors in other modules
            adj[cell, tp2cell[tp]] = 1

# print
print("    " + " ".join(f"{j:2d}" for j in range(48)))
for i in range(48):
    print(f"{i:2d}: " + "  ".join(map(str, adj[i])))

# sanity check: should be symmetric
assert (adj == adj.T).all()

np.savetxt("adjacency.csv", adj, fmt="%d", delimiter=",")
