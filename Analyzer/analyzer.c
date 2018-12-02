#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int global_rating=0;

int getrating(char * werd){
  FILE *file = fopen("negative_words.txt", "r");
  char comma[2]=",";
  int i;
  char line[100];
  char * word;
  char word2[100];
  char * ratingchar;
  int rating;
  
  //first, check positive words 
  if (file != NULL){
  //parse through each line, grabbing the word and its respective rating 
      while(fgets(line,sizeof line,file) != NULL){
	
	sscanf(line,"%s %d",word2, &rating);
      
      for(i=0;i<2;i++){
	if(i==0){
	  //get the rating of the word and assign it to ratingchar 
	 ratingchar = strtok(NULL,comma);
	
 	 }
	//once rating is declared...
	else{
	  //Word found in negative_words, so negate rating 
 	  if (strcmp(werd,word2) == 0){
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

int generate_rating(FILE * tweet, char * n){
  char word[144];
  char word2[144];
  char name[144];
  char punc[5] = ".,!?";
  int name_found =0;
  int temp = global_rating;
  int instance_rating;
  //strcpy(name,n);
  //name[0]=tolower(name[0]);
  //printf("Name Lower: %s\n",name);
  
  for(int i = 0;i<strlen(n);i++){
    if (isalpha(n[i]) && !ispunct(n[i])){
      name[i]=tolower(n[i]);
    }
  }
  printf("NEW NAME: %s",name);
  
  while(fscanf(tweet, " %144s", word2)==1){
   printf("word: %s\n",word2);
   temp = getrating(word2);
   
   for(int i = 0; i < strlen(word2); i++){
     if (isalpha(n[i]) && !ispunct(n[i])){
       word[i]=tolower(n[i]);
     
     }
   }
  
   int check = strcmp(word,name);
   if (check==0){
     name_found=1;
     printf("found name\n");
   }
   instance_rating = instance_rating + temp + getrating(word);
   printf("instance_rating : %d \n",instance_rating);
    
  }

    if(name_found==0){
      printf("Name not found in tweet\n");
      instance_rating=0;
    }
    else{
      printf("Name Found\n");
      instance_rating = global_rating + instance_rating;
    }
    
    printf("rating for this instance, where name is %s = %d\n global rating is: %d\n",name, instance_rating, global_rating);
    printf("Global Rating for %s : %d \t Instance Rating for %s : %d", name, global_rating, name, instance_rating);
    printf("\n name_found == %d\n",name_found);


    return instance_rating;
}

void main(){
  int r;
  FILE * tw = fopen("tweet.txt","r");
  char * n = "phil";
    
  FILE * tt = fopen("tweet.txt","r");
  r = generate_rating(tw,n);
  printf("Favorability rating for OBAMA is: %d\n",r);
  char * nn = "Obama";
  int p = generate_rating(tt,nn);
  printf("Favorability rating for Obama is : %d\n",p);
  
}
