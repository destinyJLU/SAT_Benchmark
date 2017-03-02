#ifndef LongInt_h
#define LongInt_h
#define MAX_LENGTH_INT 5
#define OVERFLOW_INT 1073741824
#define LENGTH_BIT 30
#define CLASS_BIT long
extern CLASS_BIT code_int[LENGTH_BIT];
struct LongInt
{
	bool sign;
	bool zero;
	CLASS_BIT digit[MAX_LENGTH_INT];
};
int Cmp_LongInt(LongInt *a, LongInt *b);//absolute value compare
void Add_LongInt(LongInt *a, LongInt *b);
void Dec_LongInt(LongInt *a, LongInt *b);
void Add_LongInt(LongInt *a, int b);
void Mult_LongInt(LongInt *a, int b);
void Print_LongInt(LongInt *a);
#endif
