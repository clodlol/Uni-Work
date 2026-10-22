[org 0x0100]
jmp start

array: dw 7, 4, 8, 2, 7, 7, 9, 5, 6, 1
rightBound: dw array+18
largest: dw 0
smallest: dw 0

start:
    mov ax, [array+0]
    mov [smallest], ax
    mov [largest], ax
    mov si, array
loop1:
    cmp si, [rightBound]
    ja end
    mov ax, [si]
    cmp ax, [largest]
    jge updateLargest
    cmp ax, [smallest]
    jle updateSmallest
iter:
    add si, 2
    jmp loop1
updateLargest:
    mov word[largest], ax
    jmp loop1
updateSmallest:
    mov word[smallest], ax
    jmp loop1
end:
    mov ax, 4c00h
    int 21h
    