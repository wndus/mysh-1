#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include  <sys/types.h>
#include<errno.h>
#include<unistd.h>
#include "commands.h"
#include "built_in.h"

static struct built_in_command built_in_commands[] = {
  { "cd", do_cd, validate_cd_argv },
  { "pwd", do_pwd, validate_pwd_argv },
  { "fg", do_fg, validate_fg_argv }
};


static int is_built_in_command(const char* command_name)
{
  static const int n_built_in_commands = sizeof(built_in_commands) / sizeof(built_in_commands[0]);

  for (int i = 0; i < n_built_in_commands; ++i) {
    if (strcmp(command_name, built_in_commands[i].command_name) == 0) {
      return i;
    }
  }

  return -1; // Not found
}

/*
 * Description: Currently this function only handles single built_in commands. You should modify this structure to launch process and offer pipeline functionality.
 */
int evaluate_command(int n_commands, struct single_command (*commands)[512])
{


  if (n_commands > 0) {
    struct single_command* com = (*commands);

    assert(com->argc != 0);

    int built_in_pos = is_built_in_command(com->argv[0]);

    if (built_in_pos != -1) {
    
if (built_in_commands[built_in_pos].command_validate(com->argc, com->argv)) {
     if(strcmp(com->argv[0],"cd")==0 && strcmp(com->argv[1],"~")==0){chdir("/home/aeis");}   

	else if (built_in_commands[built_in_pos].command_do(com->argc, com->argv) != 0) {
          fprintf(stderr, "%s: Error occurs\n", com->argv[0]);
        }
else 	
	{}
	

      } 
else {
        fprintf(stderr, "%s: Invalid arguments\n", com->argv[0]);
        return -1;
      }
   
 } 




 else if (strcmp(com->argv[0], "") == 0) {
      return 0;  
    }
 
else if (strcmp(com->argv[0], "exit") == 0) {
      return 1;  
    }

 else {int j=0;
	while(com->argv[j]!=NULL){j++;}
	
	
	char * ch_s[]={"/usr/local/bin/","/usr/bin/","/bin/","/usr/sbin/","/sbin/"};
	char str_1[100]={0,};char str_2[100]={0,};char str_3[100]={0,};char str_4[100]={0,};
	char str_5[100]={0,};
		int i=0;

	
			strcat(str_1,ch_s[0]);
			strcat(str_1,com->argv[0]);
			strcat(str_2,ch_s[1]);
			strcat(str_2,com->argv[0]);
			strcat(str_3,ch_s[2]);
			strcat(str_3,com->argv[0]);
			strcat(str_4,ch_s[3]);
			strcat(str_4,com->argv[0]);
			strcat(str_5,ch_s[4]);
			strcat(str_5,com->argv[0]);	

			pid_t pid;
			int n=0;
			
			char * str[5]={str_1,str_2,str_3,str_4,str_5};
					
			int ret=-1;
			pid =fork();
			char *com_2=com->argv[0];
				
			
			if(com_2[0] != '/')
			{if(pid<0){printf("error");}

			else if(pid==0){ char * ch[10]={0,}; 
				while(i<5)

				{   ch[0]=str[i];
				for(int k=1;k<j;k++){ch[k]=com->argv[k];}ch[j]=NULL;
				
				ret=execv(str[i],ch);
			
				if(ret!=-1){n=1;
						break;
				}else{i++;}
					
				if(i==5 || n==1){
					if(i==5){
	 				printf("%s: Command not found\n",com->argv[0]);
					
						break;	
					}
					
}
				}
			}

			else{wait(1); }
			}if(i==5){exit(0);}


	if(com_2[0]=='/')
		{
				
		
		
		char *ch[10]={0,};
		for(int k=0;k<j;k++){ch[k]=com->argv[k];}
			ch[j]=NULL;
		
		int ret;
		
		if(pid<0){printf("error");}

		else if(pid==0 ){
		
			ret=execv(ch[0],ch);
			if(ret==-1){
			printf("bash: %s: No such file or directory\n",com->argv[0]); 
			exit(0);				
			}
		}
		else{wait(1); }
			}

 } 

  return 0;}
}

void free_commands(int n_commands, struct single_command (*commands)[512])
{
  for (int i = 0; i < n_commands; ++i) {
    struct single_command *com = (*commands) + i;
    int argc = com->argc;
    char** argv = com->argv;

    for (int j = 0; j < argc; ++j) {
      free(argv[j]);
    }

    free(argv);
  }

  memset((*commands), 0, sizeof(struct single_command) * n_commands);
}
