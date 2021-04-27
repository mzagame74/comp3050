writeint:   lodl 1          ; store sum in temp
            stod temp:
cnvrt:      lodd c10:       ; convert sum to ascii
            push
            lodd temp:
            push
            div             ; divide sum by 10
            lodd lpcnt:
            addd c1:        ; count number of digits
            stod lpcnt:
            lodl 1          ; load remainder
            addd numoff:    ; add ascii offset
            push            ; push ascii digit onto stack
            lodd psum:      ; load pointer to ascii digits of sum
            popi            ; store ascii digit at psum
            addd c1:        ; increment pointer to ascii sum
            stod psum:
            lodl 0          ; load quotient
            insp 4
            jzer wrloop:    ; branch if quotient is zero
            stod temp:      ; update number for loop
            jump cnvrt:
wrloop:     lodd lpcnt:     ; print result number loop
            jzer icrnl:
            subd c1:
            stod lpcnt:
            lodd psum:
            subd c1:        ; decrement pointer to ascii sum digits
            stod psum:
            pshi            ; push ascii digit onto stack
            call xbsywt:
            pop             ; get ascii digit
            stod 4094       ; send ascii digit to xmtr
            jump wrloop:
icrnl:      lodd cr:
            stod 4094       ; send carriage return to xmtr
            call xbsywt:
            lodd nl:
            stod 4094       ; send newline to xmtr
            call xbsywt:
            retn
