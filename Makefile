.PHONY: build
build:
	@gcc -o bin/main main.c

.PHONY: run
run: build
	@./bin/main