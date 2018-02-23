all:
#	gcc -Wall -O2 -o identify_w83877f identify_w83877f.c
	gcc -Wall -O2 -o extadp_test extadp_test.c
	size identify_w83877f extadp_test
