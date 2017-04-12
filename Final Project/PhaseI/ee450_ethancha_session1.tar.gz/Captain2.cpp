#include "Captain2.h"
#define SERVER "nunki.usc.edu"

using namespace std;

int main(int argc, char *argv[])
{
  //reading Captain1.txt file my code
  char str1[15];
  char str2[15];
  char num1[2];
  char num2[2];
  char r[2];
  char c[2];
  char msg[10];
  ifstream ifile("Captain2.txt");
    

  ifile.getline(str1,15,'$');
  ifile >> num1;
  ifile.getline(str2,15,'$');
  ifile >> num2;

  if(strcmp(str1,"Resources") == 0){
    strcpy(r,num1);
    strcpy(c,num2);
  }
  else{
    strcpy(r,num2);
    strcpy(c,num1);
  }
  strcpy(msg, r);
  strcat(msg," ");
  strcat(msg,c);
  strcat(msg," ");
  strcat(msg,"9");
  

  //Run value through a function set it to Network Byte Order (Big-Endian MSB on far left page11
  //host to network, network to host conversion page 12
  //do not have bind fucntion for Captain since it is dynamically allocated
  //perhaps error checking is needed for info getaddrinfo() returns p.19

  //Copied code from Beej Manual p.20 of Beej Manual
  int sockfd;
  int status;
  int bytes_sent;
  //char z[2];
  struct addrinfo hints;
  struct addrinfo *res; // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;    // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_DGRAM; //UDP stream sockets
  struct hostent *he; 
  struct in_addr **addr_list;
  int i;
  struct sockaddr_in sin;
  socklen_t addrlen1 = sizeof(sin);
  int local_port;

  //get ready to connect
  status = getaddrinfo("nunki.usc.edu", "3430", &hints, &res); //hardcodes Major's IP address = 3300 + 130

  if(status != 0){
    cout << "getaddrinfo error" << endl;
    return 1;
  }
  //servinfo now points to a link list of 1 or more struct adrinfos
  
  //etc.
  //end of copied code from Beej Manual p.20
  
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if(sockfd == -1){
    perror("socket error");
  }

  /*
  cout << "Do you want to connect to Major? (y/n)" << endl;
  cin >> z;


  //TODO finish disconnect (close) in if statement
  if(strcmp(z,"n") == 0){
    cout << "<Captain2#> disconnects from <Major>" << endl;
  }
  else if(strcmp(z,"y") == 0){*/
    bytes_sent = sendto(sockfd, msg, 10, 0, res->ai_addr,res->ai_addrlen); 




int get = getsockname(sockfd, (struct sockaddr *)&sin, &addrlen1);

    if(get == 0 && sin.sin_family == AF_INET && addrlen1 ==sizeof(sin)){
      local_port = ntohs(sin.sin_port);
    }

    he = gethostbyname("nunki.usc.edu");

    //TODO finish display
    cout << "<Captain#2> has UDP port ";


    cout << local_port;

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

    cout << "Sending log file to the <Major>" << endl;

    if(bytes_sent == -1){
      perror("sendto error");
      exit(1);
    } 
    //}
  
  
  freeaddrinfo(res);
  close(sockfd);
  cout << "End of Phase 1 for <Captain2#>" << endl;
  
  return 0; //return 0 for int main funciton
}
