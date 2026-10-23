# A script to compile this project. The script will also try to print the output with -h arguments.
make clean
sleep 1.5s
make all
cd make-build
./ArbitraryPrecisionCalculator -h