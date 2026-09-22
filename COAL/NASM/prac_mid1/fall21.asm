[org 0x0100]

jmp start

result: db 0
arr: db 3, 4, 5, 3, 8, -1

start:
    mov ax, 0
    mov dx, 0
    mov bx, 0
    mov cl, 0
    mov di, 0

outerLoop: 
    mov bl, [arr+di]
    cmp bl, -1
    je exit
    mov bl, [arr+di+1]
    cmp bl, -1
    je exit

body:
    mov bx, [arr+di+1]
    test bx, 1
    jz evenBlock

oddBlock:
    mov bx, [arr+di]
    mov ax, [arr+di+1]
    add bx, ax
    mov [arr+di], bl
    jmp iter

evenBlock:
    mov cl, 0
    mov ax, 0
    mov bx, [arr+di+1] ; multiplicand
    mov dx, [arr+di] ; multiplier

multLoop:
    cmp cl, 8
    je iter
    shr dx, 1
    jnc nextBit
    add ax, bx
    mov [arr+di], al

nextBit:
    shl bx, 1
    inc cl
    jmp multLoop

iter:
    add di, 2
    jmp outerLoop

exit:
    mov ax, 4c00h
    int 21h