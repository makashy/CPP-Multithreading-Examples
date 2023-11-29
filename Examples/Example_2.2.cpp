// Add to a common counter (atomic) from different threads and record the
// order of adding to the counter based on the thread numbers

#include <string>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

using namespace std;

const int kNumberOfThreads = 5;
const int kNumberOfIterations = 5;

int main()
{
    // 1. Define a vector for multiple threads
    vector<thread> threads;

    // 2. Define an atomic int as a shared counter variable between threads 
    atomic<int> counter{0};
    // 3. Define a string for recording order of addition and a atomic_flag for spinlock method 
    atomic_flag lock = ATOMIC_FLAG_INIT;
    string addition_oder_string{};
    // 4. Define a charr array for recording order of addition
    char addition_oder_array[kNumberOfThreads * kNumberOfIterations * 2];
    
    // 5. Define a stateful lambda that adds to an atomic counter and records 
    // its turn to a char array
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        int id = i;
        int number_of_iteration = kNumberOfIterations;
        threads.push_back(
            thread{
                [id, number_of_iteration, &counter, &addition_oder_array, &lock, &addition_oder_string]() mutable
                {
                    string new_message{};
                    for (int i{0}; i < number_of_iteration; ++i)
                    {
                        int current_index = counter.fetch_add(2);
 
                        // 6. Use the obtained current_index to record the order in a char array
                        addition_oder_array[current_index] = to_string(id).data()[0];
                        addition_oder_array[current_index + 1] = string("-").data()[0];

                        // 7. Use a spinlock method to record the order in a string
                        while (lock.test_and_set()){} // acquire lock
                        addition_oder_string.append(to_string(id)+"-");
                        lock.clear(std::memory_order_release);

                        cout << "Thread " << id << " added to counter,"
                                                   "increased it from "
                             << current_index << " to " << current_index + 2 << endl;
                    }
                }});
    }

    // 8. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    // 5. Present the final value of the counter and also the order of additions
    // Compare the two recording methods for order of addition

    cout << endl
         << endl
         << "final value of counter: " << counter << endl;
    cout << endl
         << "Order of addition (using a char array and current_index): "
         << string(addition_oder_array) << endl;
    cout << endl
         << "Order of addition (using spinlock and a string):          "
         << addition_oder_string << endl
         << endl;
}