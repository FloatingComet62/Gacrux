src = $(wildcard */*.c)
src += $(wildcard */*.h)
out = main.exe
all: $(src)
	make build
	make run
build: $(src)
	gcc $(src) -o $(out)
run:
	$(out)
