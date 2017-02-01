CC = icc
CFLAGS1 = -g -O0 -fno-alias -std=c99
CFLAGS2 = -g -O1 -fno-alias -std=c99
CFLAGS3 = -g -O3 -no-vec -no-simd -fno-alias -std=c99
CFLAGS4 = -g -O3 -xHost -fno-alias -std=c99
CFLAGS5 = -g -O0 -std=c99
CFLAGS6 = -g -O3 -no-simd -fno-alias -std=c99

all: pi vector pi2 pi3 pi4 pi5 pi6 div

vector: vector.c timing.c dummy.c
	$(CC) $(CFLAGS4) -o $@ $^

pi: pi.c timing.c
	$(CC) $(CFLAGS1) -o $@ $^
pi2: pi.c timing.c
	$(CC) $(CFLAGS2) -o $@ $^
pi3: pi.c timing.c
	$(CC) $(CFLAGS3) -o $@ $^
pi4: pi.c timing.c
	$(CC) $(CFLAGS4) -o $@ $^
pi5: pi.c timing.c
	$(CC) $(CFLAGS5) -o $@ $^
pi6: pi.c timing.c
	$(CC) $(CFLAGS6) -o $@ $^
div: division.c timing.c
	$(CC) $(CFLAGS1) -o $@ $^

clean:
	rm pi pi2 pi3 pi4 pi5 pi6 div vector

test: pi
	qsub -l procs=8,tpn=8,mem=34gb,walltime=15:00 -q cpsc424 test.sh
