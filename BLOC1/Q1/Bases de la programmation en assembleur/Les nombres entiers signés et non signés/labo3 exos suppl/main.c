#include <stdio.h>

int main()
{
	int i = -3;
	short s = 4;
	char b = -2;
	unsigned int i1 = 8;
	unsigned short s1 = 4;
	unsigned char b1 = 5;

	/*
	* 
	i = -s1 + 2; // i = -2
	_asm
	{
		movsx eax, s1
		neg eax
		add eax, 2
		mov i, eax
	}
	*/

	/* i = ~s + 2; // i = -3

	_asm
	{
		movsx eax, s
		not eax
		add eax, 2
		mov i, eax
	}

	*/

	/* i = -(b + (char)b1 + s); // i = -7

	_asm
	{
		movsx eax, b1
		movsx ebx, s
		add eax, ebx
		movsx ebx, b
		add eax, ebx
		neg eax
		mov i, eax
	}
	*/
	/* i = -(int)((i1 + -b) / b1); // i = -2
	_asm
	{
		movsx eax, i1
		movsx ebx, b
		neg ebx
		add eax, ebx
		movsx ebx, b1
		cdq
		div ebx
		movzx eax, eax
		neg eax
		mov i, eax

	}

	*/
	

	/* i = (i1 * b1) / -(2 * b); // i = 10

	_asm
	{
		movzx eax, i1
		movzx ebx, b1
		imul eax, ebx
		movsx ebx, b
		imul ebx, 2
		neg ebx
		cdq
		idiv ebx
		mov i ,eax
	}

	*/

	/* s1 = -i - 3 + ((unsigned char)b + (short)s1); // s1 = 258

	_asm
	{
		movzx eax, b
		movsx ebx, s1
		add eax, ebx
		movsx ebx, i
		neg ebx
		sub ebx, 3
		add eax, ebx
		mov s1, ax
	}

	*/

	/* s1 = (i * 6 - s1) + 3 - (0xff + s + b1); // s1 = 65253

	_asm
	{
		movsx eax, i
		imul eax, 6
		movsx ebx, s1
		sub eax, ebx
		movsx ebx, s
		movsx edx, b1
		add ebx, edx
		add ebx, 0xff
		add eax, 3
		sub eax, ebx
		mov si, ax

	}

	*/
	
	/*
	_asm
	{
		movzx ecx, b
		movzx eax, i1
		movzx ebx, b1
		cdq
		idiv ebx
		imul edx, ecx
		neg edx
		mov i, edx
	}
	*/

}