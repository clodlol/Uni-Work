reverseStr:
    push bp
    mov bp, sp
    push cx
    push ax
    push di
    push si

    push 0
    push word[bp+4] ; push src string address
    call countLen
    pop cx
    mov di, [bp+6] ; dest string
    mov si, [bp+4] ; src string
    add si, cx
    dec si
    ; si = src string start + string len - 1
    std

rsLoop:
    lodsb ; reads from [si], decrements si
    mov [di], al
    inc di
    dec cx
    jnz rsLoop

    mov byte[di], 0 ; null terminator at destination string

    cld
    pop si
    pop di
    pop ax
    pop cx
    pop bp
    ret 4

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

    push 0
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