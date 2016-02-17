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
int no_edges;
int no_nodes;
int i;
const int cases=35;

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
  int i;
  if (posBC(g) < (strlen(g) - 6)) {
    for (i = 1; i < posBC(g); i++) {
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
  int i;
  if (posBC(g) < (strlen(g) - 6)) {
    for (i = 1; i <= (strlen(g)-3-strlen(partone(g))); i++) {
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
      int n;

      for (n = 0; n < strlen(i); n++) {
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

int isEdge(int a, int b, int edges[no_edges][2], int size, int V[3]) {
  int i;
  for(i = 0; i < no_edges; i++) {
    if (edges[i][0] == a && edges[i][1] == b) {
      return 1;
    }
  }
  return 0;
}

int variableValue(char variable, int V[3]) {
  switch(variable) {
    case 'x': return V[0]; break;
    case 'y': return V[1]; break;
    case 'z': return V[2]; break;
    default: return -1;
  }
}


int eval(char *nm, int edges[no_edges][2], int size, int V[3]) {
/*this method takes a formula, the list of edges of a graph, the number of vertices and a variable assignment.  It then evaluates the formula and returns 1 or 0 as appropriate.  */
  int i, a, b, t;
  char bc;
  char *fmla;
  int counter = 0;

  switch(parse(nm)) {

    // Atomic formula
    case (1):
      a = variableValue(*(nm+2), V);
      b = variableValue(*(nm+3), V);
      if (isEdge(a, b, edges, size, V) == 1)
        return 1;
      else
        return 0;
      break;

    // Negated formula
    case (2):
      if (eval(nm+1, edges, size, V) == 1)
        return 0;
      else
        return 1;

    // Binary connective formula
    case (3):
      fmla = partone(nm);
      t = eval(fmla, edges, size, V);
      fmla = parttwo(nm);
      bc = bin(nm);
      switch (bc) {
        case 'v':
          if (t == 1 || eval(fmla, edges, size,V) == 1)
            return 1;
          else
            return 0;
          break;

        case '^':
          if (t == 1 && eval(fmla, edges, size,V) == 1)
            return 1;
          else
            return 0;
          break;

        case '>':
          if (t == 1)
            return eval(fmla, edges, size,V);
          else
            return 1;

        default: return 0;
      }

    // Existential formula
    case (4):
      switch (*(nm+1)) {
        case 'x':
          for (i=0;i<size;i++) {
            V[0] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter > 0)
            return 1;
          else
            return 0;
          break;

        case 'y':
          for (i=0;i<size;i++) {
            V[1] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter > 0)
            return 1;
          else
            return 0;
          break;

        case 'z':
          for (i=0;i<size;i++) {
            V[2] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter > 0)
            return 1;
          else
            return 0;
          break;

        default: return 0;
      }

    // Universal formula
    case (5):
      switch (*(nm+1)) {
        case 'x':
          for (i=0;i<size;i++) {
            V[0] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter == size)
            return 1;
          else
            return 0;
          break;

        case 'y':
          for (i=0;i<size;i++) {
            V[1] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter == size)
            return 1;
          else
            return 0;
          break;

        case 'z':
          for (i=0;i<size;i++) {
            V[2] = i;
            if (eval(nm+2, edges, size, V) == 1) {
              counter++;
            }
          }
          if (counter == size)
            return 1;
          else
            return 0;
          break;

        default: return 0;
      }

    default: return 0;
	}
}


int main()
{
  char *name=malloc(Fsize); /*create space for the formula*/
  FILE *fp, *fpout;

  /* reads from input.txt, writes to output.txt*/
 if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<cases;j++)
    {
      fscanf(fp, "%s %d %d",name,&no_nodes,&no_edges);/*read formula, number of nodes, number of edges*/
      int edges[no_edges][2];  /*Store edges in 2D array*/
      for(i=0;i<no_edges;i++)	 fscanf(fp, "%d%d", &edges[i][0], &edges[i][1]);/*read all the edges*/

      /*Assign variables x, y, z to nodes */
      int W[3];
      /*Store variable values in array
	value of x in V[0]
	value of y in V[1]
	value of z in V[2] */
      for(i=0;i<3;i++)  fscanf(fp, "%d", &W[i]);
      int p=parse(name);
      switch(p)
	{case 0:fprintf(fpout,"%s is not a formula.  ", name);break;
	case 1: fprintf(fpout,"%s is an atomic formula.  ",name);break;
	case 2: fprintf(fpout,"%s is a negated formula.  ",name);break;
	case 3: fprintf(fpout,"%s is a binary connective formula.  ", name);break;
	case 4: fprintf(fpout,"%s is an existential formula.  ",name);break;
	case 5: fprintf(fpout,"%s is a universal formula.  ",name);break;
	default: fprintf(fpout,"%s is not a formula.  ",name);break;
	}

      /*Now check if formula is true in the graph with given variable assignment. */
      if (eval(name, edges, no_nodes,  W)==1)	fprintf(fpout,"The formula %s is true in G under W\n", name);
      else fprintf(fpout,"The formula %s is false in G under W\n", name);
    }

  fclose(fp);
  fclose(fpout);
  free(name);
  return(1);
}
