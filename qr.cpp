#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <string>
#include <math.h>
using namespace std;

void add_row_copy(const int rows, const bool bytes[4 + 1][8], bool bytes_copy[6][8]);

void encode_char(const char character, bool bits[8]) {
	int n = character;
	int binaryNum[32];
	int a = 0;

	if (character != '\0') {


		int i = 0;
		while (n > 0) {
			binaryNum[i] = n % 2;
			n = n / 2;
			i++;
		}

		i++;
		binaryNum[7] = 0;

		for (int j = i - 1; j >= 0; j--) {
			if (binaryNum[j] == 1) {
				bits[a] = true;
				a++;
			}
			else {
				bits[a] = false;
				a++;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			bits[i] = false;
		}
	}
}

char decode_byte(bool bits2[8]) {
	int n = 0;
	int a = 0;

	for (int i = 7; i > 0; i--) {
		if (bits2[i] == true) {
			n += pow(2, a);
		}
		a++;
	}

	return (char)(n);
}

void encode_string(const char string[], bool bytes[20][8]) {
	bool bits[8];

	for (int i = 0; i < strlen(string); i++) {
		encode_char(string[i], bits);

		for (int j = 0; j < 8; j++) {
			bytes[i][j] = bits[j];
		}

	}
	for (int i = 0; i < 8; i++) {
		bytes[strlen(string)][i] = false;
	}
}

void decode_bytes(const int rows, bool bytes[7][8], char string[7]) {
	bool boofer[8];
	char ch;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 8; j++) {
			boofer[j] = bytes[i][j];
		}
		string[i] = decode_byte(boofer);
	}
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[2 * 8][3], const int rows, bool bytes[6][8]) {
	bool bytes_copy[5 + 1][8];

	for (int i = 0; i < offset * 8; i++) {
		for (int j = 0; j < cols; j++) {
			blocks[i][j] = 0;
		}
	}

	if ((rows % offset) == 0) {
		printf("---------------------\n");
		for (int i = 0; i < (rows / offset) - 1; i++) {
			for (int y = 0; y < 8; y++) {

				for (int x = 0; x < cols; x++) {
					blocks[y + (8 * i)][x] = bytes[x + (cols * i)][y];
				}
			}
		}
	}
	else {

		add_row_copy(rows, bytes, bytes_copy);

		for (int i = 0; i < ((rows + 1) / offset) - 1; i++) {
			for (int y = 0; y < 8; y++) {

				for (int x = 0; x < cols; x++) {
					blocks[y + (8 * i)][x] = bytes[x + (cols * i)][y];
				}

			}
		}
	}

}

void add_row_copy(const int rows, const bool bytes[4 + 1][8], bool bytes_copy[6][8]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 8; j++) {
			bytes_copy[i][j] = bytes[i][j];
		}
	}

	for (int i = 0; i < 8; i++) {
		bytes_copy[rows][i] = false;
	}
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[2 * 8][3], const int rows, bool bytes[4 + 1][8]) {
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 8; j++) {
			bytes[i][j] = 0;
		}
	}

	if ((rows % 2) == 0) {
		for (int i = 0; i < (rows / offset) - 1; i++) {
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < cols; x++) {
					bytes[x + (cols * i)][y] = blocks[y + (8 * i)][x];
					//printf(" X : %d Y : %d  I : %d\n ASN : %d \n ------------- \n", x, y + (8 * i), i, blocks[y + (8 * i)][x]);
				}
				//printf("\n");
			}
		}
	}
	else {

		for (int i = 0; i < (rows / offset); i++) {
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < cols - 1*i; x++) {
					bytes[x + (cols * i)][y] = blocks[y + (8 * i)][x];
					printf(" X : %d Y : %d  I : %d\n ASN : %d \n ------------- \n", x, y + (8 * i), i, blocks[y + (8 * i)][x]);
				}
				printf("\n");

			}
		}

	}

	/*for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", blocks[i][j]);
		}
		printf("\n");
	}
	printf("--------------====================\n");
	*/
}

int main()
{
	/*int length = 4 + 1, cols = 2, offset = 3;
	bool bytes1[4 + 1][8] = {
		{0,1,0,0,0,0,0,1},
		{0,1,1,0,1,0,0,0},
		{0,1,1,0,1,1,1,1},
		{0,1,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0}
	};
	bool blocks1[2 * 8][3];
	bytes_to_blocks(cols, offset, blocks1, length, bytes1);
	for (int j = 0; j < offset * 8; j++) {
		for (int i = 0; i < cols; i++) {
			printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
		}
		printf("\n");
		if (j % 8 == 7) {
			printf("\n");
		}
	}*/
	
	/*int length = 4 + 1, cols = 3, offset = 2;
	bool bytes1[4 + 1][8] = {
		{0,1,0,0,0,0,0,1},
		{0,1,1,0,1,0,0,0},
		{0,1,1,0,1,1,1,1},
		{0,1,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0}
	};
	bool blocks1[2 * 8][3];
	bytes_to_blocks(cols, offset, blocks1, length, bytes1);
	for (int j = 0; j < offset * 8; j++) {
		for (int i = 0; i < cols; i++) {
			printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
		}
		printf("\n");
		if (j % 8 == 7) {
			printf("\n");
		}
	}
	*/
	bool blocks2[2 * 8][3] = {
	{0,0,0},
	{1,1,1},
	{0,1,1},
	{0,0,0},
	{0,1,1},
	{0,0,1},
	{0,0,1},
	{1,0,1},

	{0,0,0},
	{1,0,0},
	{1,0,0},
	{0,0,0},
	{1,0,0},
	{0,0,0},
	{1,0,0},
	{0,0,0}
	};

	int length = 4 + 1, cols = 3, offset = 2;

	bool bytes2[4 + 1][8];
	blocks_to_bytes(3, 2, blocks2, length, bytes2);
	for (int j = 0; j < length; j++) {
		for (int i = 0; i < 8; i++) {
			printf("%d", bytes2[j][i]);
		}
		printf("\n");
	}
	
}

