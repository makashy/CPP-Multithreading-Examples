// Run some simple endless printing in parallel

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int kNumberOfThreads = 20;

// 1. Define a process
void process(int process_id)
{
    int counter{};
    while (true)
    {
        cout << "Process " << process_id << " has counted to the number" << counter++ << "." << endl;
    }
}

int main()
{
    // 2. Define multiple threads
    vector<thread> treads;

    // 3. Running multiple processes in multiple threads
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        treads.push_back(thread{process, i});
    }
}