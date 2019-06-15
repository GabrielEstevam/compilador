entry = []
while True:
    try:
        entry.append(input())
    except EOFError:
        break

for i in range(100, 0, -1):
    for j in range(len(entry)):
        entry[j] = entry[j].replace(str(i), "make_pair("+str(i)+", 0)")

for i in entry:
    print(i)