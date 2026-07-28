import csv

INPUT_FILE = "adjacency.csv"
OUTPUT_FILE = "neighbor_array.h"

# Read adjacency matrix
with open(INPUT_FILE, newline="") as f:
    matrix = [[int(x) for x in row] for row in csv.reader(f)]

NUM_CELLS = len(matrix)

# Find maximum number of neighbors
max_neighbors = max(sum(row) for row in matrix)

print(f"Number of cells: {NUM_CELLS}")
print(f"Maximum neighbors: {max_neighbors}")

# Build neighbor list
neighbor_list = []

for row in matrix:

    neighbors = []

    for cell, connected in enumerate(row):
        if connected:
            neighbors.append(cell)

    while len(neighbors) < max_neighbors:
        neighbors.append(-1)

    neighbor_list.append(neighbors)

# Write C++ header
with open(OUTPUT_FILE, "w") as f:

    f.write("#pragma once\n\n")
    f.write(f"#define MAX_NEIGHBORS {max_neighbors}\n\n")

    f.write(
        f"const int neighborArray[{NUM_CELLS}][MAX_NEIGHBORS] = {{\n"
    )

    for row in neighbor_list:

        values = ", ".join(str(v) for v in row)

        f.write(f"    {{{values}}},\n")

    f.write("};\n")

print(f"Wrote {OUTPUT_FILE}")