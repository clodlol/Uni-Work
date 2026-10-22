[org 0x0100]
jmp start

arr: dw 7, -6, -5, 2, -4, 3, 0
size: dw 7
res: dw 0

start:
    mov ax, 0
    push ax ; pushing ret value
    push word[size]
    mov ax, arr
    push ax
    call equ_index
    pop ax
    mov [res], ax
    mov ax, 4c00h
    int 21h

calc_sum:
    push bp
    mov bp, sp
    push cx
    push si
    push bx
    push ax
    ; [bp+4] has arr address
    ; [bp+6] has arr size
    ; [bp+8] has ret val
    mov cx, [bp+6]
    shl cx
    sub cx, 2 ; cx holds the max offset from base arr address
    mov si, 0
    mov bx, [bp+4]
    mov ax, 0
add_next_calc_sum:
    cmp si, cx
    jg exit_calc_sum
    add ax, [bx+si]
    add si, 2
    jmp add_next_calc_sum
exit_calc_sum:
    mov [bp+8], ax
    pop ax
    pop bx
    pop si
    pop cx
    mov sp, bp
    pop bp
    ret 4

equ_index:
    push bp
    mov bp, sp
    sub sp, 2
    push cx
    push si
    push bx
    push ax
    ; [bp-2] has ret value from calc_sum
    ; [bp+4] has arr addres
    ; [bp+6] has arr size
    ; [bp+8] has ret value
    mov cx, [bp+6]
    shl cx, 1
    sub cx, 2
    mov si, 0
    mov bx, [bp+4]
    mov word[bp+8], -1

    mov ax, 0
    push ax ; pushing ret value from calc_sum
    push word[bp+6]
    push word[bp+4]
    call calc_sum
    pop word[bp-2]
    mov ax, 0

sub_acc_equ_index:
    cmp si, cx
    jg exit_equ_index

    push ax ; temporarily pushing ax to fetch value from local variable
    mov ax, [bp-2]
    sub ax, [bx+si]
    mov [bp-2], ax
    pop ax

    cmp ax, [bp-2]
    je found_equ_index

    add ax, [bx+si]
    add si, 2
    jmp sub_acc_equ_index
found_equ_index:
    mov [bp+8], si
    shr word[bp+8], 1
    jmp exit_equ_index
exit_equ_index:
    pop ax
    pop bx
    pop si
    pop cx
    mov sp, bp
    pop bp
    ret 4

