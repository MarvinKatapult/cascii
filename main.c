#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Pixel;

#define USED_CHARS  ".`;-'*|><)(][\\/+=#wxlstymjcurvzpfnqkhgedbaOoILTSPCYEJRVEUKGFDXAHQZBNMW"

Pixel * preloadImage(unsigned char * img, int w, int h, int channels) {
	Pixel * ret = calloc(w * h, sizeof(Pixel));
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Pixel * new_pix = ret + (y * w + x);
			const unsigned char * old_pix = img + (y * w + x) * channels;
			new_pix->r = old_pix[0];
			new_pix->g = old_pix[1];
			new_pix->b = old_pix[2];
			if (channels > 3) {
				new_pix->a = old_pix[3];
			} else new_pix->a = 255;
		}
	}
	return ret;
}

unsigned char getAvgBrightness(Pixel p) {
    return (p.r + p.g + p.b) / 3;
}

unsigned char getAvgBrightnessSector(Pixel * start, int w, int size) {
    int count = 0;
    int abs_brightness = 0;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            const Pixel * p = start + (x + y * w);
            abs_brightness += getAvgBrightness(*p);
            count++;
        }
    }
    return abs_brightness / count;
}

char mapAvgBToChar(unsigned char b) {
    const char * c = USED_CHARS;
    const float f = strlen(c) / 256.f;
    return c[(int)(f * b)];
}

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("USAGE: %s image_path [cell_pixel_size]\n", argv[0]);
        return 1;
    }

    int w, h, channels;
    unsigned char * img = stbi_load(argv[1], &w, &h, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        return 1;
    }

    if (!strstr(argv[1], ".jpg") && !strstr(argv[1], ".png") && !strstr(argv[1], ".jpeg")) {
        printf("Provided image is not in the right format. (.png or .jpg)\n");
        return 1;
    }

	Pixel * pixels = preloadImage(img, w, h, channels);
    stbi_image_free(img);

    int size = 8;
    if (argc > 2) {
        size = atoi(argv[2]);    
    }
    const int count_x = w / size;
    const int count_y = h / size;
    for (int y = 0; y < count_y; y++) {
        for (int x = 0; x < count_x; x++) {
            unsigned char b = getAvgBrightnessSector(pixels + ((x + y * w) * size), w, size);
            // printf("Avg. B for Sector:X=%d;Y=%d %d\n", x, y, b);
            printf("%c", mapAvgBToChar(b));
        }
        printf("\n");
    }

    printf("\n");
    free (pixels);

    return 0;
}

