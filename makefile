src = $(wildcard */*.c)
src += $(wildcard */*.h)
out = main.exe
all: $(src)
	make build
	make run
build: $(src)
	g++ $(src) -o $(out)
run:
	$(out)