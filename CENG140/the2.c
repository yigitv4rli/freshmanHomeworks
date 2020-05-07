#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ssf[3] = {1,0,0};
char inComing[201];
char ***futureSolved;
char **firstEquation;

/*
R1 -> Done 
R2 -> Done
R3_R4 -> Done
R5 -> Done
Checker -ToBeDone
Connection -> ToBeDone
*/

/* -------------------------------------------------------------*/
/* -------------------------R1 R1 R1 R1------------------------ */
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
/*-------------------------------------------------------------------------------------------------------------------- */
/*-------------------------------------------------- R2 R2 R2 R2------------------------------------------------------ */
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
/* --------------------------------------------------------------------------------------------------------------*/
/* --------------------------------------------- R3_R4 Sequence Creator----------------------------------------- */
void R3_R4SequenceCreator(char ***mainArray, int mainIndex, char **equation, int indexInEquation, int operatorIndex) {
    char **createdSeq;
    char *createdFormula;
    int equationLength = 0, i;

    while (equation[equationLength] != NULL) {
        equationLength++;
    }
    createdSeq = (char**) malloc((equationLength+1) * sizeof(char*));

    for (i = 0; i < equationLength; i++) {
        char* uniqueString;
        if (i != indexInEquation) {
            int lenWord = strlen(equation[i]), j;

            uniqueString = (char*) malloc((lenWord+ 1) * sizeof(char));
            for (j = 0; j < lenWord +1 ; j++) {
                uniqueString[j] = equation[i][j];
            }
            createdSeq[i] = uniqueString;

        } else if (i == indexInEquation) {
            int lenWord = strlen(equation[indexInEquation]), j;

            uniqueString = (char*) malloc((lenWord-operatorIndex-1) * sizeof(char));

            for (j = 0; j < lenWord-operatorIndex-2; j++) {
                uniqueString[j] = equation[indexInEquation][j+operatorIndex+1];
            }
            uniqueString[j] = '\0';
            createdSeq[indexInEquation] = uniqueString;
        }
    }
    createdSeq[i] = NULL; /* New sequent created. Do not forget to realloc and put it into last index */

    createdFormula = (char*) malloc((operatorIndex) * sizeof(char));

    for (i = 0; i < operatorIndex-1; i++) {
        createdFormula[i] = equation[indexInEquation][i+1];
    }
    createdFormula[i] = '\0';

    free(equation[indexInEquation]);
    equation[indexInEquation] = createdFormula;  /*I put it into first array at same index and make old index free */

    
    ssf[0]++;
    futureSolved = (char***) realloc(futureSolved, ssf[0]* sizeof(char**));
    futureSolved[ssf[0] -1] = createdSeq;

}


/*----------------------------------------------------------------------------- */
/*------------------------------ R5 R5 R5 R5 ---------------------------------- */
void R5Transformer(char **equation, int indexInEquation, int operatorIndex) {
    char *transformed;
    int formulaLength = strlen(equation[indexInEquation]);

    if (equation[indexInEquation][1] == '-') {
        int i = 0, k = 0;
        transformed = (char*) malloc((formulaLength) * sizeof(char));

        while (i < formulaLength+1) {
            if (i == 1) {
                i++;
            } else if (i == operatorIndex) {
                transformed[k] = '|';
                i++;
                k++;
            } else {
                transformed[k] = equation[indexInEquation][i];
                i++;
                k++;
            }
        }

    } else {
        int i = 0, k = 0;
        transformed = (char*) malloc((formulaLength+2) * sizeof(char));

        while (i < formulaLength + 2) {
            if (i == 1) {
                transformed[i] = '-';
                i++;
            } else if (k == operatorIndex) {
                transformed[i] = '|';
                i++;
                k++;
            } else {
                transformed[i] = equation[indexInEquation][k];
                i++;
                k++;
            }
        }
    }

    free(equation[indexInEquation]);
    equation[indexInEquation] = transformed;
}

/* -------------------------------------------------------------------------------------------------------- */
/* ------------------------------------ Check Whether Solved or Failed ------------------------------------ */
int checker(char **equation) {
    int lenEquation = 0, hashtagIndex, numberStr = 0;
    int i, j;

    while (equation[lenEquation] != NULL) {
        if (strlen(equation[lenEquation]) == 1) {
            numberStr++;
        }

        if (equation[lenEquation][0] == '#'){
            hashtagIndex = lenEquation;
        }
        lenEquation++;
    }

    if (lenEquation == numberStr && (equation[0][0] == '#' | equation[lenEquation-1][0] == '#')) {
        return -1;

    } else if (lenEquation == numberStr) {
        for (i = 0; i < hashtagIndex; i++) {
            for (j = hashtagIndex+1; j < lenEquation; j++) {
                if (strcmp(equation[i], equation[j]) == 0) {
                    return 1;
                }
            }
        }
        return -1;

    } else {
        for (i = 0; i < hashtagIndex; i++) {
            for (j = hashtagIndex+1; j < lenEquation; j++) {
                if (strcmp(equation[i], equation[j]) == 0) {
                    return 1;
                }
            }
        }
        return 0;
    }
}




/* side = -1 -> Left */
/* side = 1 -> Right */
/*
    mainArray = futureSolved
    mainIndex = while looping in futuresolved, store index
    equation = futureSolved[mainIndex]
    indexInEquation = storing index while looping in equation
    word = equation[index] = futureSolved[mainIndex][indexInEquation]
    side = left or right implication
*/


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
                    R5Transformer(equation, indexInEquation ,operator); /* RULE 5 -> A>B transforms to -A|B       A: [1: operator]    B: [operator+1: length-1] */

                } else if (word[index] == '|' && side == -1 && parentheses == 0) {
                    operator = index;
                    R3_R4SequenceCreator(mainArray, mainIndex, equation, indexInEquation, operator); /* RULE 3  Left -> A|B splits into two new strings one involves A, the other involves B, The others are same for each one */
                
                } else if (word[index] == '&' && side == 1 && parentheses == 0) {
                    operator = index;
                    R3_R4SequenceCreator(mainArray, mainIndex, equation, indexInEquation, operator); /* RULE 4  Right -> A&B splits into two new strings one involves A, the other involves B, The others are same for each one */
                
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
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------- Main ----------------------------------------- */
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
