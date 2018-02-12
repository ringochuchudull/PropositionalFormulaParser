#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50;
int cases=10;


int i;
int j;

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
}*tab, *node, *node1, *kid, *pa;

void newLeftchild(struct tableau *tab, char *formula){
    struct tableau *leftchild = (struct tableau*)malloc(sizeof(struct tableau));
    leftchild -> parent = tab;
    leftchild -> root = formula;
    leftchild -> left = NULL;
    leftchild -> right = NULL;
    tab -> left = leftchild;
}

void newRightchild(struct tableau *tab, char *formula){
    struct tableau *rightchild = (struct tableau*)malloc(sizeof(struct tableau));
    rightchild -> parent = tab;
    rightchild -> root = formula;
    rightchild -> left = NULL;
    rightchild -> right = NULL;
    tab -> right = rightchild;
}


char *disect(char *g, int i, int j){  //g is the sting, i is starting index where j is the end
  char *segment = (char *)malloc(sizeof(char) * (j-i+1)); 
    int a = 0;
    for (a = 0; a < (j-i); a++) {
        char n = g[i-1+a];
        segment[a]= n;
    }
    segment[j-i] = '\0'; //printf("~~~ dissection is %s ~~~\n", segment);
    return segment;
}


/*char * trimpart1(char *g) {
   //  for binary connective formulas, returns first part
    int brackets = 0, i = 0;
    while(1) {
        char c = g[i];
        if(c=='(') { brackets += 1; }
        if(c==')') { brackets -= 1; }
        if((g[i]=='v'||g[i]=='^'||g[i]=='>') && brackets==1) {
            return disect(g,1,i);
            
        }
        i++;
    }
} */
/*
char * trimpart1(char *g){      //    char* a="((p>q)^(q>p))";
    int length = strlen(g);
    
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
    char *result=(char*)malloc(sizeof(char)*strlen(g));
    char *temp=(char*)malloc(sizeof(char)*strlen(g));
    for (int i=0; i<bc-1; i++) {
        temp[i]=g[i+1];
    }
    for (int j=0; j<bc-0; j++) {
        result[j]=temp[j];
    }
    result[bc-1]='\0';
    return result;
} */


char * trimpart1(char *g){

  if(g[0]=='-')
    return trimpart1(g+1);
  
int length = strlen(g);
 
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
      
      char* prebc=(char *)malloc(sizeof(char)* (bc));
       char* postbc=(char *)malloc(sizeof(char)*(length-bc));

       if(bracket == 0 && flag ==1){ 
        prebc = disect(g, 2, bc+1);
	postbc = disect(g, bc+2, length);
      }

      return prebc;
}

char * trimpart2(char *g){
 if(g[0]=='-')
   return trimpart2(g+1);
  
int length = strlen(g);
 
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

       char* prebc=(char *)malloc(sizeof(char)* (bc));
       char* postbc=(char *)malloc(sizeof(char)*(length-bc));

      if(bracket == 0 && flag ==1){ 
       
        prebc = disect(g, 2, bc+1);
	postbc = disect(g, bc+2, length);

      }

      return postbc;
}

char binaryconnective(char *g){
    int bracket =0; 
    char bc;
    for(int index = 0;index<strlen(g); index++){ 
	if(g[index] == '('){
	  bracket += 1;}
	if(g[index] == ')'){
	  bracket -= 1;} 

	if(bracket == 1){   //Only take the location of bc in the middle
          if(g[index]=='v'||g[index]=='^'||g[index]=='>'){
            bc = g[index];
	  }} 
    }  // printf("%c", bc);   //end of for loop
    return bc;
}


//---------------------------------------------------------------------------------------------
int parse(char *g){
  int status = 0;
  int length = strlen(g); //printf(" %s has length: %d, first character %c, lastcharacter %c\n", g, length, g[0],g[length-1]); 

  //Single Character 
  if(g[0] == 'p' || g[0] == 'q'||g[0] == 'r'){
    if (length == 1){
    status = 1;
    return status;}
  }
  
  // Checks propositional formula, i think this if statement is barely used, not well written
  
  if(g[0] == '('){
      if( g[1]=='p'|| g[1]=='q'|| g[1]=='r'){
        if( g[2]=='v'|| g[2]=='^'|| g[2]=='>'){
         if( g[3]=='p'|| g[3]=='q'|| g[3]=='r'){
          if( g[4]==')'){
	    if(length == 5){
	        status = 3;
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
      //printf("Debug\n"); //debug
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
	int state2 = parse(postbc); //printf("state: %d,%d\n", state1, state2);
        if(state1 != 0){
	  if(state2 !=0){
	    status = 3; //printf("status3 %d\n", status);
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


//-----------------------------TABLEU --------------------------------------------------------------

char *addnegative(char *a){  // Add negative sign to the expression
  char *newformula = (char*)malloc((strlen(a)+2)*sizeof(char));
  newformula[0] = '-';
  int index = 0;

  while(a[index] != '\0'){
    newformula[index+1] = a[index];
    index++;
      };
  newformula[index+1]= '\0';
  return newformula;
}

char *preexpression(char *a){
  if(parse(a)==3){
    switch(binaryconnective(a)){ //Binary 
    case 'v': return trimpart1(a);   //Beta 
    case '^': return trimpart1(a);    // Alpha
    case '>': return addnegative(trimpart1(a));//Beta
    default : return NULL;
    }
  }

  if( (parse(a)==2) && (parse(a+1)==3)){   // Negated Binary
      switch(binaryconnective(a)){
      case 'v':return addnegative(trimpart1(a)); //alpha
      case '^':return addnegative(trimpart1(a)); //beta
      case '>':return trimpart1(a);             //alpha
      default: return NULL;
      }  
    }

    return NULL;
}

char *postexpression(char *a){

  if(parse(a)==3){
    switch(binaryconnective(a)){ //Binary 
    case 'v': return trimpart2(a);   //Beta 
    case '^': return trimpart2(a);    // Alpha
    case '>': return trimpart2(a);//Beta
    default : return NULL;
    }
  }

  if( (parse(a)==2) && (parse(a+1)==3)){   // Negated Binary
      switch(binaryconnective(a)){
      case 'v':return addnegative(trimpart2(a)); //alpha
      case '^':return addnegative(trimpart2(a)); //beta
      case '>':return addnegative(trimpart2(a));             //alpha
      default: return NULL;
      }  
    }

    return NULL;
}

char *doublenegation(char *a){
  if((parse(a)==2) && (parse(a+1)==2))
    return (a+2);
  return NULL;
}

void add_alpha_child(struct tableau *t, char *a){ //
    //Base case
    if(t->left == NULL)
        newLeftchild(t,a);
    else
        add_alpha_child(t->left, a);
    
    if(t->right != NULL)
        add_alpha_child(t->right, a);
    
}

void alpha(struct tableau *t, char *exp1, char *exp2){
    add_alpha_child(t,exp1);
    add_alpha_child(t,exp2);
}

void beta(struct tableau *t, char *exp1, char *exp2){
    //base case
    if(t->left == NULL){
        newLeftchild(t, exp1);
        newRightchild(t, exp2);
    }else{
        beta(t->left, exp1, exp2);
        if(t->right != NULL){
            beta(t->right,exp1,exp2);
        }
    }
    
}
/* check alpha(1), beta(2) formula, literal(3) or double negation(4) */
int checkab(char *g){  //return for alpha and beta

  if( (parse(g)==1) || ((parse(g)==2 )&&(strlen(g)==2))  ){ //This is literal
   return 3;
}
  if( (parse(g) ==2 ) && (parse(g+1)==2) ){  //  - & -phi -> double negation
    int countneg = 0;
    while(g[countneg] == '-'){
      countneg++;
    }
    if(countneg % 2 == 0)
      return 4;
    
    return 4;     
  }

  if(parse(g) ==3){  // Binary formula
    switch(binaryconnective(g)){
    case('v'): return 2;
    case('>'): return 2;
    case('^'): return 1;
    default: break;
    }
  } // end of 3rd if-loop

  if((parse(g)==2) && (parse(g+1)==3) ) { //Negated binary
      //printf("\t%c\t" ,binaryconnective(g));
      switch(binaryconnective(g)){
    case('v'): return 1;
    case('>'): return 1;
    case('^'): return 2;
    default: break;
    }
    
    }//End of for */
  
    return 0; 
}





void complete(struct tableau *t){
  if (t != NULL){
    char *root = t->root;
      //printf("%s\n", root);
    switch(checkab(root)){
    case 0: break; //dont know what is it
    case 1:
        alpha(t, preexpression(root),postexpression(root)); //printf("\n");
        break; //Alpha
    case 2:
        beta(t, preexpression(root),postexpression(root)); //printf(" & ");
        break; //Beta
    case 3:
        break; //literal
    case 4:
        t->root = doublenegation(root);
        complete(t);
        break;  //double negation
    }
      if(t->left != NULL)
          complete(t->left);
      if(t->right!=NULL)
          complete(t->right);
  }
  
}


//-----------------------expands ENDS   checking starts-------------


//Return 0 if statisfiable, 1 if not statisfiable
//so if the tableau is closed, it is satisfiable, otherwise it is not

int closedtab(struct tableau *t, int * statistic){
    char *root = t -> root;
    int new[6];
    
    for(int z =0; z<6; z++){
     new[z] = statistic[z];
    }
    
    if(parse(root) == 1) {
        switch(root[0]) {
            case 'p': new[0] = 1; break;
            case 'q': new[1] = 1; break;
            case 'r': new[2] = 1; break;
        }
    }
    if(parse(root) == 2 && parse(root+1) == 1) {
        switch(root[1]) {
            case 'p': new[3] = 1; break;
            case 'q': new[4] = 1; break;
            case 'r': new[5] = 1; break;
        }
    }
    
    for(int index = 0; index< 3; index++ ){
        if( (new[index]==1)  && (new[index+3]==1 )){
            return 1;
        }
    }
    
    if(t->left == NULL && t->right == NULL){
      return 0;
    }
    if(t->left != NULL && t->right == NULL){
        return closedtab(t->left, new);
    }
    
    if(t->left != NULL && t->right != NULL){
        int ringo = closedtab(t->left, new);
        int nameless = closedtab(t->right, new);
        return ringo && nameless;
    }
        
    return 0;
}
    
int closed(struct tableau *t){
    int statistic[6] ={0,0,0,0,0,0}; // counting appeareance of p q r -p -q -s
    char* root = t-> root;
    
    
    //Base case
    
    if(parse(root) == 0) //if root is nothing
        return 1;
    
    if(parse(root) == 1){ //a probositional formula
      switch(root[0]){
        case 'p': statistic[0] = 1;
        case 'q': statistic[1] = 1;
        case 'r': statistic[2] = 1;
        default:printf("%c\n", root[0]);break;
      }
    }
    if( (parse(root) == 2) && (parse(root+1) == 1) ){ // a negated literle e.g. --p
        switch(root[1]){
            case 'p': statistic[3] =1; break;
            case 'q': statistic[4] =1; break;
            case 'r': statistic[5] =1; break;
        }
    }
    
    if(t->left == NULL && t->right == NULL) // only one lit or a negation e.g -p , p , -q ,q
        return 0;  // end of base case
    
    if(t->left != NULL && t->right == NULL){
       return closedtab(t->left, statistic);
    }
        
    if(t->left != NULL && t->right != NULL){
        int ringo = closedtab(t->left, statistic);
        int nameless = closedtab(t->right, statistic);
        return ringo && nameless;
    }
    

    
    return 0;
}

//-----------------tableau ends
// some unit testing

void testreceiving(int *stat){
   // strlen(stat);
    for(int i = 0; i<6; i++)
      printf("element is %d" ,stat[i]);
    
}

int unittest(){
    struct tableau a={"-(p>q)"};   //test apply_alpha_rule  alpha ok
    struct tableau *c=&a;
    int statistic[6] = {1,2,3,4,5,6};
    
    closedtab(c, statistic);
    return 1 && 0;
}

void testcomplete(){
    /*    struct tableau a={"-(p>q)"};   //test apply_alpha_rule  alpha ok
     struct tableau *c=&a;
     alpha(c, "p", "-q");
     printf("%s\n",(c->left)->root);
     
     struct tableau b ={"-(p>q)"};      //test apply_beta_rule beta ok
     struct tableau *d=&b;
     beta(d, "-a", "b");
     printf("%s\n",(d->right)->root); */
    
    
    struct tableau a={"-((p>(qvr))>((p>q)v(p>r)))"};  //test complete()
    struct tableau *c=&a;
    complete(c);
    int n=0;              
    if ((c->right)==NULL) {
        n=1;
    }
    printf("%d\n",n);
    printf("%s\n",((((c->left)->left))->root));
    
    /*   struct tableau a={"-(p>p)"};  //return 0 if it is satsfiable
     struct tableau *c=&a;
     complete(c);
     int i=closed(c);
     printf("%d\n",i); */
}


//Main
int main()

{ /*input a string and check if its a propositional formula */

   //testcomplete();
    unittest();
  char *name = malloc(Fsize);
  FILE *fp, *fpout;
 
 
  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<cases;j++)
    {
        
      fscanf(fp, "%s",name);/*read formula*/
        
        //printf("\n\n tableau \n\n");
        //printf("%s\npart1 %s and part2 %s\n\n",name, trimpart1(name),trimpart2(name));
        // printf("%s is %d formila\n", name, checkab(name));
      //printf("%s new form\n", addnegative(name));
      //  printf("%s,%s\n", addnegative(trimpart1(name)),trimpart2(name));
      //printf("%s\n", doublenegation(name));
       // printf("%s adn %s\n", trimpart1(name),trimpart2(name));
      switch (parse(name))
	{case(0): fprintf(fpout, "%s is not a formula.  ", name);break;
	case(1): fprintf(fpout, "%s is a proposition.  ", name);break;
	case(2): fprintf(fpout, "%s is a negation.  ", name);break;
	case(3):fprintf(fpout, "%s is a binary.  ", name);break;
	default:fprintf(fpout, "What the f***!  ");
	}
        
      //  struct tableau t={name, NULL, NULL, NULL};
      //  complete(&t);
        //int a = closed(&t);
      //  make new tableau with name at root, no children, no parent


      
      struct tableau t={name, NULL, NULL, NULL};

      //expand the root, recursively complete the children
      if (parse(name)!=0)
	{ complete(&t);
	  if (closed(&t)) fprintf(fpout, "%s is not satisfiable.\n", name);
	  else fprintf(fpout, "%s is satisfiable.\n", name);
	}
	else fprintf(fpout, "I told you, %s is not a formula.\n", name);

    }
 
  fclose(fp);
  fclose(fpout);
  free(name);

  return(0);
}







