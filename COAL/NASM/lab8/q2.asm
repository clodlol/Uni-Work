[org 0x0100]
jmp start

str1: db 'FASTNUNUCES', 0
substr: db 'NU', 0

start:
    push 0
    mov ax, substr
    push ax
    call countLen
    pop cx
    ; cx has substr len

    push 0
    mov ax, str1
    push ax
    call countLen
    pop dx
    ; dx has str len

    mov si, 0

loop1:
    push 0
    mov ax, substr
    push substr
    mov ax, str1
    add ax, si
    push ax
    call findSubstr
    pop ax
    cmp ax, 1
    je exitFound

    inc si
    dec dx
    jnz loop1

    mov ax, 0
    jmp exit

exitFound:
    mov ax, 1
    exit:
    mov ax, 4c00h
    int 21h

countLen:
    push bp
    mov bp, sp
    push cx
    push es
    push ax
    push di

    xor cx, cx
    xor al, al
    push ds
    pop es
    mov di, [bp+4] ; src string
    cld
clLoop:
    add cx, 1
    scasb
    jne clLoop

    dec cx
    mov [bp+6], cx

    pop di
    pop ax
    pop es
    pop cx
    pop bp
    ret 2

findSubstr:
    push bp
    mov bp, sp
    push cx
    push es
    push di
    push si
    push ax

    push 0
    mov ax, [bp+6] ; substr
    push ax
    call countLen
    pop cx

    push ds
    pop es

    mov di, [bp+4]
    mov si, [bp+6]

    cld
fsLoop:
    cmpsb
    jne fsExitFalse
    dec cx
    jnz fsLoop

    jmp fsExitTrue

fsExitFalse:
    mov [bp+8], 0
    jmp fsExit
fsExitTrue:
    mov [bp+8], 1
fsExit:
    pop ax
    pop si
    pop di
    pop es
    pop cx
    pop bp
    ret 4