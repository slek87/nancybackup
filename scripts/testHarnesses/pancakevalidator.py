import fileinput
import re
import copy

start = []
end = []
i = 0
algo = 0
algoname = ['astar', 'fhat', 'risk', 'lsslrta']

for line in fileinput.input():
    if i == 0:
        s = re.split(r'\s+',line)
        for num in s:
            if len(num) > 0:
                start.append(int(num))
        i += 1
        end = copy.deepcopy(start)
        end.sort()
    elif len(line) < 6:
        indx = int(line)
        start[0:indx+1] = start[0:indx+1][::-1]
    else:
        if (start != end):
            print(algoname[algo], 'wrong!')
        algo += 1
        i = 0
        start.clear()
        end.clear()