[org 0x0100]

jmp start

N: dw 8
arr1: dw 1, 2, 3, 4, 5
arr2: dw 2, 3, 6, 7, 8
res: dw 0, 0, 0, 0, 0
dupe: db 0

start: mov bp, 0 ; We use bp as j
mov bx, 0 ; We use bx as i
mov si, 0 ; We use this as intCounter

checkArr1: 
mov bp, 0

checkArr2: mov dx, [arr1+bx]
cmp dx, [arr2+bp]
jne loop2End

mov di, 0 ; We use this as k
mov byte[dupe], 0

checkDuplicates: cmp [res+di], dx
je dupeFound
jmp checkNext
dupeFound: mov byte[dupe], 1
jmp loop2Body
checkNext: add di, 2
cmp di, si
jl checkDuplicates

loop2Body: cmp byte[dupe], 0
jne loop2End
mov word[res+si], dx
add si, 2

loop2End: add bp, 2
cmp bp, [N]
jle checkArr2

add bx, 2
cmp bx, [N]
jle checkArr1

mov ax, 4c00h
int 21h