 use16		       ;Генерировать 16-битный код
org 100h	      ;Программа начинается с адреса 100h
		     ;b-1
    mov ax,word[b]
    sub ax,1
    mov word[d],ax
 
    mov al,byte[b+2]
    sbb al,0
    mov byte[d+2],al
		     ;+a
    mov ax,word[d]
    add ax,word[a]
    mov word[d],ax
 
    mov al,byte[d+2]
    adc al,byte[a+2]
    mov byte[d+2],al
		     ;-c
    mov ax,word[d]
    sub ax,word[c]
    mov word[d],ax

    mov al,byte[d+2]
    sbb al,byte[c+2]
    mov byte[d+2],al


 
    mov ax,4C00h      ;\
    int 21h	      ;/ Завершение программы
;-------------------------------------------------------
b dw 0xF111
  db 0x11
a dw 0xF111
  db 0x11
c dw 0x2222
  db 0x22
d rb 3