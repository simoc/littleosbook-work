global lgdt           ; load Global Descriptor Table (GDT)

; lgdt - load the Global Descriptor Table (GDT)
; stack: [esp + 4] address of table
;        [esp    ] return address
lgdt:
    mov eax, [esp + 4] ; move the address to eax register
    lgdt [eax]; move the data to be sent into the al register
    mov eax, 0x10
    ; set the segment select registers
    mov ds, eax
    mov ss, eax
    mov es, eax
    ; code until here uses the previous cs
    jmp 0x08:flush_cs ; specify cs when jumping to flush cs
flush_cs:
    ; now we've changed cs to 0x08
    ret               ; return to the calling function
