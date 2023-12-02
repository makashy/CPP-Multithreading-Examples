
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

const int kNumberOfThreads = 6;

// 1. Define a shared function
void shared_function(int id)
{
    cout << "+++Thread number " << id << " has obtained the lock! " << endl;
    this_thread::sleep_for(50ms);
}

// 2. Define processes that tries to obtain the permission to use the
// shared_function.
class WaitingProcess
{
public:
    WaitingProcess(int thread_id):thread_id{thread_id}
    {
    }

    void operator()() 
    {
        unique_lock lock(shared_timed_mutex, 200ms);
        if (lock)
        {
            shared_function(thread_id);
        }
        else
        {  
            cout << "---Thread number " << thread_id << " has no chance! " << endl;
        }
    }

private:
    // 3. Define a shared timed_mutex. It should be static and because there is
    // no source file then it should be inline too.
    inline static timed_mutex shared_timed_mutex;
    int thread_id;
};

int main()
{
     // 4. Start multiple threads
    vector<thread> threads{};
    for (int i{0}; i<kNumberOfThreads; ++i)
    {
        threads.push_back( thread{WaitingProcess{i}} );
    }

    // 5. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        threads[i].join();
    }

    cout << "The program has just finished." << endl;
}