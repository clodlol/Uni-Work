[org 0x0100]
jmp main


SCREEN_COLS         equ 80
SCREEN_ROWS         equ 25
SCREEN_CELL_COUNT   equ SCREEN_COLS * SCREEN_ROWS

VIDEO_SEGMENT       equ 0B800h

ROW_HUD             equ 0
ROW_SEPARATOR       equ 1
ROW_PLAY_START      equ 2
ROW_PLAY_END        equ 23
ROW_GROUND          equ 24

COL_TIME_LABEL      equ 2
COL_TIME_DIGITS     equ 8
COL_SCORE_LABEL     equ 67
COL_SCORE_DIGITS    equ 74

SPRITE_WIDTH        equ 3
SPRITE_HEIGHT       equ 3

TITLE_ROW           equ 2
TITLE_COL           equ 5
TITLE_ROWS_COUNT    equ 5

BOX_START_ROW       equ 7
BOX_START_COL       equ 20
BOX_WIDTH           equ 40
BOX_HEIGHT          equ 11

GAME_SECONDS        equ 120
PLAYER_START_ROW    equ 21
PLAYER_START_COL    equ 38
PLAYER_MIN_COL      equ 1
PLAYER_MAX_COL      equ 76

KEY_ENTER           equ 13
KEY_ESC             equ 27
KEY_1               equ '1'
KEY_2               equ '2'
KEY_3               equ '3'
KEY_E_UPPER         equ 'E'
KEY_E_LOWER         equ 'e'
SCAN_LEFT_ARROW     equ 4Bh
SCAN_RIGHT_ARROW    equ 4Dh

CH_SPACE            equ 32
CH_STAR             equ 42
CH_SHADE_LIGHT      equ 176
CH_BOX_VERT         equ 186
CH_BOX_TOP_RIGHT    equ 187
CH_BOX_BOT_RIGHT    equ 188
CH_BOX_BOT_LEFT     equ 200
CH_BOX_TOP_LEFT     equ 201
CH_BOX_HORIZ        equ 205
CH_FULL             equ 219
CH_HALF_BOTTOM      equ 220
CH_HALF_LEFT        equ 221
CH_HALF_RIGHT       equ 222
CH_HALF_TOP         equ 223
CH_BULLET           equ 250

ATTR_BLACK          equ 00h
ATTR_GREEN_DARK     equ 02h
ATTR_CYAN           equ 03h
ATTR_BROWN          equ 06h
ATTR_GRAY_LIGHT     equ 07h
ATTR_GRAY_DARK      equ 08h
ATTR_GREEN_LIGHT    equ 0Ah
ATTR_CYAN_LIGHT     equ 0Bh
ATTR_RED_LIGHT      equ 0Ch
ATTR_YELLOW         equ 0Eh
ATTR_WHITE_BRIGHT   equ 0Fh
ATTR_BLINK_WHITE    equ 8Fh

ATTR_HUD            equ ATTR_WHITE_BRIGHT
ATTR_SEPARATOR      equ ATTR_GRAY_DARK
ATTR_GROUND         equ ATTR_BROWN
ATTR_PLAY           equ ATTR_BLACK


init_video:
    push ax
    push cx

    mov ax, 0003h
    int 10h

    mov ah, 01h
    mov ch, 20h
    mov cl, 00h
    int 10h

    mov ax, VIDEO_SEGMENT
    mov es, ax

    pop cx
    pop ax
    ret

get_cell_offset:
    push ax
    push dx

    mov al, SCREEN_COLS
    mul dh
    xor dh, dh
    add ax, dx
    shl ax, 1
    mov di, ax

    pop dx
    pop ax
    ret

put_cell:
    push di
    call get_cell_offset
    mov [es:di], ax
    pop di
    ret

fill_cells:
    push cx
    push di

    call get_cell_offset
    cld
    rep stosw

    pop di
    pop cx
    ret

fill_rect:
    push bx
    push cx
    push dx

    mov bl, ch
.row_loop:
    push cx
    push dx
    mov ch, 0
    call fill_cells
    pop dx
    pop cx
    inc dh
    dec bl
    jnz .row_loop

    pop dx
    pop cx
    pop bx
    ret

clear_screen:
    push ax
    push cx
    push dx

    xor dx, dx
    mov cx, SCREEN_CELL_COUNT
    mov ax, (ATTR_GRAY_LIGHT << 8) | CH_SPACE
    call fill_cells

    pop dx
    pop cx
    pop ax
    ret

draw_box:
    push ax
    push bx
    push cx
    push dx
    push di

    mov [box_temp_r], dh
    mov [box_temp_c], dl
    mov [box_temp_h], ch
    mov [box_temp_w], cl
    mov [box_temp_a], bl

    mov dh, [box_temp_r]
    mov dl, [box_temp_c]
    mov al, CH_BOX_TOP_LEFT
    mov ah, [box_temp_a]
    call put_cell

    mov dh, [box_temp_r]
    mov dl, [box_temp_c]
    inc dl
    mov cl, [box_temp_w]
    dec cl
    dec cl
    mov ch, 0
    mov al, CH_BOX_HORIZ
    mov ah, [box_temp_a]
    call fill_cells

    mov dh, [box_temp_r]
    mov dl, [box_temp_c]
    add dl, [box_temp_w]
    dec dl
    mov al, CH_BOX_TOP_RIGHT
    mov ah, [box_temp_a]
    call put_cell

    mov dh, [box_temp_r]
    inc dh
    mov cl, [box_temp_h]
    dec cl
    dec cl
.side_loop:
    push cx
    mov dl, [box_temp_c]
    mov al, CH_BOX_VERT
    mov ah, [box_temp_a]
    call put_cell
    mov dl, [box_temp_c]
    add dl, [box_temp_w]
    dec dl
    mov al, CH_BOX_VERT
    mov ah, [box_temp_a]
    call put_cell

    inc dh
    pop cx
    dec cl
    jnz .side_loop

    mov dh, [box_temp_r]
    add dh, [box_temp_h]
    dec dh
    mov dl, [box_temp_c]
    mov al, CH_BOX_BOT_LEFT
    mov ah, [box_temp_a]
    call put_cell

    mov dh, [box_temp_r]
    add dh, [box_temp_h]
    dec dh
    mov dl, [box_temp_c]
    inc dl
    mov cl, [box_temp_w]
    dec cl
    dec cl
    mov ch, 0
    mov al, CH_BOX_HORIZ
    mov ah, [box_temp_a]
    call fill_cells

    mov dh, [box_temp_r]
    add dh, [box_temp_h]
    dec dh
    mov dl, [box_temp_c]
    add dl, [box_temp_w]
    dec dl
    mov al, CH_BOX_BOT_RIGHT
    mov ah, [box_temp_a]
    call put_cell

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

get_string_length:
    push ax
    push si

    xor cx, cx
    cld
.count_loop:
    lodsb
    test al, al
    jz .done
    inc cx
    jmp .count_loop

.done:
    pop si
    pop ax
    ret

draw_text:
    push ax
    push di
    push si

    call get_cell_offset
    mov ah, bl
    cld
.char_loop:
    lodsb
    test al, al
    jz .done
    mov [es:di], ax
    add di, 2
    jmp .char_loop

.done:
    pop si
    pop di
    pop ax
    ret

draw_text_centered:
    push cx
    push dx

    call get_string_length
    mov dl, SCREEN_COLS
    sub dl, cl
    shr dl, 1
    call draw_text

    pop dx
    pop cx
    ret

draw_number:
    push ax
    push bx
    push cx
    push dx
    push di
    push bp

    mov bp, bx
    push dx
    add dl, cl
    dec dl
    call get_cell_offset
    pop dx

.digit_loop:
    xor dx, dx
    mov bx, 10
    div bx

    push ax

    mov bx, bp
    mov ah, bl
    mov al, dl
    add al, '0'
    mov [es:di], ax
    sub di, 2

    pop ax
    loop .digit_loop

    pop bp
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

draw_sprite:
    push ax
    push bx
    push cx
    push dx
    push di
    push si

    mov cl, SPRITE_HEIGHT
.row_loop:
    push cx
    push dx
    call get_cell_offset
    mov ch, SPRITE_WIDTH
.col_loop:
    cld
    lodsw
    cmp al, CH_SPACE
    je .skip_cell
    mov [es:di], ax
.skip_cell:
    add di, 2
    dec ch
    jnz .col_loop

    pop dx
    pop cx
    inc dh
    dec cl
    jnz .row_loop

    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

erase_sprite:
    push ax
    push cx

    mov ch, SPRITE_HEIGHT
    mov cl, SPRITE_WIDTH
    mov ax, (ATTR_PLAY << 8) | CH_SPACE
    call fill_rect

    pop cx
    pop ax
    ret

draw_pixel_row:
    push ax
    push di
    push si

    call get_cell_offset
    mov ah, bl
    cld
.pixel_loop:
    lodsb
    test al, al
    jz .done
    cmp al, '#'
    jne .skip_pixel
    mov al, CH_FULL
    mov [es:di], ax
.skip_pixel:
    add di, 2
    jmp .pixel_loop

.done:
    pop si
    pop di
    pop ax
    ret

draw_pixel_art:
    push ax
    push cx
    push dx
    push si

.art_row_loop:
    push dx
    push si
    mov si, [si]
    call draw_pixel_row
    pop si
    pop dx

    inc dh
    add si, 2
    loop .art_row_loop

    pop si
    pop dx
    pop cx
    pop ax
    ret


draw_object_table:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp

.entry_loop:
    push cx
    push si

    mov dh, [si + 2]
    mov dl, [si + 3]
    mov si, [si]
    call draw_sprite

    pop si
    push si
    mov bp, [si + 4]
    test bp, bp
    jz .skip_label

    push si
    mov si, bp
    call get_string_length
    pop si

    mov dl, [si + 3]
    inc dl
    shr cx, 1
    sub dl, cl

    mov dh, [si + 2]
    add dh, 3
    mov bl, ATTR_WHITE_BRIGHT
    mov si, bp
    call draw_text

.skip_label:
    pop si
    pop cx
    add si, 6
    dec cx
    jnz .entry_loop

    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

draw_timer:
    push ax
    push bx
    push cx
    push dx

    mov ax, [timer_seconds]
    xor dx, dx
    mov bx, 60
    div bx

    push dx
    mov cx, 2
    mov dh, ROW_HUD
    mov dl, COL_TIME_DIGITS
    mov bl, ATTR_HUD
    call draw_number

    mov dh, ROW_HUD
    mov dl, COL_TIME_DIGITS + 2
    mov ax, (ATTR_HUD << 8) | ':'
    call put_cell

    pop ax
    mov cx, 2
    mov dh, ROW_HUD
    mov dl, COL_TIME_DIGITS + 3
    mov bl, ATTR_HUD
    call draw_number

    pop dx
    pop cx
    pop bx
    pop ax
    ret

draw_score:
    push ax
    push bx
    push cx
    push dx

    mov ax, [score]
    mov cx, 4
    mov dh, ROW_HUD
    mov dl, COL_SCORE_DIGITS
    mov bl, ATTR_HUD
    call draw_number

    pop dx
    pop cx
    pop bx
    pop ax
    ret

draw_hud:
    push ax
    push bx
    push cx
    push dx
    push si

    mov dh, ROW_HUD
    mov dl, 0
    mov cx, SCREEN_COLS
    mov ax, (ATTR_HUD << 8) | CH_SPACE
    call fill_cells

    mov si, str_time_label
    mov dh, ROW_HUD
    mov dl, COL_TIME_LABEL
    mov bl, ATTR_HUD
    call draw_text

    call draw_timer

    mov si, str_score_label
    mov dh, ROW_HUD
    mov dl, COL_SCORE_LABEL
    mov bl, ATTR_HUD
    call draw_text

    call draw_score

    mov dh, ROW_SEPARATOR
    mov dl, 0
    mov cx, SCREEN_COLS
    mov ax, (ATTR_SEPARATOR << 8) | CH_BOX_HORIZ
    call fill_cells

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

draw_ground:
    push ax
    push cx
    push dx

    mov dh, ROW_GROUND
    mov dl, 0
    mov cx, SCREEN_COLS
    mov ax, (ATTR_GROUND << 8) | CH_SHADE_LIGHT
    call fill_cells

    pop dx
    pop cx
    pop ax
    ret

draw_player:
    push dx
    push si

    mov dh, PLAYER_START_ROW
    mov dl, [player_col]
    mov si, sprite_basket
    call draw_sprite

    pop si
    pop dx
    ret

erase_player:
    push dx

    mov dh, PLAYER_START_ROW
    mov dl, [player_col]
    call erase_sprite

    pop dx
    ret


read_seconds:
    push cx
    push dx

    mov ah, 2Ch
    int 21h
    mov al, dh

    pop dx
    pop cx
    ret

tick_timer:
    push ax

    call read_seconds
    cmp al, [last_seconds]
    je .no_change

    mov [last_seconds], al
    cmp word [timer_seconds], 0
    jle .no_change

    dec word [timer_seconds]
    call draw_timer

.no_change:
    pop ax
    ret

check_key:
    mov ah, 01h
    int 16h
    jz .no_key

    mov ah, 00h
    int 16h

    test sp, sp
    ret

.no_key:
    xor ax, ax
    cmp ax, ax
    ret

wait_for_key:
    mov ah, 00h
    int 16h
    ret

wait_for_specific_key:
    push ax

.wait_loop:
    call wait_for_key
    cmp al, KEY_ESC
    je .exit_game
    cmp al, bl
    je .matched
    jmp .wait_loop

.exit_game:
    call exit_to_dos

.matched:
    pop ax
    ret

handle_game_key:
    push bx

    cmp al, KEY_ESC
    je .exit_game

    cmp ah, SCAN_LEFT_ARROW
    je .move_left

    cmp ah, SCAN_RIGHT_ARROW
    je .move_right

    call handle_demo_keys
    jmp .done

.move_left:
    cmp byte [player_col], PLAYER_MIN_COL
    jle .done
    call erase_player
    dec byte [player_col]
    call draw_player
    jmp .done

.move_right:
    cmp byte [player_col], PLAYER_MAX_COL
    jge .done
    call erase_player
    inc byte [player_col]
    call draw_player
    jmp .done

.exit_game:
    call exit_to_dos

.done:
    pop bx
    ret

handle_demo_keys:
    push ax

    cmp al, KEY_1
    je .add_5
    cmp al, KEY_2
    je .add_10
    cmp al, KEY_3
    je .add_15
    cmp al, KEY_E_UPPER
    je .end_game
    cmp al, KEY_E_LOWER
    je .end_game
    jmp .done

.add_5:
    add word [score], 5
    call draw_score
    jmp .done

.add_10:
    add word [score], 10
    call draw_score
    jmp .done

.add_15:
    add word [score], 15
    call draw_score
    jmp .done

.end_game:
    mov byte [game_over_flag], 1
    jmp .done

.done:
    pop ax
    ret


show_start_screen:
    push ax
    push bx
    push cx
    push dx
    push si

    call clear_screen

    mov dh, 0
    mov dl, 0
    mov ch, SCREEN_ROWS
    mov cl, SCREEN_COLS
    mov bl, ATTR_CYAN
    call draw_box

    mov si, title_bitmap_table
    mov cx, TITLE_ROWS_COUNT
    mov dh, TITLE_ROW
    mov dl, TITLE_COL
    mov bl, ATTR_YELLOW
    call draw_pixel_art

    mov si, str_start_divider
    mov dh, 8
    mov bl, ATTR_BROWN
    call draw_text_centered

    mov si, legend_table
    mov cx, LEGEND_COUNT
    call draw_object_table

    mov si, str_how_to_play
    mov dh, 15
    mov bl, ATTR_BROWN
    call draw_text_centered

    mov si, str_help_1
    mov dh, 16
    mov bl, ATTR_GRAY_LIGHT
    call draw_text_centered

    mov si, str_help_2
    mov dh, 17
    mov bl, ATTR_GRAY_LIGHT
    call draw_text_centered

    mov si, str_help_3
    mov dh, 18
    mov bl, ATTR_GRAY_LIGHT
    call draw_text_centered

    mov si, str_start_prompt
    mov dh, 21
    mov bl, ATTR_BLINK_WHITE
    call draw_text_centered

    mov bl, KEY_ENTER
    call wait_for_specific_key

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

run_game_screen:
    push ax
    push bx
    push cx
    push dx
    push si

    call clear_screen

    call draw_hud
    call draw_ground
    call draw_player

    mov si, showcase_table
    mov cx, SHOWCASE_COUNT
    call draw_object_table

    call read_seconds
    mov [last_seconds], al

.game_loop:
    call tick_timer

    cmp word [timer_seconds], 0
    je .game_finished

    cmp byte [game_over_flag], 1
    je .game_finished

    call check_key
    jz .game_loop

    call handle_game_key

    cmp byte [game_over_flag], 1
    je .game_finished

    jmp .game_loop

.game_finished:
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

show_end_screen:
    push ax
    push bx
    push cx
    push dx
    push si

    call clear_screen

    mov dh, BOX_START_ROW
    mov dl, BOX_START_COL
    mov ch, BOX_HEIGHT
    mov cl, BOX_WIDTH
    mov bl, ATTR_YELLOW
    call draw_box

    mov si, str_game_over
    mov dh, 9
    mov bl, ATTR_RED_LIGHT
    call draw_text_centered

    mov si, str_end_divider
    mov dh, 11
    mov bl, ATTR_BROWN
    call draw_text_centered

    mov si, str_final_score
    mov dh, 13
    mov dl, 31
    mov bl, ATTR_WHITE_BRIGHT
    call draw_text

    mov ax, [score]
    mov cx, 4
    mov dh, 13
    mov dl, 45
    mov bl, ATTR_YELLOW
    call draw_number

    mov si, str_end_prompt
    mov dh, 15
    mov bl, ATTR_GRAY_LIGHT
    call draw_text_centered

    mov bl, KEY_ENTER
    call wait_for_specific_key

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

exit_to_dos:
    mov ax, 0003h
    int 10h

    mov ax, 4C00h
    int 21h


main:
    call init_video

.session_loop:
    mov word [score], 0
    mov word [timer_seconds], GAME_SECONDS
    mov byte [player_col], PLAYER_START_COL
    mov byte [game_over_flag], 0
    mov byte [last_seconds], 0FFh

    call show_start_screen

    call run_game_screen

    call show_end_screen

    jmp .session_loop


score:              dw 0
timer_seconds:      dw GAME_SECONDS
player_col:         db PLAYER_START_COL
game_over_flag:     db 0
last_seconds:       db 0FFh

box_temp_r:         db 0
box_temp_c:         db 0
box_temp_h:         db 0
box_temp_w:         db 0
box_temp_a:         db 0


sprite_basket:
    dw (ATTR_GREEN_LIGHT << 8) | CH_FULL,     (ATTR_GREEN_DARK << 8) | CH_SHADE_LIGHT, (ATTR_GREEN_LIGHT << 8) | CH_FULL
    dw (ATTR_GREEN_LIGHT << 8) | CH_FULL,     (ATTR_GREEN_DARK << 8) | CH_SHADE_LIGHT, (ATTR_GREEN_LIGHT << 8) | CH_FULL
    dw (ATTR_GREEN_LIGHT << 8) | CH_HALF_TOP, (ATTR_GREEN_LIGHT << 8) | CH_HALF_TOP,    (ATTR_GREEN_LIGHT << 8) | CH_HALF_TOP

sprite_coin_small:
    dw (ATTR_BLACK << 8) | CH_SPACE,           (ATTR_GRAY_LIGHT << 8) | CH_HALF_BOTTOM, (ATTR_BLACK << 8) | CH_SPACE
    dw (ATTR_GRAY_LIGHT << 8) | CH_HALF_RIGHT, (ATTR_GRAY_LIGHT << 8) | CH_FULL,        (ATTR_GRAY_LIGHT << 8) | CH_HALF_LEFT
    dw (ATTR_BLACK << 8) | CH_SPACE,           (ATTR_GRAY_LIGHT << 8) | CH_HALF_TOP,    (ATTR_BLACK << 8) | CH_SPACE

sprite_coin_gold:
    dw (ATTR_YELLOW << 8) | CH_HALF_BOTTOM, (ATTR_YELLOW << 8) | CH_FULL,   (ATTR_YELLOW << 8) | CH_HALF_BOTTOM
    dw (ATTR_YELLOW << 8) | CH_FULL,        (ATTR_YELLOW << 8) | CH_BULLET, (ATTR_YELLOW << 8) | CH_FULL
    dw (ATTR_YELLOW << 8) | CH_HALF_TOP,    (ATTR_YELLOW << 8) | CH_FULL,   (ATTR_YELLOW << 8) | CH_HALF_TOP

sprite_diamond:
    dw (ATTR_CYAN_LIGHT << 8) | CH_FULL,     (ATTR_CYAN_LIGHT << 8) | CH_FULL,     (ATTR_CYAN_LIGHT << 8) | CH_FULL
    dw (ATTR_CYAN_LIGHT << 8) | CH_HALF_TOP, (ATTR_CYAN_LIGHT << 8) | CH_FULL,     (ATTR_CYAN_LIGHT << 8) | CH_HALF_TOP
    dw (ATTR_BLACK << 8) | CH_SPACE,         (ATTR_CYAN_LIGHT << 8) | CH_HALF_TOP, (ATTR_BLACK << 8) | CH_SPACE

sprite_bomb:
    dw (ATTR_BLACK << 8) | CH_SPACE,        (ATTR_RED_LIGHT << 8) | CH_HALF_BOTTOM, (ATTR_YELLOW << 8) | CH_STAR
    dw (ATTR_RED_LIGHT << 8) | CH_FULL,     (ATTR_RED_LIGHT << 8) | CH_FULL,        (ATTR_RED_LIGHT << 8) | CH_FULL
    dw (ATTR_RED_LIGHT << 8) | CH_HALF_TOP, (ATTR_RED_LIGHT << 8) | CH_FULL,        (ATTR_RED_LIGHT << 8) | CH_HALF_TOP

title_row_0: db " ####  ###  #####  #### #   #    ##      ####  ####  ###  ####  #####", 0
title_row_1: db "#     #   #   #   #     #   #   #  #    #     #     #   # #   # #    ", 0
title_row_2: db "#     #####   #   #     #####    ##      ###  #     #   # ####  #### ", 0
title_row_3: db "#     #   #   #   #     #   #   #  ##       # #     #   # #  #  #    ", 0
title_row_4: db " #### #   #   #    #### #   #    ## #   ####   ####  ###  #   # #####", 0

title_bitmap_table:
    dw title_row_0
    dw title_row_1
    dw title_row_2
    dw title_row_3
    dw title_row_4


legend_table:
    dw sprite_basket
    db 10, 10
    dw str_you

    dw sprite_coin_small
    db 10, 24
    dw str_plus5

    dw sprite_coin_gold
    db 10, 38
    dw str_plus10

    dw sprite_diamond
    db 10, 52
    dw str_plus15

    dw sprite_bomb
    db 10, 66
    dw str_avoid
LEGEND_COUNT        equ 5

showcase_table:
    dw sprite_coin_small
    db 4, 12
    dw str_plus5

    dw sprite_coin_gold
    db 4, 28
    dw str_plus10

    dw sprite_diamond
    db 4, 44
    dw str_plus15

    dw sprite_bomb
    db 4, 60
    dw str_bomb
SHOWCASE_COUNT      equ 4


str_time_label:     db "TIME: ", 0
str_score_label:    db "SCORE: ", 0

str_you:            db "YOU", 0
str_plus5:          db "+5", 0
str_plus10:         db "+10", 0
str_plus15:         db "+15", 0
str_avoid:          db "AVOID!", 0
str_bomb:           db "BOMB", 0

str_start_divider:  db 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, 0
str_how_to_play:    db 250, " ", 250, " ", 250, "  HOW TO PLAY  ", 250, " ", 250, " ", 250, 0
str_help_1:         db "Catch the coins and diamonds in your basket", 0
str_help_2:         db "Don't catch the bomb!   You have 2 minutes", 0
str_help_3:         db "Left/Right Arrow  Move basket        ESC  Quit", 0
str_start_prompt:   db ">>  PRESS ENTER TO START  <<", 0

str_game_over:      db "G A M E   O V E R", 0
str_end_divider:    db 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, " ", 250, 0
str_final_score:    db "FINAL SCORE:  ", 0
str_end_prompt:     db "ENTER  Play again     ESC  Exit", 0