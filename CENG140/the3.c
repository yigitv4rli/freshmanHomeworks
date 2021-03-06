#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

char inComing[201];
int intervalCount, letterCount = 1;
long int experimentCount;
float *currentValues;
char *variableNames;
int **probabiltyArrays;
float **features;

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
    char* results;

    results = (char*) malloc(201 * sizeof(char));

    while (word[i]!= '\0') {
        if (word[i] != ' ') {
            results[j] = word[i];
            j++;
            i++;
        } else {
            i++;
        }
    }
    len = strlen(results);
    results = (char*) realloc(results, (len+1) * sizeof(char));

    results[len] = '\0';
    return results;
}

/* 
float float_rand( float min, float max ) {
    float scale = rand() / (float) RAND_MAX;    [0, 1.0] 
    return min + scale * ( max - min );         [min, max]
} 
*/

/* Random Number Generator */
void randomNumbers(int amount, int numberOfIntervals) {
    int i;

    for (i = 0; i < amount; i++) {
        int interval, numberIndex;
        float normalize, intervalRange, lower, upper, min, max;

        normalize = rand() / (float) RAND_MAX;
        lower = features[i][0];
        upper = features[i][1];
        numberIndex = rand() % 1000;
        interval = probabiltyArrays[i][numberIndex];
        intervalRange = (upper - lower) / numberOfIntervals;
        
        min = lower + ((interval-1) * intervalRange);
        max = lower + (interval * intervalRange);

        currentValues[i] = min + normalize * ( max - min );
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
    if (operator == 's') return 4;
    else if (operator == 'r') return 4;
    else if (operator == 'l') return 4;
    else if (operator == 'c') return 4;
    else if (operator == '~') return 4;
    else if (operator == '^') return 3;
    else if (operator == '*') return 2;
    else if (operator == '/') return 2;
    else if (operator == '-') return 1;
    else if (operator == '+') return 1;
    else if (operator == '(') return 0;
}



/* NEED TO FIX POPING ALL EQUAL OR HIGHER PRECEDEN WHEN SOMETHING COMES */
char* infixToPostfix(char* comingFormula) {
    char stack[201];
    int length = strlen(comingFormula), formulaP = 0, resultP = 0, stackP = 0;
    char* resulti;

    resulti = (char*) malloc(450 * sizeof(char));

    while (formulaP < length) {
        char ch = comingFormula[formulaP];

        if (ch == '(') {
            stack[stackP] = '(';
            stackP++;
            formulaP++;

        } else if (ch == ')') {
            stackP--;
            while (stack[stackP] != '(') {
                resulti[resultP] = stack[stackP];
                stackP--;
                resultP++;
            }
            formulaP++;

        /* ^ and ^ can come in a row */
        } else if(ch == '^') {
            if (stackP == 0) {
                stack[stackP] = ch;
                stackP++;
            } else {
                if (stack[stackP-1] == '^') {
                    stack[stackP] = ch;
                    stackP++;

                } else if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                    stack[stackP] = ch;
                    stackP++;
                
                } else {
                    while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                        if (ch == '^' && stack[stackP-1] == '^') {
                            stack[stackP] = '^';
                            break;
                        } else {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                    }
                    stackP++;
                }
            }
            formulaP++;

        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (stackP > 0) {
                if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                    stack[stackP] = ch;
                    stackP++;
                } else {
                    while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                        stackP--;
                        resulti[resultP] = stack[stackP];
                        stack[stackP] = ch;
                        resultP++;
                    }
                    stackP++;
                }

            } else {
                stack[stackP] = ch;
                stackP++;
            }
            formulaP++;

        } else if ('0' <= ch && '9' >= ch) {
            resulti[resultP] = '#';
            resultP++; 

            while (('0' <= comingFormula[formulaP] && '9' >= comingFormula[formulaP]) || comingFormula[formulaP] == '.') {
                resulti[resultP] = comingFormula[formulaP];
                resultP++;
                formulaP++;
            }
            resulti[resultP] = '#';
            resultP++;


        } else if (ch == '~' || ch == 's' || ch == 'c' || ch == 'l') {
            if (ch == 's' && comingFormula[formulaP+2] == 'n') { /* IF sinus function */
                if (stackP > 0) {
                    if (precedenceCompare(ch) > precedenceCompare(stack[stackP-1])) {
                        stack[stackP] = 's';
                        stackP++;
                    } else {
                        while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                        stackP++;
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
                        while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                        stackP++;
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
                        while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                        stackP++;
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
                        while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                        stackP++;
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
                        while (stackP > 0 && precedenceCompare(ch) <= precedenceCompare(stack[stackP-1])) {
                            stackP--;
                            resulti[resultP] = stack[stackP];
                            stack[stackP] = ch;
                            resultP++;
                        }
                        stackP++;
                    }

                } else {
                    stack[stackP] = '~';
                    stackP++;
                }
                formulaP++;
            }
        } else if(ch >= 'A' && ch <= 'Z') {
            resulti[resultP] = ch;
            resultP++;
            formulaP++;
        }

    }

    stackP--;
    while(stackP >= 0) {
        resulti[resultP] = stack[stackP];
        stackP--;
        resultP++;
    }

    resulti[resultP] = '\0';
    return resulti;
}


double postfixEvaluater(char* postfixversion, int numberLetter) {
    double stack[200];
    int stackP = 0, postfixP = 0, length = strlen(postfixversion);

    while (postfixP < length) {
        char ch = postfixversion[postfixP];

        if (ch == '#') {
            char numberString[200];
            int lenDouble = 0, i;
            double number;
            postfixP++;

            while (postfixversion[postfixP] != '#') {
                lenDouble++;
                postfixP++;
            }

            for(i = 0; i < lenDouble; i++) {
                numberString[i] = postfixversion[postfixP - lenDouble + i];
            }
            numberString[lenDouble] = '\0';

            sscanf(numberString, "%lf", &number);
            
            stack[stackP] = number;
            stackP++;
            postfixP++;

        } else if (ch >= 'A' && ch <= 'Z') {
            int i;

            for (i = 0; i < numberLetter; i++) {
                if(variableNames[i] == ch) {
                    stack[stackP] = currentValues[i];
                    stackP++;
                    break;
                }
            }
            postfixP++;

        /* If an operator or function comes */
        } else if (ch == '*') {
            stackP--;
            stack[stackP-1] = stack[stackP-1] * stack[stackP];
            postfixP++;

        } else if (ch == '/') {
            stackP--;
            stack[stackP-1] = stack[stackP-1] / stack[stackP];
            postfixP++;

        } else if (ch == '-') {
            stackP--;
            stack[stackP-1] = stack[stackP-1] - stack[stackP];
            postfixP++;

        } else if (ch == '+') {
            stackP--;
            stack[stackP-1] = stack[stackP-1] + stack[stackP];
            postfixP++;
            
        } else if (ch == '^') {
            stackP--;
            stack[stackP-1] = pow(stack[stackP-1], stack[stackP]);
            postfixP++;
            
        } else if (ch == 's') {
            stack[stackP-1] = sin(stack[stackP-1]);
            postfixP++;
            
        } else if (ch == 'c') {
            stack[stackP-1] = cos(stack[stackP-1]);
            postfixP++;
            
        } else if (ch == 'l') {
            stack[stackP-1] = log(stack[stackP-1]);
            postfixP++;
            
        } else if (ch == 'r') {
            stack[stackP-1] = sqrt(stack[stackP-1]);
            postfixP++;
            
        } else if (ch == '~') {
            stack[stackP-1] = -(stack[stackP-1]);
            postfixP++;
            
        }
        /* End of operators and functions */
    }
    
    return stack[0];
}



/* Main Function */
int main () {
    char *Formula;
    int index = 0, j;
    double minimum, maximum, *result;
    float intervalSize;

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
    probabiltyArrays = (int**) malloc(letterCount * sizeof(int*));

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



    Formula = infixToPostfix(Formula);

    /*Take minimum and maximum to compare with others */
    randomNumbers(letterCount, intervalCount);
    minimum = postfixEvaluater(Formula, letterCount);
    maximum = minimum;

    /* We have just made 1 experiment so experiment -1 more should be done */
    index = 0;
    while (index < experimentCount-1) {
        double functionVal;

        randomNumbers(letterCount, intervalCount); /*Create random values for each letter */
        functionVal = postfixEvaluater(Formula, letterCount);
        
        if (functionVal > maximum) {
            maximum = functionVal;
        } else if (functionVal < minimum) {
            minimum = functionVal;
        }
        
        index++;
    }

    /* To place values into intervals one more time same experiment */
    result = (double*) calloc((intervalCount), sizeof(double));
    intervalSize = (maximum-minimum) / intervalCount;
    index = 0;
    while (index < experimentCount) {
        double functionVal;
        int interval;

        randomNumbers(letterCount, intervalCount); /*Create random values for each letter */
        functionVal = postfixEvaluater(Formula, letterCount);

        if (functionVal >= maximum) {
            result[intervalCount-1]++;
        } else if (functionVal <= minimum) {
            result[0]++;
        } else {
            interval = (int) ((functionVal - minimum) / intervalSize);
            result[interval]++;
        }
        
        index++;
    }


    printf("%.3f %.3f ", minimum, maximum);

    for (index = 0; index < intervalCount; index++) {
        if(index != intervalCount-1) {
            printf("%.3f ", result[index]/experimentCount);
        } else {
            printf("%.3f\n", result[index]/experimentCount);
        }
    }
    


    return 0;
}
