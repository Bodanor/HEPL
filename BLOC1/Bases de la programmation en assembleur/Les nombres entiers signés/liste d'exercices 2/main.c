char b = 25;
short s = 40;
int i = -110;

int main(void)
{
	/* i = -s + 2; // i = -38
	_asm
	{
		movsx eax, s
		neg eax
		add eax, 2
		mov i, eax
	}
	*/

	/* i = i + b + s; // i = -45
	_asm
	{
		mov eax, i
		add al, b
		add ax, s
		mov i, eax
	}
	*/
	/* i = i * b + s * i; // i = -7150
   _asm
   {
	   movsx eax, b
	   imul eax, i
	   movsx ebx, s
	   imul ebx, i
	   add eax, ebx
	   mov i, eax
   }
   */

   /* i = -i * (b + s) * i; // i = -786500
   _asm
   {
	   movsx eax, b
	   add ax, s
	   mov ebx, i
	   neg ebx
	   imul eax, ebx
	   imul eax, i
	   mov i, eax
   }
   */

   /* i = (i + b) * -(s + i); // i = -5950
   _asm
   {
	   mov eax, i
	   add al, b
	   movsx ebx, s
	   add ebx, i
	   neg ebx
	   imul eax, ebx
	   mov i, eax
   }
   */
   /* i = i / -s; // i = 2
   _asm
   {
	   movsx ebx, s
	   neg ebx
	   mov eax, i
	   cdq
	   idiv ebx
	   mov i, eax
   }
   */

   /* i = (i - s) % 31; // i = -26
   _asm
   {
	   mov eax, i
	   sub ax, s
	   mov ebx, 31
	   cdq
	   idiv ebx
	   mov i, edx
   }
   */

   /* • i = (i * b) / -(2 * b); // i = 55
   _asm
   {
	   mov eax, i
	   imul al, b
	   movsx ebx, b
	   imul ebx, 2
	   neg ebx
	   cdq
	   idiv ebx
	   mov i, eax
   }
   */

   /* i = -(0x12 - i + b) / 5 - i * s / 2; // i = 2170
   _asm
   {
	   mov eax, 0x12
	   sub eax, i
	   add al, b
	   neg eax
	   mov ebx, 5
	   cdq
	   idiv ebx
	   mov ecx, eax
	   mov eax, i
	   imul ax, s
	   mov ebx, 2
	   cdq
	   idiv ebx
	   sub ecx, eax
	   mov i, ecx
   }
   */

   /* s = i + -s * 18 - i % b; // s = -820
   _asm
   {
	   movsx ecx, s
	   neg ecx
	   imul ecx, 18
	   mov eax, i
	   movsx ebx, b
	   cdq
	   idiv ebx
	   mov eax, edx
	   sub ecx, eax
	   add ecx, i
	   mov s, cx
   }
   */

   /* s = -b - -(s / 3 * i + 800 / -i); // s = -1448
	_asm
	{
		mov eax, i
		neg eax
		mov ecx, eax
		movsx eax, s
		mov ebx, 3
		cdq
		idiv ebx
		imul eax, i
		mov ebx, ecx
		mov ecx, eax
		mov eax, 800
		cdq
		idiv ebx
		add eax, ecx
		movsx ebx, b
		neg ebx
		neg eax
		sub ebx, eax
		mov s, bx
	}
	*/
	/* s = -(b % 10) * +0xff - -(s / 3); // s = -1262
	_asm
	{
		movsx eax, b
		mov ebx, 10
		cdq
		idiv ebx
		mov ecx, edx
		movsx eax, s
		mov ebx, 3
		cdq
		idiv ebx
		neg ecx
		neg eax
		imul ecx, 0xff
		sub ecx, eax
		mov s, cx
	}
	*/

	/* i = -(s * 0xffe1) / -(b * -(s / 3)); // i = -8062
	_asm
	{
		movsx eax, s
		mov ebx, 3
		cdq
		idiv ebx
		neg eax
		imul al, b

		movsx ebx, s
		imul ebx, 0xffe1
		neg ebx
		neg eax
		mov ecx, ebx
		mov ebx, eax
		mov eax, ecx
		cdq
		idiv ebx
		mov i, eax
	}
	*/
	/* i = -(s * 0xffe1) / -(b * -(s / 3) + (3 - i)) / 2; // i = -6179
	_asm
	{
		movsx eax,s
		mov ebx, 3
		cdq
		idiv ebx
		mov ebx, 3
		mov ecx, i
		sub ebx, ecx
		neg eax
		imul al, b
		add ebx, eax
		movsx eax, s
		imul eax, 0xffe1
		neg eax
		neg ebx
		cdq
		idiv ebx
		mov ebx, 2
		cdq
		idiv ebx
		mov i, eax
	}
	*/

}

