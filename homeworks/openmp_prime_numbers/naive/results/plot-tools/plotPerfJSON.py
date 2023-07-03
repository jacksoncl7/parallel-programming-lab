import json
import matplotlib.pyplot as plt

myPerfInput = "perf_output_2"
perf_output_file = open(f"{myPerfInput}.json", "r")
perf_output = json.load(perf_output_file)

filenames = [filenames for filenames in perf_output]


maxPrime = 3250000
for filename in filenames:
    xAxis325_000 = [x["threads"] for x in perf_output[filename] if x["maxPrime"] == maxPrime]
    yAxis325_000 = [y["avg"] for y in perf_output[filename] if y["maxPrime"] == maxPrime]
    plt.plot(xAxis325_000, yAxis325_000, label = filename)
plt.title(f"Primo máximo: {maxPrime}")
plt.xlabel("threads")
plt.ylabel("tempo (s)")
plt.legend()
plt.savefig(f"plots_2/{maxPrime:_}.png")

plt.close()

maxPrime = 32500000
for filename in filenames:
    xAxis3_250_000 = [x["threads"] for x in perf_output[filename] if x["maxPrime"] == maxPrime]
    yAxis3_250_000 = [y["avg"] for y in perf_output[filename] if y["maxPrime"] == maxPrime]
    plt.plot(xAxis3_250_000, yAxis3_250_000, label = filename)
plt.title(f"Primo máximo: {maxPrime}")
plt.xlabel("threads")
plt.ylabel("tempo (s)")
plt.legend()
plt.savefig(f"plots_2/{maxPrime:_}.png")
