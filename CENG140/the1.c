#include "loop.h"
#include <stdio.h>
#include <stdlib.h>

char curr_variable;
int curr_start, curr_end, curr_step;
char variables[255];
int start_values[255], end_values[255], step_sizes[255], curr_values[255];
int curr_loop = 0;
int compare[1];


void loop_execute(void){
    printf("X:%d r:%d Y:%d\n",
           loop_variable_value('X'),
           loop_variable_value('r'),
           loop_variable_value('Y'));
    if ((loop_variable_value('X')+loop_variable_value('r')+loop_variable_value('Y')) % 5 == 0) { 
        printf("JUST MAGIC OF FIVE HAPPENED!...Continuing with next ’r’ value.\n");
        loop_continue('r'); 
    }
}


int side_finder(int a) { // (WORKS)
    if (start_values[a] > end_values[a]) {
        return 0;
    } else if (start_values[a] < end_values[a]) {
        return 1;
    }
}

// Using for loop to find index in variables, then curr_values[index] = loop variable value (WORKS)
int loop_variable_value(char c) {
    int index;

    for (index = 0; index < curr_loop; index++) {
        if (variables[index] == c) {
            return curr_values[index];
        }
    }
}

// Pointer make sense since we are changing the values? Or can we use arrays as pointers since it include pointers
void next_value(char c) {
    int index;
    compare[0] = 1;
    
    if (variables[0] == c) {
        curr_values[0] += step_sizes[0];
    }

    for (index = 1; index < curr_loop; index++) {
        if (variables[index] == c) {
            if (side_finder(index) == 1) {
                if (curr_values[index] + step_sizes[index] > end_values[index]) {
                    curr_values[index] = start_values[index];
                    next_value(variables[index-1]);
                } else {
                    curr_values[index] += step_sizes[index];
                }
            } else if (side_finder(index) == 0) {
                if (curr_values[index] + step_sizes[index] < end_values[index]) {
                    curr_values[index] = start_values[index];
                    next_value(variables[index-1]);
                } else {
                    curr_values[index] += step_sizes[index];
                }
            }
        }
    }
}

void loop_continue(char c) {  // Check this func
    int index;

    for (index = 0; index < curr_loop; index++) {
        if (variables[index] == c) {
            int i;
            for (i = index+1; i < curr_loop; i++) {
                curr_values[i] = start_values[i];
            }
        }
    }
    next_value(c);
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

// Main function starts
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

    curr_loop--;
    
    while (1) {
        if (side_finder(0) == 1 && curr_values[0] > end_values[0]) {
            break;
        } else if (side_finder(0) == 0 && curr_values[0] < end_values[0]) {
            break;
        } else {
            loop_execute();
            if (compare[0] != 1) {
                next_value(variables[curr_loop-1]);
            }
        compare[0] = 0;
        }
    }

    finish:
        return 0;
    return 0;
}
