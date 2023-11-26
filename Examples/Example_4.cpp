// Handle thread exceptions in the main thread

#include <string>
#include <thread>
#include <iostream>
#include <functional>

using namespace std;

// 1. Define a function that throw an exception. The function should accept an
// exception_ptr&. It also should catch the exception and record it in that
// exception_ptr& using current_exception().
void exception_thread(exception_ptr &error, int process_id)
{
    try
    {
        cout << "Thread " << process_id << " is throwing an exception..." << endl;
        throw runtime_error{string{"Exception from "} + to_string(process_id)};
    }
    catch (const std::exception &e)
    {
        error = current_exception();
    }
}

int main()
{
    // 2. Define an exception_ptr to be passed to the thread
    exception_ptr error;
    thread t{exception_thread, ref(error), 10};

    t.join();

    // 3. Check whether error is null or not, and then print its message
    if (error)
    {
        try
        {
            rethrow_exception(error);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    cout << "Program is finished." << endl;
}