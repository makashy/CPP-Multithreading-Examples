// Call a function from multiple threads only once

#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <iostream>

using namespace std;
using namespace std::chrono;

const int kNumberOfThreads = 10;

// 1. Define an once_flag to coordinate threads with each other 
once_flag flag;

// 2. Define a function to be called once, although all threads try to call it
void show_the_winner_thread(int thread_id)
{
    cout << "***************** Thread number " << thread_id << " won!" << endl;
}

// 3. Define a thread function that tries to call a function that should be called once.
void competitor_thread(int thread_id, long long start_time)
{
    // * Display the time that threads try to call the call_once
    long long call_time_absolute =
        time_point_cast<microseconds>(steady_clock::now()).time_since_epoch().count();
    cout << "Thread " << thread_id << " started to call the function at: "
         << call_time_absolute - start_time << endl;

    // 4. Call show_the_winner_thread function with call_once and the defined once_flag
    call_once(flag, show_the_winner_thread, thread_id);
}

int main()
{
    // * Record the start of the program as a reference 
    long long start_time =
        time_point_cast<microseconds>(steady_clock::now()).time_since_epoch().count();

    // 5. Start multiple threads that tries to call the show_the_winner_thread()
    vector<thread> threads{};
    for (int i{}; i < kNumberOfThreads; ++i)
    {
        threads.push_back(thread{competitor_thread, i, start_time});
    }

    // 6. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }
}