start:      lodd on:        ; turn on transmitter and receiver
            stod 4095
            stod 4093
            loco str1:      ; load user prompt string address
            push
            call writestr:  ; output string to screen
            insp 1
            call readint:   ; get first number input
            stod binum1:
            loco str1:      ; output user prompt string to screen
            push
            call writestr:
            insp 1
            call readint:   ; get second number input
            stod binum2:
            lodd binum1:
            push
            lodd binum2:
            push
            call addints:   ; add both binums together
            insp 2
            stod sum:       ; store result in sum
            jpos prtsum:    ; branch if result did not overflow
            loco str3:      ; output overflow message to screen
            push
            call writestr:
            insp 1
            halt
prtsum:     loco str2:
            push
            call writestr:  ; output addition result string to screen
            insp 1
            lodd sum:
            push
            call writeint:  ; output sum to screen
            insp 1
            halt
