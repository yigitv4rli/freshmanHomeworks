#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

char inComing[201];
int intervalCount, letterCount = 1;
long int experimentCount;

/*
1) Delete spaces -> DONE 
2) Dijkstra’s algorithm
3) Random number generation with weighted probabilities -> DONE
4) 3 precision for input, may use double for output?  (TAKING AS FLOAT SO 5 PRECISION)
5) Normalizing input probabilty distribution and outcome probabilty distribution since their summation may not equal to 1 ? 


Making struct Value is logical??
*/


/* To Delete Spaces*/
char* spaceDeleter(char* word) {
    int i = 0, j = 0, len;
    char* result;

    result = (char*) malloc(201 * sizeof(char));

    while (word[i]!= '\0') {
        if (word[i] != ' ') {
            result[j] = word[i];
            j++;
            i++;
        } else {
            i++;
        }
    }
    len = strlen(result);
    result = (char*) realloc(result, (len+1) * sizeof(char));

    result[len] = '\0';
    return result;
}

/* 
float float_rand( float min, float max ) {
    float scale = rand() / (float) RAND_MAX;    [0, 1.0] 
    return min + scale * ( max - min );         [min, max]
} 
*/

/* Random Number Generator */
void randomNumbers(float **limits ,int **probArr, float* values, int amount, int numberOfIntervals) {
    int i;

    for (i = 0; i < amount; i++) {
        int interval, numberIndex;
        float normalize, intervalRange, lower, upper, min, max;

        normalize = rand() / (float) RAND_MAX;
        lower = limits[i][0];
        upper = limits[i][1];
        numberIndex = rand() % 1000;
        interval = probArr[i][numberIndex];
        intervalRange = (upper - lower) / numberOfIntervals;
        
        min = lower + ((interval-1) * intervalRange);
        max = lower + (interval * intervalRange);

        values[i] = min + normalize * ( max - min );
        /* printf("min: %f max: %f value: %f, on interval: %d\n", min, max, values[i], interval); */
    }
}



/* 
    s -> sin;
    r -> sqrt;
    l -> ln;
    c -> cos;
*/

int precedenceCompare(char operator) {
    if (operator == 's') return 3;
    else if (operator == 'r') return 3;
    else if (operator == 'l') return 3;
    else if (operator == 'c') return 3;
    else if (operator == '~') return 3;
    else if (operator == '^') return 3;
    else if (operator == '*') return 2;
    else if (operator == '/') return 2;
    else if (operator == '-') return 1;
    else if (operator == '+') return 1;
    else if (operator == '(') return 0;
}


char* infixToPostfix(char* comingFormula) {
    char stack[201];
    int length = strlen(comingFormula), formulaP = 0, resultP = 0, stackP = 0;
    char* result;

    result = (char*) malloc((resultP+1) * sizeof(char*));

    while (formulaP < length) {
        char ch = comingFormula[formulaP];
        if (ch == '(') {
            stack[stackP] = '(';
            stackP++;
            formulaP++;

        } else if (ch == ')') {
            stackP--;
            while (stack[stackP] != '(') {
                result[resultP] = stack[stackP];
                stackP--;
                resultP++;
                result = (char*) realloc(result, (resultP+1) * sizeof(char));
            }
            formulaP++;

        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            if (stackP > 0) {
                if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                    stack[stackP] = ch;
                    stackP++;
                } else {
                    stackP--;
                    result[resultP] = stack[stackP];
                    stack[stackP] = ch;
                    resultP++;
                    stackP++;
                    result = (char*) realloc(result, (resultP+1) * sizeof(char));
                }

            } else {
                stack[stackP] = ch;
                stackP++;
            }
            formulaP++;

        } else if ('0' <= ch && '9' >= ch) {
            result[resultP] = '#';
            resultP++; 
            result = (char*) realloc(result, (resultP+1) * sizeof(char));

            while (('0' <= comingFormula[formulaP] && '9' >= comingFormula[formulaP]) || comingFormula[formulaP] == '.') {
                result[resultP] = comingFormula[formulaP];
                resultP++;
                formulaP++;
                result = (char*) realloc(result, (resultP+1) * sizeof(char));
            }
            result[resultP] = '#';
            resultP++;
            result = (char*) realloc(result, (resultP+1) * sizeof(char));


        } else if (ch == '~' || ch == 's' || ch == 'c' || ch == 'l') {
            if (ch == 's' && comingFormula[formulaP+2] == 'n') { /* IF sinus function */
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = 's';
                        stackP++;
                    } else {
                        stackP--;
                        result[resultP] = stack[stackP];
                        stack[stackP] = 's';
                        resultP++;
                        stackP++;
                        result = (char*) realloc(result, (resultP+1) * sizeof(char));
                    }

                } else {
                    stack[stackP] = 's';
                    stackP++;
                }
                formulaP+=3;


            } else if (ch == 's' && comingFormula[formulaP+2] == 'r') {
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = 'r';
                        stackP++;
                    } else {
                        stackP--;
                        result[resultP] = stack[stackP];
                        stack[stackP] = 'r';
                        resultP++;
                        stackP++;
                        result = (char*) realloc(result, (resultP+1) * sizeof(char));
                    }

                } else {
                    stack[stackP] = 'r';
                    stackP++;
                }
                formulaP+=4;

            } else if (ch == 'c') {
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = 'c';
                        stackP++;
                    } else {
                        stackP--;
                        result[resultP] = stack[stackP];
                        stack[stackP] = 'c';
                        resultP++;
                        stackP++;
                        result = (char*) realloc(result, (resultP+1) * sizeof(char));
                    }

                } else {
                    stack[stackP] = 'c';
                    stackP++;
                }
                formulaP+=3;

            } else if (ch == 'l') {
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = 'l';
                        stackP++;
                    } else {
                        stackP--;
                        result[resultP] = stack[stackP];
                        stack[stackP] = 'l';
                        resultP++;
                        stackP++;
                        result = (char*) realloc(result, (resultP+1) * sizeof(char));
                    }

                } else {
                    stack[stackP] = 'l';
                    stackP++;
                }
                formulaP+=2;

            } else if (ch == '~') {
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = '~';
                        stackP++;
                    } else {
                        stackP--;
                        result[resultP] = stack[stackP];
                        stack[stackP] = '~';
                        resultP++;
                        stackP++;
                        result = (char*) realloc(result, (resultP+1) * sizeof(char));
                    }

                } else {
                    stack[stackP] = '~';
                    stackP++;
                }
                formulaP++;
            }
        } else if(ch >= 'A' && ch <= 'Z') {
            result[resultP] = ch;
            resultP++;
            formulaP++;
            result = (char*) realloc(result, (resultP+1) * sizeof(char));
        }

    }

    stackP--;
    while(stackP >= 0) {
        result[resultP] = stack[stackP];
        stackP--;
        resultP++;
        result = (char*) realloc(result, (resultP+1) * sizeof(char));
    }

    return result;
}


/* Main Function */
int main () {
    char *Formula;
    char *variableNames;
    float **features, *currentValues;
    int index = 0, j;
    int **probabiltyArrays;

    srand(time(NULL));

    scanf("%[^\n]s", inComing); /*Take input until see newline character */
    scanf("%d %ld", &intervalCount, &experimentCount);

    variableNames = (char*) malloc(letterCount*sizeof(char));
    features = (float**) malloc(letterCount*sizeof(float*));

    while (1) {
        int ch = getchar();

        if(ch == EOF) {
            break;
        } else {
            int i;
            float *comingProbability;
    
            ungetc(ch, stdin);
            variableNames = (char*) realloc(variableNames, letterCount * sizeof(char)); /* To put variable names */ 
            features = (float**) realloc(features, letterCount * sizeof(float*)); /* To put lower upper and N features which mean INTERVAL COUNT*/ 
            comingProbability = (float*) malloc((intervalCount+2) * sizeof(float)); 


            scanf(" %c %f %f", &variableNames[index], &comingProbability[0], &comingProbability[1]);

            for (i = 0; i < intervalCount; i++) {
                scanf(" %f", &comingProbability[i+2]);
            }
            
            features[index] = comingProbability; /*Inside comingProbability: lower upper limit and N probabilities */

            index++;
            letterCount++;

        }
    } /*Inputs were taken */
    letterCount--;
    Formula = spaceDeleter(inComing);
    
    currentValues = (float*) malloc(letterCount * sizeof(float));
    probabiltyArrays = (int**) malloc(letterCount * sizeof(int));

    for (j = 0; j < letterCount; j++) {
        int *probs, k, m = 0;

        probs = (int*) malloc(1000 * sizeof(int));

        for (k = 1; k < intervalCount+1; k++) {
            int count = features[j][k+1] * 1000;
            int l;

            for (l = 0; l < count; l++) {
                probs[m] = k;
                m++;
            }
        }
        probabiltyArrays[j] = probs;
    }

    /* Now we have an array of 1000 integers like [1,1,1,1,2,2,2,3,3] */

    index = 0;
    while (index < experimentCount) {
        randomNumbers(features, probabiltyArrays, currentValues, letterCount, intervalCount); /*Create random values for each letter */
        index++;
    }

    printf("%s\n",infixToPostfix(Formula));

    return 0;
}
