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
#define CR2	0x02
#define CR0	0x00

int main() {
	unsigned char temp;
	unsigned char reg_cr0, reg_cr9;

	ioperm(EFER1, 2, 1);
	
	printf("unlock w83877f by writing 0x87 to 0x3F0 twice...\n");
	outb(0x87, 0x3F0);
	outb(0x87, 0x3F0);
	outb(CR9, 0x3F0);
	temp = inb(0x3F1);
	printf("CR9=0x%02x ", temp);
	if((temp & 0x0F) != 0x0A) {
		printf("ID != 0x0A, failed.\n");
		exit(-1);
	} else { 
		printf("chip found!\n");
	}

	printf("enabling extadp mode in CR0/CR9\n");
	outb(CR0, 0x3F0);
	reg_cr0 = inb(0x3F1);
	outb(CR9, 0x3F0);
	reg_cr9 = inb(0x3F1);
	
	printf("CR0 was 0x%02x, CR9 was 0x%02x\n", reg_cr0, reg_cr9);

	reg_cr9 &= ~(0x80);	// clear BIT7
	reg_cr0 &= ~(0x04);	// clear BIT2
	reg_cr0 |= 0x08;	// set BIT3

	printf("CR0 will be 0x%02x, CR9 will be 0x%02x\n", reg_cr0, reg_cr9);

	outb(CR0, 0x3F0);
	outb(reg_cr0, 0x3F1);
	outb(CR9, 0x3F0);
	outb(reg_cr9, 0x3F1);

	printf("setting address to 0x380 (CR2=0xE0)...\n");

	outb(CR2, 0x3F0);
	outb(0xE0, 0x3F1);
	
	ioperm(EFER1, 2, 0);

	printf("testing read/write \n");
	ioperm(0x380, 8, 1);
	temp = 0;
	for(;;) {
		if(temp == 0x00) temp = 0x01;
		outb(~temp, 0x380);
		temp = temp << 1;
		usleep(55000);

	}

	return 0;
}
