#include<winsock2.h>
#include<stdio.h>
#include<dirent.h>
#include <string.h>
#include<sys/stat.h>



int main() {
	
	SOCKET sockfd;
  int len;
  struct sockaddr_in address;
  int result;
  
  char dirPath[100],dupli[100],dupli1[100],userFile[100],sysFile[100];
  int siNo;
 
  WSADATA wsadata;
  if(WSAStartup(0x101,(LPWSADATA)&wsadata) != 0) {
    printf("Winsock Error\n"); 
    exit(1);
  }
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("192.168.56.1");
  address.sin_port = 8080;
  len = sizeof(address);
 
  result = connect(sockfd, (struct sockaddr *)&address, len);  
  if(result == -1) {
    printf("Connect Error");
    exit(1);
  }
  
  
    recv(sockfd,dirPath,100,0);
    struct dirent *de;
  char data[100];
  DIR *dr=opendir(dirPath);
  if(dr)
  { 
     
 	while((de=readdir(dr))!=NULL)
  	{ 
  	strcpy(data,de->d_name);
    send(sockfd,data, 100, 0);
  
}
shutdown(sockfd,1);
rewinddir(dr);
}

 char selectNo,option;

     recv(sockfd,&option,sizeof(option),0);

int count =0;
while((de=readdir(dr))!=NULL)
 {  
 	count ++;
 	recv(sockfd,&selectNo,sizeof(selectNo),0);
 	if(selectNo==(count-1))
 	{
       
 		switch(option)
 		{
 		    case 1:
 		    	{
 		    		strcpy(dupli1,dirPath);
 		    		printf("%s%s",dirPath,de->d_name);
 		    		if(remove(strcat(dirPath,de->d_name))==0)
 		    		{  
 		    			printf("\nThe file deleted successsfully\n");
 		    			
					 }
					 else if(rmdir(strcat(dupli1,de->d_name))==0)
					 {  
					 	printf("\n The folder is deleted\n");
					 }
					 else
					 {  
					 	printf("\nThe entered serial no. is a non empty folder\n");
					 }
					 break;
				 }
			case 2:
			{
				char statName[50];
				struct stat info;
				printf("Enter the new filename\n");
				scanf("%s",userFile);
				strcpy(sysFile,de->d_name);
				strcpy(dupli,dirPath);
				rename(strcat(dirPath,sysFile),strcat(dupli,userFile));
				  if (stat(dupli,&info)==0)
				  {
				  	printf("\nThe file renamed successfully");
				  }
				  else
				  {
				  	printf("\nThe file is being used by another application");
				  }
				  break;
				 }	 
		 }
	 }
 }



  closesocket(sockfd);

     
  
}



