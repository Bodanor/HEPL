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

TesterPythagore PROC
	cotea EQU <DWORD PTR[ESP + 4]>
	coteb EQU <DWORD PTR[ESP + 8]>
	cotec EQU <DWORD PTR[ESP + 12]>
	
	mov eax, cotea
	cmp eax, coteb

	jna tryb
	
	cmp eax, cotec
	jna tryc
	
	imul eax, eax
	mov ebx, coteb
	imul ebx, ebx
	mov ecx, cotec
	imul ecx, ecx
	add ebx, ecx
	cmp eax, ebx
	je rectTrue
	jmp rectFalse


tryb:
	mov eax, coteb
	cmp eax, cotec
	jna tryc
	
	imul eax, eax
	mov ebx, cotea
	imul ebx, ebx
	mov ecx, cotec
	imul ecx, ecx
	add ebx, ecx
	cmp eax, ebx
	je rectTrue
	jmp rectFalse

tryc:
	mov eax, cotec

	imul eax, eax
	mov ebx, coteb
	imul ebx, ebx
	mov ecx, cotea
	imul ecx, ecx
	add ebx, ecx
	cmp eax, ebx
	je rectTrue
	jmp rectFalse

rectTrue:
	mov eax, 1
	ret
	
rectFalse:
	mov eax, 0
	ret




TesterPythagore ENDP

Calculer PROC
val1 EQU <QWORD PTR[ESP + 12]>
val2 EQU <QWORD PTR[ESP + 20]>
operation EQU <DWORD PTR[ESP + 28]>
tmp EQU <QWORD PTR[ESP + 0]>

sub esp, 8

movsd xmm0, val1
movsd xmm1, val2


cmp operation, 1
je addition

cmp operation, 2
je soustraction

cmp operation, 3
je multiplication

	divsd xmm0, xmm1
	movsd tmp, xmm0
	jmp return_statement

addition:
	addsd xmm0, xmm1
	movsd tmp, xmm0
	jmp return_statement

soustraction:
	subsd xmm0, xmm1
	movsd tmp, xmm0
	jmp return_statement


multiplication:
	mulsd xmm0, xmm1
	movsd tmp, xmm0

return_statement:
	fld tmp
	add esp, 8
	ret

Calculer ENDP


END
