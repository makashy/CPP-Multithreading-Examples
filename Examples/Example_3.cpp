// Run some precesses in parallel and get their results

#include <iostream>
#include <thread>
#include <vector>

// a. Add this for using ref()
#include <functional>
// b. for random numbers
#include <random>

using namespace std;

const int kNumberOfThreads = 20;
const int kNumberOfIterations = 100;

// 1. Define a function object as a process. This class will be passed to a
// thread to do a process. After finishing of the process, we can use the
// result of the process in a data member of this class.
class AFunctionObject
{
public:
    AFunctionObject(int process_id, int number_of_iterations)
        : process_id_{process_id}, number_of_iterations_{number_of_iterations}
    {
    }

    void operator()()
    {
        // Calculates an average over 100 random number

        float sum{};
        srand(static_cast<unsigned int>(process_id_));
        for (int counter{0}; counter < number_of_iterations_; ++counter)
        {
            sum += rand();
        }
        average_ = sum / number_of_iterations_;
    }

    int get_id() const { return process_id_; }

    float get_average() const { return average_; }

private:
    int process_id_;
    int number_of_iterations_;
    float average_{};
};

int main()
{
    // 2. Define a vector for multiple threads
    vector<thread> treads;

    // 3. Define a vector for multiple process classes to be passed to threads
    vector<AFunctionObject> processes;

    // 4. Define multiple processes
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        processes.push_back(AFunctionObject{i, kNumberOfIterations});
    }

    // 5. Start processes by passing them to threads
    // Pass process instance by using ref(). Without it, copies of the
    // processes will be passed to threads and later we cant use the
    // results.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        treads.push_back(thread{ref(processes.data()[i])});
    }

    // 6. Wait for all threads to end, otherwise the program will end prematurely.
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        treads[i].join();
    }

    // 7. Obtain the results from function objects
    for (int i{0}; i < kNumberOfThreads; ++i)
    {
        cout << "Process " << processes[i].get_id() << " has an average value of: "
             << processes[i].get_average() << endl;
    }

    cout << "Program is finished." << endl;
}