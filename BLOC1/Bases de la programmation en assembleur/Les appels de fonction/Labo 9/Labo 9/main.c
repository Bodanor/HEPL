#include <stdlib.h>
#include <math.h>

char b = -15, * pb = &b;
int i = 0xff1, * pi = &i;
float f = 352.318, * pf = &f;
double d = 975.24, * pd = &d;

/*
 * Ici, j'utilise des variables pour stocker le resultat de chaque fonction comme rien ne me l'interdit. Cependant, ca reste quand meme une mauvaise chose ...
 * Par après, pour contourner cela, etant donner qu'on ne peux push un registre xmm0, il faut "coder" l'instruction push manuellement
 * Donc dans les prochains exercices je n'utiliserais que des movsd qword ptr[esp] pour stocker les resultats !
 */



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
	
	/* f = pow(*pd, 3) / (*pb * 15 - sqrt(36)); // f = -4015342.00
	const double d36 = 36;
	const double d3 = 3;
	double dtemp, dtemp1;
	_asm
	{
		mov eax, pb
		movsx eax, BYTE PTR[eax]
		imul eax, 15
		push eax
		push dword ptr d36 + 4
		push dword ptr d36
		call dword ptr sqrt
		add esp, 8
		pop eax
		fstp dtemp
		movsd xmm1, dtemp
		cvtsi2sd xmm0, eax
		subsd xmm0, xmm1
		movsd dtemp, xmm0
		

		push qword ptr d3 + 4
		push qword ptr d3
		mov ebx, pd
		movsd xmm1, qword ptr[ebx]
		sub esp, 8
		movsd qword ptr[esp], xmm1
		call qword ptr pow
		fstp dtemp1

		movsd xmm0, dtemp
		movsd xmm1, dtemp1
		divsd xmm1, xmm0

		cvtsd2ss xmm1, xmm1
		movss f, xmm1
	}
	*/
	
	/* *pi = ((int)floor(*pd) | 0xf00f) - 2 + fabs(b * f); // i = 67697
	double dtemp;
	_asm
	{
		mov eax, pd
		movsd xmm0, QWORD PTR[eax]
		sub esp, 8
		movsd QWORD PTR[esp], xmm0
		call qword ptr floor
		add esp, 8
		fstp dtemp
		movsd xmm0, dtemp
		cvttsd2si eax, xmm0
		or eax, 0xf00f
		sub eax, 2
		push eax
		movsx ebx, b
		cvtsi2ss xmm0, ebx
		mulss xmm0, f
		cvtss2sd xmm0, xmm0
		sub esp, 8
		movsd qword ptr[esp], xmm0
		call qword ptr fabs
		add esp, 8
		fstp dtemp
		movsd xmm0, dtemp
		pop eax
		cvtsi2sd xmm1, eax
		addsd xmm1, xmm0
		cvttsd2si eax, xmm1
		mov ebx, pi
		mov DWORD PTR[ebx], eax
	}
	*/

	/* d = -sin(b * 3 + 5) + pow(*pi + *pd + f, 3); // d = 158213840345.31961
	double dtemp;
	const double d3 = 3, dconst_neg = -1;
	_asm
	{
		movsx eax, b
		imul eax, 3
		add eax, 5
		cvtsi2sd xmm0, eax
		sub esp, 8
		movsd qword ptr[esp], xmm0
		call qword ptr sin
		add esp, 8
		fstp dtemp
		movsd xmm0, dtemp
		mulsd xmm0, dconst_neg
		sub esp, 8
		movsd qword ptr[esp], xmm0
		// Push du deuxieme parametre
		push qword ptr d3 + 4
		push qword ptr d3
		mov eax, pi
		mov eax, dword ptr[eax]
		mov ebx, pd
		movsd xmm1, qword ptr[ebx]
		cvtsi2sd xmm2, eax
		addsd xmm1, xmm2
		movss xmm2, f
		cvtss2sd xmm2, xmm2
		addsd xmm1, xmm2
		sub esp, 8
		movsd qword ptr[esp], xmm1
		call qword ptr pow
		add esp, 16
		fstp dtemp
		movsd xmm1, dtemp
		movsd xmm0, qword ptr[esp]
		addsd xmm0, xmm1
		movsd d, xmm0		
	}
	*/

/* f = cos(-i) * 100 - exp(b / 5 + 6) + *pf * d; // f = 343474.781
	double dtemp;
	const double d100 = 100;
	_asm
	{
		movsx eax, b
		mov ebx, 5
		cdq
		idiv ebx
		add eax, 6
		cvtsi2sd xmm0, eax
		sub esp, 8
		movsd qword ptr[esp], xmm0
		call qword ptr exp
		add esp, 8
		fstp dtemp
		push dtemp + 4
		push dtemp

		mov eax, i
		neg eax
		cvtsi2sd xmm0, eax
		sub esp, 8
		movsd qword ptr[esp], xmm0
		call qword ptr cos
		add esp, 8
		fstp dtemp
		movsd xmm0 , dtemp
		mulsd xmm0, d100
		movsd xmm1, qword ptr[esp]
		add esp, 8
		subsd xmm0, xmm1
		mov eax, pf
		movss xmm1, DWORD PTR[eax]
		cvtss2sd xmm1, xmm1
		mulsd xmm1, d
		addsd xmm0, xmm1
		cvtsd2ss xmm0, xmm0
		movss f, xmm0
	}
	*/

	/* • d = ceil(*pd * 3 + -i) / (cos(2.9) * 6); // d = 198.25776939662740
	double dtemp;
	const double d3 = 3;
	const double d29 = 2.9;
	const double d6 = 6;
	_asm
	{
		mov ebx, i
		neg ebx
		mov eax, pd
		movsd xmm0, qword ptr[eax]
		mulsd xmm0, d3
		cvtsi2sd xmm1, ebx
		addsd xmm0, xmm1
		sub esp, 8
		movsd qword ptr[esp], xmm0
		call qword ptr ceil
		add esp, 8
		fstp dtemp
		sub esp, 8
		movsd xmm0, dtemp
		movsd qword ptr[esp], xmm0
		push d29 + 4
		push d29
		call qword ptr cos
		add esp, 8
		fstp dtemp
		movsd xmm1, dtemp
		mulsd xmm1, d6
		movsd xmm0, qword ptr[esp]
		add esp, 8
		divsd xmm0, xmm1
		movsd d, xmm0
	}
	*/


}