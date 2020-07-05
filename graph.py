from statistics import stdev, mean
import csv
import numpy as np
import matplotlib.pyplot as plt

rng = [4, 8, 32, 64, 128, 256, 512, 1024]

def calculateDeviation(type): # type 'C' or 'S'
    deviation = dict()
    time = dict()
    minimum = dict()
    maximum = dict()

    for i in rng:
        with open('./data/result/' + str(i) +  type + '.txt', 'r') as f:
            next(f)
            arr = f.read().replace('\n', ' ').split(' ')
            arr.pop()
            seconds      = [int(i)/1000.0 for i in arr]
            minimum[i]   = sorted(seconds)[-1]
            maximum[i]   = sorted(seconds)[0]
            time[i]      = mean(seconds)
            deviation[i] = stdev(seconds)
    return [time, deviation, [minimum, maximum]]

concurrencyTime, concurrencyDeviation, minMaxConcurrency = calculateDeviation('C')
sequentialTime,  sequentialDeviation, minMaxSequential   = calculateDeviation('S')

# plot time
ind = np.arange(8)

concurrencyTimeFromDict = list(concurrencyTime.values())
sequentialTimeFromDict  = list(sequentialTime.values())
p1 = plt.bar(ind, sequentialTimeFromDict)
p2 = plt.bar(ind, concurrencyTimeFromDict)

plt.legend((p1[0], p2[0]), ('Sequential', 'Concurrency'))
plt.title('Median of time per seconds')
plt.show()

# print deviation
print(concurrencyDeviation)
print(sequentialDeviation)

# print speed up
for i in rng:
    # print('max: {}, min: {}'.format(minMaxConcurrency[0][i], minMaxConcurrency[1][i]))
    # print('max: {}, min: {}'.format(minMaxSequential[0][i], minMaxSequential[1][i]))
    print('{} x {}: {}'.format(i, i, sequentialTime[i]/concurrencyTime[i]))