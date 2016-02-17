#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>   /* malloc, free, rand */

char binaryPredicate = 'X';
char negated = '-';
char existential = 'E';
char universal = 'A';
char variable1 = 'x';
char variable2 = 'y';
char variable3 = 'z';
char openSquare = '[';
char closeSquare = ']';
char endString = '\0';
char binaryConnective1 = 'v';
char binaryConnective2 = '^';
char binaryConnective3 = '>';
char openParan = '(';
char closeParan = ')';

int Fsize=50;  /*big enough for our formulas*/

int posBC(char *g) {
/*
Given a formula (A*B) this should return index position of character *
*/
  int bracketCounter = 0;
  char *bc = malloc(Fsize);
  bc = g;

  while (*bc) {
    if (*bc == openParan) {
      bracketCounter++;
      bc++;
    }
    if (*bc == closeParan) {
      bracketCounter--;
      bc++;
    }
    if (*bc != openParan && *bc != closeParan && *bc != binaryConnective1 && *bc != binaryConnective2 && *bc != binaryConnective3 && *bc != endString) {
      bc++;
    }
    if ((bracketCounter == 1) && (*bc == binaryConnective1 || *bc == binaryConnective2 || *bc == binaryConnective3)) {
      break;
    }
    if ((bracketCounter != 1) && (*bc == binaryConnective1 || *bc == binaryConnective2 || *bc == binaryConnective3)) {
      bc++;
    }
    if (*bc == endString) {
      break;
    }
  }
  return (bc-g);
}

char bin(char *g) {
/*
Given a formula (A*B) this should return the character *
*/
  int bracketCounter = 0;
  char *bc = malloc(Fsize);
  bc = g;

  while (*bc) {
    if (*bc == openParan) {
      bracketCounter++;
      bc++;
    }
    if (*bc == closeParan) {
      bracketCounter--;
      bc++;
    }
    if (*bc != openParan && *bc != closeParan && *bc != binaryConnective1 && *bc != binaryConnective2 && *bc != binaryConnective3 && *bc != endString) {
      bc++;
    }
    if ((bracketCounter == 1) && (*bc == binaryConnective1 || *bc == binaryConnective2 || *bc == binaryConnective3)) {
      break;
    }
    if ((bracketCounter != 1) && (*bc == binaryConnective1 || *bc == binaryConnective2 || *bc == binaryConnective3)) {
      bc++;
    }
    if (*bc == endString) {
      *bc = 'B';
      break;
    }
  }
  return *bc;
}

char *partone(char *g) {
/*
Given a formula (A*B) this should return A
*/
  char *a = malloc(Fsize);

  if (posBC(g) < (strlen(g) - 6)) {
    for (int i = 1; i < posBC(g); i++) {
      *(a+i-1) = *(g+i);
    }
  }
  else
      *a = 'O';

  return a;
}

char *parttwo(char *g) {
/*
Given a formula (A*B) this should return B
*/
  char *b = malloc(Fsize);

  if (posBC(g) < (strlen(g) - 6)) {
    for (int i = 1; i <= (strlen(g)-3-strlen(partone(g))); i++) {
      *(b+i-1) = *(g+posBC(g)+i);
    }
  }
  else
    *b = 'T';

  return b;
}

int parse(char *g) {
/* returns 0 for non-formulas, 1 for atoms, 2 for negations, 3 for binary connective fmlas, 4 for existential and 5 for universal formulas.*/

  int p = 0;
  char *i = malloc(Fsize);
  i = g;

  while (*i) {

    if (*i == binaryPredicate) {
      i++;
      if (*i == openSquare) {
        i++;
        if (*i == variable1 || *i == variable2 || *i == variable3) {
          i++;
          if (*i == variable1 || *i == variable2 || *i == variable3) {
            i++;
            if (*i == closeSquare) {
              i++;
              if (*i == endString) {
                p = 1;
                break;
              }
              else
                break;
            }
            else
              break;
          }
          else
            break;
        }
        else
          break;
      }
      else
        break;
    }

    else if (*i == negated) {
      i++;
      if (parse(i)>0 && parse(i)<6) {
        p = 2;
        break;
      }
      else
        break;
    }


    else if (*i == existential) {
      i++;
      if (*i == variable1 || *i == variable2 || *i == variable3) {
        i++;
          if (parse(i)>0 && parse(i)<6) {
            p = 4;
            break;
          }
          else
            break;
      }
      else
        break;
    }


    else if (*i == universal) {
      i++;
      if (*i == variable1 || *i == variable2 || *i == variable3) {
        i++;
          if (parse(i)>0 && parse(i)<6) {
            p = 5;
            break;
          }
          else
            break;
      }
      else
        break;
    }


    else if (*i == openParan) {

      int bracketCounter = 0;
      char *anb = malloc(Fsize);
      anb = i;

      for (int n = 0; n < strlen(i); n++) {
        if (*(anb+n) == openParan) {
          bracketCounter++;
        }
        if (*(anb+n) == closeParan) {
          bracketCounter--;
        }
      }

      if (bracketCounter != 0) {
        break;
      }

      if ((bin(i) == binaryConnective1 || bin(i) == binaryConnective2 || bin(i) == binaryConnective3) && (parse(partone(i))>0 && parse(partone(i))<6) && (parse(parttwo(i))>0 && parse(parttwo(i))<6)) {
        p = 3;
        break;
      }
      else
        break;
    }
    else
      break;
  }
  return p;
}


int main()
{
  /*Input a string and check if its a formula*/
  char *name=malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);

  int p=parse(name);
  switch(p) {
    case 0: printf("Not a formula\n");break;
    case 1: printf("An atomic formula\n");break;
    case 2: printf("A negated formula\n");break;
    case 3: printf("A binary connective formula\n");break;
    case 4: printf("An existential formula\n");break;
    case 5: printf("A universal formula\n");break;
    default: printf("Not a formula\n");break;
  }

  if (p==3) {
      printf("The first part is %s.\n", partone(name));
      printf("The binary connective is %c.\n", bin(name));
      printf("The second part is %s.\n", parttwo(name));
  }

  free(name);
  return(1);
}
