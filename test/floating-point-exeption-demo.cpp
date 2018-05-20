
#include <cfloat>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

string FPClass(double x)
{
	int i = _fpclass(x);
	string s;
	switch (i)
	{
	case _FPCLASS_SNAN: s = "Signaling NaN";                break;
	case _FPCLASS_QNAN: s = "Quiet NaN";                    break; 
	case _FPCLASS_NINF: s = "Negative infinity (-INF)";     break; 
	case _FPCLASS_NN:   s = "Negative normalized non-zero"; break;
	case _FPCLASS_ND:   s = "Negative denormalized";        break; 
	case _FPCLASS_NZ:   s = "Negative zero (-0)";           break; 
	case _FPCLASS_PZ:   s = "Positive 0 (+0)";              break; 
	case _FPCLASS_PD:   s = "Positive denormalized";        break; 
	case _FPCLASS_PN:   s = "Positive normalized non-zero"; break; 
	case _FPCLASS_PINF: s = "Positive infinity (+INF)";     break;
	}
	return s;
}

string HexDump(double x)
{
	unsigned long* pu;
	pu = (unsigned long*)&x;
	ostringstream os;
	os << hex << pu[0] << " " << pu[1];
	return os.str();
}


void DemoFloatingPointExceptions()
{
	double x, y, z;

	cout << "Testing z = 1/0\n";
	// cannot set x = 1/0 directly or would produce compile error.
	x = 1.0; y = 0; z = x/y;
	cout << "z = " << x/y << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = -1/0\n";
	x = -1.0; y = 0; z = x/y;
	cout << "z = " << x/y << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = sqrt(-1)\n";
	x = -1.0;
	z = sqrt(x);
	cout << "z = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = log(-1)\n";
	x = -1.0;
	z = sqrt(x);
	cout << "z = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting overflow\n";
	z = DBL_MAX;
	cout << "z = DBL_MAX = " << z; 
	z *= 2.0;
	cout << "; 2z = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting denormalized underflow\n";
	z = DBL_MIN;
	cout << "z = DBL_MIN = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";
	z /= pow(2.0, 52);
	cout << "z = DBL_MIN / 2^52= " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";
	z /= 2;
	cout << "z = DBL_MIN / 2^53= " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = +infinity + -infinty\n";
	x = 1.0; y = 0.0; x /= y; y = -x;
	cout << x << " + " << y << " = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = 0 * infinity\n";
	x = 1.0; y = 0.0; x /= y; z = 0.0*x;
	cout << "x = " << x << "; z = 0*x = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting 0/0\n";
	x = 0.0; y = 0.0; z = x/y;
	cout << "z = 0/0 = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting z = infinity/infinity\n";
	x = 1.0; y = 0.0; x /= y; y = x; z = x/y;
	cout << "x = " << x << "; z = x/x = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting x fmod 0\n";
	x = 1.0; y = 0.0; z = fmod(x, y);
	cout << "fmod(" << x << ", " << y << ") = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nTesting infinity fmod x\n";
	y = 1.0; x = 0.0; y /= x; z = fmod(y, x);
	cout << "fmod(" << y << ", " << x << ") = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";

	cout << "\nGetting cout to print QNAN\n";
	unsigned long nan[2]={0xffffffff, 0x7fffffff};
	z = *( double* )nan;
	cout << "z = " << z << "\n";
	cout << HexDump(z) << " _fpclass(z) = " << FPClass(z) << "\n";
}