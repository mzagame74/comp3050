readint:    call rbsywt:    ; call receiver (rcvr) busy wait subroutine
            lodd 4092       ; load first digit of input value
            subd numoff:    ; subtract ascii offset
            push            ; push digit onto stack
nxtdig:     call rbsywt:
            lodd 4092       ; load digit from rcvr
            stod nxtchr:    ; store in nxtchr
            subd nl:
            jzer done:      ; branch if newline character
            mult 10         ; multiply value on stack by 10
            lodd nxtchr:    ; get digit from nxtchr
            subd numoff:    ; subtract ascii offset
            addl 0          ; add digit to number on stack
            stol 0
            jump nxtdig:
done:       pop             ; get number off of stack and return
            retn
