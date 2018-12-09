#include "key.hpp"
#include "util.hpp"

int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<Key> T = read_input(); // Computes T table

    Key encrypted(argv[1]); // Encrypted password.

    encrypted.print_key();  // Exhibits provided password;
    cout << endl;

    Key max;
    for (int i{0}; i < C; i++) max.digit[i] = R-1;

    Key match; // Key we want to match
    Key checker;
    while (match != max){
        if (match.subset_sum(T) == encrypted)
            cout << match << endl;
        ++match;
    }

    return 0;
}
