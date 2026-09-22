[org 0x0100]

arr: db 0x03, 0x07, 0x0F, 0x01, 0x00
N: dw 5

start:
    mov di, 0
    mov si, 0

outer:
    cmp di, [N]
    jge exit
storeCurrent:
    mov si, di
    mov al, [arr+di]
    mov bl, [arr+di]
    mov cx, 0
    mov dx, 0
countBits:
    cmp cx, 8 ; 1 byte = 8bits
    jge checkBits
    shr al, 1
    adc dx, 0
    inc cx
    jmp countBits
checkBits:
    test dx, 1
    jz outerIter
inner:
    cmp si, [N]-1
    jge outerIter
    cmp si, [N]-2
    jne erm
    mov byte[arr+si+1], 0
erm:
    mov al, [arr+si+1]
    mov [arr+si], al
    inc si
    jmp inner
outerIter:
    cmp bl, [arr+di]
    jne outer
    inc di
    jmp outer

exit:
    mov ax, 4c00h
    int 21h
    