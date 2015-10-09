#include <iostream>
using namespace std;

#include "BigInteger.h"

// c'tors
BigInteger::BigInteger ()
{
    Zero();  // default c'tor: create number zero
}

// copy c'tor
BigInteger::BigInteger(const BigInteger& a)
{
    m_length = a.m_length;
    m_sign = a.m_sign;

    m_digits = new int[m_length];
    for (int i = 0; i < m_length; i ++)
        m_digits[i] = a.m_digits[i];
}

// user-defined c'tor
BigInteger::BigInteger(char* s)
{
    // count number of digits 
    m_length = 0;
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] >= '0' && s[i] <= '9')
            m_length ++;

        i ++;
    }

    // set sign
    m_sign = (s[0] == '-') ? false : true;

    // copy digits into array in reverse order
    m_digits = new int[m_length];
    for (int k = 0, j = i - 1; j >= 0; j --)
    {
        if (s[j] >= '0' && s[j] <= '9')
        {
            m_digits[k] = s[j] - '0';
            k++;
        }
    }
}

// internal helper c'tor
BigInteger::BigInteger(bool sign, int digits[], int length)
{
    m_digits = digits;
    m_sign = sign;
    m_length = length;
}

// type conversion c'tors
BigInteger::BigInteger(int n)
{
    ToBigInteger(n);
}

BigInteger::BigInteger(long n)
{
    ToBigInteger(n);
}

// d'tor
BigInteger::~BigInteger ()
{
    delete[] m_digits;
}

// getter
bool BigInteger::Sign() const
{
    return m_sign;
}

int BigInteger::Cardinality() const
{
    return m_length;
}

bool BigInteger::IsNull() const
{
    return m_length == 1 && m_digits[0] == 0;
}

// assignment operator
BigInteger& BigInteger::operator= (const BigInteger& a)
{
    if (this == &a)
        return *this;

    delete[] m_digits;

    m_length = a.m_length;
    m_sign = a.m_sign;

    m_digits = new int[m_length];
    for (int i = 0; i < m_length; i ++)
        m_digits[i] = a.m_digits[i];

    return *this;
}

// unary arithmetic operators
BigInteger operator+ (const BigInteger& a)
{
    BigInteger tmp;
    return tmp;
}

BigInteger operator- (const BigInteger& a)
{
    BigInteger tmp;
    return tmp;
}

// binary arithmetic operators
BigInteger operator+ (const BigInteger& a, const BigInteger& b)
{
    // handle sign and change operation
    if (a.Sign() != b.Sign())
        return (a.Sign()) ? a - b.Abs() : b - a.Abs();

    // allocate array
    int length = (a.Cardinality() >= b.Cardinality()) ?
         a.Cardinality() + 1 :
         b.Cardinality() + 1;

    int* digits = new int[length];

    // add numbers digit per digit
    int carry = 0;
    for (int i = 0; i < length; i++)
    {
        if (i < a.Cardinality())
            carry += a[i];
        if (i < b.Cardinality())
            carry += b[i];

        digits[i] = carry % 10;
        carry /= 10;
    }

    BigInteger tmp (a.Sign(), digits, length);
    tmp.RemoveLeadingZeros();
    return tmp;
}

BigInteger operator- (const BigInteger& a, const BigInteger& b)
{
    // handle sign and change operation
    if (a.Sign() != b.Sign())
        return (a.Sign()) ? a + b.Abs() : -(a.Abs() + b);

    if (a.Abs() < b.Abs())
        return (a.Sign()) ? -(b - a) : b.Abs() - a.Abs();

    // create copy of minuend
    BigInteger tmp (a);

    // traverse digits of subtrahend
    for (int i = 0; i < b.Cardinality(); i++)
    {
        if (tmp[i] < b[i])
        {
            if (tmp[i + 1] != 0)
            {
                tmp[i + 1]--;
                tmp[i] += 10;
            }
            else
            {
                // preceding digit is zero, cannot borrow directly
                int pos = i + 1;
                while (tmp[pos] == 0)
                    pos++;

                // borrow indirectly
                for (int k = pos; k >= i + 1; k--)
                {
                    tmp[k]--;
                    tmp[k - 1] += 10;
                }
            }
        }

        // subtract current subtrahend digit from minuend digit
        tmp[i] -= b[i];
    }

    tmp.RemoveLeadingZeros();
    return tmp;
}

BigInteger operator* (const BigInteger& a, const BigInteger& b)
{
    int length = a.Cardinality() + b.Cardinality();
    int* digits = new int[length];

    int carry = 0;
    for (int i = 0; i < length; i++)
    {
        digits[i] = carry;

        for (int j = 0; j < b.Cardinality(); j++)
            if (i - j >= 0 && i - j < a.Cardinality())
                digits[i] += a[i - j] * b[j];

        carry = digits[i] / 10;
        digits[i] %= 10;
    }

    bool sign = (a.Sign() == b.Sign()) ? true : false;
    BigInteger tmp (sign, digits, length);
    tmp.RemoveLeadingZeros();
    return tmp;
}

BigInteger operator/ (const BigInteger& a, const BigInteger& b)
{
    BigInteger remainder;

    char* result = new char[1];
    result[0] = '\0';

    // need positive divisor
    BigInteger bAbs = b.Abs();

    int pos = a.Cardinality() - 1;
    while (pos >= 0)
    {
        // append next digit from dividend to temporary divisor
        int len = (remainder.IsNull()) ? 1 : remainder.Cardinality() + 1;
        int* digits = new int[len];

        // copy old digits
        for (int k = 0; k < len - 1; k++)
            digits[k + 1] = remainder.m_digits[k];

        // fetch digit from dividend
        digits[0] = a.m_digits[pos];

        remainder = BigInteger(true, digits, len);  // TODO: Ob len hier stimmt, ist OFFEN

        // divide current dividend with divisor
        int n = 0;
        while (bAbs <= remainder)
        {
            n++;
            remainder -= bAbs;
        }

        // append digit to result string
        int slen = strlen(result);
        char* tmp = new char[slen + 2];
        strcpy_s (tmp, slen + 2, result);
        tmp[slen] = '0' + n;
        tmp[slen + 1] = '\0';
        delete[] result;
        result = tmp;

        // fetch next digit from divisor
        pos--;
    }

    BigInteger tmp (result);
    tmp.m_sign = (a.Sign() == b.Sign()) ? true : false;
    tmp.RemoveLeadingZeros();
    return tmp;
}

BigInteger operator% (const BigInteger& a, const BigInteger& b)
{
    return a - b * (a / b);  
}

// arithmetic-assignment operators
const BigInteger& operator+= (BigInteger& a, const BigInteger& b)
{
    a = a + b;
    return a;
}

const BigInteger& operator-= (BigInteger& a, const BigInteger& b)
{
    a = a - b;
    return a;
}

const BigInteger& operator*= (BigInteger& a, const BigInteger& b)
{
    a = a * b;
    return a;
}

const BigInteger& operator/= (BigInteger& a, const BigInteger& b)
{
    a = a / b;
    return a;
}

// increment operator: prefix version
BigInteger& operator++ (BigInteger& a)
{
    a += 1;
    return a;
}

// decrement operator: prefix version
BigInteger& operator-- (BigInteger& a)
{
    a -= 1;
    return a;
}

// increment operator: postfix version
const BigInteger operator++ (BigInteger& a, int)
{
    BigInteger tmp (a); // construct a copy
    ++ a;               // increment number
    return tmp;         // return the copy
}

// decrement operator: postfix version
const BigInteger operator-- (BigInteger& a, int)
{
    BigInteger tmp (a); // construct a copy
    -- a;               // decrement number
    return tmp;         // return the copy
}

BigInteger Faculty (BigInteger n)
{
    if (n == 1)
        return 1;
    else
        return n * Faculty(n - 1);
}

// comparison operators
bool operator== (const BigInteger& a, const BigInteger& b)
{
    return (a.CompareTo(b) == 0) ? true : false;
}

bool operator!= (const BigInteger& a, const BigInteger& b)
{
    return !(a == b);
}

bool operator< (const BigInteger& a, const BigInteger& b)
{
    return (a.CompareTo(b) < 0) ? true : false;
}

bool operator<= (const BigInteger& a, const BigInteger& b)
{
    return (a.CompareTo(b) <= 0) ? true : false;
}

bool operator> (const BigInteger& a, const BigInteger& b)
{
    return b < a;
}

bool operator>= (const BigInteger& a, const BigInteger& b)
{
    return b <= a;
}

// public helper methods
BigInteger BigInteger::Abs() const
{
    BigInteger tmp (*this);
    tmp.m_sign = true;
    return tmp;
}

// private helper operator
int& BigInteger::operator[] (int n) const
{
    static int empty;

    if (n < 0)
        return empty;
    if (n >= m_length)
        return empty;
    return m_digits[n];
}

// private helper methods
void BigInteger::RemoveLeadingZeros()
{
    // count leading zeros
    int zeros = 0;
    for (int i = m_length - 1; i >= 0; i--)
    {
        if (m_digits[i] == 0)
        {
            zeros++;
        }
        else
            break;
    }

    // remove leading zeros
    if (zeros > 0)
    {
        if (zeros < m_length)
        {
            int* tmp = new int[m_length - zeros];

            for (int i = 0; i < m_length - zeros; i++)
                tmp[i] = m_digits[i];

            delete[] m_digits;
            m_digits = tmp;
            m_length -= zeros;
        }
        else
        {
            delete[] m_digits;

            // create number '0'
            Zero();
        }
    }
}

void BigInteger::Zero()
{
    m_digits = new int[1];
    m_digits[0] = 0;
    m_length = 1;
    m_sign = true;
}

int BigInteger::CompareTo(const BigInteger& a) const
{
    if (m_sign && !a.m_sign)
        return 1;
    if (!m_sign && a.m_sign)
        return -1;

    int order = 0;
    if (Cardinality() < a.Cardinality())
    {
        order = -1;
    }
    else if (Cardinality() > a.Cardinality())
    {
        order = 1;
    }
    else
    {
        for (int i = Cardinality() - 1; i >= 0; i--)
        {
            if (m_digits[i] < a.m_digits[i])
            {
                order = -1;
                break;
            }
            else if (m_digits[i] > a.m_digits[i])
            {
                order = 1;
                break;
            }
        }
    }

    return (m_sign) ? order : -order;
}

void BigInteger::ToBigInteger (long n)
{
    // create digits array being long enough
    m_length = 64;
    m_digits = new int[m_length];

    // clear all digits
    for (int i = 0; i < 64; i ++)
        m_digits[i] = 0;

    // handle sign
    m_sign = true;
    if (n < 0)
    {
        m_sign = false;
        n *= -1;
    }
    
    // extract digits from number
    int i = 0;
    while (n != 0)
    {
        m_digits[i] = n % 10;
        n /= 10;
        i ++;
    }

    RemoveLeadingZeros();
}

// output
ostream& operator<< (ostream& os, const BigInteger& n)
{
    if (!n.m_sign)
        os << '-';

    for (int i = n.m_length - 1; i >= 0; i--)
    {
        os << n.m_digits[i];
        if (i > 0 && i % 3 == 0)
            os << '.';
    }

    return os;
}
