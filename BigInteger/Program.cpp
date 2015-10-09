#include <iostream>
#include <iomanip>
using namespace std;

// #include <limits.h>

#include "BigInteger.h"

// function prototypes
void TestCtors();
void TestAdd();
void TestSub();
void TestAddWithSign();
void TestSubWithSign();

void Test_Mul_01_Unsigned();
void Test_Mul_02_Signed();
void Test_Mul_03_Signed();

void Test_Div_01_Unsigned();
void Test_Div_02_Signed();
void Test_Div_03_Signed();
void Test_Div_03_PowerByTwo();

void Test_Mod_01_Signed();
void Test_Mod_02_Signed();

void Test_IncrementDecrement();
void Test_Faculty();
void Test_PowerByTwo();
void Test_BigMersennePrime();

void main ()
{
    TestCtors();
    TestAdd();
    TestSub();

    TestAddWithSign();
    TestSubWithSign();

    Test_Mul_01_Unsigned();
    Test_Mul_02_Signed();

    Test_Div_01_Unsigned();
    Test_Div_02_Signed();
	Test_Div_03_Signed();

    Test_Mod_01_Signed();
    Test_Mod_02_Signed();

    Test_IncrementDecrement(); 

    Test_Faculty();
    Test_PowerByTwo();
    Test_Div_03_PowerByTwo();

    Test_BigMersennePrime();

	getchar();
}

void TestCtors()
{
    // testing c'tors
    BigInteger n1 ("1234567");
    cout << n1 << endl;

    BigInteger n2 ("-1234567");
    cout << n2 << endl;

    BigInteger n3 ("123.456.789.012.345.678");
    cout << n3 << endl;

    BigInteger n4 (123);
    cout << n4 << endl;

    BigInteger n5 (INT_MIN + 1);
    cout << n5 << endl;

    BigInteger n6 (INT_MAX);
    cout << n6 << endl;
}

void TestAdd()
{
    // testing addition
    BigInteger n1 = BigInteger("11111111");
    BigInteger n2 = BigInteger("22222222");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;

    n1 = BigInteger("99999999999999");
    n2 = BigInteger("1");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;
}

void TestSub()
{
    // testing subtraction
    BigInteger n1 ("999");
    BigInteger n2 ("900");
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("999");
    n2 = BigInteger("998");
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("999");
    n2 = BigInteger("999");
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("11111");
    n2 = BigInteger("222");
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("1000000");
    n2 = BigInteger("1");
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;
}

void TestAddWithSign()
{
    // testing c'tors
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;
    cout << endl;
}

void TestSubWithSign()
{
    // testing c'tors
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;
    cout << endl;

    // -----------------------------------------------------

    n1 = BigInteger("222");
    n2 = BigInteger("333");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("-222");
    n2 = BigInteger("333");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("222");
    n2 = BigInteger("-333");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;

    n1 = BigInteger("-222");
    n2 = BigInteger("-333");
    cout << n1 << " + " << n2 << " = " << n1 - n2 << endl;
}

void Test_Mul_01_Unsigned()
{
    // testing unsigned mul operation
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger(99);
    n2 = BigInteger(99);
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    n1 = BigInteger((int) 9999999999);
    n2 = BigInteger((int) 9999999999);
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    // testing multiplication
    n1 = BigInteger("1212121212");
    n2 = BigInteger("4343434343");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    // multiplication example from script
    n1 = BigInteger("973018");
    n2 = BigInteger("9758");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    // testing multiplication
    n1 = BigInteger("3");
    n2 = BigInteger("50");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;
}

void Test_Mul_02_Signed()
{
    // testing signed mul operation
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;
    cout << endl;
}

void Test_Div_01_Unsigned()
{
    // testing unsigned div operation
    BigInteger n1;
    BigInteger n2;

    // 10
    n1 = 100;
    n2 = 10;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    // 34.096
    n1 = 6682850;
    n2 = 196;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    // 3003
    n1 = 30027000;
    n2 = 9999;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    // 3707
    n1 = BigInteger("1234567");
    n2 = BigInteger("333");
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    // 22985
    n1 = BigInteger("7654321");
    n2 = BigInteger("333");
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    // 33
    n1 = BigInteger("1111");
    n2 = BigInteger("33");
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;
}

void Test_Div_02_Signed()
{
    // testing signed div operation
    BigInteger n1;
    BigInteger n2;

    n1 = 1000;
    n2 = 33;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    n1 = -1000;
    n2 = 33;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    n1 = 1000;
    n2 = -33;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

    n1 = -1000;
    n2 = -33;
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;
}

void Test_Div_03_Signed()
{
    // testing signed div operation
    BigInteger n1 ("4.835.703.278.458.516.698.824.704");
    BigInteger n2 ("2");
    cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;
}

void Test_Mod_01_Signed()
{
    // testing signed modulus operation
    BigInteger n1;
    BigInteger n2;

    n1 = 1000;
    n2 = 33;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = -1000;
    n2 = 33;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = 1000;
    n2 = -33;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = -1000;
    n2 = -33;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;
}

void Test_Mod_02_Signed()
{
    // testing signed modulus operation - from Wikipedia ("Division mit Rest")
    BigInteger n1;
    BigInteger n2;

    n1 = 7;
    n2 = 3;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = -7;
    n2 = 3;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = 7;
    n2 = -3;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;

    n1 = -7;
    n2 = -3;
    cout << n1 << " % " << n2 << " = " << n1 % n2 << endl;
}

void Test_IncrementDecrement()
{
    // addition example from script
    BigInteger n1 = 5;
    BigInteger b2;

    b2 = n1;
    cout << b2 << " [expecting '5'] " << endl;

    b2 = n1++;
    cout << b2 << " [expecting '5'] " << endl;

    b2 = ++n1;
    cout << b2 << " [expecting '7'] " << endl;

    b2 = --n1;
    cout << b2 << " [expecting '6'] " << endl;

    b2 = n1--;
    cout << b2 << " [expecting '6'] " << endl;
}
 
void Test_Faculty()
{
    for (BigInteger i = 1; i <= 40; i++)
    {
        BigInteger f = Faculty (i);

        cout << "Faculty of ";
        if (i < 10)
            cout << ' ';
        cout << i << ": " << f << endl;
    }
}

void Test_PowerByTwo()
{
    BigInteger two (2);
    BigInteger power (1);

    for (int i = 1; i <= 100; i ++)
    {
        power = power * two;
        cout << "2 ^ " << i << " = " << power << endl;
    }
}

void Test_Div_03_PowerByTwo()
{
    BigInteger huge ("2.475.880.078.570.760.549.798.248.448");
    while (huge != 1)
    {
        cout << huge << " / 2 = ";
        huge = huge / 2;
        cout << huge << endl;
    }
}

void Test_BigMersennePrime()
{
    BigInteger mersenne (1);
    BigInteger two (2);
    for (int i = 0; i < 11213; i ++)
        mersenne = mersenne * two;
    mersenne = mersenne - 1;

    cout << "Mersenne: " << endl << mersenne << endl;
    cout << "Number of Digits: " << mersenne.Cardinality() << endl;
}
