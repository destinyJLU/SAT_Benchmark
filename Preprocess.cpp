#include "Preprocess.h"
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_MAX 32767
using namespace std;
void er_usage()
{
	printf("\nusage of ER SAT solver:\n\n");
	printf("-s the name of the file of SAT problem needed to solve\n");
}
void RandomGenerationSATProblem( char* problemfile, int clauseNum, int valNum,
								int max_length, int min_length)
{
	FILE *out = fopen( problemfile, "w" );
	int x;
	bool symbol;
	bool *pos = new bool[valNum];
	bool *neg = new bool[valNum];

	fprintf( out, "p cnf %d %d\n", valNum, clauseNum );

	srand( (unsigned)time( NULL ) );

	for( int i = 0; i < clauseNum; i++ )
	{
		for(int j = 0; j < valNum+1; j++)
		{
			pos[j] = false;
			neg[j] = false;
		}
		int randLength = rand()%(max_length - min_length + 1) + min_length;
		while(randLength > 0)
		{
			symbol = ( rand()%2 ) ? true : false ;
			x = rand()%valNum + 1;
			if(pos[x] || neg[x])
				continue;
			if ( symbol )
			{
				if(pos[x]) printf("ERROE\n");
				pos[x] = true;
				fprintf( out, "%d ", x );
			}
			else
			{
				if(neg[x]) printf("ERROE\n");
				neg[x] = true;
				fprintf( out, "%d ", -x );
			}
			randLength--;
		}
		fprintf( out, "0\n" );
	}
	fclose(out);
}
/**************************************************************
*
*         load_clauses      в╟тьнд╪Ч
*
***************************************************************/
void LoadClauses( char *infile, int **clauses, int *clause_length, int &num_clauses,
				  int &num_vars)
{
	ifstream fin(infile);
    int i,j,k;
	char ch;
	char str[10];
	fin>>ch;
	if(ch != 'p') {
		printf( "ch != p\n" );
		printf( "ch = %c\n", ch );
		return;
	}
	fin>>str;
	if( strlen( str ) != 3 ) {
		printf( "str != cnf\n" );
		printf( "str = %s\n", str );
		return;
	}
	else if( strlen( str ) == 3 ) {
		if ( str[0] != 'c' || str[1] != 'n' && str[2] != 'f' ) {
			printf( "str != cnf\n" );
			printf( "str = %s\n", str );
			return;
		}
	}
	fin>>num_vars;
	//printf( "num_vars = %d\n", num_vars );
	fin>>num_clauses;
	//printf( "num_clauses = %d\n", num_clauses );
	if( num_clauses == 0 )
		return;
	for(i = 0; i < num_clauses; i++) {
		for(j = 0; j < MAX_VAR; ) {
			fin>>clauses[i][j];
			/*/
			printf( "%d ", clauses[i][j] );
			//*/
			if(clauses[i][j] == 0) break;
			for(k = 0; k < j; k++)
				if(clauses[i][k] == clauses[i][j]) break;
			if(k == j) j++;
		}
		clause_length[i] = j;
		//printf( "len = %d\n", j );
	}
}



