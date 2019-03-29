import fileinput
import re
import copy

start = []
end = []
read = True


# Takes a state 



'''
algo = 0
algoname = ['astar', 'fhat', 'risk', 'lsslrta']
for line in fileinput.input():
    if line[0] == '{':
        # A
        if (start != end):
            print(algoname[algo], 'wrong!')
        algo += 1
        read = True
        break
    elif read:
        # B
        s = re.split(r'\s+',line)
        for num in s:
            if len(num) > 0:
                start.append(int(num))
        end = copy.deepcopy(start)
        end.sort()
        read = False
    elif len(line) < 6:
        indx = int(line)
        start[0:indx+1] = start[0:indx+1][::-1]
    else:
        # A
        if (start != end):
            print(algoname[algo], 'wrong!')
        algo += 1
        start.clear()
        end.clear()

        # B
        s = re.split(r'\s+',line)
        for num in s:
            if len(num) > 0:
                start.append(int(num))
        end = copy.deepcopy(start)
        end.sort()
        
'''