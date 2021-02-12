.section .text.spgui_get_byte,"ax",%progbits
.global spgui_get_byte
.type spgui_get_byte, %function
.extern spgui_spriteList
.syntax unified
spgui_get_byte:
ldrb.w r7, [r0, #0x100] // layer->mode
cmp r7, #0x00
bne loc_mode_portrait
loc_mode_landscape:
ldrb.w r7, [r0, #0x101] // layer->posx
add r7, r1 // x += layer->posx
and r7, #0xff
and r8, r7, #0x07 // xdelta = x & 0x07
lsr r7, #0x03 // x = x >> 3
//mov r9, #0x08 // spritesid = layer->main.sprites_landscape[x][ydiv8]
//mul r9, r7
lsl r9, r7, #0x03
add r0, r9
ldrb r0, [r0, r2]
//mov r9, #0x08 // spgui_spriteList.sprites[spritesid].data[xdelta]
//mul r9, r0
//lsl r9, r0, #0x03
add r9, r8, r0, LSL#3
ldr r0, =spgui_spriteList
//add r0, r9
ldrb r0, [r0, r9]
bx lr
loc_mode_portrait:
and r8, r1, #0x07 // xdelta = x & 0x07
lsr r7, r1, #0X03 // x = x >> 3
// mov r9, #0x08 // ypos = ydiv8 * 8 + layer->posy
// mul r9, r2
lsl r9, r2, #0x03
ldrb.w r10, [r0, #0x102]
add r9, r10
and r10, r9, #0x07 // ydelta = ypos & 0x07
lsr r9, #0x03 // ypos = ypos >> 3
// lsl r7, #0x04 // mul r7, r7, #0x10
add r0, r0, r7, LSL#4
and r9, #0x0f
ldrb r11, [r0, r9]
add r9, #0x01
and r9, #0x0f
ldrb r12, [r0, r9]
ldr r0, =spgui_spriteList
lsl r11, #0x03 // mul r11, r11, #0x08
lsl r12, #0x03 // mul r12, r12, #0x08
add r7, r0, r12
add r0, r11
ldrb r0, [r0, r8]
ldrb r7, [r7, r8]
lsl r7, #0x08
orr r0, r7
lsr r0, r10
and r0, #0xff
bx lr

.section .text.spgui_get_alpha,"ax",%progbits
.global spgui_get_alpha
.type spgui_get_alpha, %function
.extern spgui_spriteList
.syntax unified
spgui_get_alpha:
ldrb.w r7, [r0, #0x100] // layer->mode
cmp r7, #0x00
bne loc_mode_portrait_alpha
loc_mode_landscape_alpha:
ldrb.w r7, [r0, #0x101] // layer->posx
add r7, r1 // x += layer->posx
and r7, #0xff
and r8, r7, #0x07 // xdelta = x & 0x07
lsr r7, #0x03 // x = x >> 3
//mov r9, #0x08 // spritesid = layer->main.sprites_landscape[x][ydiv8]
//mul r9, r7
lsl r9, r7, #0x03
add r0, #0x103
add r0, r9
ldrb r0, [r0, r2]
//mov r9, #0x08 // spgui_spriteList.sprites[spritesid].data[xdelta]
//mul r9, r0
//lsl r9, r0, #0x03
add r9, r8, r0, LSL#3
ldr r0, =spgui_spriteList
//add r0, r9
ldrb r0, [r0, r9]
bx lr
loc_mode_portrait_alpha:
and r8, r1, #0x07 // xdelta = x & 0x07
lsr r7, r1, #0X03 // x = x >> 3
//mov r9, #0x08 // ypos = ydiv8 * 8 + layer->posy
//mul r9, r2
lsl r9, r2, #0x03
ldrb.w r10, [r0, #0x102]
add r9, r10
and r10, r9, #0x07 // ydelta = ypos & 0x07
lsr r9, #0x03 // ypos = ypos >> 3
//lsl r7, #0x04 // mul r7, r7, #0x10
add r0, r0, r7, LSL#4
add r0, #0x103
and r9, #0x0f
ldrb r11, [r0, r9]
add r9, #0x01
and r9, #0x0f
ldrb r12, [r0, r9]
ldr r0, =spgui_spriteList
lsl r11, #0x03 // mul r11, r11, #0x08
lsl r12, #0x03 // mul r12, r12, #0x08
add r7, r0, r12
add r0, r11
ldrb r0, [r0, r8]
ldrb r7, [r7, r8]
lsl r7, #0x08
orr r0, r7
lsr r0, r10
and r0, #0xff
bx lr

.section .text.spgui_render,"ax",%progbits
.global spgui_render
.type spgui_render, %function
.extern spgui_firstLayer
.extern spgui_layer
.extern spgui_get_byte
.extern spgui_get_alpha
.extern spgui_portable_outputData
spgui_render:
push {r0-r12}
mov r3, lr
push {r3}

ldr r2, =0x00 // ydiv8 = 0
ldr r1, =0x00 // x = 0

loc_ydiv8_loop_start:
loc_x_loop_start:

ldr r0, =spgui_firstLayer
bl spgui_get_byte
mov r3, r0

ldr r4, =spgui_layer
ldr r6, =0x00
loc_layer_loop_start:
mov r0, r4
bl spgui_get_alpha
mov r5, r0
mov r0, r4
bl spgui_get_byte
and r0, r5
bic r3, r5
orr r3, r0
ldr r5, =0x203
add r4, r5
add r6, #0x01
cmp r6, #0x04
bne loc_layer_loop_start

mov r0, r3
push {r0-r12}
bl spgui_portable_outputData
pop {r0-r12}

add r1, #0x01
cmp r1, #0x80
bne loc_x_loop_start
mov r1, #0x00
add r2, #0x01
cmp r2, #0x08
bne loc_ydiv8_loop_start

pop {r3}
mov lr, r3
pop {r0-r12}
BX LR
