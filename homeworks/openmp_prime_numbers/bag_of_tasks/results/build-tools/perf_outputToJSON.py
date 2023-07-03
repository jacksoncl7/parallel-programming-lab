import json

myPerfInput = "jack_test/bag_of_tasks_mpi"
perf_output_file = open(f"{myPerfInput}.txt", "r")

perf_output_dict = {}
currFileKey = ""
currThreads = ""
currMaximum = ""
for line in perf_output_file:
    # IS A FILE NAME
    if line[0] == '.' and line[1] != '.':
        # NOTE(Gustavo): [1:-1] to remove '.' and '\n'
        currFileKey = line[1:-1] # Ex: ".naive_omp_atomic".
        perf_output_dict[currFileKey] = []
    # IS A TEST DESCRIPTION
    elif line[0] == '.' and line[1] == '.': # Ex: "..threads = 1, num_primo_max = 325000"
        currThreads = line[2:].split(",")[0].split()[-1]
        currMaximum = line[2:].split(",")[1].split()[-1]

        entryBuffer = {
            "threads": int(currThreads),
            "maxPrime": int(currMaximum),
            "test1": 0,
            "test2": 0,
            "test3": 0,
            "avg": 0
        }

        average = 0
        # NOTE(Gustavo): a 'TEST DESCRIPTION' line is always followed by 3 test results.
        for count in range(3):
            # NOTE(Gustavo): line[:-1] to remove '\n'
            testLine = perf_output_file.readline()
            entryBuffer[f"test{count+1}"] = float(testLine[:-1])
            average += float(testLine[:-1])
        average /= 3
        entryBuffer["avg"] = float(f"{average:.3f}")

        perf_output_dict[currFileKey].append(entryBuffer)


jsonOutput = json.dumps(perf_output_dict, indent=4)
with open(f"{myPerfInput}.json", "w") as output:
    output.write(jsonOutput)
