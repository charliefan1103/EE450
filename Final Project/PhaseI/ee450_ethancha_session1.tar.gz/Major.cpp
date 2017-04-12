#include "Major.h"
#define SERVER "nunki.usc.edu"

using namespace std;

int main(int argc, char *argv[])
{     
  //the following code is copied from Beej Guide p. 19-20
  int sockfd, sockbind;
  int status;
  int bytes_sent;
  struct addrinfo hints;
  struct addrinfo *res; //will point to the results
  
  struct hostent *he;
  char buf[10];
  struct sockaddr_storage their_addr;
  socklen_t addr_len;
  struct in_addr **addr_list;
  int i;
  //char **sa_data;
  struct sockaddr_in sin;
  socklen_t addrlen1 = sizeof(sin);
  int local_port;
  int tab = 0;
  int bat = 0;
  int count = 0;

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  
  hints.ai_family = AF_UNSPEC; // don't care IPV4 or IPv6
  hints.ai_socktype = SOCK_DGRAM; // UDP stream sockets
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me
  //TODO: Check Port number 3430
  status = getaddrinfo(NULL, "3430", &hints, &res);
  if (status != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    return 1;
    
  }
  else{

    //inet_ntoa(addr);

    //mycode
    //TODO error-checking on getaddrinfo() p.22
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if(sockfd == -1){
      perror("socket error");
    }
    
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    
    if(sockbind == -1){
      perror("bind error");
      return 1;
    }
    
    freeaddrinfo(res);
    
    //TODO cout <Major> is now connected to the Captain#
        

    int get = getsockname(sockfd, (struct sockaddr *)&sin, &addrlen1);

    if(get == 0 && sin.sin_family == AF_INET && addrlen1 ==sizeof(sin)){
      local_port = ntohs(sin.sin_port);
    }

    he = gethostbyname("nunki.usc.edu");

    //TODO finish display
    cout << "<Major> has UDP port ";


    cout << "3430";   //local_port?

    /*
    sa_data = (char **)((res->ai_addr)->sa_data);
    for(i = 0; sa_data[i] != NULL; i++){
      printf("%s ",ntohs(*sa_data[i])); 
    }
    */

    cout  << " and IP address ";

    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
      printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");

    while((tab && bat) != 1){
      bytes_sent = recvfrom(sockfd, buf, 9, 0, (struct sockaddr *)&their_addr, &addr_len);
      
      if(bytes_sent == -1){
	perror("recvfrom error");
	exit(1);
      }
      count = count + 1;

      if((int)buf[4] == 56){
	cout <<"<Major> is now connected to the Captain1#" << endl;
	cout << "<Major> has received the following:" << endl;
	cout << count << ". ";
	cout << "<Captain1#>: Resources" << buf[0] << "#, Confidence" << buf[2] << "#, Record8#" <<  endl;
	tab = 1;
      }
      else if((int)buf[4] == 57){
	cout << "<Major> is now connected to Captain2#" << endl;
	cout << "<Major> has received the following:" << endl;
	cout << count << ". ";
	cout << "<Captain2#>: Resources" << buf[0] << "#, Confidence" << buf[2] << "# Record9#" <<  endl;
	bat = 1;
      }
      
      
    }

    close(sockfd);
    cout << "End of Phase 1 for <Major>" << endl;
    
     return 0; //return 0 for int main funciton
     
  } //endl of else statement
}
