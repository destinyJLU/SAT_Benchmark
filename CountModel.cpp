#include "CountModel.h"
#include "LongInt.h"
#include "mersenne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Mersenne rng;
int DG_number=0;
int **l_clauses;
int *l_clause_length;
int l_num_clauses;
int l_num_vars;
int number=0;
int *l_assigned;
int *l_decision_stack;
int l_num_decision_stack;
bool *l_assigned_c;
int *l_decision_stack_c;
int l_num_decision_stack_c;
int var_weight[1000] = {0};
int clause_weight[2000] = {0};
MemberList **l_pos_c_in_clause_start;
MemberList **l_pos_c_in_clause_end;
MemberList **l_neg_c_in_clause_start;
MemberList **l_neg_c_in_clause_end;
void initialize( int **clauses, int *clause_length, int num_clauses, int num_vars )
{
	int i, j, weight;
	l_num_vars = num_vars;
	l_num_clauses = num_clauses;
	l_clauses = new int *[l_num_clauses];
	l_clause_length = new int [l_num_clauses];
	for ( i = 0; i < l_num_clauses; i++ ) {
		l_clauses[i] = new int [l_num_vars];
		l_clause_length[i] = 0;
	}

	l_assigned = new int [l_num_vars+1];
	for ( i = 0; i < l_num_vars+1; i++ ) {
		l_assigned[i] = -1;
	}
	l_decision_stack = new int [l_num_vars];
	l_num_decision_stack = 0;
	l_assigned_c = new bool [l_num_clauses];
	for ( i = 0; i < l_num_clauses; i++ ) {
		l_assigned_c[i] = false;
	}
	l_decision_stack_c = new int [l_num_clauses];
	l_num_decision_stack_c = 0;
	l_pos_c_in_clause_start = new MemberList *[l_num_vars+1];
	l_pos_c_in_clause_end = new MemberList *[l_num_vars+1];
	l_neg_c_in_clause_start = new MemberList *[l_num_vars+1];
	l_neg_c_in_clause_end = new MemberList *[l_num_vars+1];
	for ( i = 0; i <= l_num_vars; i++ ) {
		l_pos_c_in_clause_start[i] = NULL;
		l_neg_c_in_clause_start[i] = NULL;
		l_pos_c_in_clause_end[i] = NULL;
		l_neg_c_in_clause_end[i] = NULL;
	}

	for ( i = 0; i < num_clauses; i++ ) {
		for ( j = 0; j < clause_length[i]; j++ ) {
			l_clauses[i][j] = clauses[i][j];
			var_weight[abs(clauses[i][j])]++;
		}
		l_clause_length[i] = clause_length[i];
	}
	for ( i = 0; i < num_clauses; i++ ) {
	    weight = 0;
		for ( j = 0; j < clause_length[i]; j++ ) {
                weight += var_weight[abs(clauses[i][j])];
		}
		clause_weight[i] = weight;
	}
	do_membership_lists();

	if ( 0 ) {
		Print_clauses( clauses, clause_length, num_clauses );
		Print_all_MemberList();
	}
}
void do_membership_lists()
{
	int i, j, v;

	for ( i = 1; i <= l_num_vars; i++ ) {
		l_pos_c_in_clause_start[i] = new MemberList;
		l_pos_c_in_clause_start[i]->clause = -1;
		l_pos_c_in_clause_end[i] = new MemberList;
		l_pos_c_in_clause_end[i]->clause = -1;
		l_pos_c_in_clause_start[i]->next = l_pos_c_in_clause_end[i];
		l_neg_c_in_clause_start[i] = new MemberList;
		l_neg_c_in_clause_start[i]->clause = -1;
		l_neg_c_in_clause_end[i] = new MemberList;
		l_neg_c_in_clause_end[i]->clause = -1;
		l_neg_c_in_clause_start[i]->next = l_neg_c_in_clause_end[i];
	}
	for ( i = l_num_clauses - 1; i >= 0; i-- ) {
		for ( j = 0; j < l_clause_length[i]; j++ ) {
			if ( l_clauses[i][j] > 0 ) {
				v = l_clauses[i][j];
				if ( l_pos_c_in_clause_end[v]->clause == -1 ) {
					l_pos_c_in_clause_end[v]->clause = i;
					l_pos_c_in_clause_end[v]->next = new MemberList;
					l_pos_c_in_clause_end[v]->next->clause = -1;
					l_pos_c_in_clause_end[v] = l_pos_c_in_clause_end[v]->next;
				}
				else {
					l_pos_c_in_clause_end[v]->clause = i;
					l_pos_c_in_clause_end[v] = l_pos_c_in_clause_end[v]->next;
				}
			}
			else {
				v = -l_clauses[i][j];
				if ( l_neg_c_in_clause_end[v]->clause == -1 ) {
					l_neg_c_in_clause_end[v]->clause = i;
					l_neg_c_in_clause_end[v]->next = new MemberList;
					l_neg_c_in_clause_end[v]->next->clause = -1;
					l_neg_c_in_clause_end[v] = l_neg_c_in_clause_end[v]->next;
				}
				else {
					l_neg_c_in_clause_end[v]->clause = i;
					l_neg_c_in_clause_end[v] = l_neg_c_in_clause_end[v]->next;
				}
			}
		}
	}
}
void Print_all_MemberList()
{
	printf( "Positive MemberList\n" );
	for ( int i = 1; i <= l_num_vars; i++ ) {
		printf( "%3d : ", i );
		MemberList *ml = l_pos_c_in_clause_start[i]->next;
		while ( ml->clause != -1 ) {
			printf( "%3d", ml->clause );
			ml = ml->next;
		}
		printf( "\n" );
	}
	printf( "Negative MemberList\n" );
	for (int i = 1; i <= l_num_vars; i++ ) {
		printf( "%3d : ", -i );
		MemberList *ml = l_neg_c_in_clause_start[i]->next;
		while ( ml->clause != -1 ) {
			printf( "%3d", ml->clause );
			ml = ml->next;
		}
		printf( "\n" );
	}
}
int MAX(int *length,int num)
{
    int M=0;
    for(int i=0;i<num;i++)
    {
        if(length[i]>=M)
            M = length[i];
    }
    return M;
}
void count( LongInt *mc )
{
    DG_number++;
	int entry_num_decision_stack = l_num_decision_stack;
	int entry_num_decision_stack_c = l_num_decision_stack_c;
	int i, v, dec_c,p=0,q,w=0;

	if ( l_num_decision_stack_c == l_num_clauses ) {
		Add_LongInt( mc, l_num_vars - l_num_decision_stack );
		return;
	}
	// with SP
//	if(rng.next(10)+1 <= 8)
//    {
//        for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
//            if(l_assigned_c[dec_c] == false && clause_weight[dec_c]>=p)
//            {
//                p = clause_weight[dec_c];
//                q = dec_c;
//            }
//        }
//        dec_c = q;
//    }
//    else
//    {
//        //NCER_LC
//        for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
//            if(l_assigned_c[dec_c] == false && l_clause_length[dec_c]>=p)
//            {
//                p = l_clause_length[dec_c];
//                q = dec_c;
//            }
//        }
//        dec_c = q;
//    }


//    NCER_GW
//    for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
//        if(l_assigned_c[dec_c] == false && clause_weight[dec_c]>=p)
//        {
//            p = clause_weight[dec_c];
//            q = dec_c;
//        }
//    }
//    dec_c = q;

    //NCER_LC & NCER_GW
    for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
        if(l_assigned_c[dec_c] == false)
        {
            if(l_clause_length[dec_c]>=p || (l_clause_length[dec_c]==p && clause_weight[dec_c]>=w))
            {
                p = l_clause_length[dec_c];
                w = clause_weight[dec_c];
                q = dec_c;
            }
        }
    }
    dec_c = q;

//        //NCER_LC
//        for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
//            if(l_assigned_c[dec_c] == false && l_clause_length[dec_c]>p)
//            {
//                p = l_clause_length[dec_c];
//                q = dec_c;
//            }
//        }
//        dec_c = q;

	//SHARP_ER

//	for ( dec_c = 0; dec_c < l_num_clauses; dec_c++ ) {
//		if(l_assigned_c[dec_c] == false)
//        {
//            break;
//        }
//	}



	l_assigned_c[dec_c] = true;
	//dec_c 加入子句决策栈
	l_decision_stack_c[l_num_decision_stack_c++] = dec_c;
	//对dec_C子句中的未指派的变量进行指派
	for ( i = 0; i < l_clause_length[dec_c]; i++ ) {
		v = l_clauses[dec_c][i];
		if ( v > 0 && l_assigned[v] == -1 ) {
			l_assigned[v] = 0;
			l_decision_stack[l_num_decision_stack++] = -v;
		}
		else if ( v < 0 && l_assigned[-v] == -1 ) {
			l_assigned[-v] = 1;
			l_decision_stack[l_num_decision_stack++] = -v;
		}
	}
	LongInt a;
	a.zero = true;
	if ( do_unit_props( entry_num_decision_stack ) ) {
		count(&a);
	}
	for ( i = entry_num_decision_stack; i < l_num_decision_stack; i++ ) {
		if ( l_decision_stack[i] < 0 ) {
			v = -l_decision_stack[i];
		} else {
			v = l_decision_stack[i];
		}
		l_assigned[v] = -1;
	}
	l_num_decision_stack = entry_num_decision_stack;
	for ( i = entry_num_decision_stack_c+1; i < l_num_decision_stack_c; i++ ) {
		l_assigned_c[l_decision_stack_c[i]] = false;
	}
	l_num_decision_stack_c = entry_num_decision_stack_c+1;

	LongInt b;
	b.zero = true;
	count(&b);
	for ( i = entry_num_decision_stack; i < l_num_decision_stack; i++ ) {
		if ( l_decision_stack[i] < 0 ) {
			v = -l_decision_stack[i];
		} else {
			v = l_decision_stack[i];
		}
		l_assigned[v] = -1;
	}
	l_num_decision_stack = entry_num_decision_stack;
	for ( i = entry_num_decision_stack_c; i < l_num_decision_stack_c; i++ ) {
		l_assigned_c[l_decision_stack_c[i]] = false;
	}
	l_num_decision_stack_c = entry_num_decision_stack_c;
	Dec_LongInt( mc, &a );
	Add_LongInt( mc, &b );
}
bool do_unit_props( int startidx )
{
	int idx, i, v, c, v_, numopenlits, lastopen;
	MemberList *i_ml;

	idx = startidx;
	while ( idx < l_num_decision_stack ) {
		if ( l_decision_stack[idx] < 0 ) {
			v = -l_decision_stack[idx];
			i_ml = l_neg_c_in_clause_start[v]->next;
			while (i_ml->clause != -1 ) {
				int c = i_ml->clause;
				if( l_assigned_c[c] == 0 ) {
					l_assigned_c[c] = 1;
					l_decision_stack_c[l_num_decision_stack_c++] = c;
				}
				i_ml = i_ml->next;
			}
			for ( i_ml = l_pos_c_in_clause_start[v]->next;
			i_ml != l_pos_c_in_clause_end[v]; i_ml = i_ml->next ) {
				if ( l_assigned_c[i_ml->clause] == 1 ) continue;//!!
				c = i_ml->clause;
				numopenlits = 0;
				lastopen = 0;
				for ( i = 0; i < l_clause_length[c]; i++ ) {
					if ( numopenlits > 1 ) break;
					if ( l_clauses[c][i] > 0 ) {
						v_ = l_clauses[c][i];
						if ( l_assigned[v_] == -1 ) {
							numopenlits++;
							lastopen = l_clauses[c][i];
						}
						if ( l_assigned[v_] == 1 ) {
							break;
						}
					} else {
						v_ = -l_clauses[c][i];
						if ( l_assigned[v_] == -1 ) {
							numopenlits++;
							lastopen = l_clauses[c][i];
						}
						if ( l_assigned[v_] == 0 ) {
							break;
						}
					}
				}
				if ( i < l_clause_length[c] ) {
					continue;
				}
				if ( numopenlits == 0 ) {
					return false;
				}
				if ( numopenlits == 1 ) {
					if ( lastopen > 0 ) {
						l_assigned[lastopen] = 1;
					} else {
						l_assigned[-lastopen] = 0;
					}
					l_decision_stack[l_num_decision_stack++] = lastopen;
				}
			}
		} else {
			v = l_decision_stack[idx];
			i_ml = l_pos_c_in_clause_start[v]->next;
			while (i_ml->clause != -1 ) {
				int c = i_ml->clause;
				if( l_assigned_c[c] == 0 ) {
					l_assigned_c[c] = 1;
					l_decision_stack_c[l_num_decision_stack_c++] = c;
				}
				i_ml = i_ml->next;
			}
			for ( i_ml = l_neg_c_in_clause_start[v]->next;
			i_ml != l_neg_c_in_clause_end[v]; i_ml = i_ml->next ) {
				if ( l_assigned_c[i_ml->clause] == 1 ) continue;
				c = i_ml->clause;
				numopenlits = 0;
				lastopen = 0;
				for ( i = 0; i < l_clause_length[c]; i++ ) {
					if ( numopenlits > 1 ) break;
					if ( l_clauses[c][i] > 0 ) {
						v_ = l_clauses[c][i];
						if ( l_assigned[v_] == -1 ) {
							numopenlits++;
							lastopen = l_clauses[c][i];
						}
						if ( l_assigned[v_] == 1 ) {
							break;
						}
					} else {
						v_ = -l_clauses[c][i];
						if ( l_assigned[v_] == -1 ) {
							numopenlits++;
							lastopen = l_clauses[c][i];
						}
						if ( l_assigned[v_] == 0 ) {
							break;
						}
					}
				}
				if ( i < l_clause_length[c] ) {
					continue;
				}
				if ( numopenlits == 0 ) {
					return false;
				}
				if ( numopenlits == 1 ) {
					if ( lastopen > 0 ) {
						l_assigned[lastopen] = 1;
					} else {
						l_assigned[-lastopen] = 0;
					}
					l_decision_stack[l_num_decision_stack++] = lastopen;
				}
			}
		}
		idx++;
  }
  return true;
}
void Print_clauses( int **clauses, int *clause_length, int num_clauses )
{
	printf( "All the clauses\n" );
	for ( int i = 0; i < num_clauses; i++ ) {
		printf( "%3d : ", i );
		for ( int j = 0; j < clause_length[i]; j++ ) {
			printf( "%3d", clauses[i][j] );
		}
		printf( "\t -> len = %d\n", clause_length[i]);
	}
}
void Print_complementary_factor()
{
    int i,j,k;
	printf( "Comlementary factor : " );
	long num = 0;
	bool pos[1000];
	bool neg[1000];
	for ( i = 0; i < l_num_clauses; i++ ) {
		for ( j = 0; j < l_num_vars; j++ ) {
			pos[j] = false;
			neg[j] = false;
		}
		for ( j = 0; j < l_clause_length[i]; j++ ) {
			int v = l_clauses[i][j];
			if ( v > 0 ) pos[v] = true;
			else neg[-v] = true;
		}
		for ( j = 0; j < i; j++ ) {
			for (  k = 0; k < l_clause_length[j]; k++ ) {
				int v = l_clauses[j][k];
				if ( v > 0 && neg[v] ) {
					num++;
					break;
				}
				else if ( v < 0 && pos[-v] ) {
					num++;
					break;
				}
			}
		}
	}
	printf( "%f\n", 2.0 * num / (l_num_clauses * ( l_num_clauses-1 ) ) );
}
