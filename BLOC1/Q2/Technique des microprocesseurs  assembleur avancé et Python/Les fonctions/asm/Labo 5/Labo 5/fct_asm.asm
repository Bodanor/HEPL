.MODEL FLAT, C

.DATA

	PI DQ 3.14

.CODE

ConvertToFahr PROC

	celsius EQU <DWORD PTR [ESP + 4]>
	
	mov eax, celsius
	imul eax, 9

	mov ebx, 5
	cdq
	div ebx
	add eax, 32

	ret


ConvertToFahr ENDP

LoiOhm PROC
	resistance EQU <DWORD PTR[ESP + 8]>
	intensite EQU <DWORD PTR[ESP + 4]>

	mov eax, resistance
	imul eax, intensite

	ret

LoiOhm ENDP

PerimetreCercle PROC
	rayon  EQU <QWORD PTR[ESP + 12]>
	varloc EQU <QWORD PTR[ESP + 0]>

	sub esp, 8

	movsd xmm0, rayon
	mov eax, 2
	cvtsi2sd xmm1, eax
	mulsd xmm0, xmm1
	mulsd xmm0, PI
	movsd varloc, xmm0

	fld varloc

	add esp, 8
	ret

PerimetreCercle ENDP

END
