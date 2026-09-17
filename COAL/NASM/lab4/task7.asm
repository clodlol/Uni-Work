[org 0x0100]

mov al, 10110101b
mov cx, 8
mov bx, 0

loop1: shr al, 1
adc bx, 0
dec cx
jnz loop1

mov ax, 4c00h
int 21h