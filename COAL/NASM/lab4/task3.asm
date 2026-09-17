[org 0x0100]

jmp start

N: dw 10
M: dw 6
arr1: dw 1, 2, 3, 4, 5
arr2: dw 3, 7, 8
res: dw 0, 0, 0, 0, 0
dupe: db 0
found: db 0

start: mov bp, 0 ; We use bp as j
mov bx, 0 ; We use bx as i
mov si, 0 ; We use this as intCounter

checkArr1:
mov bp, 0
mov byte[found], 0

checkArr2: mov dx, [arr1+bx]
cmp dx, [arr2+bp]
jne loop2End

mov byte[found], 1
jmp loop1Body

loop2End: add bp, 2
cmp bp, [M]
jl checkArr2

loop1Body: cmp byte[found], 0
jne loop1End

mov byte[dupe], 0
mov di, 0

checkDuplicates: cmp [res+di], dx
je dupeFound 
jmp checkNext
dupeFound: mov byte[dupe], 1
jmp loop1End
checkNext: add di, 2
cmp di, si
jl checkDuplicates

cmp byte[dupe], 0
je addToRes
jmp loop1End

addToRes: mov [res+si], dx
add si, 2

loop1End: add bx, 2
cmp bx, [N]
jl checkArr1

mov ax, 4c00h
int 21h