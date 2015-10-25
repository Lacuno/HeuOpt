#!/usr/bin/python2.7

from subprocess import Popen, PIPE
import math

instances = [
	"automatic-1",
	"automatic-2",
	"automatic-3",
	"automatic-4",
	"automatic-5",
	"automatic-6",
	"automatic-7",
	"automatic-8",
	"automatic-9",
	"automatic-10",
]

def executeHeuOpt(args):
	argList = ["./heuopt_ex1"]
	argList.extend(args)
	process = Popen(argList, stdout=PIPE)
	(output, err) = process.communicate()
	exit_code = process.wait()

	lines = output.split('\n')
	crossings = []
	times = []
	for line in lines:
		if "Crossings" in line:
			x = int(line[12:])
			crossings.append(x)
		if "Done in " in line:
			x = float(line[8:-8])
			times.append(x)
	return (crossings, times)

# Deterministic version:
(crossings, times) = executeHeuOpt(["-c", "g"])
print("Instance & Obj & Time \\\\")
print("\\hline")

for index in range(0, len(crossings)):
	crossing = crossings[index]
	time = times[index]
	instance = instances[index]
	print(instance + " & %d & %.2f ms \\\\" % (crossing, time * 1000))


allcrossings = []
alltimes = []

for instance in instances:
	allcrossings.append([])
	alltimes.append([])

# Random version
numRuns = 30
for index in range(0, numRuns):
	print("Iteraton " + str(index))
	(crossings, times) = executeHeuOpt(["-c", "g", "-r"])
	for instanceindex in range(0, len(instances)):
		allcrossings[instanceindex].append(crossings[instanceindex])
		alltimes[instanceindex].append(times[instanceindex])

print("Instance & Best Obj & Mean Obj & Std Dev Obj & Mean Time & Std Dev Time & Runs \\\\")
print("\\hline")
for index in range(0, len(crossings)):
	instance = instances[index]
	crossingsforinstance = allcrossings[index]
	timesforinstance = alltimes[index]
	
	bestObj = min(crossingsforinstance)
	meanObj = sum(crossingsforinstance) / float(numRuns)
	stdDevObj = map(lambda x : (meanObj - x) ** 2, crossingsforinstance)
	stdDevObj = math.sqrt(sum(stdDevObj) / float(numRuns))

	meanTime = sum(timesforinstance) / float(numRuns)
	stdDevTime = map(lambda x : (meanTime - x) ** 2, timesforinstance)
	stdDevTime = math.sqrt(sum(stdDevTime) / float(numRuns))

	#print(instance + " & " + str(bestObj) + " & " + str(meanObj) + " & " + str(stdDevObj) + " & " + str(meanTime*1000)  + "ms & " + str(stdDevTime* 1000) + "ms & " + str(numRuns))
	print(instance + " & %d & %.2f & %.2f & %.2f ms & %.2f ms & %d \\\\" % (bestObj, meanObj, stdDevObj, meanTime*1000, stdDevTime*1000, numRuns))

