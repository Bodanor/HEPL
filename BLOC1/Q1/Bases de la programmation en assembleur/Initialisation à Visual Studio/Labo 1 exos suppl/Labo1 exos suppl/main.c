#include <stdio.h>

int i = -36;
int j = 25;

/*
• i = 143; // i = 143
• i = j; // i = 25
• i = i + j; // i = -11
• i = i + j - 8; // i = -19
• i = i - j + 8; // i = -53
• i = i + j * 8; // i = 164
• i = i * j + 8; // i = -892
*/



int main(void)
{	

	/* • i = 143; // i = 143;
	_asm
	{
		mov i, 143
	}
	*/

	/* i = j; // i = 25
	_asm
	{
		mov eax, j
		mov i, eax
	}
	
	*/

	/* • i = i + j; // i = -11

	_asm
	{
		mov eax, i
		add eax, j
		mov i, eax
	}
	*/

	/* • i = i + j - 8; // i = -19
	_asm
	{
		mov ebx, 0
		mov ebx, j
		add ebx, i
		sub ebx, 8
		mov i, ebx
	}

	*/

	/* • i = i - j + 8; // i = -53
	_asm
	{
		mov eax ,i
		sub eax, j
		add eax, 8
		mov i, eax
	}

	 */

	/*• i = i + j * 8; // i = 164

	_asm
	{
		mov eax, j
		imul eax, 8
		add eax, i
		mov i, eax
	}
	*/

	/* • i = i * j + 8; // i = -892
	_asm
	{
		mov eax, i
		imul eax, j
		add eax, 8
		mov i, eax
	}
	*/
}