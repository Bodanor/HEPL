/* EXERCICE 1 */

/*
int i = -3;
short s = 4;
char b = -2;
unsigned int i1 = 8;
unsigned short s1 = 4;
unsigned char b1 = 5;

int main(void)
{
	/* i = i1 - (3 & b) - s; // i = 2
	_asm
	{
		movsx eax, b
		and eax, 3
		mov ebx, i1
		sub ebx, eax
		movsx eax, s
		sub ebx, eax
		mov i, ebx
	}

	*/
	/* s = -i - 3 + (unsigned char)b ^ (short)s1; // s = 250
	_asm
	{
		mov eax, i
		neg eax
		movzx ebx, b
		movsx ecx, s1
		sub eax, 3
		add eax, ebx
		xor ebx, ecx
		mov s, bx
	}
	*/

	/* s1 = (i * 6 | s1) + 3 + b; // s1 = 65519
	_asm
	{
		mov eax, i
		imul eax, 6
		movzx ebx, s1
		or eax, ebx
		add eax, 3
		movsx ebx, b
		add eax, ebx
		mov s1, ax
	}
	*/

	/* b = b1 * s1 * i | i - 8; // b = -11
	_asm
	{
		movzx eax, b1
		movzx ebx, s1
		imul eax, ebx
		mov ebx, i
		imul eax, ebx
		sub ebx, 8
		xor eax, ebx
		mov b, bl
	}

	*/

	/* s1 = i1 * 100 ^ 255 - b1 | (unsigned char)b; // s1 = 1022
	_asm
	{
		movzx eax, b
		movzx ebx, i1
		imul ebx, 100
		movzx ecx, b1
		mov edx, 255
		sub edx, ecx
		xor ebx, edx
		or ebx, eax
		mov s1, bx
	}
	}
	 */


/* EXERCICE 2*/

/*
* ENONCÉ :
* 
short s = 4;
unsigned char b1 = 5;
unsigned int i1 = 8;
int main()
{
	_asm
	{
		mov eax, i1
		movzx ebx, b1
		add eax, ebx
		mov edx, 0
		movzx ebx,s
		div ebx
		mov ebx, 8
		mul ebx
		mov i1, eax // i1 = 24
	}
	return 0;
}
*/

/*
* SOLUTION : 
* 
short s = 4;
unsigned char b1 = 5;
unsigned int i1 = 8;

int main()
{
	i1 = ((i1 + b1) / s) * 8;

}

*/

/*
* ENONCÉ
* 
unsigned int i = 35;
unsigned short s = 8;
unsigned char b = 4;
int main()
{
	_asm
	{
		mov eax, i
		mov edx, 0
		mov ebx, 3
		div ebx
		not eax
		mov ecx, eax
		movzx eax, b
		mov ebx, 232
		mul ebx
		sub ecx, eax
		mov s, cx // s = 64596
	}
	return 0;
}
*/
/* 
* SOLUTION :
* 
unsigned int i = 35;
unsigned short s = 8;
unsigned char b = 4;

int main(void)
{
	s = (~(i / 3)) - (232 * b);
}

*/

/*
* ENONCÉ
* 
unsigned char b = 5;
short s = 0xbe15;
int i = -60000;
int main()
{
	_asm
	{
		movzx eax, b
		sub eax, 0xffe1
		mov ebx, 3
		mul ebx
		mov ebx, i
		sub ebx, 8
		movsx ecx, s
		add ebx, ecx
		add eax, ebx
		mov i, eax // i = -273383
	}
	return 0;
}
*/

/*
* SOLUTION :
* 
unsigned char b = 5;
short s = 0xbe15;
int i = -60000;

int main()
{
	i = ((b - 0xffe1) * 3) + ((i - 8) + s);

}
*/