#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct Tree {
	int value;
	Tree* left, * right;
};

int find(int v, Tree *root) {
	_asm {
		mov edi, [ebp + 8]		//in edi pun valoarea lui v
		mov esi, [ebp + 12]		//in esi voi avea adresa primului element din structura
		cmp esi, '\0'			//verific daca arborele este null
		jz _nu_este_gasit
		cmp edi, [esi]			//compar valoare cu v si verific daca sunt egale si am gasit elementul
		je _gasit
		mov ebx, [esi + 4]		//mut in ebx adresa subarborelui stang
		push ebx
		push edi
		call find				//apelez recursiv functia pentru subarborele stang
		add esp, 8
		cmp eax, 1
		je _gasit
		mov ebx, [esi + 8]		//mut in ebx adresa arborelui drept
		push ebx
		push edi
		call find				//apelez recursiv functia pentru subarborele drept
		add esp, 8
		cmp eax, 1
		je _gasit
		jmp _nu_este_gasit
		
		_gasit:
		mov eax, 1			//voi returna 1 in cazul in care nu am gasit elementul cautat in arbore
		jmp _afara

		_nu_este_gasit:
		mov eax, 0				//voi returna 0 in cazul in care nu am gasit elementul cautat in arbore

		_afara:
	}
}
int main() {
	Tree* r;
	r = new Tree;
	r->value = 7;
	r->left = new Tree;
	r->left->value = 4;
	r->left->left = new Tree;
	r->left->left->value = 3;
	r->left->left->left = r->left->left->right = NULL;
	r->left->right = NULL;
	r->right = new Tree;
	r->right->value = 2;
	r->right->left = r->right->right = NULL;
	cout << find(5, r);
	return 0;
}