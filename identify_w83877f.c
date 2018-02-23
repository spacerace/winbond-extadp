#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <asm/io.h>
#include <sys/perm.h>
#define MAGIC0	0x86
#define MAGIC1	0x87
#define MAGIC2	0x88
#define MAGIC3  0x89

#define EFER0	0x250
#define EFIR0	0x251
#define EFDR0	0x252

#define EFER1	0x3F0
#define EFIR1	0x3F0
#define EFDR1	0x3F1

#define CR9	0x09

int main() {
	unsigned char temp;
	int method = -1;

	printf("trying to detect w83877f by trying all 4 access methods to get chip ID...\n");


	ioperm(EFER0, 3, 1);
	ioperm(EFER1, 2, 1);
	
	printf(" try 0: [ 0x89=>0x250 ] ...\n");
	outb(0x89, 0x250);	// 0x89 to 0x250 (unlock);
	outb(CR9, 0x251);	// we want CR9, place it in index
	temp = inb(0x252);	// get data from CR9
	printf(" try 0: CR9=0x%02x ", temp);
	if((temp & 0x0F) != 0x0A) printf("ID != 0x0A, failed.\n");
	else { 
		printf("try0 succeeded.\n");
		method = 0;
		goto found_w83877f;
	}

	printf(" try 1: [ 0x88=>0x250 ] ...\n");
	outb(0x88, 0x250);
	outb(CR9, 0x251);
	temp = inb(0x252);
	printf(" try 1: CR9=0x%02x ", temp);
	if((temp & 0x0F) != 0x0A) printf("ID != 0x0A, failed.\n");
	else {
		printf("try1 succeeded.\n");
		method = 1;
		goto found_w83877f;
	}

	printf(" try 2: [ 0x86=>0x3F0 twice ] ...\n");
	outb(0x86, 0x3F0);
	outb(0x86, 0x3F0);
	outb(CR9, 0x3F0);
	temp = inb(0x3F1);
	printf(" try 2: CR9=0x%02x ", temp);
	if((temp & 0x0F) != 0x0A) printf("ID != 0x0A, failed.\n");
	else { 
		printf("try2 succeeded.\n");
		method = 2;
		goto found_w83877f;
	}

	printf(" try 3: [ 0x87=>0x3F0 twice ] ...\n");
	outb(0x87, 0x3F0);
	outb(0x87, 0x3F0);
	outb(CR9, 0x3F0);
	temp = inb(0x3F1);
	printf(" try 3: CR9=0x%02x ", temp);	
	if((temp & 0x0F) != 0x0A) printf("ID != 0x0A, failed.\n");
	else {
		printf("try3 succeeded.\n");
		method = 3;
		goto found_w83877f;
	}

	printf(" >>>>> NO W83877F FOUND IN YOUR SYSTEM <<<<<\n");
	exit(-1);

found_w83877f:
	printf(" >>>>> W83877F FOUND AT ");
	if(method < 2) printf("0x250-0x252 <<<<<\n");
	else           printf("0x3F0-0x3F1 <<<<<\n");

	exit(0);

	return 0;
}
