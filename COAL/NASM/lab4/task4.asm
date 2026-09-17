[org 0x0100]

mov ax, 12
shl ax, 1
shr ax, 1
mov bx, ax

mov ax, 4c00h
int 21h