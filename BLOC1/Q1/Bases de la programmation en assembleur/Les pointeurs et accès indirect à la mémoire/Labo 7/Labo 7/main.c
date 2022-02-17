char b = -2, * pb = &b;
short s = 4, * ps = &s;
int i = -3, * pi = &i;
float f = 52.5, * pf = &f;
double d = 3.14, * pd = &d;

 /*
 * Pourquoi ne peux t'on pas directement écrire :
 * movsx ebx, DWORD PTR [pb]
 * Car faire :
 * mov eax, pb --> eax contient l'addresse de b
 * donc faire movsx ebx,DWORD PTR[pb] --> Devrait faire la meme chose ?
 * */

int main()
{
	/* i = *pb + *pf; // i = 50
	_asm
	{
		mov eax, pb
		movsx ebx, DWORD PTR[eax]
		mov eax, pf
		movss xmm0, DWORD PTR[eax]
		cvtsi2ss xmm1, ebx
		addss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax
	}
	*/
	/* *pi = -b + 2 * ~b | i + 0xfe; // i = 255
	_asm
	{
		movsx eax, b
		neg eax
		movsx ebx, b
		not ebx
		imul ebx, 2
		add eax, ebx
		mov ebx, i
		add ebx, 0xfe
		or eax, ebx
		mov ebx, pi
		mov DWORD PTR[ebx], eax
	}
	*/
	 
	/* *pd = *pf + (double)*pb + 0.2; // d = 50.700...
	const double d2 = 0.2;
	_asm
	{
		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		cvtsi2sd xmm0, ebx
		mov eax, pf
		movss xmm1, DWORD PTR[eax]
		cvtss2sd xmm1, xmm1
		addsd xmm0, xmm1
		addsd xmm0, d2
		mov eax, pd
		movsd QWORD PTR[eax], xmm0
	}
	*/

	/* s = ++s * -(*pi)-- / 2 * ~(*ps)--; // s = -43, i = -4
	_asm
	{
		inc s
		mov eax, pi
		mov ebx, DWORD PTR [eax]
		neg ebx

		mov eax, ps
		movsx ecx, WORD PTR[eax]
		not ecx 
		movsx edx, s
		imul ebx, edx
		mov eax, ebx
		mov ebx, 2
		cdq
		idiv ebx
		imul eax, ecx
		mov s, ax
		dec ecx
		mov eax, pi
		mov ebx, DWORD PTR[eax]
		dec ebx
		mov DWORD PTR[eax], ebx
		mov eax, ps
		movsx ebx, WORD PTR[eax]
		dec ebx
		mov WORD PTR[eax], bx
	}
	*/
	/* *ps = -*pb * -(float)*ps * 3.5; // s = -28
	const float fconst = -1;
	const float f35 = 3.5;
	_asm
	{
		mov eax, ps
		movsx ebx, WORD PTR[eax]
		cvtsi2ss xmm0, ebx
		mulss xmm0, fconst

		mov eax, pb
		movsx ebx, BYTE PTR[eax]
		neg ebx
		cvtsi2ss xmm1, ebx
		mulss xmm0, xmm1
		mulss xmm0, f35
		cvttss2si ebx, xmm0
		mov eax, ps
		mov WORD PTR [eax], bx
	}
	*/
	/* s = s * (*pi)-- / 2 + --b * (*ps)--; // s = -19, i = -4, b = -3
	_asm
	{
		dec b
		movsx eax, s
		mov ebx, pi
		mov ecx, DWORD PTR[ebx]
		imul eax, ecx
		mov ebx, 2
		cdq
		idiv ebx
		movsx ebx, b
		mov ecx, ps
		movsx edx, WORD PTR [ecx]
		imul ebx, edx
		add eax, ebx
		mov s, ax

		mov eax, ps
		movsx ebx, WORD PTR [eax]
		dec ebx
		mov WORD PTR[eax], bx

		mov eax, pi
		mov ebx, DWORD PTR [eax]
		dec ebx
		mov DWORD PTR[eax], ebx
	}
	*/
	
	/* i = ~i * (5.3 * (float)*pb); // i = -21
	const float f53 = 5.3;
	_asm
	{
		mov eax, pb
		movsx ebx, BYTE PTR [eax]
		cvtsi2ss xmm0, ebx
		mulss xmm0, f53
		mov eax, i
		not eax
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax
	}
	*/
	/* *pd = (float)i * 2.45 + (int)*pf - ((int)(5.8 * b) | 0xff); // d = 45.649999...
	const double f58 = 5.8, f245 = 2.45;
	_asm
	{
		movsx eax, b
		cvtsi2sd xmm0, eax
		mulsd xmm0, f58
		cvttsd2si eax, xmm0
		or eax, 0xff // EAX contient tout ce qui est a droite

		mov ebx, i
		cvtsi2ss xmm0, ebx
		mov ecx, pf
		movss xmm1, DWORD PTR [ecx]
		cvttss2si ebx, xmm1 // ebx = (int)*pf

		cvtss2sd xmm0, xmm0
		mulsd xmm0, f245
		cvtsi2sd xmm1, ebx
		addsd xmm0, xmm1
		cvtsi2sd xmm1, eax
		subsd xmm0, xmm1
		mov eax, pd
		movsd DWORD PTR [eax], xmm0
	}
	*/
	
	/* f = ++b + -(float)(*pd)-- * ++i; // f = 5.28000021, b = -1, d = 2.14, b = , i = -2
	const float fconst = -1;
	const double dconst = 1;
	_asm
	{
		inc b
		inc i
		mov eax, pd
		movsd xmm0, QWORD PTR [eax]
		cvtsd2ss xmm0, xmm0
		mulss xmm0, fconst
		cvtsi2ss xmm1, i
		mulss xmm0, xmm1
		movsx eax, b
		cvtsi2ss xmm1, eax
		addss xmm0, xmm1
		movss f, xmm0
		mov eax, pd
		movsd xmm0, QWORD PTR [eax]
		subsd xmm0, dconst
		movsd QWORD PTR[eax], xmm0
	}
	*/
	/* *ps = -(int)((*pf)++ + (--b | 0xf) * (float)i) ^ 0xf00f * *pb; // s = -12262, f = 53.5, b = -3
	const float fconst = 1;
	_asm
	{
		dec b
		movsx eax, b
		or eax, 0xf

		cvtsi2ss xmm0, i
		cvtsi2ss xmm1, eax
		mulss xmm0, xmm1
		mov eax, pf
		addss xmm0, DWORD PTR[eax]
		cvttss2si eax, xmm0
		neg eax
		mov ebx, 0xf00f
		mov ecx, pb
		movsx edx, BYTE PTR[ecx]
		imul ebx, edx
		xor eax, ebx
		mov ebx, ps
		mov WORD PTR[ebx], ax
		mov ebx, pf
		movss xmm0, DWORD PTR[ebx]
		addss xmm0, fconst
		movss DWORD PTR[ebx], xmm0
	}
		*/

/* *pi = (float)i * f + (int)*pf - 15435 / (float)*pb; // i = 7612
	const double d15435 = 15435;
	_asm
	{
		cvtsi2ss xmm0, i
		mov eax, pf
		cvttss2si ebx, DWORD PTR[eax]
		mov eax, pb
		movsx ecx, BYTE PTR[eax]
		cvtsi2ss xmm1, ecx
		mulss xmm0, f
		cvtsi2ss xmm2, ebx
		addss xmm0, xmm2

		movsd xmm2, d15435
		cvtsd2ss xmm2, xmm2
		divss xmm2, xmm1
		subss xmm0, xmm2

		cvttss2si eax, xmm0
		mov ebx, pi
		mov DWORD PTR [ebx], eax
	}
	*/

}