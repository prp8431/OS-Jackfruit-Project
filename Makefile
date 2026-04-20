all:
	gcc engine.c -o engine
	gcc cpu_hog.c -o cpu_hog
	gcc io_pulse.c -o io_pulse
	gcc memory_hog.c -o memory_hog

clean:
	rm -f engine cpu_hog io_pulse memory_hog
