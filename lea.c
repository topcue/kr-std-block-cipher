/*
 * @author topcue
 */

#include <stdio.h>

#define NR_128 24
#define NR_192 28
#define NR_256 32

#define flip(a) a = (a >> 24) | (a >> 8 & 0xff00) | (a << 8 & 0xff0000) | (a << 24 & 0xff000000) 
#define inv_flip(a) a = (a << 24 & 0xff000000) | (a << 8 & 0xff0000) | (a >> 8 & 0xff00) | (a >> 24 & 0xff)

typedef unsigned int uint;

uint delta[8] = {
	0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec,
	0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957
};

void show_array(uint* arr, int len) {
	for (int i = 0; i < len; i++)
		printf("%08x ", arr[i]);
	printf("\n");
}

void flip_array(uint* X, int len) {
	for (int i = 0; i < len; i++)
		flip(X[i]);
}

void inv_flip_array(uint* X, int len) {
	for (int i = 0; i < len; i++)
		inv_flip(X[i]);
}

uint rot(uint val, int n) {
	for (int i = 0; i < n; i++)
		val = (val >> 31 & 0x1) | (val << 1 & 0xffffffff);
	return val;
}

void round_enc_128(uint* X, uint* K, int r) {
	uint tmp;
	uint RK[6] = {0x00, };

	// key schedule
	K[0] = rot(K[0] + rot(delta[r % 4], r+0), 1);
	K[1] = rot(K[1] + rot(delta[r % 4], r+1), 3);
	K[2] = rot(K[2] + rot(delta[r % 4], r+2), 6);
	K[3] = rot(K[3] + rot(delta[r % 4], r+3), 11);
	RK[0] = K[0];
	RK[1] = K[1];
	RK[2] = K[2];
	RK[3] = K[1];
	RK[4] = K[3];
	RK[5] = K[1];

	// round encryption
	tmp = X[0];
	X[0] = rot((X[0] ^ RK[0]) + (X[1] ^ RK[1]), 9);
	X[1] = rot((X[1] ^ RK[2]) + (X[2] ^ RK[3]), 27);
	X[2] = rot((X[2] ^ RK[4]) + (X[3] ^ RK[5]), 29);
	X[3] = tmp;
}

void round_enc_192(uint* X, uint* K, int r) {
	uint tmp;
	uint RK[6] = {0x00, };

	// key schedule
	K[0] = rot(K[0] + rot(delta[r % 6], r + 0), 1);
	K[1] = rot(K[1] + rot(delta[r % 6], r + 1), 3);
	K[2] = rot(K[2] + rot(delta[r % 6], r + 2), 6);
	K[3] = rot(K[3] + rot(delta[r % 6], r + 3), 11);
	K[4] = rot(K[4] + rot(delta[r % 6], r + 4), 13);
	K[5] = rot(K[5] + rot(delta[r % 6], r + 5), 17);
	RK[0] = K[0];
	RK[1] = K[1];
	RK[2] = K[2];
	RK[3] = K[3];
	RK[4] = K[4];
	RK[5] = K[5];

	// round encryption
	tmp = X[0];
	X[0] = rot((X[0] ^ RK[0]) + (X[1] ^ RK[1]), 9);
	X[1] = rot((X[1] ^ RK[2]) + (X[2] ^ RK[3]), 27);
	X[2] = rot((X[2] ^ RK[4]) + (X[3] ^ RK[5]), 29);
	X[3] = tmp;
}

void round_enc_256(uint* X, uint* K, int r) {
	uint tmp;
	uint RK[6] = {0x00, };

	// Key_schedule
	K[(6 * r + 0) % 8] = rot(K[(6 * r + 0) % 8] + rot(delta[r % 8], r+0), 1);
	K[(6 * r + 1) % 8] = rot(K[(6 * r + 1) % 8] + rot(delta[r % 8], r+1), 3);
	K[(6 * r + 2) % 8] = rot(K[(6 * r + 2) % 8] + rot(delta[r % 8], r+2), 6);
	K[(6 * r + 3) % 8] = rot(K[(6 * r + 3) % 8] + rot(delta[r % 8], r+3), 11);
	K[(6 * r + 4) % 8] = rot(K[(6 * r + 4) % 8] + rot(delta[r % 8], r+4), 13);
	K[(6 * r + 5) % 8] = rot(K[(6 * r + 5) % 8] + rot(delta[r % 8], r+5), 17);
	RK[0] = K[(6 * r + 0) % 8];
	RK[1] = K[(6 * r + 1) % 8];
	RK[2] = K[(6 * r + 2) % 8];
	RK[3] = K[(6 * r + 3) % 8];
	RK[4] = K[(6 * r + 4) % 8];
	RK[5] = K[(6 * r + 5) % 8];
	
	// Round_encrypt
	tmp = X[0];
	X[0] = rot((X[0] ^ RK[0]) + (X[1] ^ RK[1]), 9);
	X[1] = rot((X[1] ^ RK[2]) + (X[2] ^ RK[3]), 27);
	X[2] = rot((X[2] ^ RK[4]) + (X[3] ^ RK[5]), 29);
	X[3] = tmp;
}

void LEA_128() {
	uint P[4];
	uint K[4];

	// KISA LEA-128 Test Vector
	K[0] = 0x0f1e2d3c;
	K[1] = 0x4b5a6978;
	K[2] = 0x8796a5b4;
	K[3] = 0xc3d2e1f0;
	P[0] = 0x10111213;
	P[1] = 0x14151617;
	P[2] = 0x18191a1b;
	P[3] = 0x1c1d1e1f;

	printf("P : ");
	show_array(P, 4);

	printf("K : ");
	show_array(K, 4);

	flip_array(K, 4);
	flip_array(P, 4);

	// Encryption
	for(int round = 0; round < NR_128; round++)
		round_enc_128(P, K, round);
	inv_flip_array(P, 4);
	
	printf("C : ");
	show_array(P, 4);
}


void LEA_192() {
	uint P[4];
	uint K[6];
	
	// KISA LEA-196 Test Vector
	K[0] = 0x0f1e2d3c;
	K[1] = 0x4b5a6978;
	K[2] = 0x8796a5b4;
	K[3] = 0xc3d2e1f0;
	K[4] = 0xf0e1d2c3;
	K[5] = 0xb4a59687;
	P[0] = 0x20212223;
	P[1] = 0x24252627;
	P[2] = 0x28292a2b;
	P[3] = 0x2c2d2e2f;

	printf("P : ");
	show_array(P, 4);
	printf("K : ");
	show_array(K, 6);

	flip_array(K, 6);
	flip_array(P, 4);

	// Encryption
	for (int round = 0; round < NR_192; round++)
		round_enc_192(P, K, round);
	inv_flip_array(P, 4);

	printf("C : ");
	show_array(P, 4);
}

void LEA_256() {
	uint P[4];
	uint K[8];

	// KISA LEA-256 Test Vector
	K[0] = 0x0f1e2d3c;
	K[1] = 0x4b5a6978;
	K[2] = 0x8796a5b4;
	K[3] = 0xc3d2e1f0;
	K[4] = 0xf0e1d2c3;
	K[5] = 0xb4a59687;
	K[6] = 0x78695a4b;
	K[7] = 0x3c2d1e0f;
	P[0] = 0x30313233;
	P[1] = 0x34353637;
	P[2] = 0x38393a3b;
	P[3] = 0x3c3d3e3f;

	printf("P : ");
	show_array(P, 4);
	printf("K : ");
	show_array(K, 8);

	flip_array(K, 8);
	flip_array(P, 4);

	// Encryption
	for (int round = 0; round < NR_256; round++)
		round_enc_256(P, K, round);
	inv_flip_array(P, 4);

	printf("C : ");
	show_array(P, 4);
}

int main() {
	printf("\n[*] LEA 128\n");
	LEA_128();
	
	printf("\n[*] LEA 192\n");
	LEA_192();
	
	printf("\n[*] LEA 256\n");
	LEA_256();
	
	return 0;
}


// EOF

