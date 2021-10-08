char b = 40;
int i = 20;
int j = -125;
float f = 2.7;
const float f281 = 2.81, f32 = 3.5;

int main()
{
	/* b = f;	// b = 2
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

	/* i = j + ~(int)f; // i = -128 */
	_asm
	{

	}
}
