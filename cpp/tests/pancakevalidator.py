import fileinput
import re

start = []
i = 0
for line in fileinput.input():
    if i == 0:
        start = re.split(r'\s+',line)

print(start)