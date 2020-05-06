#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toBeSolved = 1, solved = 0, failed = 0;
char inComing[201];
char ***futureSolved;
char **firstEquation;

/*
R1 -> Done 
R2 -> Done
R3 -> ToBeDone
R4 -> ToBeDone
R5 -> InProgress
Checker -ToBeDone
Connection -> ToBeDone
*/


void R1SideChanger(char **equation, int side, int indexInEquation) {
    int i, j, lenEquation = 0, wordLength = strlen(equation[indexInEquation]);
    char *value = (char*) malloc(wordLength * sizeof(char));

    for (j=0; j< wordLength; j++) {
        value[j] = equation[indexInEquation][j+1];
    }

    while (equation[lenEquation] != NULL) {
        lenEquation++;
    }

    free(equation[indexInEquation]);
    equation[indexInEquation] = NULL;

    if (side == -1) {
        for (i = 0; i < lenEquation-1; i++) {
            if (i >= indexInEquation) {
                equation[i] = equation[i+1];
            }
        }
        equation[lenEquation-1]  = value;

    } else if (side == 1) {
        for (i = lenEquation-1; i > 0; i--) {
            if (i <= indexInEquation) {
                equation[i] = equation[i-1];
            }
        }
        equation[0] = value;
    }
}


void R2CommaReplacer(char ***mainArray, int mainIndex, char **equation, int side, int indexInEquation, int operatorIndex) {
    int i, j, lenEquation = 0;
    int formulaLength = strlen(equation[indexInEquation]);
    int firstLength = operatorIndex - 0, secondLength = formulaLength - operatorIndex -1;
    char *firstPhrase;
    char *secondPhrase;
    char **newEquation;

    firstPhrase = (char*) malloc(firstLength * sizeof(char));
    secondPhrase = (char*) malloc(secondLength * sizeof(char));

    while (equation[lenEquation] != NULL) {
        lenEquation++;
    }

    for (i = 0; i < operatorIndex-1; i++) {
        firstPhrase[i] = equation[indexInEquation][i+1];
    }
    firstPhrase[i] = '\0';

    for (j= 0; j < formulaLength - operatorIndex -2; j++) {
        secondPhrase[j] = equation[indexInEquation][j+operatorIndex+1];
    }
    secondPhrase[j] = '\0';


    newEquation = (char**) malloc((lenEquation+2) * sizeof(char*));

    if (side == -1) {
        int k = 0, l=0;
        newEquation[0] = firstPhrase;
        newEquation[1] = secondPhrase;

        while (k < lenEquation) {
            if (l != indexInEquation){
                newEquation[k+2] = equation[l];
                l++;
                k++;
            } else {
                l++;
            }
        }
        free(equation[indexInEquation]); /* It can give invalid free error IMPORTANT!!! */
        free(mainArray[mainIndex]);
        mainArray[mainIndex] = newEquation;

    } else if (side == 1) {
        int k = 0, l = 0;
        newEquation[lenEquation+1] = NULL;
        newEquation[lenEquation] = firstPhrase;
        newEquation[lenEquation-1] = secondPhrase;

        while (k < lenEquation-1) {
            if (l != indexInEquation){
                newEquation[k] = equation[l];
                l++;
                k++;
            } else {
                l++;
            }
        }
        free(equation[indexInEquation]);
        free(mainArray[mainIndex]);
        mainArray[mainIndex] = newEquation;
    }
}



/* side = -1 -> Left */
/* side = 1 -> Right */
void operandProcessor(char ***mainArray, int mainIndex, char **equation ,char *word, int side, int indexInEquation) {
    int length = strlen(word);

    if (length == 1){
        return;

    } else if (length == 2) {
        R1SideChanger(equation, side, indexInEquation);  /* RULE 1  if there is - take it to other side  */

    } else {
        int index = 0, parentheses = -1, operator;
        
        if (word[0] == '-') {
            R1SideChanger(equation, side, indexInEquation); /* RULE 1 again -> Take it to other side */
        } else {
            while (index < length) {
                if (word[index] == '(') {
                    parentheses++;
                    index++;
                } else if (word[index] == ')') {
                    parentheses--;
                    index++;

                } else if (word[index] == '>' && parentheses == 0) {
                    operator = index;
                    R5Transformfer(word, operator); /* RULE 5 -> A>B transforms to -A|B       A: [1: operator]    B: [operator+1: length-1] */

                } else if (word[index] == '|' && side == -1 && parentheses == 0) {
                    operator = index;
                    R3SequenceCreator(word, operator); /* RULE 3  Left -> A|B splits into two new strings one involves A, the other involves B, The others are same for each one */
                
                } else if (word[index] == '&' && side == 1 && parentheses == 0) {
                    operator = index;
                    R4SequenceCreator(word, operator); /* RULE 4  Right -> A&B splits into two new strings one involves A, the other involves B, The others are same for each one */
                
                } else if (word[index] == '&' && side == -1 && parentheses == 0) {
                    operator = index;
                    R2CommaReplacer(mainArray, mainIndex, equation, side, indexInEquation, operator); /* RULE 2 Left -> A&B becomes A, B */

                } else if(word[index] == '|' && side == 1 && parentheses == 0) {
                    operator = index;
                    R2CommaReplacer(mainArray, mainIndex, equation, side, indexInEquation, operator);; /* RULE 2 Right -> A|B becomes A, B */
                }
            }
        }
    }

}


int main() {
    int comma = 0, i = 0;
    int opening = 0, closing, arrIndex = 0;

    futureSolved = (char ***) malloc(1*sizeof(char**)); /* At first we have only one equation so.. AND array size == TOBESOLVED*/
    scanf("%s", inComing); /* Taking string as input */

    while (inComing[i] != '\0') {
        if (inComing[i] == ',' | inComing[i] == '#') {
            comma++;
        }
        i++;
    }
    firstEquation = (char **) malloc((comma+3)*sizeof(char*));  /* Number of , and # + 3 */


    /*   char*** -> char** -> X times char*   */
    for (i = 0; inComing[i] != '\0'; i++) {
        if (inComing[i] == ',') {
            int j;
            char *formula;
            closing = i;
            formula = (char*) malloc((closing - opening + 1)* sizeof(char));

            for(j=0; j < closing - opening; j++) {
                formula[j] = inComing[j+opening];
            }

            formula[closing - opening] = '\0';
            firstEquation[arrIndex] = formula;
            opening = closing+1;
            arrIndex++;

        } else if (inComing[i] == '#') {
            if (i != 0) {
                int j;
                char *formula;
                char *hashtag;

                formula = (char*) malloc((i - opening + 1)* sizeof(char));

                for(j=0; j < i - opening; j++) {
                    formula[j] = inComing[j+opening];
                }

                formula[i - opening] = '\0';
                firstEquation[arrIndex] = formula;
                arrIndex++;
                hashtag = (char*) malloc(2* sizeof(char));
                hashtag[0] = '#';
                hashtag[1] = '\0';
                firstEquation[arrIndex] = hashtag;
                arrIndex++;
                opening = i+1;

            } else {
                char *hashtag;

                hashtag = (char*) malloc(2* sizeof(char));
                hashtag[0] = '#';
                hashtag[1] = '\0';
                firstEquation[arrIndex] = hashtag;
                arrIndex++;
                opening = i+1;
            }
        }
    }

    if (i - opening != 0) {
        char *last;
        int j;
        last = (char*) malloc((i - opening + 1)* sizeof(char));

        for(j=0; j < i - opening; j++) {
            last[j] = inComing[j+opening];
        }
        last[i - opening] = '\0';
        firstEquation[arrIndex] = last;
        arrIndex++;
        firstEquation[arrIndex] = NULL;
    }
    
    futureSolved[0] = firstEquation;

    return 0;
}
