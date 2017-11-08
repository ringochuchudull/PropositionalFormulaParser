#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int inputs=6;

int i;
int j;


/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
Of course you will almost certainly need other functions.

You may vary this program provided it reads 6 formulas in a file called "input.txt" and outputs in the way indicated below to a file called "output.txt".
*/

int status = -1;

int counter, bool;  //status refers to returning number (ow)

char *disect(char *g, int i, int j){  //g is the sting, i is starting index where j is the end
  char *seg = (char *)malloc(sizeof(char) * (j-i+1)); 
    int a = 0;
    for (a = 0; a < (j-i); a++) {
        char n = g[i-1+a];
        seg[a]= n;
    }
    seg[j-i] = '\0';
    printf("~~~ dissection is %s ~~~\n", seg);
    return seg;
}

// Parser initiates
int parse(char *g){
  status = 0;
  int length = strlen(g); printf(" %s has length: %d, first character %c, lastcharacter %c\n", g, length, g[0],g[length-1]); 

  //Single Character 
  if(g[0] == 'p' || g[0] == 'q'||g[0] == 'r'){
    status = 4;
    return status;
  }
  
  // Checks propositional formula
  if(g[0] == '('){
      if( g[1]=='p'|| g[1]=='q'|| g[1]=='r'){
        if( g[2]=='v'|| g[2]=='^'|| g[2]=='>'){
         if( g[3]=='p'|| g[3]=='q'|| g[3]=='r'){
          if( g[4]==')'){
	    if(length == 5){
	        status = 1;
		return status;
	     }
	     else{ // If length id longer then 5 but (pvq);
	       status = 0;
	       return status;
	     }	
	  }
	  else // According to the sheet, (p^q^r) is not considered as formula
	    status = 0;
	    return status;

	 }}}}
  
    //Checks Negation formula
    if(g[0] == '-'){
      if(length ==1){
	status = 0;
	return status;
      }else{
        char *disection = disect(g,2,strlen(g)+1);
        int lamba = parse(disection);
        if(lamba != 0){
          status = 2;
	  return status;
	}	
      }
    }


   //Binary formula, Check brackets, check position of Connectives
    if(g[0]=='(' && g[length-1]==')'){
      printf("Debug\n"); //debug
      status = 0;
      int index = 0, bc=-1, bracket =0,  flag=0; //Locate the binary connective in the array
  
      for(index =0;index<length;index++){ //eg: ((pvr)>(p>r)) brackets
	if(g[index] == '('){
	  bracket += 1;}
	if(g[index] == ')'){
	  bracket -= 1;} 

	if(bracket == 1){   //Only take the location of bc in the middle
          if(g[index]=='v'||g[index]=='^'||g[index]=='>'){
            bc = index;
	    flag += 1;
	  }} 
      }  //End of the looping
      if(bracket == 0 && flag ==1){  //dissect two parts
	char* prebc = (char *)malloc(sizeof(char)* (bc));
	char* postbc =(char *)malloc(sizeof(char)*(length-bc));
        prebc = disect(g, 2, bc+1);
	postbc = disect(g, bc+2, length);
        int state1 = parse(prebc); 
	int state2 = parse(postbc); printf("state: %d,%d\n", state1, state2);
        if(state1 != 0){
	  if(state2 !=0){
	    status = 3; printf("status3 %d\n", status);
	    return status;
	  }else{
            status = 0;
	    return status;
	  }
	}else{
	  status = 0;
	  return status;
	}

      }	 
    }
  
      return status;
}


int main()
{ /*input 10 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/



  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
 
  /*lets check your parser*/
  printf("\n---This is where it starts---------------------------------------------\n");
  
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
	{
	case(0):fprintf(fpout,"%s is not a formula\n", names[i]); printf("%s is not a formula\n", names[i]);break;
	case(1):fprintf(fpout,"%s is a proposition\n",names[i]); printf("%s is prososition\n", names[i]);break;
	case(2):fprintf(fpout,"%s is a negation\n",names[i]); printf("%s is negation\n", names[i]);break;
	case(3):fprintf(fpout,"%s is a binary formula\n",names[i]);printf("%s is binary\n", names[i]);break;
	case(4):fprintf(fpout,"%s is not a formula\n", names[i]);printf("%s is a single character, not a formula\n", names[i]);  
        case(-1):printf("%s is nothing but an error\n",names[i]);break;
	default:printf("%s is nothing but an error\n",names[i]);break;
	}
         printf("\n=====CLOSES============\n");
    }
 
 
  fclose(fp);
  fclose(fpout);
 
  return(0);
}

