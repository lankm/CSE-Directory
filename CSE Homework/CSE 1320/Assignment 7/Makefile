CC = gcc

util_files = $(wildcard $(src)/utils/*c)
project_files = $(wildcard $(src)/*c)

src = src
build_dir = build

program = problem1
debug_flags = -g -Wall


release: $(util_files) $(project_files)
	mkdir $(build_dir)
	$(CC) $^ -lm -o $(build_dir)/$(program)

debug: $(util_files) $(project_files)
	mkdir $(build_dir)
	$(CC) -DDEBUG $^ -lm -o $(build_dir)/$(program)_debug $(debug_flags)

clean:
	rm -rf $(build_dir)
