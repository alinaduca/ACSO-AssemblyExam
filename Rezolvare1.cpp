#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
float harmean(int* x, int nr) {
	float rezultat;
	int valoare1 = 1;
	_asm {
		mov esi, [ebp + 8]  //pun in esi adresa la care se afla vectorul v
		mov ebx, 0			//ebx va fi contorul
		/*
		Strategie: incep de cu parcurgerea in bucla de la a doua pozitie pentru ca pe st(i), 
		adica la sfarsitul stivei, sa fac suma 1/xj
		*/
		fild valoare1
		fild dword ptr[esi + ebx * 4] //st(0) = xi
		fdivp st(1), st(0)
		_bucla:
		cmp ebx, [ebp + 12]		//while(i < nr)
			je _afara
			inc ebx
			fild valoare1
			fild dword ptr[esi + ebx * 4] //st(0) = xi
			fdivp st(1), st(0)
			faddp st(1), st(0)
			jmp _bucla
		_afara:
		fild dword ptr[ebp + 12]
		fdivrp st(1), st(0)
		fstp rezultat;
	}
	return rezultat;
}
int main() {
	int v[] = { 1, 2, 3, 4, 5 };
	cout << harmean(v, 5);
	return 0;
}
