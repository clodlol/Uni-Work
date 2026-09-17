[org 0x0100]

mov al, 10110101b

and al, 01111111b ; clears the highest bit
xor al, 00000100b ; toggles the third bit
and al, 00000001b ; saves numeric 1 to al if last bit is set

mov ax, 4c00h
int 21h