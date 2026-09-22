[org 0x0100]

jmp start

N: dw 5
arr: db 0x1F, 0x05, 0x88, 0xE3, 0x97
count: dw 0

start:
    mov di, 0
loop1:
    cmp di, [N]
    jge exit
body:
    mov al, [arr+di]
    mov cx, 8
    mov dx, 0
counting:
    shr al, 1
    jc setBit
    mov dx, 0
    dec cx
    jnz counting
    jmp iter
setBit:
    inc dx
    cmp dx, 3
    jge incCount
    dec cx
    jnz counting
    jmp iter
incCount:
    inc byte[count]
iter:
    inc di
    jmp loop1

exit:
    mov ax, 4c00h
    int 21h