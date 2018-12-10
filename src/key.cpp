#include <algorithm>
#include <iomanip>      // std::setw
#include "key.hpp"

Key::Key(){
    for (int i{0}; i < C; i++) this->digit[i] = 0;
}

Key::Key(const Key &k){
    for (int i{0}; i < C; i++) this->digit[i] = k.digit[i];
}

Key::Key(const string &s){
    int j;
    for (int i = 0; i < C; ++i) {
        for (j = 0; j < R; ++j) {
            if (s[i] == ALPHABET[j]) {
                this->digit[i] = j;
                break;
            }
        }
    }
}

void Key::print_key() const{
    for (uchar c : digit)
        std::cout << ALPHABET[c];
    std::cout << "  ";
    for (uchar c : digit)
        std::cout << std::setw(2) << static_cast<int>(c) << ' ';

    std::cout << "  ";
    for (int i = 0; i < N; ++i) {
        std::cout << bit(i) << std::flush;
    }
    std::cout << endl;
}

bool Key::is_nullKey(){
    return this->digit[0] == 255;
}

Key Key::subset_sum(const vector<Key> &T){
    Key sum;
    for (int i = 0; i < N; ++i) {
        if (bit(i)) {
            sum += T[i];
            // cout << i << " "; // For testing
            // T[i].print_key(); // For testing
        }
    }
    return sum;
}