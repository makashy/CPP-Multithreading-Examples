// Add to a common counter (atomic) from different threads and record the
// order of adding to the counter based on the thread numbers

#include <string>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>

using namespace std;

const int kNumberOfThreads = 5;
const int kNumberOfIterations = 5;

int main()
{
    // 1. Define a vector for multiple threads
    vector<thread> threads;

    // 2. Define an atomic int and an array for recording order of addition 
    char addition_oder[kNumberOfThreads * kNumberOfIterations * 2];
    atomic<int> counter{0};

    // 3. Define a stateful lambda that adds to an atomic counter and records 
    // its turn to a char array
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        int id = i;
        int number_of_iteration = kNumberOfIterations;
        threads.push_back(
            thread{
                [id, number_of_iteration, &counter, &addition_oder]() mutable
                {
                    string new_message{};
                    for (int i{0}; i < number_of_iteration; ++i)
                    {
                        int current_index = counter.fetch_add(2);
                        addition_oder[current_index] = to_string(id).data()[0];
                        addition_oder[current_index + 1] = string("-").data()[0];

                        cout << "Thread " << id << " added to counter,"
                                                   "increased it from "
                             << current_index << " to " << current_index + 2 << endl;
                    }
                }});
    }

    // 4. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    // 5. Present the final value of the counter and also the order of additions
    cout << endl
         << endl
         << "final value of counter: " << counter << endl;
    cout << endl
         << "The order of adding to the counter based on the thread number: "
         << string(addition_oder) << endl
         << endl;
}