import csv

MAX_NEIGHBORS = 12

neighbor_lists = []

with open("adjacency.csv") as f:
    reader = csv.reader(f)

    for row in reader:
        row = [int(x) for x in row]

        neighbors = []

        for j, val in enumerate(row):
            if val == 1:
                neighbors.append(j)

        neighbor_lists.append(neighbors)

print("const unsigned char numNeighbors[48] = {")

for neighbors in neighbor_lists:
    print(f"    {len(neighbors)},")

print("};")
print()

print(f"const int neighborArray[48][{MAX_NEIGHBORS}] = {{")

for neighbors in neighbor_lists:

    padded = neighbors + [-1]*(MAX_NEIGHBORS-len(neighbors))

    print("    {" + ", ".join(map(str,padded)) + "},")

print("};")