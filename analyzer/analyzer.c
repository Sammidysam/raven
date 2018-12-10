#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <getopt.h>

int global_rating=0;

void strip_word(char *src){
  int i = 0;
  int p = 0;
  int len = strlen(src);
  for (i=0;i<len;i++){
    if(! ispunct(src[i])){
	src[p]=tolower(src[i]);
	p++;
    }
  }
}
      
	
int getrating(char * werd){
  FILE *file = fopen("negative_words.txt", "r");
  char comma[2]=",";
  int i;
  char line[100];
  char * word;
  char word2[100];
  char * ratingchar;
  int rating;
  //printf("werd: %s\n",werd);
  //strip_word(werd);
  //printf("stripped werd: %s\n",werd);
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

int generate_rating(char * tweet, char * n){
  //char word[144];
  char tweet_word[144]; //the word grabbed from the tweet 
  char name[144]; //the lowercase version of the name passed in 
  char punc[5] = ".,!?";
  int name_found =0;
  int temp;//= global_rating;
  int instance_rating = 0;
  char space [1] = " ";
  for(int i =0;i<strlen(n);i++){
    if(isalpha(n[i])&&!ispunct(n[i])){
      name[i]=tolower(n[i]);
    }
  }
  //name is the tolower() version of name
  //printf("NEW NAME: %s\n",name);
  
  //while(fscanf(tweet, " %144s", tweet_word)==1){
  char *token = strtok(tweet,space);
  
  while(token != NULL){
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

    token = strtok(tweet,space);
    global_rating=global_rating + instance_rating;
    //printf("Global Rating for %s : %d \t Instance Rating for %s : %d", name, global_rating, name, instance_rating);
    
    return instance_rating;
}
int main(int argc, char *argv[]){
      int ch;
      int l = 0; //likes
      int r = 0; //retweets
      int i = 0; //the id of the tweet
      char * t; //the tweet text
      char * date; //the date the tweet was sent 
  char * name;
  if(argc>1){
    while((ch = getopt(argc,argv,"n:l:r:i:t:d:")) != -1){
      switch(ch){
      case 'n':
	name = optarg;
	break;
      case 'l':
	l=atoi(optarg);
	break;
      case 'r':
	r=atoi(optarg);
	break;
      case 'i':
	i=atoi(optarg);
	break;
      case 't':
	t=optarg;
	break;
      case 'd':
	date=optarg;
	break;
      default:
	printf("Usage: ./analyzer -n <name> -l <likes> -r <retweets> -i<id> -t<tweet text>\n");
	exit(1);
      }
    }
  }
  else{
    printf("Usage: ./analyzer -n <name> -l <likes> -r <retweets> -i <id> -t <tweet text> \n");
    exit(1);
  }
  
      
      
  FILE * INFO = fopen("info.txt","r");
  char comma [2] = ",";
  /*char line[100];
  while(fgets(line,sizeof line,INFO) != NULL){
    name=strtok(line,comma);
  }
  */
  //printf("name : %s",name);
  //FILE * tw = fopen("tweet.txt","r");
  int rating = generate_rating(t,name);
  //printf("rating for %s: %d\n",name,p);
  time_t time_out = time(NULL);
  char * time_str = ctime(&time_out);
  time_str[strlen(time_str)-1] = '\0'; 
  printf("%s,%i,%d,%s\n",time_str,i,rating,date);
  //printf("likes : %d\n",l);
  //printf("retweets: %d\n",r);
  //printf("tweet: %s\n",t);
  //use getoptlong to parse commands
  
  
}
