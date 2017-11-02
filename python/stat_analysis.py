from tqdm import *
import matplotlib.pyplot as plt

def find_max_growth(block):
    data = map(lambda x : float(x), block)
    v = map(lambda x: ((data[-1] - x)/x)*100, [data[i] for i in range(len(data) - 1)])
    return max(v)

block_size = 12 * 60
data_range = 4 * 31 * 24 * 60 # last 4 moths
results = []

with open("bit_pr.csv", "r") as f:
    data = map(lambda x: float(x.split(",")[2].rstrip()), f.readlines()[1:])
    data = data[-data_range:]
    for i in tqdm(range(120, len(data))):
        if i <= block_size:
            block = data[:i]
        else:
            block = data[i-block_size:i]
        results.append(find_max_growth(block))

plt.hist(results)
plt.title("Gaussian Histogram")
plt.xlabel("Value")
plt.ylabel("Frequency")
plt.show()
