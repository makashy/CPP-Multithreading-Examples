// Check whether a type can be atomic or not

#include <iostream>
#include <atomic>

using namespace std;


int main()
{

    // Check which types can be atomic. Types should be copyable to become atomic.
    cout << "String can" << (is_trivially_copyable_v<string> ? " be atomic!" : " not be atomic!") << endl;
    cout << "Int can" << (is_trivially_copyable_v<int> ? " be atomic!" : " not be atomic!") << endl;
    cout << "Char* can" << (is_trivially_copyable_v<char *> ? " be atomic!" : " not be atomic!") << endl << endl;

    // Check which atomic types are always lock-free. An atomic type is lock-free if no atomic operations on that type use locks.
    // ref -> https://learn.microsoft.com/en-us/cpp/standard-library/atomic?view=msvc-170
    cout << "Is atomic<int> always lock-free? " << (atomic<int>::is_always_lock_free? "yes":"no") << endl << endl;

}