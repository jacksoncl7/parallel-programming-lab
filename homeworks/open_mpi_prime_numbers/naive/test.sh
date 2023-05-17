firstMaxPrimeNumber=3250000
secondMaxPrimeNumber=32500000

cd build
for file in $(ls)
do
    echo ".$file"
    for numberOfProcesses in {1..8}
    do
        echo "..processos = $numberOfProcesses, num_primo_max = $firstMaxPrimeNumber"
        for test in {1..3}
        do
            mpirun --oversubscribe -n $numberOfProcesses ./$file $firstMaxPrimeNumber | sed 1d | awk '{print $4}'
        done

        echo "..processos = $numberOfProcesses, num_primo_max = $secondMaxPrimeNumber"
        for test in {1..3}
        do
            mpirun --oversubscribe -n $numberOfProcesses ./$file $secondMaxPrimeNumber | sed 1d | awk '{print $4}'
        done
    done
done
cd ..
