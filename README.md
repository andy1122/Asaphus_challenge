# Asaphus_challenge


git clone https://github.com/andy1122/Asaphus_challenge.git

mkdir build
cd build
cmake -S . -B build
cmake --build build


To check if test case passed
./build/test/unit_tests 

Randomness seeded to: 2454658080
===============================================================================
All tests passed (4 assertions in 4 test cases)


Get more comprehensive view of the test case
cd build
ctest

    Start 1: Final scores for first 4 Fibonacci numbers
1/4 Test #1: Final scores for first 4 Fibonacci numbers ...............   Passed    0.01 sec
    Start 2: Final scores for first 8 Fibonacci numbers
2/4 Test #2: Final scores for first 8 Fibonacci numbers ...............   Passed    0.01 sec
    Start 3: Final scores of reverse of  first  4 Fibonacci numbers
3/4 Test #3: Final scores of reverse of  first  4 Fibonacci numbers ...   Passed    0.01 sec
    Start 4: Final scores with 4 Random numbers
4/4 Test #4: Final scores with 4 Random numbers .......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.03 sec

