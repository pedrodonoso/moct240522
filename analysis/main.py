import matplotlib.pyplot as plt

dir = "../"
name = "c_5r7_0"
file_name = dir + name + ".histo"
f = open(file_name, "r")
ranges = []
result = []

for line in f:
    range, freq = line.strip().split(" ")
    # listPlot.append((range, freq))
    ranges.append(float(range))
    result.append(int(freq))
    print(range, freq)
    
    
f.close()
print(ranges)
    
plt.plot(ranges, result)
plt.ylabel('some numbers')
plt.show()
    