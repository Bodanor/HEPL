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
}