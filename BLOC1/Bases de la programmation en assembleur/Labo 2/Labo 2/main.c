#include <stdio.h>

int main()
{
	char b = 25;
	short s = 40;
	int i = -110;

	/*
	i = s;
	_asm{
		movsx eax, s
		mov i, eax

	}
	*/

	/*
	i =b;
	_asm{
		movsx eax, b
		mov eax, i
	}
	*/

	/*
	i = i + b + s
	_asm{
		movsx eax, b
		movsx ebx, s
		add eax, ebx
		add eax, i
		mov i, eax
	}
	*/


	/*
	i = i *b + s *i;
	_asm{
		movsx eax, b
		imul eax, i
		movsx ebx, s
		imul ebx, i
		add eax, ebx
		mov i, eax
	}
	*/

	/*
	i = i * (b + s) * i;
	_asm{
		movsx eax, b
		movsx ebx, s
		add eax, ebx
		imul eax, i
		imul eax, i
		mov i, eax
	}
	*/

	/*
	i = (i - s) *3;
	_asm{
		movsx eax, s
		imul eax, -1
		add eax, i
		imul eax, 3
		mov i, eax
	}

	*/

	/*
	i = (i + b) * (s + i);

	_asm{

		movsx eax, b
		add eax, i
		movsx ebx, s
		add ebx, i
		imul eax, ebx
		mov i, eax
	}
	*/

	/*
	i = i % b;
	_asm{
		mov eax, i
		cdq
		movsx ebx, b
		idiv ebx
		mov i, edx
	}
	*/

	/*
	i = i / s;
	_asm{
		mov eax, i
		cdq
		movsx ebx, s
		idiv ebx
		mov i, eax
	}
	*/

	/*
		i = i / 3 * i / 2;
	*/
	_asm {
		mov eax, i
		cdq
		mov ebx, 3
		idiv ebx
		mov i, eax
		imul eax, i
		mov ebx, 2
		idiv ebx
		mov i, eax

	}

}