CC = icc
CFLAGS1 = -g -O0 -fno-alias -std=c99
CFLAGS2 = -g -O1 -fno-alias -std=c99
CFLAGS3 = -g -O3 -no-vec -no-simd -fno-alias -std=c99
CFLAGS4 = -g -O3 -xHost -fno-alias -std=c99

all: pi vector

vector: vector.c timing.c dummy.c
	$(CC) $(CFLAGS4) -o $@ $^

pi: pi.c timing.c
	$(CC) $(CFLAGS4) -o $@ $^

test: pi
	qsub -l procs=8,tpn=8,mem=34gb,walltime=15:00 -q cpsc424 test.sh
