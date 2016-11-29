
#include <stdio.h>
//#include <stdlib.h>
#include <assert.h>
#include "bdi_compression.c"

int main() {

	unsigned char *blk_ptr = (unsigned char *)malloc(32 * sizeof(char));

	/*int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	for (a = 0; a < 256; a++) {
		for (b = 0; b < 256; b++) {
			for (c = 0; c < 256; c++) {
				for (d = 0; d < 256; d++) {
					for (e = 0; e < 256; e++) {
						for (f = 0; f < 256; f++) {
							for (g = 0; g < 256; g++) {
								for (h = 0; h < 256; h++) {

									unsigned block_compressed_bit_length = BDICompress(blk_ptr, 8);

									if (block_compressed_bit_length != 8) {
										printf("\nAchevied a size different that 8!\n");
										printf("\tSize is %u and the block contents are 0x%X%X%X%X%X%X%X%X",
												block_compressed_bit_length, a, b, c, d, e, f, g, h);

										char c[128];
										scanf("%s", c);
									}
									//printf("\tAddress 0x%X%X%X%X%X%X%X%X", a, b, c, d, e, f, g, h);
									blk_ptr[0]++;
								}
								blk_ptr[0] = 0;
								blk_ptr[1]++;
							}
							blk_ptr[1] = 0;
							blk_ptr[2]++;
						}
						blk_ptr[2] = 0;
						blk_ptr[3]++;
					}
					blk_ptr[3] = 0;
					blk_ptr[4]++;
				}
				blk_ptr[4] = 0;
				blk_ptr[5]++;
			}
			blk_ptr[5] = 0;
			blk_ptr[6]++;
		}
		blk_ptr[6] = 0;
		blk_ptr[7]++;
	}*/

	unsigned block_compressed_bit_length, i;

	// Testing out block content 0x0101010101010101010101010101010101010101010101010101010101010101.
	for (i = 0; i < 32; i++)
		*(blk_ptr + i) = 1;

	printf("\n\tTrying block content as '0x");
	for (i = 32; i > 0; i--)
		printf("%02X", blk_ptr[i - 1]);
	printf("' (32 bytes), should compress to 4... ");

	block_compressed_bit_length = BDICompress(blk_ptr, 32);
	assert(block_compressed_bit_length == 4);

	printf("SUCCESS!!!\n\n");


	// Testing out block content 0x0000000000000000000000000000000000000000000000000000000000000000.
	for (i = 0; i < 32; i++)
		*(blk_ptr + i) = 0;

	printf("\tTrying block content as '0x");
	for (i = 32; i > 0; i--)
		printf("%02X", blk_ptr[i - 1]);
	printf("' (32 bytes), should compress to 1... ");

	block_compressed_bit_length = BDICompress(blk_ptr, 32);
	assert(block_compressed_bit_length == 1);

	printf("SUCCESS!!!\n\n");


	// Testing out block content 0x00000000000000000000000000000000000000000000000000000000000000FF.
	*blk_ptr = 255;

	printf("\tTrying block content as '0x");
	for (i = 32; i > 0; i--)
		printf("%02X", blk_ptr[i - 1]);
	printf("' (32 bytes), should compress to 16... ");

	block_compressed_bit_length = BDICompress(blk_ptr, 32);
	//printf("WHAT? %u      ", block_compressed_bit_length);
	assert(block_compressed_bit_length == 16);

	printf("SUCCESS!!!\n\n");


	// Testing out block content 0xFF00000000000000000000000000000000000000000000000000000000000000.
	*blk_ptr = 0;
	*(blk_ptr + 31) = 255;

	printf("\tTrying block content as '0x");
	for (i = 32; i > 0; i--)
		printf("%02X", blk_ptr[i - 1]);
	printf("' (32 bytes), should compress to 16... ");

	block_compressed_bit_length = BDICompress(blk_ptr, 32);
	//printf("WHAT? %u      ", block_compressed_bit_length);
	assert(block_compressed_bit_length == 16);

	printf("SUCCESS!!!\n\n");

	return 0;
}
