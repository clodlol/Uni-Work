[org 0x0100]

mov al, 10110101b
rol al, 4

mov ax, 4c00h
int 21h