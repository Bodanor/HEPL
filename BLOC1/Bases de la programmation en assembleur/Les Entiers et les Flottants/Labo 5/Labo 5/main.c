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


}