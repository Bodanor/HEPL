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

	/* i = (float)i * 2 + f - 5.2 * b; // i = -115 */

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


}