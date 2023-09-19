from sys import stdin

for line in map(str.strip, stdin):
	if line != '' and len(line) > 4 and line[0] != 'X':
		print(line)
