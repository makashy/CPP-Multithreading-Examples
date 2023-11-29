// Print messages from multiple threads on a terminal without interference of messages
// (run this example multiple time to compare the two different methods)

#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int kNumberOfThreads = 10;
// 1. Add a list signs for each thread
const string KSigns{"!@#$%^&*()"};

// 2. Define a function to be passed to threads. It can print its message by
// locking a mutex or without it
void print_sign(char sign, mutex &cout_mutex, bool use_mutex)
{
    string message{""};
    for (int i{30}; i > 0; --i)
        message.push_back(sign);
    if (use_mutex)
    {
        lock_guard lock{cout_mutex};
        cout << message << endl;
    }
    else
    {
        cout << message << endl;
    }
}

int main()
{
    // 3. Define a mutex
    mutex cout_mutex;

    cout << "Without using mutex: " << endl
         << endl;
    // 4. Start multiple threads that tries to print their messages without mutex
    vector<thread> threads{};
    for (int i{}; i < kNumberOfThreads; ++i)
    {
        threads.push_back(thread{print_sign, KSigns[i], ref(cout_mutex), false});
    }

    // 5. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    cout << endl
         << endl
         << "Using mutex: " << endl
         << endl;
    // 6. Start multiple threads that tries to print their messages with mutex
    vector<thread> threads_using_mutex{};
    for (int i{}; i < kNumberOfThreads; ++i)
    {
        threads_using_mutex.push_back(thread{print_sign, KSigns[i], ref(cout_mutex), true});
    }

    // 7. Wait for all threads to end.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads_using_mutex[i].join();
    }
}