#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct Circle {
	short int x, y;
	int radius;
};

float area(Circle* x, int nr) {
	_asm {
		mov esi, [ebp + 8]		//pun in esi adresa tabloului cu elemente de tip Circle
		mov ebx, 1				//ebx va fi contorul tabloului
		fild dword ptr[esi + 4]	//voi calcula aria primului cerc
		fmul st(0), st(0)
		fldpi
		fmulp st(1), st(0)
		_bucla:
			cmp ebx, [ebp + 12]		//compar de fiecare data contorul cu nr
			je _iesire_din_bucla
			fild dword ptr[esi + 4 + 8 * ebx]	//calculez aria cercului curent
			fmul st(0), st(0)
			fldpi
			fmulp st(1), st(0)
			fcomi st(0), st(1)
			jc _primul_este_mai_mic			//daca st(0)<st(1), doar il scot din stiva
			fxch st(1)						//daca st(0)>st(1), mai intai inversez ariile, apoi scot din stiva valoarea mai mica
			_primul_este_mai_mic:
				fstp st(0)
			inc ebx
			jmp _bucla
		_iesire_din_bucla:
	}
}

int main() {
	Circle c[] = { {1, 4, 7}, {2, 3, 12}, {4, 2, 8}};
	cout << area(c, 3);
	return 0;
}