#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
////#include "soal_common.c"
//
extern int datainput_1[999],datainput_2[999],datainput_3[999];
extern int number_data;
extern char *txtResult;
extern char datain1[200],dataraw[999][200];
//
typedef struct{
 char **Input1;
 char **Input2;
 char **Input3;
 int ndata;
} dataInput;
//
char* replaceWordInString(const char* s, const char* oldW, const char* newW);

char *trim(char *s);
//
char *shift_trim(char *s);

//void read_file(char *namafile);

void get_data_from_rawdata();

//void save_data_file(char *namafile, dataInput datatulis);

char *IntToStr(int x);

int c_round(double x);

double c_modulus(double a,double b);

int isGanjil(int num);
