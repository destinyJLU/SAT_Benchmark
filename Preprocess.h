#ifndef Preprocess_h
#define Preprocess_h
#define MAX_CLAUSE 2000
#define MAX_VAR 1000
void er_usage();//WTF?
void RandomGenerationSATProblem( char* problemfile, int clauseNum, int valNum,
								int max_length, int min_length);//生成随机SAT文件
void LoadClauses( char *infile, int **clauses, int *clause_length, int &num_clauses,
				  int &num_vars );//导入文件
// 文件名，子句集二维数组保存，子句长度数组保存（每个元素为第i个子句的长度），子句个数，变量个数
#endif
