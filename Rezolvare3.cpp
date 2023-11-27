#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct Complex {
	float re, im;
};

void division(Complex* c1, Complex c2, Complex r) {
	_asm {
		mov esi, [ebp + 8]
		mov edi, [ebp + 12]
		fld dword ptr [esi]
		fld dword ptr [edi]
		fmulp st(1), st(0)
		fld dword ptr[esi + 4]
		fld dword ptr[edi + 4]
		fmulp st(1), st(0)
		faddp st(1), st(0)
		fld dword ptr [edi]
		fmul st(0), st(0)
		fld dword ptr [edi + 4]
		fmul st(0), st(0)
		faddp st(1), st(0)
		fdivp st(1), st(0)
		mov esi, [ebp + 16]
		fstp dword ptr [esi]
		mov esi, [ebp + 8]
		fld dword ptr [edi]
		fld dword ptr [esi + 4]
		fmulp st(1), st(0)
		fld dword ptr [esi]
		fld dword ptr [edi + 4]
		fmulp st(1), st(0)
		fsubp st(1), st(0)
		fld dword ptr [edi]
		fmul st(0), st(0)
		fld dword ptr[edi + 4]
		fmul st(0), st(0)
		faddp st(1), st(0)
		fdivp st(1), st(0)
		mov esi, [ebp + 16]
		fstp dword ptr [esi + 4]		
	}
}

int main() {
	Complex a1 = { 2.5, 4.5 }, a2 = { 3.0, 2.75 }, res;
	division(&a1, &a2, &res);
	cout << res.re << " + " << res.im << "i";
	return 0;
}