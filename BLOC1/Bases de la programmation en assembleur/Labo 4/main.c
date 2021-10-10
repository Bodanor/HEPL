char b = 40;
int i = 20;
int j = -125;
float f = 2.7;
const float f281 = 2.81, f35 = 3.5;

int main()
{
	/* b = f; // b = 2
	_asm
	{
		cvttss2si eax, f
		mov b, al
	}
	*/

	/* f = (int)f281 + i; // f = 22.0

	_asm
	{
		cvttss2si eax, f281
		add eax, i
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}

	*/

	/* i = j + ~(int)f; // i = -128
	_asm
	{
		cvttss2si eax, f
		not eax
		add eax, j
		mov i, eax
	}
	*/
	
	/* b = j / 2 + -f + f35 / 2; // b = -62
	const float fconst = -1;
	_asm
	{
		movss xmm0, f
		mulss xmm0, fconst
		mov eax, j
		mov ebx, 2
		cdq
		idiv ebx
		cvtsi2ss xmm2, ebx
		movss xmm1, f35
		divss xmm1, xmm2
		addss xmm0, xmm1
		cvtsi2ss xmm1, eax
		addss xmm0, xmm1
		cvttss2si eax, xmm0
		mov b, al

	}
	*/

	/* • j = ~(j ^ 0xfff) + -(int)f + f35; // j = 3972
	_asm
	{
		mov eax, j
		xor eax, 0xfff
		cvttss2si ebx, f
		neg ebx
		not eax
		add eax, ebx
		
		cvtsi2ss xmm0, eax
		addss xmm0, f35
		cvttss2si eax, xmm0
		mov j, eax
	}
	*/

	/* i = (float)i * j; // i = -2500
	_asm
	{
		cvtsi2ss xmm0, i
		cvtsi2ss xmm1, j
		mulss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax
	}
	*/

	/* i = i * 2 + f - 5 * b; // i = -157
	_asm
	{
		mov eax, i
		imul eax, 2
		movsx ebx, b
		imul ebx, 5

		cvtsi2ss xmm0, eax
		movss xmm1, f
		addss xmm0, xmm1
		cvtsi2ss xmm1, ebx
		subss xmm0, xmm1
		cvttss2si eax, xmm0
		mov i, eax

	}

	*/

	/* f = (f * 100) / (b - 20 | 0xf0); // f = 1.10655737
	_asm
	{
		mov eax, 100
		cvtsi2ss xmm0, eax
		mulss xmm0, f
		movsx eax, b
		sub eax, 20
		or eax, 0xf0
		cvtsi2ss xmm1, eax
		divss xmm0, xmm1
		movss f, xmm0
	}
	*/
	
	/* f = ((int)f * 100) / (~b - 20); // f = -3.00000000
	_asm
	{
		cvttss2si eax, f
		mov ebx, 100
		imul ebx
		movsx ebx, b
		not ebx
		sub ebx, 20
		cdq
		idiv ebx
		cvtsi2ss xmm0, eax
		movss f, xmm0
	}
	*/
	
	/* f = b * (i & 0x0f | 0x1f00) - f; // f = 317597.313
	_asm
	{
		mov eax, i
		and eax, 0x0f
		or eax, 0x1f00
		movsx ebx, b
		imul ebx
		movss xmm0, f
		cvtsi2ss xmm1, eax
		subss xmm1, xmm0
		movss f, xmm1
	}
	*/
	
	/* f = (-i + f281 - -b * f + f35) / 2; // f = 47.1549988
	_asm
	{	
		mov eax, i
		neg eax
		movsx ebx, b
		neg ebx
		cvtsi2ss xmm0, ebx
		mulss xmm0, f
		cvtsi2ss xmm1, eax
		addss xmm1, f281
		subss xmm1, xmm0
		addss xmm1, f35
		mov eax, 2
		cvtsi2ss xmm0, eax
		divss xmm1, xmm0
		movss f, xmm1

	}
	*/
	
	/* f = b / 2 + i / f + (b - 3); // f = 64.4074097
	_asm
	{
		movsx ecx, b
		sub ecx, 3
		movsx eax, b
		cdq
		mov ebx, 2
		idiv ebx
		cvtsi2ss xmm0, i
		divss xmm0, f
		cvtsi2ss xmm1, eax
		addss xmm0, xmm1
		cvtsi2ss xmm1, ecx
		addss xmm0, xmm1
		movss f, xmm0
	}
	*/
	
	/* j = f + (0xf2 | i) / (b - 32) / -f; // j = -8 */
	/*
	_asm
	{
		
		mov eax, i 
		or eax, 0xf2
		movsx ebx, b
		sub ebx, 32
		*/
		/* Comme l'instruction neg n'existe pas pour les flottants, on doit multiplier par -1 notre registre. Sauf qu'on ne peux utiliser une
		* constante dans n'importe desquelles opérandes, on doit soit utiliser une varibale contenant -1 (EX : const float fconst = -1;)
		* ou alors faire comme ici, c'est a dire, deplacer -1 dans un registre général 32 bits, convertir celui-ci en un flottant et utiliser un
		* registre adéquat. Bien que cela fasse la même chose dans les deux cas, n'une des deux solutions utilise plus d'instructions 
		*/
		/*
		movss xmm0, f
		mov ecx , -1
		cvtsi2ss xmm1, ecx
		// Fin de la convertion
		mulss xmm0, xmm1
		cdq
		idiv ebx
		cvtsi2ss xmm1, eax
		divss xmm1, xmm0
		addss xmm1, f
		cvttss2si eax , xmm1
		mov j, eax
	}
	*/
}
