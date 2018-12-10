#include "keyPair.hpp"

KeyPair::KeyPair() : 
    fst(Key()), 
    snd(Key()) {
}

KeyPair::KeyPair(const Key &k1, const Key &k2) :
    fst(k1),
    snd(k2) { 
}