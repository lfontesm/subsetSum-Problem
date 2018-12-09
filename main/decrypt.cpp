#include <array>
#include "key.hpp"
#include "util.hpp"

void decrypt(KeyMap &map, Key &iter, vector<Key> &stack, vector<Key> &T, Key &matcher){
    while (1){ // Technically while the last key haven't been found.
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
        if (carry) return;

        i++; // This line ensures performance. Avoids computing an already computed item in the stack

        while (i < C){
            Key *k_sum = map[i][iter.digit[i]];

            if (k_sum == NULL){
                Key sssDigit;            // Used to compute subset_sum for a single digit
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

        if (stack[C-1] == matcher) // Checks if last position of the stack (which should contain iter.subset_sum) == provided password
            iter.print_key();
    }
}

int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    KeyMap map{};           // Initializing every position to NULL
    vector<Key> stack{C};   // An implementation of sorts of a stack

    vector<Key> T = read_input(); // Computes T table

    Key encrypted(argv[1]); // Encrypted password.

    encrypted.print_key();  // Exhibits provided password;
    cout << endl;

    Key iter;
    decrypt(map, iter, stack, T, encrypted); // Decrypts key
    
    cout << endl;

    for (auto v1 : map) // Frees allocated memory for map
        for (auto v2 : v1)
            delete v2;
    
    return 0;
}