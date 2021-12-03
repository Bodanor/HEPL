#include <stdlib.h>
#include <math.h>

char b = -15, * pb = &b;
int i = 0xff1, * pi = &i;
float f = 352.318, * pf = &f;
double d = 975.24, * pd = &d;



/*
* Gros questionnement si c'est la bonne facon de push des constante 
*/

int main()
{
	
	/* pd = abs(b); // d = 15.0
	_asm
	{
		movsx eax, b
		push eax
		call abs
		add esp , 4
		cvtsi2sd xmm0, eax
		mov ebx, pd
		movsd QWORD PTR [ebx], xmm0
	}
	*/

	/* f = *pi * (float)sqrt(d); // f = 127444.867
	double dtemp;
	_asm
	{
		mov ebx, pi
		mov eax, DWORD PTR[ebx]
		push eax
		push DWORD PTR d + 4
		push DWORD PTR d
		call sqrt
		add esp, 8
		fstp dtemp
		cvtsd2ss xmm0, dtemp
		pop eax
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		movss f, xmm0

	}
	*/

	/* *pd = log(f) / log(2); // d = 8.460734346... 
	double dtemp, dtemp1;
	_asm
	{
		
		cvtss2sd xmm0, f
		movsd dtemp, xmm0
		push dword ptr dtemp + 4
		push dword ptr dtemp
		call log

		fstp dtemp

		mov eax, 2
		cvtsi2sd xmm1, eax
		movsd dtemp1, xmm1
		push dword ptr dtemp1 + 4
		push dword ptr dtemp1
		call log
		add esp, 16
		fstp dtemp1
		movsd xmm0, dtemp
		movsd xmm1, dtemp1
		divsd xmm0, xmm1

		mov eax, pd
		movsd QWORD PTR[eax],xmm0
	}
	*/

	/* f = sqrt(d) + pow(b, 2) * exp(4); // f = 12315.8125
	const double d2 = 2;
	const double d4 = 4;
	double dtemp, dtemp1;
	_asm
	{
		push dword ptr d2 + 4
		push dword ptr d2
		movsx eax, b
		cvtsi2sd xmm0, eax
		movsd dtemp, xmm0
		push dword ptr dtemp + 4
		push dword ptr dtemp
		call dword ptr pow
		add esp, 16
		fstp dtemp

		push dword ptr d4 + 4
		push dword ptr d4
		call dword ptr exp
		add esp, 8
		fstp dtemp1

		movsd xmm0, dtemp
		movsd xmm1, dtemp1
		mulsd xmm0, xmm1

		push dword ptr d + 4
		push dword ptr d
		call dword ptr sqrt
		add esp, 8
		fstp dtemp
		movsd xmm1, dtemp
		addsd xmm0, xmm1
		cvtsd2ss xmm0, xmm0
		movss f, xmm0
	}
	*/

	/* *pi = -((float)*pi / 2) * (f - 5.2 * sqrt(-*pb)); // i = -677810
	const double d52 = 5.2;
	const double dconst = -1;
	float dtemp;
	double dtemp1;
	_asm
	{
		mov eax, pi
		mov eax, dword ptr[eax]
		cvtsi2ss xmm0, eax

		mov eax, 2
		cvtsi2ss xmm1, eax
		divss xmm0, xmm1
		movss dtemp, xmm0

		movsd xmm1, d52
		mov eax, pb
		movsx eax, DWORD PTR[eax]
		neg eax
		cvtsi2sd xmm0, eax
		movsd dtemp1, xmm0
		push dword ptr dtemp1 + 4
		push dword ptr dtemp1
		call dword ptr sqrt
		add esp, 8
		fstp dtemp1
		movsd xmm2, dtemp1
		mulsd xmm1, xmm2
		movss xmm2, f
		cvtss2sd xmm2, xmm2
		subsd xmm1, xmm2
		
		movss xmm0, dtemp
		cvtss2sd xmm0, xmm0
		mulsd xmm0, dconst
		mulsd xmm0, xmm1

		mov eax, pi
		mov eax, dword ptr[eax]
		cvttsd2si ebx, xmm0
		mov i, ebx
	}
	*/

}