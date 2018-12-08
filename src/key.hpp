#if !defined(KEY_HPP)
#define KEY_HPP

#include <iostream>
#include <vector>

using namespace std;

#define C 4          // Number of character in the password.
#define B 5          // Number of bits per character.
#define R (1 << B)   // Size of alphabet (always = 32).
#define N (B * C)    // Number of bits per password.

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

typedef unsigned char uchar;

class Key{
private:
    inline int bit(const int &i) const {
        return (this->digit[i/B] >> (B - 1 - i % B)) & 1;
    }
public:
    uchar digit[C];
    Key();
    Key(const Key &k);
    Key(const string &s);
    // ^~~~~ Constructors

    // Computes the subset_sum of a given key.
    // Returns the encrypted version of a key.
    Key subset_sum(const vector<Key> &T);


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

    friend Key operator++(Key &a){
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
    
};

#endif // KEY_HPP