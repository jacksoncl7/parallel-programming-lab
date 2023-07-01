firstMaxPrimeNumber=325000
secondMaxPrimeNumber=3250000
# numberOfTestsForEachEntry=3
# maxNumberOfThreads=8

cd build
for file in $(ls)
do
    echo ".$file"
    for numberOfThreads in {1..8}
    do
        echo "..threads = $numberOfThreads, num_primo_max = $firstMaxPrimeNumber"
        for test in {1..3}
        do
            ./$file $firstMaxPrimeNumber $numberOfThreads | sed 1d | awk '{print $4}'
        done

        echo "..threads = $numberOfThreads, num_primo_max = $secondMaxPrimeNumber"
        for test in {1..3}
        do
            ./$file $secondMaxPrimeNumber $numberOfThreads | sed 1d | awk '{print $4}'
        done
    done
done
cd ..