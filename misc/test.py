import sys

li = []
for line in sys.stdin:
    li.append(line.split())

for x in li:
    for i in xrange(len(x)):
        x[i] = int(x[i])

n = li[0][0]
m = li[0][1]
city_in = []

for x in xrange(n + 1):
    city_in.append(set())

for i in xrange(1, m+1):
    city_in[li[i][0]].add(li[i][1])

city_in_num = []

for x in city_in:
    city_in_num.append(len(x))

total = 0

while total < sum(city_in_num):
    total = sum(city_in_num)
    for i in xrange(len(city_in)):
        tmp = set()
        tmp.update(city_in[i])
        for x in city_in[i]:
            tmp.update(city_in[x])
        city_in[i] = tmp
        city_in_num[i] = len(tmp)

city_out_num = [0 for x in xrange(m+2)]

for i in xrange(len(city_in)):
    for x in city_in[i]:
        city_out_num[x] += 1

res = 0

for i in xrange(len(city_in)):
    if city_out_num[i] > city_in_num[i]:
        res += 1

print res