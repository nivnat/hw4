//
// Created by Ari Trachtenberg on 3/15/17.
//

#include "bigNum.h"

/**
 * Reduce #num to a smaller number
 * @return A number between 1 and range-1 inclusive
 */
bigNum reduce(const bigNum &num, const bigNum& range) {
    if (num+1<=range)
        return num;
    else
        return reduce(num/range, range);
}

/*
 * Computes a hash of the provided #plaintext
 * @param nonce A nonce with which to vary the hash
 * @param plaintext The text to hash
 */
bigNum hasher(bigNum nonce, string plaintext) {
    const bigNum bigPrime("622288097498926496141095869268883999563096063592498055290461");

    bigNum theHash = nonce+1;
    std::string::iterator iter;
    for (iter=plaintext.begin(); iter!=plaintext.end(); iter++)
        theHash= reduce(theHash * (*iter), bigPrime);
    return theHash;
}