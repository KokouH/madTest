import matplotlib.pyplot as plt

points = []
with open('Points.txt', 'r') as file:
    s = file.readline()
    while (s != '\n'):
        points.append(list(map(float, s.split())))
        s = file.readline()

print(len(points))
plt.scatter([i[0] for i in points], [i[1] for i in points])
plt.show()