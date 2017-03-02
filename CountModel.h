#ifndef EnumModel_h
#define EnumModel_h
#include "LongInt.h"
struct MemberList
{
	int clause;
	struct MemberList *next;
};
void initialize( int **clauses, int *clause_length, int num_clauses, int num_vars );
void do_membership_lists();
void Print_all_MemberList();
void count( LongInt *mc );
bool do_unit_props( int startidx );
void Print_clauses( int **clauses, int *clause_length, int num_clauses );
void Print_complementary_factor();
#endif
