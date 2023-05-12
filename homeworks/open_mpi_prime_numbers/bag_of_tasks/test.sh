# TODO(Gustavo): put all the tests into a file in a way that
# make it easy to generate the necessary graphs later.

firstMaxPrimeNumber=2500000
secondMaxPrimeNumber=25000000
# numberOfTestsForEachEntry=3
# maxNumberOfProcesses=16

cd build
for file in $(ls)
do
    for numberOfProcesses in {2..16}
    do
        for test in {1..3}
        do
            mpirun --oversubscribe -n $numberOfProcesses ./$file $firstMaxPrimeNumber
        done
        # TODO(Gustavo): Average the 3 tests here.
        for test in {1..3}
        do
            mpirun --oversubscribe -n $numberOfProcesses ./$file $secondMaxPrimeNumber
        done
        # TODO(Gustavo): Average the 3 tests here.

        # TODO(Gustavo): Save both cases for the 'file' entry.
    done
done
cd ..