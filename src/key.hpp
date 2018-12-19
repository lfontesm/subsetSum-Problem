#if !defined(KEY_HPP)
#define KEY_HPP

#include <iostream>
#include <vector>
#include <array>
// #include <functional>
// #include <unordered_map>

// #include <unordered_map>

using namespace std;

#define C 4          // Number of character in the password.
#define B 5          // Number of bits per character.
#define R (1 << B)   // Size of alphabet (always = 32).
#define N (B * C)    // Number of bits per password.

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

typedef unsigned char uchar;
typedef array<uchar, C> word_type; // fixed size word

class Key{
private:
    inline int bit(const int &i) const {
        return (this->digit[i/B] >> (B - 1 - i % B)) & 1;
    }
public:
    word_type digit;
    Key();
    Key(const Key &k);
    Key(const string &s);
    // ^~~~~ Constructors

    // Computes the subset_sum of a given key.
    // Returns the encrypted version of a key.
    Key subset_sum(const vector<Key> &T);

    // Checks if a key's first digit is 255 (which should be equivalent to NULL_key)
    bool is_nullKey();

    void set_string(const std::string &s);

    void print_key(void) const;

    friend Key operator+(const Key &a, const Key &b){
        int carry = 0;
        Key k;
        for (int i = C-1; i >= 0; i--) {
            int sum    = b.digit[i] + a.digit[i] + carry;
            k.digit[i] = sum  % R;
            carry      = sum >= R;
        }
        return k;
    }

    inline Key& operator+=(const Key &a){
        *this = *this + a;

        return *this;
    }

    friend Key& operator++(Key &a){
        int carry = 1;
        int digit;
        int i = C-1;

        while (carry && i >= 0){ // This loop is equivalent to add( (Key){0,0,0,0,1}, key);
            digit = a.digit[i];
            digit += 1;

            carry = digit >= R;
            if (carry) digit = 0;
            
            a.digit[i] = digit;
            i--;
        }

        return a;
    }

    inline friend ostream& operator<<(ostream &os, const Key &a){
        for (auto i : a.digit)
            os << ALPHABET[i];

        return os;
    }

    inline friend bool operator!=(const Key &a, const Key &b){
        for (int i{0}; i < C; i++)
            if (a.digit[i] != b.digit[i])
                return true;
        return false;
    }

    inline friend bool operator==(const Key &a, const Key &b){
        return !(a != b);
    }

    bool operator<(const Key &k) const {
        return this->digit < k.digit;
    }

    inline bool operator>(const Key &k){
        return !(*this < k);
    }
    
};

// map a string to its representation in given alphabet
static inline word_type to_string(const std::string& s) {
	word_type w;
	int j;
	for (int i = 0; i < C; ++i) {
		for (j = 0; j < R; ++j) {
			if (s[i] == ALPHABET[j]) {
				w[i] = j;
				break;
			}
		}
		if (j == R) throw std::out_of_range("invalid character");
	}
	return w;
}

// A hashing function for key
template<class T, size_t S> 
struct std::hash<std::array<T, S>> {
    size_t operator() (const std::array<T, N>& key) const {
        std::hash<T> hasher;
        size_t result = 0;
        for(size_t i = 0; i < N; ++i) {
            result = result * 31 + hasher(key[i]); // ??
        }
        return result;
    }
};

#endif // KEY_HPP