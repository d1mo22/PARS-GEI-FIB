all: proc_time nproc_time nproc_time_max max_5sec nproc_time_max2

proc_time: proc_time.c
	g++ -o proc_time proc_time.c

nproc_time: nproc_time.c
	g++ -o nproc_time nproc_time.c

nproc_time_max: nproc_time_max.c
	g++ -o nproc_time_max nproc_time_max.c

max_5sec: max_5sec.c
	g++ -o max_5sec max_5sec.c

nproc_time_max2: nproc_time_max.c
	g++ -o nproc_time_max2 nproc_time_max2.c

clean:
	rm -rf max_5sec proc_time nproc_time_max2 nproc_time_max nproc_time
