#include "keyPair.hpp"
#include "key.hpp"

KeyPair::KeyPair() : 
    fst(Key()), 
    snd(Key()) {
}

KeyPair::KeyPair(const Key &k1, const Key &k2) :
    fst(k1 < k2 ? k1 : k2),
    snd(k1 < k2 ? k2 : k1) { // To facilitate operations, the first key will always be the lesser one
}

Key subset_map(const Key &k, const vector<Key> &T, unordered_set<KeyPair> &sumSet){
    Key sum;
    for (int i = 0; i < N; ++i){
        if (bitP(k, i)){
            KeyPair kp(T[i], sum);
            sum += T[i];

            sumSet.insert(kp);
        }
    }
    return sum;
}
