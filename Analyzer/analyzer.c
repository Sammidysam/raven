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
	word=strtok(line,comma);
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
  fclose(file2);
    //if the word isnt found, its rating is 0
  return 0;
   
}

int generate_rating(FILE * tweet, char * n){
  //char word[144];
  char tweet_word[144]; //the word grabbed from the tweet 
  char name[144]; //the lowercase version of the name passed in 
  char punc[5] = ".,!?";
  int name_found =0;
  int temp;//= global_rating;
  int instance_rating = 0;
  
  for(int i =0;i<strlen(n);i++){
    if(isalpha(n[i])&&!ispunct(n[i])){
      name[i]=tolower(n[i]);
    }
  }
  //name is the tolower() version of name
  //printf("NEW NAME: %s\n",name);
  
  while(fscanf(tweet, " %144s", tweet_word)==1){
   temp = getrating(tweet_word);
   instance_rating = instance_rating + temp;
   for(int i = 0; i < strlen(tweet_word); i++){
     if (isalpha(tweet_word[i]) && !ispunct(tweet_word[i])){
       tweet_word[i]=tolower(tweet_word[i]);
     
     }
   }
  
   int name_check = strcmp(tweet_word,name);
   if (name_check==0){
     name_found=1;
   }
   //instance_rating = instance_rating + temp;
   
    
  }

    if(name_found==0){
      instance_rating=0;
    }
    else{
      instance_rating = temp + instance_rating;
       }

    
    global_rating=global_rating + instance_rating;
    printf("Global Rating for %s : %d \t Instance Rating for %s : %d", name, global_rating, name, instance_rating);
    
    return instance_rating;
}

void main(){
  int r;
  FILE * tw = fopen("tweet.txt","r");
  char * n = "phil";
    
  FILE * tt = fopen("tweet.txt","r");
  r = generate_rating(tw,n);
  printf("Favorability rating for phil is: %d\n",r);
  char * nn = "Obama";
  int p = generate_rating(tt,nn);
  printf("Favorability rating for Obama is : %d\n",p);
  FILE * tp = fopen("tweet.txt","r");
  int f = generate_rating(tp,nn);
  printf("Global rating: %d\n",global_rating);
  
}
