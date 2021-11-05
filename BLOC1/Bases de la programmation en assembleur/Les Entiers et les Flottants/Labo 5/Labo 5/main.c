int i = 20;
float f = 52.5;
double d = 3.14;
char b = 40;
const double f35 = 3.5;
const float f52 = 5.2;

int main()
{	
	/* d = d + b * 3.5; // d = 143.13999...
	_asm
	{
		movsd xmm0, f35
		movsx eax, b
		cvtsi2sd xmm1, eax
		mulsd xmm0, xmm1
		movsd xmm1, d
		addsd xmm0, xmm1
		movsd d, xmm0
	}
	*/

	/* f = i * (float)d; // f = 62.8000031
	_asm
	{
		cvtsd2ss xmm0, d
		mov eax, i
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		movss f, xmm0
	}
	*/

	/* i = (float)i * 2 + f - 5.2 * b; // i = -115

	_asm
	{
		mov eax, i
		cvtsi2ss xmm0, i
		mov eax, 2
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		movss xmm1, f52
		movsx eax, b
		cvtsi2ss xmm2,eax
		mulss xmm1, xmm2
		addss xmm0, f
		subss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax

	}
	*/

	/* f = (int)f / (b - 36); // f = 13.0
	_asm
	{
		movss xmm0, f
		cvtss2si eax, xmm0
		movsx ebx,b
		sub ebx,36
		cdq
		idiv ebx
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}
	*/

	/* i = (float)d * 2 + f - 5 * b; // i = -141
	_asm
	{
		cvtsd2ss xmm0, d
		mov eax, 2
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		mov eax, 5
		movsx ebx, b
		imul eax, ebx
		addss xmm0, f
		cvtsi2ss xmm1, eax
		subss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax
	}
	*/
	/* d = ((int)d * 1000) / (f - 20); // d = 92.30769348...
	_asm
	{
		cvttsd2si eax, d
		imul eax, 1000
		movss xmm1, f
		mov ebx, 20
		cvtsi2ss xmm2, ebx
		subss xmm1, xmm2
		cvtsi2ss xmm0, eax
		divss xmm0, xmm1
		cvtss2sd xmm0, xmm0
		movsd d, xmm0
	}
	*/
	/* d = -((double)b + (int)d * i) / 2.3; // d = -43.478260... 
	const double dconst = -1;
	const double d23 = 2.3;
	_asm
	{
		cvttsd2si eax, d
		imul eax, i
		cvtsi2sd xmm0, b
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		movsd xmm1, dconst
		mulsd xmm0, xmm1
		movsd xmm1, d23
		divsd xmm0, xmm1
		movsd d, xmm0
	}
	*/
	
	/* i = (int)(-d + 2.81 - -b * f + 3.5) / 3; // i = 701
	const double dconst = -1;
	const double d281 = 2.81;
	const double d35 = 3.5;
	_asm
	{	
		movsd xmm0, d
		movsd xmm1, dconst
		mulsd xmm0, xmm1

		movsx eax, b
		neg eax
		movss xmm1, f
		cvtsi2ss xmm2, eax
		mulss xmm1, xmm2
		
		addsd xmm0, d281
		cvtss2sd xmm1, xmm1
		subsd xmm0, xmm1
		addsd xmm0, d35
		cvttsd2si eax, xmm0

		mov ebx, 3
		cdq
		idiv ebx
		mov i, eax
	}
	*/
	
	/* d = (int)d * 3 + (double)-i / f + (b + 2.1); // d = 50.7190476190...
	const double d21 = 2.1;
	const double dconst = -1;
	_asm
	{	
		// d'abord la parenthèse
		movsx eax, b
		movsd xmm0, d21
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1

		// casting et signe
		cvttsd2si eax, d
		cvtsi2sd xmm1, i
		mulsd xmm1, dconst

		// Operations
		imul eax, 3
		cvtss2sd xmm2, f
		divsd xmm1, xmm2
		cvtsi2sd xmm2, eax
		addsd xmm1, xmm2
		addsd xmm1, xmm0
		movsd d, xmm1
	}
	*/
	/* b = (f + 0.5 * i) / b + f; // b = 54
	const double d05 = 0.5;
	_asm
	{
		movsd xmm0, d05
		cvtsi2sd xmm1, i
		mulsd xmm0, xmm1

		cvtss2sd xmm1, f
		addsd xmm0, xmm1

		cvtsi2sd xmm1, b
		divsd xmm0, xmm1

		cvtss2sd xmm1, f
		addsd xmm0, xmm1
		cvttsd2si eax, xmm0
		mov b, al
		
	}
	*/
	/* f = d / 2 * i / 3 + b / 2.5; // f = 26.4666672
	const double d25 = 2.5;
	_asm
	{
		movsd xmm0, d
		mov eax, 2
		cvtsi2sd xmm1, eax
		divsd xmm0, xmm1
		cvtsi2sd xmm1, i
		mulsd xmm0, xmm1
		mov eax, 3
		cvtsi2sd xmm1, eax
		divsd xmm0, xmm1

		movsx eax, b
		cvtsi2sd xmm1, eax
		divsd xmm1, d25
		addsd xmm0, xmm1
		cvtsd2ss xmm0, xmm0
		movss f, xmm0

	}
	*/
	/* f = (d * 100) / (b - 0xff & 0xf0); // f = 9.8125
	_asm
	{
		mov eax, 100
		cvtsi2sd xmm0, eax
		mulsd xmm0, d

		movsx eax, b
		sub eax, 0xff
		and eax, 0xf0

		cvtsi2sd xmm1, eax
		divsd xmm0, xmm1

		cvtsd2ss xmm0, xmm0
		movss f, xmm0
	}
	*/
}