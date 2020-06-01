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
3) Random number generation with weighted probabilities
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
            int count = features[j][k+1] * 1000, deneme = 0;
            int l;

            for (l = 0; l < count; l++) {
                probs[m] = k;
                m++;
                deneme++;
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


    return 0;
}
