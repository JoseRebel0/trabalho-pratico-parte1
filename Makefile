all: clean prog run

prog: ./Main/main.c ./Functions/funcoes.c
	gcc ./Main/main.c ./Functions/funcoes.c -o prog

clean:
	rm -f prog

run: prog
	./prog