[org 0x0100]

jmp start

N: dw 5
fact: dw 1

start: mov cx, [N] ; Move 5 to cx
mov ax, 1 ; Declare fact = 1

loop1: mov bx, cx ; We will use bx as multiplier and dx as multiplicand
mov dx, ax ; Multiplicand is just whatever fact is

mov di, 0 ; We use this as multiplication result
mov si, 4 ; Counter to track 4 bit multiplication

mult: shr bx, 1 ; Shift multiplier right
jc addToRes
jmp noAdd

addToRes: add di, dx ; Add dx to di
noAdd: shl dx, 1 ; Shift multiplicand left
dec si
jnz mult

mov ax, di

dec cx
cmp cx, 1
jge loop1
jmp end

end: mov word[fact], ax
mov ax, 4c00h
int 21h