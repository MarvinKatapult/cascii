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

Pixel * preloadImage(unsigned char * img, int w, int h, int channels) {
	Pixel * ret = calloc(w * h * channels, sizeof(Pixel));
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

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("USAGE: %s image_path\n", argv[0]);
        return 1;
    }

    int w, h, channels;
    unsigned char *img = stbi_load(argv[1], &w, &h, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        return 1;
    }

	Pixel * pixels = preloadImage(img, w, h, channels);
    stbi_image_free(img);

	for (int i = 0; i < w * h * channels; i++) {
		if (i > w * h * channels - 10) printf("R:%d\n", pixels[i].r);
	}

    return 0;
}

