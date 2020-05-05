#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toBeSolved = 1, solved = 0, failed = 0;
char inComing[201];
char ***futureSolved;
char **firstEquation;

/* side = -1 -> Left */
/* side = 1 -> Right */
void operandProcessor(char *word, int side) {
    int length = strlen(word);

    if (length == 1){
        return;

    } else if (length == 2) {
        R1SideChanger(word, side);  /* RULE 1  if there is - take it to other side  */

    } else {
        int index = 0, parentheses = -1, operator;
        
        if (word[0] == '-') {
            R1SideChanger(word, side); /* RULE 1 again -> Take it to other side */
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
                    R2CommaReplacer(word, operator); /* RULE 2 Left -> A&B becomes A, B */

                } else if(word[index] == '|' && side == 1 && parentheses == 0) {
                    operator = index;
                    R2CommaReplacer(word,operator); /* RULE 2 Right -> A|B becomes A, B */
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
