#include "Preprocess.h"
#include "CountModel.h"
#include "LongInt.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
CLASS_BIT code_int[LENGTH_BIT];
extern int DG_number;
//LENGTH_BIT = 30
int main(int argc, char *argv[])
{
    //extern int DG_number=0;
	//global variable init
	CLASS_BIT aa = 1;
	int i;
	for(i = 0; i < LENGTH_BIT; i++)
	{
		code_int[i] = aa;
		aa *= 2;
	}
    /*
	LongInt a;
	a.zero = false;
	for ( i = 0; i < MAX_LENGTH_INT-1; i++ ) {
		a.digit[i] = i * i +1;
	}
	Mult_LongInt( &a, 50);
	//Print_LongInt( &a );
	/*******************************
	* generation random SAT problem
	********************************/
	int vv ;//var_num
	char filename[200];
    int len;
//	vv = 20;
////    for(len = 30;len <= 100; len= len+10){
////        sprintf(filename,"E:\\%d-%d-%d.txt",vv,len,10);
////        RandomGenerationSATProblem(filename,len,vv,10,3);
////    }
////    vv = 30;
////    for(len = 60;len <= 150; len= len+10){
////        sprintf(filename,"E:\\%d-%d-%d.txt",vv,len,10);
////        RandomGenerationSATProblem(filename,len,vv,10,3);
////    }
    vv = 40;
    for(len = 300;len <= 300; len= len+10){
        sprintf(filename,"E:\\%d-%d-%d.txt",vv,len,10);
        RandomGenerationSATProblem(filename,len,vv,10,1);
    }
////    vv = 50;
////    for(len = 150;len <= 250; len= len+10){
////        sprintf(filename,"E:\\%d-%d-%d.txt",vv,len,10);
////        RandomGenerationSATProblem(filename,len,vv,10,3);
////    }
    return 0;
	//start timing
    //RandomGenerationSATProblem("e:\\30-100-3.txt",100,30,1,3);

//	clock_t tm1,tm2;
//	int interval;
//	/******************
//	* input the problem
//	*******************/
//    char infile[50];
//    FILE *fp=fopen("D:\\lab\\output-V20-L10.csv","w");
//    ifstream in("D:\\lab\\input3.txt");
//    while(!in.eof())
//    {
//        in>>infile;
//        int **clauses = new int *[MAX_CLAUSE];
//        int *clause_length = new int [MAX_CLAUSE];
//        int *var_weight = new int[MAX_VAR];
//        int *clause_weight = new int[MAX_CLAUSE];
//        int num_clauses = 0;
//        int num_vars = 0;
//        for (i = 0; i < MAX_CLAUSE; i++ ) {
//            clauses[i] = new int [MAX_VAR];
//        }
//        LoadClauses( infile, clauses, clause_length, num_clauses, num_vars);
//    //Print_clauses( clauses, clause_length, num_clauses );
//        /******************
//        * solve the problem
//        *******************/
//        tm1 = clock();
//        LongInt l_num_model;
//        initialize( clauses, clause_length, num_clauses, num_vars );
//        count( &l_num_model );
//        Print_LongInt( &l_num_model );
//        printf("the num of model:%ld\n",l_num_model.digit[0]);
//        tm2 = clock();
//        interval=tm2-tm1;
//        printf("Seconds Elasped: ");
//        printf("%f\n",interval/1000.0);
//        Print_complementary_factor();
//        printf("calling number:%ld       %d \n",l_num_model.digit[0],DG_number);
//        fprintf(fp,"%f\t%d\n",interval/1000.0,DG_number);
//        DG_number=0;
//        }
//        fclose(fp);
//        getchar();
//	return 1;
}

