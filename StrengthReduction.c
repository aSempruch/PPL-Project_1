/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2017                                *
 *  Author: Uli                              *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "InstrUtils.h"
#include "Utils.h"

int logb2(double num){
    int result = 0;
    while((int)num > 1){
        num = num/2;
        result++;
    }
    return result;
}

void Optimize(Instruction *i1, Instruction *i2, Instruction *i3){
    
    if(i1->opcode == LOADI){ //Found LOADI operation
        int val = i1->field1;
        
        if(val && (!(val&(val-1)))){ //val is a power of 2
            if(i2->opcode == DIV){ //DIV detected - performing optimization
                int log = logb2((double)i1->field1);
                i1->opcode = RSHIFTI;
                i1->field1 = i2->field1;
                i1->field2 = log;
                i1->field3 = i2->field3;
            }
            else if(i2->opcode == MUL) { //MUL detected - performing optimization
                int log = logb2((double)i1->field1);
                i1->opcode = LSHIFTI;
                i1->field1 = i2->field1;
                i1->field2 = log;
                i1->field3 = i2->field3;
            }
            free(i2);
            i1->next = i3;
            if(i3 != NULL)
                i3->prev = i1;
        }
    }
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	Instruction *ptr = head;
        
        /*while(ptr->next != NULL){
            Optimize(ptr, ptr->next, ptr->next->next);
            ptr = ptr->next;
        }*/

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

