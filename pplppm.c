/*

Pixel Per Line Portable PixMap

Loads the image at the given path.
Outputs the image to stdout as a P3 (ASCII) .ppm image
  with each pixel on its own line.
The first 3 lines outputted are the .ppm header.
Each color channel value is [0-255].

Returns 0 on success.
On error, prints to stderr and returns greater than 0.



Public domain program, or alternatively:
BSD Zero Clause License

Copyright (C) 2022 by Costava

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "stb_image.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Pass exactly 1 argument: path to image\n");
		exit(1);
	}

	int x, y, n;
	unsigned char *const data = stbi_load(argv[1], &x, &y, &n, 3);

	if (data == NULL) {
		fprintf(stderr, "Failed to load %s\n", argv[1]);
		exit(2);
	}

	if (x < 1 || y < 1) {
		fprintf(stderr, "Image dimensions (%d, %d) must both be >= 1\n", x, y);
		exit(3);
	}

	// Output .ppm file.

	// Output the header.
	{
		const int headerRet = fprintf(stdout, "P3\n%d %d\n255\n", x, y);
		if (headerRet < 0) {
			fprintf(stderr, "Header fprintf error\n");
			exit(4);
		}
	}

	if (SIZE_MAX / (size_t)x <= (size_t)y) {
		fprintf(stderr,
			"Number of pixels must be < SIZE_MAX (%zu)\n", SIZE_MAX);
		exit(5);
	}

	const size_t numPixels = (size_t)x * (size_t)y;
	for (size_t p = 0; p < numPixels; p += 1) {
		const size_t i = p * 3;

		const int ret =
			fprintf(stdout, "%d %d %d\n", data[i], data[i+1], data[i+2]);

		if (ret < 0) {
			fprintf(stderr, "fprintf error\n");
			exit(6);
		}
	}

	stbi_image_free(data);

	return 0;
}
