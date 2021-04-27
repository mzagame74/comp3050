all: AddInts.exe

AddInts.exe: linker AddInts/main.o AddInts/writestr.o AddInts/readint.o AddInts/addints.o AddInts/writeint.o AddInts/xbsywt.o AddInts/rbsywt.o AddInts/data.o
	./linker AddInts/main.o AddInts/writestr.o AddInts/readint.o AddInts/addints.o AddInts/writeint.o AddInts/xbsywt.o AddInts/rbsywt.o AddInts/data.o > AddInts.exe

AddInts.o: linker AddInts/main.o AddInts/writestr.o AddInts/readint.o AddInts/addints.o AddInts/writeint.o AddInts/xbsywt.o AddInts/rbsywt.o AddInts/data.o
	./linker -o AddInts/main.o AddInts/writestr.o AddInts/readint.o AddInts/addints.o AddInts/writeint.o AddInts/xbsywt.o AddInts/rbsywt.o AddInts/data.o > AddInts.o

linker: linker.o
	gcc -o linker linker.o

linker.o: linker.c
	gcc -c -g linker.c

AddInts/addints.o: AddInts/addints.asm
	./masm_mrd -o < AddInts/addints.asm > AddInts/addints.o

AddInts/main.o: AddInts/main.asm
	./masm_mrd -o < AddInts/main.asm > AddInts/main.o

AddInts/writestr.o: AddInts/writestr.asm
	./masm_mrd -o < AddInts/writestr.asm > AddInts/writestr.o

AddInts/readint.o: AddInts/readint.asm
	./masm_mrd -o < AddInts/readint.asm > AddInts/readint.o

AddInts/writeint.o: AddInts/writeint.asm
	./masm_mrd -o < AddInts/writeint.asm > AddInts/writeint.o

AddInts/xbsywt.o: AddInts/xbsywt.asm
	./masm_mrd -o < AddInts/xbsywt.asm > AddInts/xbsywt.o

AddInts/rbsywt.o: AddInts/rbsywt.asm
	./masm_mrd -o < AddInts/rbsywt.asm > AddInts/rbsywt.o

AddInts/data.o: AddInts/data.asm
	./masm_mrd -o < AddInts/data.asm > AddInts/data.o

clean:
	rm -f AddInts.exe linker *.o AddInts/*.o
