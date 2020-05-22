/*----------------------------
  ;    K V S Krishna Teja  ;
  ;.........................*/
//History can be stored upto 1000 commands (can be changed if needed)
//pids of user generated commands are set parent id

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
void ep(char *argv[],char *input,char *input2);
void pipes(char **argv,char *input,char *input2);
void eh(char *argv[],char *input,char *input2);
void er(char **argv,char *input,char *input2);
void funcs(char **argv,char *input,char *input2);
char** div1(char *input,char comp[]);
struct hist{
  	char *process;
	int id;
	int fl;
           };
struct hist hy[1000];
int hcounter=0;
char a[1000];
char *input1;
int l1=0;
int flag2=0;
int flag=0;
int l2=-1;
int arguments=0;
char comp[]=" \t";

void handler(int sig)
{
  int status,g;
  pid_t pid;
  pid = waitpid(WAIT_ANY,&status,WNOHANG);
  if(pid>0)
  {
    for(g=0;g<=hcounter;g++)
    {
      if(hy[g].id==pid && hy[g].fl == 0)
      {
	printf("%s %d exited normally\n",hy[g].process,hy[g].id);
	hy[g].fl=1;
	break;
      }
    }
  }
}
int main()
{
  signal(SIGINT,SIG_IGN);
  signal(SIGCHLD, handler);
  int iter2=0;
  for(iter2=0;iter2<1000;iter2++)
  {
     hy[iter2].process= (char *)malloc(1000*(sizeof(char)));
  }
  char parentdirectory[1000];
  char workingdir[1000];
  char h[200];
  char *t=getenv("USER");
  gethostname(h,100);
  getcwd(a,1000);
  char *input,*input2;
  input = (char *)malloc(1000*(sizeof(char)));
  input1 = (char *)malloc(1000*(sizeof(char)));
  input2 = (char *)malloc(1000*(sizeof(char)));
  char *temp;
  char *hist[1000];
  hy[0].process="./a.out";
  hy[0].id=getpid();
  while(1)
  {
//      printf("%s,%s,%d,%d\n",a,input1,l1,l2);
    if(l1>=l2)
    {
   // printf("len=%d\n",l);
   // printf("%s\n",input);
      temp=input1;
      input1=input1+l2;
      printf("<%s@%s:~%s>",t,h,input1);
      input1=temp;
    }
    if(l1<l2)
    {
      printf("<%s@%s:%s>",t,h,input1);
    }
    int daridram=scanf("%[^\n]",input);
    getchar();
    if(daridram<1) continue;
    strcpy(input2,input);
    hcounter++;
    hy[hcounter].fl=1;
    //printf("%s\n",input);
    //printf("%s\n",a);
    //printf("%s",t);
   // printf("%s\n",h);
    char *p=NULL;
    char **argv;
    if(strcmp(input,"quit")==0)
    {
      exit(0);
    }
    funcs(argv,input,input2);
  }
}
void funcs(char **argv,char *input,char *input2)
{
    char *tp=(char *)malloc(1000*sizeof(char));
    argv=div1(input,comp);
//    printf("inp2is thdf%s\n",input2);
    if(strstr(input2,"|"))
    {
      pipes(argv,input,input2);
    }
    else if(strstr(input2,"<") || strstr(input2,">"))
    {
  //    printf("hell of a good call \n");
      er(argv,input,input2);
    }
    else if(strstr(input2,"hist"))
    {
      eh(argv,input,input2);
    }
    else
    {
      ep(argv,input,input2);
    }
}
char** div1(char *input,char comp[])
{
    char **argv = (char **)malloc(100*sizeof(char*));
    int i=0;
    char *tem;
    char bg[1000];
    strcpy(bg,input);
    tem=(char *)malloc(1000*sizeof(char));
    strcpy(tem,a);
    argv[0] = (char *)malloc(100*sizeof(char));
    argv[0]=strtok(bg,comp);
    while(argv[i]!=NULL)
    {
      i++;
      argv[i] = (char *)malloc(100*sizeof(char));
      argv[i]=strtok(NULL,comp);
    }
    
    int z=0;
    for(z=0;z<i;z++)
    {
      if(argv[z]!=NULL && argv[z][0]=='~')
      {
	argv[z]++;
	strcat(tem,argv[z]);
	strcpy(argv[z],tem);
//	printf("here %d command is changed into %s\n",z,argv[z]);
      }
    }
    if(strcmp(argv[i-1],"&")==0)
    {
      flag2=1;
      argv[i-1]=NULL;
    }
    arguments=i;
  //  printf("%d%s\n",i,argv[i-1]);
    return argv;
}
void ep(char **argv,char *input,char *input2)
{
    int tp; 
   // printf("command is%s\n",input2);
    if (strcmp(argv[0],"cd")==0)
    {
      if(flag==0){
        strcpy(hy[hcounter].process,input2);
        hy[hcounter].id=getpid();
      }
      flag=0;
//      printf("here %d is stored as p=%s,id=%d",hcounter,input2,hy[hcounter].id);
//      printf("argv1 %s\n",argv[1]);
      if (argv[1]==NULL)
      {
        chdir(a);
      }
      else if (argv[1]!=NULL)
      {
          int wqe=chdir(argv[1]);
	  if(wqe){
	  printf("%s such a directory or file cannot be accessed or does not exist\n",input2);
	  }
      }	
      getcwd(input1,150);
      l1=strlen(input1);
      l2=strlen(a);
  //    printf("%s,%s,%d,%d\n",a,input1,l1,l2);
    }
    else if(strcmp(argv[0],"pid")==0)
    {
      if(flag==0){
        strcpy(hy[hcounter].process,input2);
        hy[hcounter].id=getpid();
  //    printf("here %d is stored as p=%s,id=%d",hcounter,input2,hy[hcounter].id);
      }
      if (argv[1]==NULL)
      {
	flag=0;
	printf("command name: %s process id: %d\n",hy[0].process,hy[0].id);
      }
      else if(strcmp(argv[1],"all")==0)
      {
        int iter=0;
	flag=0;
        for(iter=1;iter<hcounter;iter++)
        {
	   printf("command name: %s process id: %d\n",hy[iter].process,hy[iter].id);
        }
      }
      else if(strcmp(argv[1],"current")==0)
      {
	int iter=0;
	flag=0;
//	printf("in the right area\n");
	for(iter=1;iter<hcounter;iter++)
	{
	  if(hy[iter].fl==0)
	  {
	    printf("command name: %s process id:%d\n",hy[iter].process,hy[iter].id);
	  }
	}
      }

    }
    else
    {
      int st=fork();
      if(st==0)
      {
	flag=0;
        execvp(argv[0],argv);
	printf("error occured while executing %s\n",input2);
	exit(0);
      }
      else
      {
	  tp = st;
	if(flag==0){
          strcpy(hy[hcounter].process,input2);
          hy[hcounter].id=tp;
//	  printf("here %d is stored as p=%s,id=%d",hcounter,input2,hy[hcounter].id);
	}
	if(flag2!=1)
	{
	  waitpid(st,&st,0);
	}
	else if(flag2==1)
	{
//	   printf("here %s process flag is set to 0\n",hy[hcounter].process);
	  hy[hcounter].fl=0;
	}
	flag2=0;
      }
    }
}
void eh(char **argv,char *input,char *input2)
{
  int l=0,iterl=0;
  char *tp;
  tp=(char *)malloc(1000*sizeof(char));
 // printf("correct call\n");
  if(flag==0){
    strcpy(hy[hcounter].process,input2);
    hy[hcounter].id=hy[0].id;
  }
  if(argv[0]!=NULL && argv[0][0]=='!')
  {
    argv[0]+=5;
    flag=1;
    l=atoi(argv[0]);
    strcpy(tp,hy[l].process);
//    printf("command is %s\n",tp);
//    printf("here command is changed to%s\n",argv[0]);
    funcs(argv,tp,tp);
    flag=0;/*
    if(strstr(hy[l].process,"hist"))
    {
      eh(argv,input2,input2);
    }
    else
    {
      ep(argv,input2,input2);
    }*/
  }
  else if(argv[0][4]!='\0')
  {
    argv[0]+=4;
    l=atoi(argv[0]);
    if(l<hcounter-1){
      for(iterl=hcounter-l;iterl<hcounter;iterl++)
      {
        printf("%d. %s\n",iterl,hy[iterl].process);
      }
    }
    else{
      printf("NOT POSSIBLE\n");
    }
  }
  else if(argv[0]!=NULL && argv[0][4]=='\0')
  {
    for(iterl=1;iterl<hcounter;iterl++)
    {
      printf("%d. %s\n",iterl,hy[iterl].process);
    }
  }
}
void er(char **argv,char *input,char *input2)
{
  char *f1,*f2;
  int flagn=0;
  f1=(char *)malloc(1000*sizeof(char));
  f2=(char *)malloc(1000*sizeof(char));
  int gt=0,lt=0,it=0;
  char *command;
  command=(char *)malloc(1000*sizeof(char));
  for(it=0;it<arguments;it++)
  {
    if(argv[it]!=NULL && strcmp(argv[it],">")==0)
    {
      gt=1;
      if(flagn==0)
      {
	strcpy(f1,argv[it+1]);
	flagn=1;
      }
      else
      {
	strcpy(f2,argv[it+1]);
      }
    }
    else if(argv[it]!=NULL && strcmp(argv[it],"<")==0)
    {
      lt=1;
      if(flagn==0)
      {
	strcpy(f1,argv[it+1]);
	flagn=1;
      }
      else
      {
	strcpy(f2,argv[it+1]);
      }
    }
    if(gt==0 && lt==0)
    {
      strcat(command,argv[it]);
      strcat(command,"  ");
    }
  }
  int rd=fork();
  if(rd==0){
//    printf("command=%s\n",command);
    if(gt==0 || lt==0)
    {
      if(lt==1)
      {
        freopen(f1,"r",stdin);
      }
      if(gt==1)
      {
        freopen(f1,"w",stdout);
      }
    }
    else if(gt==1 && lt==1)
    {
      freopen(f1,"r",stdin);
      freopen(f2,"w",stdout);
    }
  //  printf("command is %s\n",command);
    flag=1;
    funcs(argv,command,command);
   /* if(strstr(command,"hist"))
    {
      flag=1;
      eh(argv,command,command);
    }
    else
    {
      flag=1;
      ep(argv,command,command);
    }*/
    exit(0);
  }
  else
  {
    int tp=rd;
	if(flag==0){
          strcpy(hy[hcounter].process,input2);
          hy[hcounter].id=tp;
//	printf("here %d is stored as p=%s,id=%d",hcounter,input2,hy[hcounter].id);
	}
    waitpid(rd,&rd,0);
  }
}
void pipes(char **argv,char *input,char *input2)
{
  if(flag==0)
  {
    strcpy(hy[hcounter].process,input2);
    hy[hcounter].id=hy[0].id;
  }
  int np=0;
  int iter=0;
 /* while(argv[iter]!=NULL)
  {
    printf("%s,",argv[iter]);
    iter++;
  }*/
  char commands[1000][1000]={'\0'};
  int c=0;
  for(iter=0;iter<arguments;iter++)
  {
   if(strcmp(argv[iter],"|")==0)
   {
     np++;
     c++;
   } 
   else if(argv[iter]!=NULL)
   {
     strcat(commands[c],argv[iter]);
     strcat(commands[c],"  ");
   }
  }
//  printf("command =%s\n",commands[c]);
  int fd[1000][2];
  int i=0;
  int pid;
  for(i=0;i<c;i++)
  {
    pipe(fd[i]);
  //  printf("fd are %d%d\n",fd[i][0],fd[i][1]);
  }
  for(i=0;i<=c;i++)
  {
    int temp=0;
    pid=fork();
    if(pid==0)
    {
      if(i==0)
      {
	dup2(fd[0][1],1);
	close(fd[0][0]);
	for(temp=0;temp<c-1;temp++)
	{
	  close(fd[temp][0]);
	  close(fd[temp][1]);
	}
      }
      if(i==c)
      {
	dup2(fd[i-1][0],0);
	close(fd[i-1][1]);
	for(temp=0;temp<c-1;temp++)
	{
	  close(fd[temp][0]);
	  close(fd[temp][1]);
	}
      }
      else
      {
	dup2(fd[i-1][0],0);
	dup2(fd[i][1],1);
	close(fd[i-1][1]);
	close(fd[i][0]);
	for(temp=0;temp<c-1;temp++)
	{
	  if(temp!=i-1 && temp!=i)
	  {
	    close(fd[temp][0]);
	    close(fd[temp][1]);
	  }
	}
      }
      flag=1;
  //   printf("command =%s\n",commands[c]);
      funcs(argv,commands[i],commands[i]);
      exit(1);
    }
/*    else
    {
      wait(NULL);
    }*/
  }
     for(i=0;i<c;i++)
     {
       wait(NULL);
     }
  for(i=0;i<c;i++)
  {
    close(fd[i][0]);
    close(fd[i][1]);
  }
}
