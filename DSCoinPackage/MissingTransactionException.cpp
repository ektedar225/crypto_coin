#include <iostream>
#include <exception>

using namespace std;

class MissingTransactionException : public exception {
public:
    const char* what() const noexcept override {
        return "Required transaction missing from blockchain!";
    }
};

// Example usage
int main() {
    try {
        throw MissingTransactionException();
    } catch (const MissingTransactionException& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
