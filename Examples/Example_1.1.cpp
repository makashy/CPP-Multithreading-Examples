// Run some simple transient printing in parallel

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int kNumberOfThreads = 20;

// 1. Define a transient process
void process(int process_id)
{
    for (int counter{0}; counter < 100; ++counter)
    {
        cout << "Process " << process_id << " has counted to the number" << counter << "." << endl;
    }
}

int main()
{
    // 2. Define multiple threads
    vector<thread> threads;

    // 3. Run multiple processes in multiple threads
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads.push_back(thread{process, i});
    }

    // 4. Wait for all threads to end, otherwise the program will end prematurely.
    // (Comment it out to see it)
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    cout << "Program is finished." << endl;
}