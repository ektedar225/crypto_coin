#ifndef PAIR_H
#define PAIR_H

template <typename K, typename V>
class Pair {
public:
    K first;
    V second;

    // Constructor
    Pair(K _first, V _second) : first(_first), second(_second) {}

    // Getters
    K get_first() const {
        return first;
    }

    V get_second() const {
        return second;
    }
};

#endif // PAIR_H
