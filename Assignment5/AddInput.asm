; add two positive base 10 integers using mic1's polled IO and updated 
; microcode with mult, rshift, and div instructions

start:  lodd on:        ; turn on transmitter (xmtr)
        stod 4095
        call xbsywt:    ; call xmtr busy wait subroutine
        loco str1:      ; load user prompt string address
        call nextw:     ; call string output subroutine
        lodd on:        ; turn on receiver (rcvr)
        stod 4093
bgndig: call rbsywt:    ; start receiving input
        lodd 4092       ; load first digit of input value
        subd numoff:    ; subtract ascii offset
        push            ; push digit onto stack
nxtdig: call rbsywt:
        lodd 4092       ; load digit from rcvr
        stod nxtchr:    ; store in nxtchr
        subd nl:
        jzer endnum:    ; branch if newline character
        mult 10         ; multiply value on stack by 10
        lodd nxtchr:    ; get digit from nxtchr
        subd numoff:    ; subtract ascii offset
        addl 0          ; add digit to number on stack
        stol 0
        jump nxtdig:
endnum: lodd numptr:    ; pointer to binums
        popi            ; store number at numptr
        addd c1:        ; increment numptr
        stod numptr:
        lodd numcnt:    ; load number of values left to add
        jzer addnms:    ; branch if ready to add numbers
        subd c1:
        stod numcnt:
        jump start:     ; get next number to add
addnms: lodd binum1:    ; add both binums
        addd binum2:
        jneg ovrflw:    ; branch if overflow
        stod sum:       ; store result of addition in sum
        stod temp:      ; store sum in temp for conversion
cnvrt:  lodd c10:       ; convert sum to ascii
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
        jzer rslt:      ; branch if quotient is zero
        stod temp:      ; update number for loop
        jump cnvrt:
rslt:   call xbsywt:    ; print result string
        loco str2:
        call nextw:
prntnm: lodd lpcnt:     ; print result number loop
        jzer done:
        subd c1:
        stod lpcnt:
        lodd psum:
        subd c1:        ; decrement pointer to ascii sum digits
        stod psum:
        pshi            ; push ascii digit onto stack
        call xbsywt:
        pop             ; get ascii digit
        stod 4094       ; send ascii digit to xmtr
        jump prntnm:
done:   lodd cr:        ; print newline and return 0
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        loco 0
        halt
ovrflw: call xbsywt:    ; print overflow message and return -1
        loco str3:
        call nextw:
        lodd cn1:
        halt
nextw:  pshi            ; push string onto stack (two bytes at a time)
        addd c1:        ; increment pointer to string character bytes
        stod pstr:
        lodl 0          ; load string character bytes
        jzer crnl:      ; branch if end of string
        stod 4094       ; send first character (lower byte) to xmtr
        subd c255:
        jneg crnl:      ; branch if last single character in string
        pop             ; get characters back
        rshift 8        ; right shift by one character byte
        push            ; push remaining character byte onto stack
        call xbsywt:
        pop             ; get second character back
        stod 4094       ; send second character to xmtr
        call xbsywt:
        lodd pstr:      ; load next two bytes in string
        jump nextw:
crnl:   insp 1
        lodd cr:
        stod 4094       ; send carriage return to xmtr
        call xbsywt:
        lodd nl:
        stod 4094       ; send newline to xmtr
        call xbsywt:
        retn
xbsywt: lodd 4095       ; get xmtr status
        subd mask:      ; check if xmtr is busy or done
        jneg xbsywt:
        retn   
rbsywt: lodd 4093       ; get rcvr status
        subd mask:      ; check if rcvr is busy or done
        jneg rbsywt:
        retn
on:     8               ; local variables
mask:   10
nl:     10
cr:     13
cn1:    -1
c1:     1
c10:    10
c255:   255
pstr:   0
numoff: 48
nxtchr: 0
numptr: binum1:
binum1: 0
binum2: 0
numcnt: 1
sum:    0               ; sum stored here
temp:   0
lpcnt:  0
psum:   asum:
str1:   "PLEASE ENTER AN INTEGER BETWEEN 1 AND 32767"
str2:   "THE SUM OF THESE TWO INTEGERS IS:"
str3:   "OVERFLOW, NO SUM POSSIBLE"
asum:   0               ; ascii sum digits array
