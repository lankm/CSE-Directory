CC = gcc

project_files = $(wildcard *c)

program = problem1

release: $(project_files)
	$(CC) $^ -lm -o $(program)

clean:
	rm $(program)
