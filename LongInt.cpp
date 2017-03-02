#include "LongInt.h"
#include <stdio.h>
int gn = 1;
int Cmp_LongInt(LongInt *a, LongInt *b)//absolute value compare
{
	for(int i = MAX_LENGTH_INT-1; i >= 0; i--)
	{
		if(a->digit[i] > b->digit[i])
			return 1;
		if(a->digit[i] < b->digit[i])
			return -1;
	}
	return 0;
}
void Add_LongInt(LongInt *a, LongInt *b)
{
    int i;
	if((a->zero) || (b->zero))
	{
		if(b->zero) return;
		else
		{
			a->sign = b->sign;
			a->zero = false;
			for(int i = 0; i <  MAX_LENGTH_INT; i++)
				a->digit[i] = b->digit[i];
		}
	}
	else if((a->sign && b->sign) || (!a->sign && !b->sign))
	{
		for(i = 0; i <  MAX_LENGTH_INT; i++)
		{
			a->digit[i] = a->digit[i] + b->digit[i];
			if(a->digit[i] >= OVERFLOW_INT)
			{
				a->digit[i+1]++;
				a->digit[i] -= OVERFLOW_INT;
			}
		}
	}
	else
	{
		int flag = Cmp_LongInt(a, b);
		if( flag == 0) a->zero = true;
		if( flag > 0)
		{
			for(i = 0; i <  MAX_LENGTH_INT; i++)
			{
				a->digit[i] = a->digit[i] - b->digit[i];
				if(a->digit[i] < 0)
				{
					a->digit[i+1]--;
					a->digit[i] += OVERFLOW_INT;
				}
			}
		}
		else
		{
			a->sign = b->sign;
			for(i = 0; i <  MAX_LENGTH_INT; i++)
			{
				a->digit[i] = b->digit[i] - a->digit[i];
				if(a->digit[i] < 0)
				{
					b->digit[i+1]--;
					a->digit[i] += OVERFLOW_INT;
				}
			}
		}
		for(i = 0; i <  MAX_LENGTH_INT; i++)
		{
			if(a->digit[i]) break;
		}
		if( i == MAX_LENGTH_INT) a->zero = true;
	}
	//Print_LongInt(a);
}
void Dec_LongInt(LongInt *a, LongInt *b)
{
    int i;
	if((a->zero) || (b->zero))
	{
		if(b->zero) return;
		else
		{
			a->sign = !b->sign;
			a->zero = false;
			for(int i = 0; i <  MAX_LENGTH_INT; i++)
				a->digit[i] = b->digit[i];
		}
	}
	else if((a->sign && !b->sign) || (!a->sign && b->sign))
	{
		for(i = 0; i <  MAX_LENGTH_INT; i++)
		{
			a->digit[i] = a->digit[i] + b->digit[i];
			if(a->digit[i] >= OVERFLOW_INT)
			{
				a->digit[i+1]++;
				a->digit[i] -= OVERFLOW_INT;
			}
		}
	}
	else
	{
		int flag = Cmp_LongInt(a, b);
		if( flag == 0) a->zero = true;
		if( flag > 0)
		{
			for(i = 0; i <  MAX_LENGTH_INT; i++)
			{
				a->digit[i] = a->digit[i] - b->digit[i];
				if(a->digit[i] < 0)
				{
					a->digit[i+1]--;
					a->digit[i] += OVERFLOW_INT;
				}
			}
		}
		else
		{
			a->sign = !b->sign;
			for(i = 0; i <  MAX_LENGTH_INT; i++)
			{
				a->digit[i] = b->digit[i] - a->digit[i];
				if(a->digit[i] < 0)
				{
					b->digit[i+1]--;
					a->digit[i] += OVERFLOW_INT;
				}
			}
		}
		for(i = 0; i <  MAX_LENGTH_INT; i++)
		{
			if(a->digit[i]) break;
		}
		if(i == MAX_LENGTH_INT) a->zero = true;
	}
	//Print_LongInt(a);
}
void Add_LongInt(LongInt *a, int b)
{
	// debug
	//printf("%4d : %d\n", gn++, b);
	int i;
	for(i = 0; b >= LENGTH_BIT; i++)
	{
		b -= LENGTH_BIT;
	}
	if(a->zero)
	{
		a->zero = false;
		a->sign = true;
		for(int j = 0; j <  MAX_LENGTH_INT; j++)
			a->digit[j] = 0;
		a->digit[i] = code_int[b];
	}
	else
	{
		a->digit[i] += code_int[b];
		while(i < MAX_LENGTH_INT - 1)
		{
			if(a->digit[i] >= OVERFLOW_INT)
			{
				a->digit[i] -= OVERFLOW_INT;
				i++;
				a->digit[i]++;
			}
			else break;
		}

	}
}
void Mult_LongInt(LongInt *a, int b)
{
	/*/debug
	printf("%4d : %d\n", gn++, b);
	//*/
	int i,j;
	for(i = 0; b >= LENGTH_BIT; i++)
	{
		b -= LENGTH_BIT;
	}
	if(!a->zero)
	{
		for (j = MAX_LENGTH_INT - i - 1; j > 0; j-- )
		{
			a->digit[j] = a->digit[j] << b;
			a->digit[j] += a->digit[j-1] >> ( LENGTH_BIT - b );
		}
		a->digit[0] = a->digit[0] << b;
		for ( j = MAX_LENGTH_INT - i - 1; j >= 0 ; j-- )
		{
			a->digit[j+i] = a->digit[j];
		}
		for ( j = i - 1; j >= 0; j-- ) {
			a->digit[j] = 0;
		}
	}
}
void Print_LongInt(LongInt *a)
{
	if(a->zero)
	{
		printf("0\n");
		return;
	}
	if(!a->sign)
		printf("-");
	for(int i = 0; i <  MAX_LENGTH_INT; i++)
		printf("%ld\t", a->digit[i]);
	printf("\n");
}
