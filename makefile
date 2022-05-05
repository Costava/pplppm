# makefile

CSTD=-std=c99
EXECUTABLE=pplppm

.PHONY: build clean

build: ${EXECUTABLE}

clean:
	rm -f ./${EXECUTABLE}
	rm -f ./tmp/stb_image.o

tmp:
	mkdir tmp

tmp/stb_image.o: vendor/stb_image.c vendor/stb_image.h | tmp
	gcc vendor/stb_image.c --output $@ ${CSTD} -c -w

${EXECUTABLE}: pplppm.c tmp/stb_image.o
	gcc $^ --output $@ ${CSTD} -I vendor \
		-Wall -Wextra -Wconversion -Wshadow \
		-lm
