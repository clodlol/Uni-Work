[org 0x0100]
mov al, 11010010b  
mov bl, 0   
mov cx, 8            

loop1: shr al, 1       
rcl bl, 1        
dec cx
jnz loop1
    
mov ax, 4c00h
int 21h