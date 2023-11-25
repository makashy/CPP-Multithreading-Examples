// Run some precesses in parallel and get their results

#include <iostream>
#include <thread>
#include <vector>

// for random numbers
#include <random>

using namespace std;

const int kNumberOfThreads = 20;
const int kNumberOfIterations = 100;

int main()
{
    // 1. Define a vector for multiple threads
    vector<thread> threads;

    // 2. Define an array averages
    float averages[100];

    // 3. Define a stateful lambda that calculate an average over random 
    // numbers. Then pass it to threads. Lambda should be defined mutable and  
    // elements of the averages array should be passed by reference.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        int num = kNumberOfIterations;
        float& average{averages[i]};
        int id = i;

        threads.push_back(
            thread{
                [id, num, &average] () mutable
                {
                    float sum{};
                    srand(static_cast<unsigned int>(id));
                    for (int counter{0}; counter < num; ++counter)
                    {
                        sum += rand();
                    }
                    average = sum / num;
                }
            });
    }

    // 4. Wait for all threads to end, otherwise the program will end prematurely.
    for(int i{0}; i<kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    // 7. Show the results
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        cout << "Process " << i << " has an average value of: "
             << averages[i] << endl;
    }

    cout << "Program is finished." << endl;
}