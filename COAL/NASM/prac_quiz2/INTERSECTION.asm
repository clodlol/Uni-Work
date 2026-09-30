[org 0x0100]
jmp start

setA: dw 1, 2, 3, 4, 5
setB: dw 2, 3, 6
sizeA: dw 5
sizeB: dw 3
res: dw 0, 0, 0
resLen: dw 3

linearSearch:
    push bp
    mov bp, sp
    ; [bp+4] is arr
    ; [bp+6] is size
    ; [bp+8] is target
    push bx
    push dx
    push si

    mov ax, -1
    mov si, 0
    mov bx, [bp+4]
    mov dx, [bp+6]
    shl dx, 1
    sub dx, 2

linearSearchLoop:
    cmp si, dx
    jg linearSearchEnd
    mov ax, [bx+si]
    cmp ax, [bp+8]
    mov ax, -1
    jne linearSearchIter
    shr si, 1
    mov ax, si
    jmp linearSearchEnd
linearSearchIter:
    add si, 2
    jmp linearSearchLoop
linearSearchEnd:
    pop si
    pop dx
    pop bx
    mov sp, bp
    pop bp
    ret 6

intersection:
    push bp
    mov bp, sp
    sub sp, 2
    ; [bp-2] is resCounter
    mov word[bp-2], 0
    ; [bp+4] is resLen
    ; [bp+6] is res
    ; [bp+8] is sizeB
    ; [bp+10] is sizeA
    ; [bp+12] is setB
    ; [bp+14] is setA

    push ax
    push bx
    push dx
    push si

    mov bx, [bp+14]
    mov dx, [bp+10]
    shl dx, 1
    sub dx, 2
    mov si, 0

intersectionLoop:
    cmp si, dx
    jg intersectionEnd
    
    ; passing parameters for linearSearch call
    mov ax, [bx+si]
    push ax
    mov ax, [bp+8]
    push ax
    mov ax, [bp+12]
    push ax
    
    call linearSearch
    ; linearSearch returns a value in ax

    cmp ax, -1
    je intersectionIter
    mov ax, [bp-2]
    cmp ax, [bp+4]
    jge intersectionIter

    ; passing parameters for linearSearch call again
    mov ax, [bx+si]
    push ax
    mov ax, [bp-2]
    push ax
    mov ax, [bp+6]
    push ax
    
    call linearSearch
    ; linearSearch returns a value in ax

    cmp ax, -1
    jne intersectionIter

    mov ax, [bx+si]
    push bx
    mov bx, [bp+6]
    push si
    mov si, [bp-2]
    shl si, 1
    mov word[bx+si], ax
    add word[bp-2], 1
    pop si
    pop bx

intersectionIter:
    add si, 2
    jmp intersectionLoop

intersectionEnd:
    pop si
    pop dx
    pop bx
    pop ax
    mov sp, bp
    pop bp
    ret 12

start:
    mov ax, setA
    push ax
    mov ax, setB
    push ax
    mov ax, [sizeA]
    push ax
    mov ax, [sizeB]
    push ax
    mov ax, res
    push ax
    mov ax, [resLen]
    push ax
    call intersection

end:
    mov ax, 4c00h
    int 21h