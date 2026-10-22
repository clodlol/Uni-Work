[org 0x0100]
jmp start

str1: db 'Welcome to COAL Lab', 0

start:
    mov dx, 0
    mov ax, 0b800h
    mov es, ax

    cld

loop1:
    mov di, 10*160 + 0 * 2 ; mov di to start of 10th row
    mov cx, dx
    mov ax, 0720h
    rep stosw

    mov ax, str1
    push ax
    mov ax, dx
    push ax
    mov ax, 10
    push ax
    call printStr

    ; --- Delay Loop ---
    push cx
    mov cx, 0FFFFh
d1:
    dec cx
    jnz d1
    pop cx
    ; ------------------

    inc dx
    cmp dx, 60
    jl loop1

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

printStr:
    push bp
    mov bp, sp
    push si
    push di
    push cx
    push es
    push ax
    push bx

    mov ax, 0b800h
    mov es, ax
    mov al, [bp+4] ; y pos
    mov bl, 80
    mul bl
    add ax, [bp+6] ; x pos
    shl ax, 1

    mov di, ax
    ; es:di points to required location

    mov ax, 0
    push ax
    push word[bp+8]
    call countLen
    pop cx

    cld
    mov si, [bp+8] ; src string
    mov ah, 01h ; attr byte

psLoop:
    mov al, [si]
    mov [es:di], ax
    inc si
    add di, 2
    dec cx
    jnz psLoop

    pop bx
    pop ax
    pop es
    pop cx
    pop di
    pop si
    pop bp
    ret 6