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
}