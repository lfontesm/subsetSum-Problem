#include "key.hpp"
#include "util.hpp"

int main(int argc, char *argv[]){
    if (argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    Key password(argv[1]);   // Password provided by user.
    Key encrypted;           // Encrypted password.

    password.print_key(); // Exibits provided password;
    cout << endl;

    vector<Key> T = read_input(); // Computes T table

    encrypted = password.subset_sum(T); // Computes the encrypted password.

    cout << endl << endl;

    cout << encrypted << endl;

    return 0;
}