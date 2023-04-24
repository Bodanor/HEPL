char b = -25;
short s = 40;
int i = -110, j = -125;
float f = 212.9;
double d = 6.48;
const float f251 = 2.51, f85 = -8.5;
const float fconst1 = 1;

int main()
{
	/* i = ++s + 2 + ++s; // i = 86, s = 42
	_asm
	{
		inc s
		inc s
		movsx eax, s
		add eax, 2
		movsx ebx, s
		add eax, ebx
		mov i, eax

	}
	*/
	/* i = s++ + 2 + s++; // i = 82, s = 42
	_asm
	{
		movsx eax, s
		add eax, eax
		add eax, 2
		mov i, eax
		inc s
		inc s
	}
	*/
	/* s = -i++ + -++b + s; // s = 174, i = -109, b = -24
	_asm
	{
		inc b
		movsx eax, b
		neg eax
		mov ebx, i
		neg ebx
		movsx ecx, s
		add ebx, eax
		add ebx, ecx
		mov s, bx
		inc i
	}
	*/
	/* i = i++ * b * i + i * (b++ + s) * --i; // i = -123209, b = -24
	_asm
	{
		dec i

		movsx eax, b
		movsx ebx, s
		add ebx, eax
		mov eax, i
		movsx ecx, b
		imul eax, ecx
		mov ecx, i
		imul eax, ecx
		mov ecx, i
		imul ebx, ecx
		mov ecx, i
		imul ebx, ecx
		add eax, ebx
		mov i, eax
		inc b
		inc i

	}
	*/


	/* d = (++i + b) * -(--s + i); // d = -9380.0, i = -109, s = 39
	_asm
	{
		inc i
		mov eax, i
		movsx ebx, b
		add eax, ebx
		dec s
		movsx ebx, s
		add ebx, i
		neg ebx
		imul eax, ebx
		cvtsi2sd xmm0, eax
		movsd d, xmm0
	}
	*/

	/* f = -f-- * ---f; // f = 44900.6055
	_asm
	{
		movss xmm0, f
		subss xmm0, fconst1
		movss f, xmm0

		movss xmm0, f
		mulss xmm0, fconst1

		movss xmm1, f
		mulss xmm1, fconst1

		mulss xmm0, xmm1
		movss f, xmm0

		movss xmm0, f
		subss xmm0, fconst1
		movss f, xmm0

	}
	*/

	/* f = -(0x12 - i + ++b) * 5 / 2.4; // f = -216.666672, b = -24

	const double d24 = 2.4;
	_asm
	{
		inc b
		mov eax, 0x12
		mov ebx, i
		sub eax, ebx
		movsx ebx, b
		add eax, ebx
		neg eax
		imul eax, 5
		cvtsi2sd xmm0, eax
		movsd xmm1, d24
		divsd xmm0, xmm1
		cvtsd2ss xmm0, xmm0
		movss f, xmm0
	}
	*/

	/* f = (int)++f + i; // f = 103.0
		_asm
		{
			movss xmm0, f
			addss xmm0, fconst1
			movss f, xmm0
			cvttss2si eax, xmm0
			add eax, i
			cvtsi2ss xmm0, eax
			movss f, xmm0
		}
		*/

		/* f = i * (float)d-- * (int)--d; // f = -3014.0, d = 4.48000…
	_asm
	{
		movsd xmm0, d
		subsd xmm0, fconst1
		movsd d, xmm0

		cvtsd2ss xmm1, d
		cvttsd2si eax, xmm0
		cvtsi2ss xmm2, i
		mulss xmm2, xmm1
		cvtsi2ss xmm1, eax
		mulss xmm2, xmm1
		movss f, xmm2
	}
	*/

/* i = (double)--j + ~(int)f--; // i = -339, j = -126, f = 211.899994
	const float fconst = 1;
	_asm
	{
		dec j
		cvtsi2sd xmm0, j
		cvttss2si eax, f
		not eax
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		cvttsd2si eax, xmm0
		mov i, eax
		movss xmm0, f
		subss xmm0, fconst
		movss f, xmm0
	}
	*/
	/* i = -j / 2 + --f + (int)f85 / 2.3; // i = 270, f = 211.899994
	const float dconst = 1;
	const double d23 = 2.3;

	_asm
	{
		movss xmm0, f
		subss xmm0, dconst
		movss f, xmm0

		mov eax, j
		neg eax

		cvttss2si ecx, f85

		mov ebx, 2
		cdq
		idiv ebx

		cvtsi2sd xmm0, ecx
		divsd xmm0, d23

		cvtsi2ss xmm1, eax
		addss xmm1, f

		cvtss2sd xmm1, xmm1
		addsd xmm0, xmm1

		cvttsd2si eax, xmm0
		mov i, eax

	}
	*/

	/* f = --f + (0xf2 | i++) * (double)--b * 1 / -f; // f = 210.182205, i = -109, b = -26
	const float fconst = -1;
	_asm
	{

		movsx eax, b
		dec eax
		mov b, al

		movss xmm0, f
		subss xmm0, fconst1
		movss f, xmm0

		mov eax, 0xf2
		mov ebx, i
		or eax, ebx

		movsx ebx, b
		cvtsi2sd xmm0, ebx

		movss xmm1, f
		mulss xmm1, fconst

		cvtsi2sd xmm2, eax
		mulsd xmm0, xmm2
		mov ebx, 1
		cvtsi2sd xmm2, ebx
		mulsd xmm0, xmm2
		cvtss2sd xmm1, xmm1
		divsd xmm0, xmm1

		cvtss2sd xmm1, f
		addsd xmm0, xmm1

		cvtsd2ss xmm0, xmm0
		movss f, xmm0

		mov eax, i
		inc i
		mov i, eax
	}
	*/
	/* d = ((int)f + 0.5 * i) / (float)b + (int)++f; // d = 206.6800..., f = 213.899994
	const double d05 = 0.5;
	_asm
	{
		movss xmm0, f
		addss xmm0, fconst1
		movss f, xmm0

		cvttss2si eax, f
		movsd xmm0, d05
		cvtsi2sd xmm1, i
		mulsd xmm0, xmm1
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1

		movsx eax, b
		cvtsi2ss xmm1, eax

		cvttss2si eax, f
		
		cvtss2sd xmm1, xmm1
		divsd xmm0, xmm1

		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1

		movsd d, xmm0

	}
	*/
}