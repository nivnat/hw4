//
// Created by Ari Trachtenberg on 1/30/17.
//

#include "bigNum.h"

#include <sstream>
#include <memory>
#include "bigNum.h"

// IMPLEMENTATION

bigNum::bigNum(string num) {
    bool leading = true; // used to ignore leading zeroes
    for (int ii = 0; ii < num.length(); ii++)
        if (leading && num[ii] == '0')
            continue;
        else {
            leading = false;
            digits.insert(digits.begin(), num[ii] - '0');
        }
}

bigNum::bigNum(unsigned int num) {
    stringstream ss; ss<<num;
    *this=bigNum(ss.str());
}


bigNum::bigNum(const bigNum& otherNum):digits(otherNum.digits) {
}

bigNum& bigNum::operator=(const bigNum& otherNum) {
    digits = otherNum.digits;
    return *this;
}

bigNum& bigNum::operator+=(const bigNum& addor) {
    bigNum first, second; // second always has at least as many digits as first
    auto_ptr<bigNum> result(new bigNum("0"));
    if (digits.size() > addor.digits.size()) {
        first = addor;
        second = *this;
    } else {
        first = *this;
        second = addor;
    }

    int ii;
    int carry = 0;
    for (ii = 0; ii < first.digits.size(); ii++) {
        int sum = first.digits[ii] + second.digits[ii];
        result->digits.push_back((sum + carry) % base);
        if (sum + carry > (base - 1)) {
            carry = 1;
        } else {
            carry = 0;
        }
    }

    // finish up with the larger number
    for (; ii < second.digits.size(); ii++)
        if (carry) {
            int dig = (second.digits[ii] + carry);
            result->digits.push_back(dig % base);
            carry = (dig > (base - 1) ? dig / base : 0);
        } else
            result->digits.push_back(second.digits[ii]);
    if (carry)
        result->digits.push_back(carry);

    *this = *result;
    return *this;
}

bigNum &bigNum::operator*=(const int cc) {
    // multiplies by small number cc
    int carry = 0;
    auto_ptr<bigNum> result(new bigNum());

    for (int ii = 0; ii < digits.size(); ii++) {
        int prod = digits[ii] * cc + carry;
        result->digits.push_back(prod % base);
        if (prod > (base - 1))
            carry = prod / base;
        else
            carry = 0;
    }

    while (carry) {
        result->digits.push_back(carry % base);
        carry /= base;
    }

    *this=*result;
    return *this;
}

bigNum &bigNum::operator*=(const bigNum& multiplicator) {
    auto_ptr<bigNum> sum(new bigNum());
    for (int ii = 0; ii < multiplicator.digits.size(); ii++) {
        bigNum smallProd = *this * multiplicator.digits[ii];
        smallProd << ii;
        *sum += smallProd;
    }
    *this = *sum;
    return *this;
}

bigNum &bigNum::operator/=(const bigNum& divisor) {
    // pretty naive algorithm that is easy to implement
    auto_ptr<bigNum> guess(new bigNum());
    for (int ii = digits.size() - 1; ii >= 0; ii--) {
        int dig;
        bigNum trial("");
        for (dig = 9; dig > 0; dig--) {
            bigNum num("1");
            num << ii;
            trial = (num * dig);
            if ((*guess + trial) * divisor <= *this)
                break;
        }
        if (dig != 0)
            *guess = *guess + trial;
    }
    if (guess->digits.size() == 1 && guess->digits[0] == 0)
        guess->digits.pop_back(); // make it the empty representation
    *this = *guess;
    return *this;
}

bool bigNum::operator==(const bigNum& otherNum) const {
    if (digits.size() != otherNum.digits.size()) {
        return false;
    }
    for (int ii = 0; ii < digits.size(); ii++)
        if (digits[ii] != otherNum.digits[ii])
            return false;
    return true;
}

bool bigNum::operator<=(const bigNum& otherNum) const {
    if (digits.size() > otherNum.digits.size())
        return false;
    if (digits.size() < otherNum.digits.size())
        return true;
    // same number of digits
    for (int ii = digits.size() - 1; ii >= 0; ii--)
        if (digits[ii] < otherNum.digits[ii])
            return true;
        else if (digits[ii] > otherNum.digits[ii])
            return false;
    return true; // they are equal
}

void bigNum::operator<<(int cc) {
    digits.insert(digits.begin(), cc, 0);
}


// friends and helpers
std::ostream & operator<<(std::ostream& stream, const bigNum& num) {
    if (num.digits.size() == 0)
        stream << "[0]";
    else
        for (int ii = num.digits.size() - 1; ii >= 0; ii--)
            stream << num.digits[ii];
    return stream;
}

bigNum& operator+(const bigNum& addend, const bigNum& addor) {
    bigNum *result = new bigNum();
    *result = addend;
    *result += addor;
    return *result;
}

bigNum& operator*(const bigNum& multiplicand, const bigNum& multiplicator) {
    bigNum *result = new bigNum();
    *result = multiplicand;
    *result *= multiplicator;
    return *result;
}

bigNum& operator/(const bigNum& dividend, const bigNum& divisor) {
    bigNum *result = new bigNum();
    *result = dividend;
    *result /= divisor;
    return *result;
}

bigNum& operator*(const bigNum& multiplicand, int cc) {
    bigNum *result = new bigNum(multiplicand);
    *result *= cc;
    return *result;
}