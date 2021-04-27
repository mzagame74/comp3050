rbsywt: lodd 4093       ; get rcvr status
        subd mask:
        jneg rbsywt:    ; loop if busy
        retn
