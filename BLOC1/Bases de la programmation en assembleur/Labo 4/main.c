char b = 40;
int i = 20;
int j = -125;
float f = 2.7;
const float f281 = 2.81, f35 = 3.5;

int main()
{
	/* b = f; // b = 2
	_asm
	{
		cvttss2si eax, f
		mov b, al
	}
	*/

	/* f = (int)f281 + i; // f = 22.0

	_asm
	{
		cvttss2si eax, f281
		add eax, i
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}

	*/

	/* i = j + ~(int)f; // i = -128
	_asm
	{
		cvttss2si eax, f
		not eax
		add eax, j
		mov i, eax
	}
	*/
	
	/* b = j / 2 + -f + f35 / 2; // b = -62
	const float fconst = -1;
	_asm
	{
		movss xmm0, f
		mulss xmm0, fconst
		mov eax, j
		mov ebx, 2
		cdq
		idiv ebx
		cvtsi2ss xmm2, ebx
		movss xmm1, f35
		divss xmm1, xmm2
		addss xmm0, xmm1
		cvtsi2ss xmm1, eax
		addss xmm0, xmm1
		cvttss2si eax, xmm0
		mov b, al

	}
	*/

	/* • j = ~(j ^ 0xfff) + -(int)f + f35; // j = 3972
	_asm
	{
		mov eax, j
		xor eax, 0xfff
		cvttss2si ebx, f
		neg ebx
		not eax
		add eax, ebx
		
		cvtsi2ss xmm0, eax
		addss xmm0, f35
		cvttss2si eax, xmm0
		mov j, eax
	}
	*/

	/* i = (float)i * j; // i = -2500
	_asm
	{
		cvtsi2ss xmm0, i
		cvtsi2ss xmm1, j
		mulss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax
	}
	*/

	/* i = i * 2 + f - 5 * b; // i = -157
	_asm
	{
		mov eax, i
		imul eax, 2
		movsx ebx, b
		imul ebx, 5

		cvtsi2ss xmm0, eax
		movss xmm1, f
		addss xmm0, xmm1
		cvtsi2ss xmm1, ebx
		subss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax

	}

	*/

	/* f = (f * 100) / (b - 20 | 0xf0); // f = 1.10655737
	_asm
	{
		mov eax, 100
		cvtsi2ss xmm0, eax
		mulss xmm0, f
		movsx eax, b
		sub eax, 20
		or eax, 0xf0
		cvtsi2ss xmm1, eax
		divss xmm0, xmm1
		movss f, xmm0
	}
	*/

}
