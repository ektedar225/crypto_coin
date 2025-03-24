#include <iostream>
#include <exception>

class EmptyQueueException : public std::exception {
public:
    // Constructor to print an error message
    EmptyQueueException() {
        std::cout << "Queue is empty!" << std::endl;
    }

    // Override the what() function to provide an error message
    const char* what() const noexcept override {
        return "Queue is empty!";
    }
};

// Example usage
int main() {
    try {
        throw EmptyQueueException(); // Simulating an exception throw
    } catch (const EmptyQueueException& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }
    return 0;
}
