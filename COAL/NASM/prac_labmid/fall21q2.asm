[org 0x0100]
jmp start

array: db 1, 2, 1, 3, 4, 7, 9, 3, 2, 5
size: dw 10

start:
    mov si, 0
    mov bx, array
    mov cx, [size]
outer_loop:
    cmp si, cx
    jge end
    mov di, si
    add di, 1 ; initialize di to si+1
    mov al, [bx+si]
inner_loop:
    cmp di, cx
    jge outer_iter ; break inner loop
    cmp [bx+di], al
    push di
    je swap
inner_iter:
    pop di
    inc di
    jmp inner_loop
swap:
    mov dl, [bx+di+1]
    mov byte[bx+di], dl
    
    inc di
    push cx
    dec cx
    cmp di, cx
    pop cx

    jl swap
    mov byte[bx+di+1], -1
    dec cx
    jmp inner_iter
outer_iter:
    inc si
    jmp outer_loop
end:
    mov ax, 4c00h
    int 21h