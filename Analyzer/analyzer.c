#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int getrating(char * werd){
  FILE *file = fopen("negative_words.txt", "r");
  char comma[2]=",";
  int i;
  char line[100];
  char *word;
  char word2 [100];
  char * ratingchar;
  int rating;
  //first, check positive words 
  if (file != NULL){
  //parse through each line, grabbing the word and its respective rating 
      while(fgets(line,sizeof line,file) != NULL){

	//word is the word in line n 
	word=strtok(line,comma);
	sscanf(line,"%s %d",word2, &rating);
      
      for(i=0;i<2;i++){
	if(i==0){
	  //get the rating of the word and assign it to ratingchar 
	 ratingchar = strtok(NULL,comma);
	 // printf("RATING %s\n", ratingchar); 
 	 }
	//once rating is declared...
	else{
	  //Word found in negative_words, so negate rating 
	  if (strcmp(werd,word) == 0){
	    int mult = -1;
	    int r = atoi(ratingchar);
	    return mult * r;
	    }
      }
      }
      }
      
    fclose(file);
    //end of negative words test
  }
  FILE *file2 = fopen("positive_words.txt","r");
  if(file2!=NULL){
    while(fgets(line,sizeof line, file) != NULL){
      word=strtok(line,comma);
      sscanf(line, "%s %d", word2, &rating);
      
      for(i=0;i<2;i++){
	if(i==0){
	  ratingchar=strtok(NULL,comma);
	}
	else{
	  if(strcmp(werd,word)==0){
	    //word is found in positive words, so return its respective rating 
     	    return atoi(ratingchar);
	  }
	}
	
      }
    }
  }
    //if the word isnt found, its rating is 0
  return 0;
   
}

void main(){
  char *f;
  f="fuck";
  char *lost;
  lost="lost";
  char *out;
  out="outrageous";
  int rating;
  rating = getrating(f);
  printf("Rating for %s : %d\n",f, rating);
  char *boo;
  boo="boo";
  rating = getrating(lost);
  printf("Rating for %s : %d\n",lost,rating);
  rating = getrating(out);
  printf("Rating for %s : %d\n",out,rating);
  char *fine;
  fine="fine";
  rating=getrating(fine);
  printf("Rating for %s : %d\n",fine,rating);
  char *test;
  test="test";
  rating=getrating(test);
  printf("Rating for %s : %d\n",test,rating);
}
