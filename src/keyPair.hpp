#if !defined(KEYPAIR_H_)
#define KEYPAIR_H_

#include <map>
#include "key.hpp"

class KeyPair{
public:
    KeyPair();
    KeyPair(const Key &k1, const Key &k2);

    Key fst;
    Key snd;

    inline bool operator<(const KeyPair &kp){
        return this->fst < kp.fst;
    }

// private:
    
    
};

Key subset_map(const Key &k, const vector<Key> &T, map<KeyPair*, int> &m);

inline int bitP(const Key &k, const int &i) {
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}

#endif // KEYPAIR_H_
