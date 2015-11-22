#!/usr/bin/python2.7

from subprocess import Popen, PIPE
import sys
import math
import shutil
import os
import threading

instances = [
	"automatic-1.txt",
	"automatic-2.txt",
	"automatic-3.txt",
	"automatic-4.txt",
	"automatic-5.txt",
	"automatic-6.txt",
	"automatic-7.txt",
	"automatic-8.txt",
	"automatic-9.txt",
	"automatic-10.txt",
]

timeout = 15*60

global_best_solutions = {}

def executeHeuOpt(args):
	argList = ["./heuopt_ex3.exe"]
	argList.extend(args)
	
	def kill( p ):
		if p.poll() is None:
			try:
				p.kill()
				print 'Error: process taking too long to complete--terminating'
			except OSError as e:
				if e.errno != errno.ESRCH:
					return
			
	crossing = sys.maxint
	time = None
		
	process = Popen(argList, stdout=PIPE)
	
	t = threading.Timer( timeout, kill, [process] )
	t.start()

	(output, err) = process.communicate()
	exit_code = process.wait()
	t.cancel()

	lines = output.split('\n')
		
	for line in lines:
		if "Improved Obj:" in line:
			crossing = min(crossing, int(line[13:]))
				
		if "Done in" in line:
			time = float(line[8:-1])
	
	
	if not time:
		time = timeout * 1000
	
	return (crossing, time)

def run(args):
	# Deterministic version:
	print("\n\n#------------------------------------------#")
	print(args)
	print("Instance & Obj & Time \\\\")
	print("\\hline")

	for instance in instances:
		(crossing, time) = executeHeuOpt(args + ["-i", instance])
		
		if instance not in global_best_solutions or global_best_solutions[instance] > crossings:
			global_best_solutions[instance] = crossings
			if os.path.exists("result_" + instance):
				shutil.copy("result_" + instance, "best_result_" + instance)
		
		print(instance + " & %d & %.2f ms \\\\" % (crossing, time))

def run_random(args, numRuns):
	print("\n\n#------------------------------------------#")
	print(args)
	print("Instance & Best Obj & Mean Obj & Std Dev Obj & Mean Time & Std Dev Time & Runs \\\\")
	print("\\hline")
	
	for instance in instances:
		crossings = []
		times = []

		for index in range(0, numRuns):
			(crossing, time) = executeHeuOpt(args + ["-i", instance])
			crossings += [crossing]
			times += [time]
			
			if instance not in global_best_solutions or global_best_solutions[instance] > crossing:
				global_best_solutions[instance] = crossing
				if os.path.exists("result_" + instance):
					shutil.copy("result_" + instance, "best_result_" + instance)

			#else:
			#	print("crossings {} not better than {}!".format(crossings, global_best_solutions[instance]))
			
		bestObj = min(crossings)
		meanObj = sum(crossings) / float(numRuns)
		stdDevObj = map(lambda x : (meanObj - x) ** 2, crossings)
		stdDevObj = math.sqrt(sum(stdDevObj) / float(numRuns))

		meanTime = sum(times) / float(numRuns)
		stdDevTime = map(lambda x : (meanTime - x) ** 2, times)
		stdDevTime = math.sqrt(sum(stdDevTime) / float(numRuns))

		#print(instance + " & " + str(bestObj) + " & " + str(meanObj) + " & " + str(stdDevObj) + " & " + str(meanTime*1000)  + "ms & " + str(stdDevTime* 1000) + "ms & " + str(numRuns))
		print(instance + " & %d & %.2f & %.2f & %.2f ms & %.2f ms & %d \\\\" % (bestObj, meanObj, stdDevObj, meanTime, stdDevTime, numRuns))


#run(["-c", "g", "-l", "mmc", "-s" "f"])
run_random(["-c", "g", "-v", "-l", "mmc", "-s", "r", "-l", "map", "-s", "r"], 1)

