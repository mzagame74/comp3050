LOOP:       LODD dcount:
            JZER DONE:
            SUBD c1:
            STOD dcount:
P1:         LODD daddr:
            PSHI
            ADDD c1:        
            STOD daddr:
            CALL FIB:
            INSP 1
P2:         PUSH
            LODD raddr:
            POPI
            ADDD c1:
            STOD raddr:
            JUMP LOOP:

FIB:        LODL 1
            JZER FIBZER:
            SUBD c1:
            JZER FIBONE:
            PUSH
            CALL FIB:
            PUSH
            LODL 1
            SUBD c1:
            PUSH            
            CALL FIB:
            INSP 1
            ADDL 0
            INSP 2
            RETN

FIBZER:     LODD c0:
            RETN
FIBONE:     LODD c1:
            RETN
DONE:       HALT

.LOC        100
data:       3
            9
            18
            23
            25
results:    0
            0
            0
            0
            0
daddr:      data:
raddr:      results:
c0:         0
c1:         1
dcount:     5