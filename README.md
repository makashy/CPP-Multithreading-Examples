# C++ Multithreading Examples

This is a collection of examples for multithreading in C++. 

## 1. Threads

| <p>Example<p>number | <p>C++<p>Version |  Description |
|:-----:|:---------------:|:---------------:|
| Exp 1.1  | <sup>`C++11`</sup> | Run some simple transient printing in parallel (using function pointers in threads) |
| Exp 1.2  | <sup>`C++11`</sup> | Run some precesses in parallel and get their results (using object functions and ref()) |
| Exp 1.3  | <sup>`C++11`</sup> | Run some precesses in parallel and get their results (using lambda) |
| Exp 1.4  | <sup>`C++11`</sup> | Handle thread exceptions in the main thread (using current_exception() and rethrow_exception() and ref()) |

## 2. Atomic <atomic>

| <p>Example<p>number | <p>C++<p>Version |  Description |
|:-----:|:---------------:|:---------------:|
| Exp 2.1  | <sup>`C++17`</sup> | Check whether a type can be atomic or not (is_trivially_copyable_v, is_always_lock_free) |
| Exp 2.2  | <sup>`C++11`</sup> | Add to a common counter (atomic) from different threads and record the order of adding to the counter based on the thread numbers (using atomic\<T>, fetch_add(), atomic_flag and spinlock method) |

## 3. Mutual Exclusion

| <p>Example<p>number | <p>C++<p>Version |  Description |
|:-----:|:---------------:|:---------------:|
| Exp 3.1  | <sup>`C++11`</sup> | Call a function from multiple threads only once (using call_once() and once_flag) |
| Exp 3.2  | <sup>`C++11`</sup> | Print messages from multiple threads on a terminal without interference of messages (using mutex and guard_lock() and ref()) |
| Exp 3.3  | <sup>`C++17`</sup> | Give 6 processes 200ms to use a shared function in parallel. The shared_function takes 50ms to finish. (using timed_mutex and unique_lock() (<sup>`C++17`</sup>: inline keyword) ) |










