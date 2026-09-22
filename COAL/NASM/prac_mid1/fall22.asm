[org 0x0100]

jmp start

Set1: db 1, 3, 5, 7, 9
Set2: db 2, 3, 6, 7, 10
Difference: db 0, 0, 0, 0, 0
M: dw 5
N: dw 5

start:
    mov di, 0 ; Set1 pointer
    mov si, 0 ; Set2 pointer
    mov bx, 0 ; Difference pointer
    mov ax, 0 ; General variable
    mov dl, 0 ; Found flag

outer:
    cmp di, [M]
    jge exit
outerBody:
    mov si, 0
    mov dl, 0
    mov al, [Set1+di]
inner:
    cmp si, [N]
    jge outerBodyNext
    cmp al, [Set2+si]
    jne innerIter
    mov dl, 1
    jmp outerBodyNext
innerIter:
    add si, 1
    jmp inner
outerBodyNext:
    cmp dl, 1
    je outerIter
    mov byte[Difference+bx], al
    add bx, 1
outerIter:
    add di, 1
    jmp outer

exit:
    mov ax, 4c00h
    int 21h