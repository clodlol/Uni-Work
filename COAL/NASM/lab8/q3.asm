[org 0x0100]
jmp start

str1: db 'STRING LAB', 0
buf: db 'S', 0Bh, 'T', 0Bh, 'R', 0Bh, 'I', 0Bh, 'N', 0Bh, 'G', 0Bh, ' ', 0Bh, 'L', 0Bh, 'A', 0Bh, 'B', 0Bh, 0

start:
    mov ax, 0b800h
    mov es, ax

    mov si, buf
    
    mov al, 4 ; row
    mov bl, 80
    mul bl
    add ax, 25 ; col
    shl ax, 1

    mov di, ax

    push 0
    mov ax, buf
    push ax
    call countLen
    pop cx

    cld
    rep movsb

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