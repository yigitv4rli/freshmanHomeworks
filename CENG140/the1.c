#include "loop.h"
#include <stdio.h>
#include <stdlib.h>

char curr_variable;
int curr_start, curr_end, curr_step;
char variables[52];
int start_values[52], end_values[52], step_sizes[52], curr_values[52];
int curr_loop = 0;

int loop_variable_value(char c);
void loop_continue(char c);


// Using for loop to find index in variables, then curr_values[index] = loop variable value (WORKS)
int loop_variable_value(char c) {
    int index;

    for (index = 0; index < curr_loop; index++) {
        if (variables[index] == c) {
            return curr_values[index];
        }
    }
}

// Pointer make sense since we are changing the values? 
int next_value(char c) {
    int index;
    
    if (variables[0] == c) {
        if (curr_values[0] + step_sizes[0] > end_values[0]) {
                return 'signal';
        } else {
            curr_values[0] += step_sizes[0];
        }
    }

    for (index = 1; index < curr_loop; index++) {
        int i;

        if (variables[index] == c) {
            if (curr_values[index] + step_sizes[index] > end_values[index]){
                curr_values[index] = start_values[index];
                curr_values[index -1] = next_value(variables[index-1]);

            } else {
                curr_values[index] += step_sizes[index];
            }
            
        }
    }
    return 
}

void loop_continue(char c) {
    
}

int check_conditions(int start, int end, int step) {
    if (start > end && step > 0) {
        return 1;
    } else if (start < end && step < 0) {
        return 1;
    } else {
        return 0;
    }
}



int main() {



    while (1) {
       int ch = getchar();
       if(ch == EOF) {
          break;

       } else {
          ungetc(ch, stdin);
       }

       scanf(" %c", &curr_variable);
       variables[curr_loop] = curr_variable;

       scanf(" %d %d %d", &curr_start, &curr_end, &curr_step);
       if (check_conditions(curr_start, curr_end, curr_step) == 1) {
           goto finish;

       } else { 
            start_values[curr_loop] = curr_start;
            end_values[curr_loop] = curr_end;
            step_sizes[curr_loop] = curr_step;
            curr_values[curr_loop] = curr_start;
            curr_loop++;
       }
    }



    finish:
        printf("Something happened\n");

    return 0;
}
