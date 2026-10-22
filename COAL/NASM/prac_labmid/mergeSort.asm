mergeSortedHalves:
    push bp
    mov bp, sp
    ; [bp+4] has arr, +6 has leftStart, +8 has leftEnd, +10 has rightStart, +12 has rightEnd
    push ax
    push cx
    push di
    push si
    push bx
    mov cx, [bp+12]
    sub cx, [bp+6]
    add cx, 2 ; cx = rightEnd - leftStart + 2 bytes
    sub sp, 2 ; [bp-12] will hold number of bytes offset from itself to access first element of temp array
    sub sp, cx

    mov si, [bp+6] ; use this as iterator on left array
    mov di, [bp+10] ; iterator on right array
    mov bx, [bp+4]
    mov word[bp-12], 2

mergeSortedHalves_loopCondition:
    cmp si, [bp+8]
    jle mergeSortedHalves_loopBody ; short circuit to loop body
    cmp di, [bp+12]
    jg mergeSortedHalves_loopEnd
mergeSortedHalves_loopBody:
    cmp si, [bp+8]
    jg mergeSortedHalves_putRight ; left elements all merged
    cmp di, [bp+12]
    jg mergeSortedHalves_putLeft ; right elements all merged
    mov ax, [bx+si] ; ax = arr[left]
    cmp ax, [bx+di]
    jg mergeSortedHalves_putRight ; if arr[left] > arr[right], merge right element (ascending order sorting)
mergeSortedHalves_putLeft:
    push di
    mov di, [bp-12]
    neg di ; we have to do [bp-di-12] to access temp array's active element
    mov ax, [bx+si]
    mov word[bp+di-12], ax
    add si, 2
    add word[bp-12], 2
    pop di
    jmp mergeSortedHalves_loopCondition
mergeSortedHalves_putRight:
    push si
    mov si, [bp-12]
    neg si
    mov ax, [bx+di]
    mov word[bp+si-12], ax
    add di, 2
    add word[bp-12], 2
    pop si
    jmp mergeSortedHalves_loopCondition
mergeSortedHalves_loopEnd:
    mov si, [bp+6]
    mov di, -2
mergeSortedHalves_copyLoop:
    cmp si, [bp+12]
    jg mergeSortedHalves_exit

    mov ax, [bp+di-12]
    mov [bx+si], ax
    sub di, 2
    add si, 2
    jmp mergeSortedHalves_copyLoop
mergeSortedHalves_exit:
    add sp, cx
    add sp, 2
    pop bx
    pop si
    pop di
    pop cx
    pop ax
    mov sp, bp
    pop bp
    ret 10
