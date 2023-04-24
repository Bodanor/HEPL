char b = -20, * pb = &b;
int i = 1317, * pi = &i;
float f = 2452.578, * pf = &f;
double d = 7983.14, * pd = &d;

/* Si il y a un pre dec hors d'une parenthese, est ce que il a une plus haute priorité que la parenthèse ?*/

int main()
{
	/* *pd = b + *pf * 82.195; // d = 201569.63891723630
	const double d82 = 82.195;
	_asm
	{
		mov eax, pf
		movss xmm0, DWORD PTR [eax]
		cvtss2sd xmm0, xmm0
		mulsd xmm0, d82
		movsx eax, b
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		mov eax, pd
		movsd QWORD PTR[eax], xmm0
	}
	*/
	/* f = *pi * (float)*pd; // f = 10513796.0
	_asm
	{
		mov eax, pd
		cvtsd2ss xmm0, QWORD PTR [eax]
		mov eax, pi
		cvtsi2ss xmm1, DWORD PTR[eax]
		mulss xmm0, xmm1
		movss f, xmm0
	}
	*/

	/* i = -((float)*pi) * (2 + f - 5.2 * *pb); // i = -3369647
	const double d52 = 5.2;
	const double dconst = -1;
	_asm
	{
		mov eax, pi
		cvtsi2ss xmm0, DWORD PTR [eax]

		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		cvtsi2sd xmm1, ebx
		mulsd xmm1, d52
		mov eax, 2
		cvtsi2ss xmm2, eax
		addss xmm2, f
		cvtss2sd xmm2, xmm2
		subsd xmm2, xmm1

		cvtss2sd xmm0, xmm0
		mulsd xmm0, xmm2
		mulsd xmm0, dconst

		cvttsd2si eax, xmm0
		mov i, eax

	}
	*/
	/* f = (int)*pd / (*pb - 36); // f = -142.0
	_asm
	{
		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		sub ebx, 36
		mov ecx, pd
		cvttsd2si eax, DWORD PTR[ecx]
		cdq
		idiv ebx
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}
	*/

	/* *pi = (float)*pd * 2 + ++(*pf) - 5 * b; // i = 18519; f = 2453.57788
	const float dconst = 1;
	_asm
	{
		mov eax, pf
		movss xmm0, DWORD PTR[eax]
		addss xmm0, dconst
		movss DWORD PTR[eax], xmm0

		mov eax, pd
		cvtsd2ss xmm0, QWORD PTR[eax]
		mov eax, 2
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1

		mov eax, 5
		movsx ebx, b
		imul eax, ebx

		mov ebx, pf
		addss xmm0, DWORD PTR[ebx]
		cvtsi2ss xmm1, eax
		subss xmm0, xmm1

		cvttss2si eax, xmm0
		mov i, eax
	}
	*/

	/* *pd = ((int)*pd / 100) + (--(*pf) / 20); // d = 201.57888793945313; f = 2451.57788
	const float dconst = 1;

	_asm
	{
		mov eax, pf
		movss xmm0, DWORD PTR[eax]
		subss xmm0, dconst
		movss DWORD PTR[eax], xmm0

		mov ebx, 100
		mov eax, pd
		cvttsd2si eax, QWORD PTR[eax]
		cdq
		idiv ebx

		mov ebx, pf
		movss xmm0, DWORD PTR[ebx]
		mov ebx, 20
		cvtsi2ss xmm1, ebx
		divss xmm0, xmm1

		cvtsi2ss xmm1, eax
		addss xmm0, xmm1

		cvtss2sd xmm0, xmm0
		mov eax, pd
		movsd QWORD PTR[eax], xmm0
	}
	*/

	/* d = -((double)b + (int)*pd * i) / --(*pb); // d = 500647.14285714284; b = -21
	const double dconstneg = -1;
	_asm
	{
		mov eax, pb
		movsx ebx, BYTE PTR [eax]
		dec ebx
		mov BYTE PTR[eax], bl

		movsx eax, b
		cvtsi2sd xmm0, eax
		mov eax, pd
		cvttsd2si eax, QWORD PTR[eax]
		imul eax, i

		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1

		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		cvtsi2sd xmm1, ebx

		mulsd xmm0, dconstneg
		divsd xmm0, xmm1
		movsd d, xmm0

	}
	*/
	/* f = (int)(-97 - --(*pf) - - --(*pb) * d + 46.67); // f = -170147.0; b = -21
	const float fconst = 1;
	const float fconstneg = -1;
	const double d4667 = 46.67;
	_asm
	{
		mov eax, pf
		movss xmm0, DWORD PTR[eax]
		subss xmm0, fconst
		movss DWORD PTR[eax], xmm0

		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		dec ebx
		mov BYTE PTR[eax], bl

		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		neg ebx
		cvtsi2sd xmm0, ebx
		mulsd xmm0, d

		mov eax, -97
		cvtsi2ss xmm1, eax
		mov eax, pf
		subss xmm1, DWORD PTR[eax]

		cvtss2sd xmm1, xmm1
		subsd xmm1, xmm0
		addsd xmm1, d4667

		cvttsd2si eax, xmm1
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}
	*/
/* d = (int)(*pd)++ * 3 + (double)-i / *pf; // d = 23949.463013994264
	const double dconst = 1;
	_asm
	{
		mov eax,pd
		movsd xmm0, QWORD PTR[eax]
		cvttsd2si eax, xmm0
		
		mov ebx, i
		neg ebx
		cvtsi2sd xmm0, ebx

		imul eax, 3

		mov ebx, pf
		movss xmm1, DWORD PTR[ebx]
		cvtss2sd xmm1, xmm1
		divsd xmm0, xmm1

		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		movsd d, xmm0

		mov eax, pd
		movsd xmm0, QWORD PTR[eax]
		addsd xmm0, dconst
		movsd QWORD PTR[eax], xmm0
	}
	*/

	/* *pi = (int)(*pf + 0.5 * i) | 0xff + *pb; // i = 3311
	const double d05 = 0.5;
	_asm
	{
		
		movsd xmm0, d05
		mov eax, i
		cvtsi2sd xmm1, eax
		mulsd xmm0, xmm1
		mov eax, pf
		cvtss2sd xmm1, DWORD PTR[eax]
		addsd xmm0, xmm1
		cvttsd2si eax, xmm0

		mov ebx, pb
		movsx ecx, BYTE PTR[ebx]
		add ecx, 0xff
		or eax, ecx

		mov ebx, pi
		mov DWORD PTR[ebx], eax

	}
	*/

	/* • *pf = (*pi * 0xff & 0xfff0) / (*pd - 4278.45); // f = 2.19829464
	const double d427845 = 4278.45;
	_asm
	{
		mov eax, pi
		mov eax, DWORD PTR[eax]
		imul eax, 0xff
		and eax, 0xfff0

		mov ebx, pd
		movsd xmm0, QWORD PTR[ebx]
		subsd xmm0, d427845
		cvtsi2sd xmm1, eax
		divsd xmm1, xmm0
		cvtsd2ss xmm1, xmm1
		mov eax, pf
		movss DWORD PTR[eax], xmm1
	}
	*/
}