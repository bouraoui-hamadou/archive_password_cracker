#pragma once

#include <coroutine>
#include <optional>
#include <vector>

class CombinationGenerator {
public:
    // Promise type for the generator coroutine
    struct promise_type {
        std::vector<char> current_value;  // Store the current combination of characters
        auto get_return_object() { return CombinationGenerator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        auto initial_suspend() { return std::suspend_always{}; }  // Coroutine initial suspend point
        auto final_suspend() noexcept { return std::suspend_always{}; }  // Coroutine final suspend point
        void return_void() {}  // Allow the coroutine to return void
        void unhandled_exception() {}  // Handle any unhandled exception in the coroutine
        auto yield_value(std::vector<char> value) {
            current_value = value;  // Yield the current combination of characters
            return std::suspend_always{};  // Suspend the coroutine after yielding a value
        }
    };

    // Constructor takes a coroutine handle
    CombinationGenerator(std::coroutine_handle<promise_type> handle) : handle_(handle) {}

    // Destructor to properly clean up the coroutine handle
    ~CombinationGenerator() {
        if (handle_) {
            handle_.destroy();
        }
    }

    // Move to the next combination and return true if more combinations are available
    bool move_next() {
        if (handle_) {
            handle_.resume();  // Resume the coroutine execution
            return !handle_.done();  // Check if the coroutine is still active
        }
        return false;  // Return false if the coroutine handle is empty
    }

    // Get the current combination of characters
    std::vector<char> current_value() const { return handle_.promise().current_value; }

private:
    std::coroutine_handle<promise_type> handle_;  // Handle to the coroutine instance
};

// Function to create a combination generator with the given characters and length
CombinationGenerator combinations(const std::vector<char>& characters, int length);
