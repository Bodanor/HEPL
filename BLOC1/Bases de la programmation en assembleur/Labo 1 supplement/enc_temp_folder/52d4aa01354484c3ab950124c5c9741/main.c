#include <stdio.h>

int i = -36;
int j = 25;

int main()
{
	/* i = 2 - i * j + 8; // i = 910
	_asm
	{
		mov eax, i
		imul eax, j
		mov ebx, 2
		sub ebx, eax
		add ebx, 8
		mov i, ebx
	}
	*/

	/* i = j * 0x12 + i + i * 5 + 9; // i = 243
	_asm
	{
		mov eax, j
		imul eax, 0x12
		mov ebx, i
		imul ebx, 5
		add eax, ebx
		add eax, i
		add eax, 9
		mov i, eax
	}

	*/

	/* j = j - j * i + j + i * 0x12; // j = 302
	_asm
	{
		mov eax, j
		imul eax, i
		mov ebx, i
		imul ebx, 0x12
		mov ecx, j
		sub ecx, eax
		add ecx, j
		add ecx, ebx
		mov j, ecx
	}

	 */

	/* j = i + j * 18 - i * j * 178; // j = 160614

	_asm
	{
		mov eax, j
		imul eax, 18
		mov ebx, i
		imul ebx, j
		imul ebx, 178
		add eax, i
		sub eax, ebx
		mov j, eax
	}
	*/

	/* i = 0x12 - i + i * 5 - i * j - 8; // i = 766
	_asm
	{
		mov eax, i
		imul eax, 5
		mov ebx, i
		imul ebx, j
		mov ecx, 0x12
		sub ecx, i
		add ecx, eax
		sub ecx, ebx
		sub ecx, 8
		mov i, ecx
	}
	*/

	/* i = 0x1AB * j + i - 35 * i - j - 8 - 0x22 - i * i - 5; // i = 10531 */
	_asm
	{
		mov eax, 0x1AB
		imul eax, j
		mov ebx, 35
		imul ebx, i
		mov ecx, i
		imul ecx, ecx
		add eax, i
		sub eax, ebx
		sub eax, j
		sub eax, 8
		sub eax, 0x22
		sub eax, ecx
		sub eax, 5
		mov i, eax
	}
}