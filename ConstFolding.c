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
#include "InstrUtils.h"
#include "Utils.h"

void OptimizeConstFolding(Instruction *i1, Instruction *i2, Instruction *i3){
    if(i1->opcode == LOADI && i2->opcode == LOADI){ //Found two consecutive LOADI instructions
        
        if((i3->opcode == ADD || i3->opcode == SUB || i3->opcode == MUL) && i1->field2 == i3->field1 && i2->field2 == i3->field2){ //Found OP
            int a = i1->field1;
            int b = i2->field1;
            int c;
            
            if(i3->opcode == ADD)
                c = a + b;
            else if(i3->opcode == SUB)
                c = a - b;
            else
                c = a * b;
                        
            i1->field1 = c;
            i1->field2 = i3->field3;
            i1->next = i3->next;
            
            free(i2);
            free(i3);
            
            if(i1->next != NULL)
                i1->next->prev = i1;
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
        while(ptr->next->next != NULL){
            OptimizeConstFolding(ptr, ptr->next, ptr->next->next);
            ptr = ptr->next;
        }

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

