#include "keyPair.hpp"
#include "key.hpp"

KeyPair::KeyPair() : 
    fst(Key()), 
    snd(Key()) {
}

KeyPair::KeyPair(const Key &k1, const Key &k2) :
    fst(k1),
    snd(k2) { 
}

Key subset_map(const Key &k, const vector<Key> &T, map<KeyPair*, int> &m){
    Key sum;
    for (int i = 0; i < N; ++i) {
        if (bitP(k, i) == 0) continue;
        for (int j{0}; j < N; j++){
            if (bitP(k, i) && bitP(k, j)) {
                // sum += T[i];
                KeyPair *kp = new KeyPair(T[i], T[j]);
                
                map<KeyPair*, int>::iterator it;

                it = m.find(kp);
                if (it != m.end())
                    it->second++;
                else
                    m.insert(make_pair(kp, 1));
            }
        }
    }
    return sum;
}
