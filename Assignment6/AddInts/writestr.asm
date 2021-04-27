writestr:   lodl 1          ; load address of string
            pshi            ; push string onto stack (two bytes at a time)
            addd c1:        ; increment string address
            stol 2
            call xbsywt:    ; call transmitter (xmtr) busy wait subroutine
            lodl 0          ; load string character bytes
            jzer scrnl:     ; branch if end of string
            stod 4094       ; send first character (lower byte) to xmtr
            subd c255:
            jneg scrnl:     ; branch if last single character in string
            pop             ; get characters back
            rshift 8        ; right shift by one character byte
            push            ; push remaining character byte onto stack
            call xbsywt:
            pop             ; get second character back
            stod 4094       ; send second character to xmtr
            jump writestr:
scrnl:      insp 1
            lodd cr:
            stod 4094       ; send carriage return to xmtr
            call xbsywt:
            lodd nl:
            stod 4094       ; send newline to xmtr
            call xbsywt:
            retn
