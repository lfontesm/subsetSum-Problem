#include <set>
#include "keyPair.hpp"
#include "util.hpp"
#include <algorithm>
#include <cmath>

typedef array<array<Key*, R>, C> KeyMap;

int decrypt(KeyMap &map, Key &iter, vector<Key> &stack, vector<Key> &T, Key &matcher){
    int carry = 1;
    int digit;
    int i = C-1;
    
    while (carry && i >= 0){ // This loop is equivalent to add( (Key){0,0,0,0,1}, key);
        digit = iter.digit[i];
        digit += 1;

        carry = digit >= R;
        if (carry) digit = 0;
        
        iter.digit[i] = digit;
        i--;
    }
    if (carry) return carry; // This means the last key was found.

    i++; // This line ensures performance. Avoids computing an already computed 
         // item that is already in the stack

    while (i < C){
        Key *k_sum = map[i][iter.digit[i]];

        if (k_sum == NULL){
            Key sssDigit;                            // Used to compute subset_sum for a single digit
            sssDigit.digit[i] = iter.digit[i]; 
            k_sum = new Key(sssDigit.subset_sum(T)); // subset_sum for one digit
            map[i][iter.digit[i]] = k_sum;
        }
        
        if (i == 0) // If i <= 0, then won't try to access stack[i - 1]
            stack[i] = *k_sum;
        else                                     // If i != 0, then the last position of stack
            stack[i] = stack[i-1] + *k_sum;      // Already contains computed subset_sum
        i++;
    }

    return 0;
}

int 
fill_sumSet(
    KeyMap &map, Key &iter, vector<Key> &stack, vector<Key> &T,
    Key &matcher, unordered_set<KeyPair> &sumSet, int halfC
    ){
    int carry = 1;
    int digit;
    int i = halfC;
    
    while (carry && i >= 0){
        digit = iter.digit[i];
        digit += 1;

        carry = digit >= R;
        if (carry) digit = 0;
        
        iter.digit[i] = digit;
        i--;
    }
    if (carry) return carry; 

    i++;

    while (i < halfC){
        Key *k_sum = map[i][iter.digit[i]];

        if (k_sum == NULL){
            Key sssDigit;                            
            sssDigit.digit[i] = iter.digit[i]; 
            k_sum = new Key(subset_map(sssDigit, T, sumSet)); 
            map[i][iter.digit[i]] = k_sum;
        }
        
        if (i == 0)
            stack[i] = *k_sum;
        else                               
            stack[i] = stack[i-1] + *k_sum;
        i++;
    }

    return 0;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    unordered_set<KeyPair> sumSet;

    vector<Key> T = read_input(); // Computes T table

    Key encrypted(argv[1]);
    encrypted.print_key();
    cout << endl;

    Key max;
    for (int i{0}; i < C; i++) max.digit[i] = R-1;
    
    float halfC = (float)C / 2;
    int ceilhalfC = ceilf(halfC);
    cout << ceilhalfC << endl;

    Key match; // Key we want to match
    Key checker;

    KeyMap map{};           // Initializing every position to NULL
    vector<Key> stack{C};   // An implementation of sorts of a stack

    // Max value for keys with size C/2
    Key firstHalfKeys_Max;
    for (int i{0}; i < ceilhalfC; i++)
        firstHalfKeys_Max.digit[i] = R-1;
    /* 
     Pre-computing the values of the most used sums.
     I don't have probabilistic skills enought to explain why the most computed sums
     will be found in the first half of a key of size C.
     For instance, in a key of size 4, the most computed sums will be computed between "55aa" and "5555"
    */
    while (fill_sumSet(map, match, stack, T, max, sumSet, ceilhalfC-1) != 1){

    }

    // while (match != max){
    //     subset_map(match, T, m);
    //     ++match;
    //     // match += b;
    //     // match.print_key();
    // }
    subset_map(match, T, sumSet);

    return 0;
}
