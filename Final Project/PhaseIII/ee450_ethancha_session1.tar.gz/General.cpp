#include "General.h"
#define SERVER "nunki.usc.edu"

using namespace std;

int main(int argc, char *argv[])
{     

  //reading passGn.txt file my code
  int apple1, apple2;
  int checker = 1;
  char msg[5];
  int a, b, c, t, get;
  int Cap1, Cap2;
  int g = 1;
  char s1[10];
  char s2[10];
  char *pch;
  char mport[5];
  char password[20];
  char check[40];
  char bufmod[40];
  ifstream ifile("passGn.txt");
    
  ifile >> mport;
  ifile >> password;

  strcpy(check, mport);
  strcat(check, password);

  //the following code is copied from Beej Guide p. 19-20
  int sockfd, sockbind, connectfd, sendfd;
  int status;
  int bytes_sent;
  struct addrinfo hints;
  struct addrinfo *res; //will point to the results
  
  struct hostent *he;
  char buf[50];
  struct sockaddr_storage their_addr;
  socklen_t addr_len;
  struct in_addr **addr_list;
  int i;
  //char **sa_data;
  struct sockaddr_in sin;
  socklen_t addrlen1 = sizeof(sin);
  int local_port;

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  
  hints.ai_family = AF_UNSPEC; // don't care IPV4 or IPv6
  hints.ai_socktype = SOCK_DGRAM; // UDP stream sockets

  //TODO: Check Port number 3830

cout << "Preparing for Phase 2" << endl;
cout << endl;

  status = getaddrinfo("nunki.usc.edu", "3830", &hints, &res);
  if (status != 0){
     cout << "getaddrinfo error" << endl;
    return 1;
    
  }

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

while(g){
  bytes_sent = recvfrom(sockfd, buf, 50, 0, (struct sockaddr *)&their_addr, &addr_len);


if(checker){
    get = getsockname(sockfd, (struct sockaddr *)&sin, &addrlen1);

    if(get == 0 && sin.sin_family == AF_INET && addrlen1 ==sizeof(sin)){
      local_port = ntohs(sin.sin_port);
    }

    freeaddrinfo(res);

    he = gethostbyname("nunki.usc.edu");

    //TODO finish display
    cout << "<General> has UDP port ";


    cout << local_port;   //local_port?

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
    
   cout << "for Phase 2" << endl;
   checker = 0;
}



//cout << "this is buf: " << buf << endl;
//cout << "this is check: " << check << endl;

  if(bytes_sent == -1){
	perror("recvfrom error");
	exit(1);
      }
  else if(bytes_sent != -1){
     cout << "Received the password from <Major>" << endl;
   }
  pch = strchr(buf, ' ');
  a = pch- buf;
  for(b = 0; b < a; b++){
    bufmod[b] = buf[b];
    }
  bufmod[b] = NULL;

//cout << "this is bufmod: " << bufmod << endl; 
//cout << "this is a: " << a << endl;
  if( !strcmp(check, bufmod) ) {
	cout << "Correct password from <Major>" << endl;
	pch = strchr(pch+1, ' ');
	c = pch-buf-a;
	//cout << "this is c: " << c << endl;
	//cout << "buf[b+a+1]: " << buf[15] << buf[16] << endl;
  	for(b = 0; b < (c-1); b++){
    		s1[b] = buf[(b+a+1)];
		//cout << "this is s1[b] " << s1[b] << endl;
    	}
	s1[b] = NULL;
	cout << "<Captain 1> has P(success rate) = " << s1 << "#" << endl;

	//cout << s1 << endl;
	pch = strchr(pch+1, ' ');
	t = pch-buf-c-a;
	//cout << "t-1 = " << (t-1) << endl;
  	for(b = 0; b < (t-1); b++){
    		s2[b] = buf[(b+a+c+1)];
    	}
	s2[b] = NULL;
	cout << "<Captain 2> has P(success rate) = " << s2 << "#" << endl;

	//cout << s1 << s2 << endl;
	g = 0;
}
  else if(strcmp(check, bufmod)){
       cout << "Wrong password from <Major>, try again" << endl;
   }
}

    close(sockfd);
    cout << "End of Phase 2 for <General>" << endl;
    cout << endl;
    
//***************************************************PHASEIII

cout << "Preparing for Phase 3" << endl;
cout << endl;
sleep(20);

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;    // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; //TCP stream sockets

  status = getaddrinfo("nunki.usc.edu", "21330", &hints, &res); //hardcodes Captain1's port address = 21200 + 130

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


    get = getsockname(sockfd, (struct sockaddr *)&sin, &addrlen1);

    if(get == 0 && sin.sin_family == AF_INET && addrlen1 ==sizeof(sin)){
      local_port = ntohs(sin.sin_port);
    }

    he = gethostbyname("nunki.usc.edu");

    //TODO finish display
    cout << "<General> has TCP port ";


    cout << "3930"; //General TCP Port = 3800 + 130

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

    cout << "for Phase 3" << endl;

  freeaddrinfo(res);
  close(sockfd);

    Cap1 = atoi(s1);
    Cap2 = atoi(s2);
    //cout << "This is Cap1 and s1 respectively: " << Cap1 << " " << s1 << endl;
    //cout << "This is Cap2 and s2 respectively: " << Cap2 << " " << s2 << endl;

    if((Cap1 >= Cap2)){
	msg[0] = 1;
	cout << "<Captain#1> has the highest probability of success" << endl;
	cout << "Command to start the mission sent to <Captain#1>" << endl;
	cout << "Command to be the backup for the mission sent to <Captain#2>" << endl;
apple1 = 1;
apple2 = 0;
     }
     else if((Cap1 < Cap2)){
	msg[0] = 0;
	cout << "<Captain#2> has the highest probability of success" << endl;
	cout << "Command to start the mission sent to <Captain#2>" << endl;
	cout << "Command to be the backup for the mission sent to <Captain#1>" << endl;
apple1 = 0;
apple2 = 1;
     }

//*****************This message is for Captain1
here:
if(apple1){
 memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;    // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; //TCP stream sockets

  status = getaddrinfo("nunki.usc.edu", "21330", &hints, &res); //hardcodes Captain's port address = 21300 + 130

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

     connectfd = connect(sockfd, res->ai_addr, res->ai_addrlen);
     if(connectfd == -1){
	perror("connect error");
      }

     sleep(7);

     sendfd = send(sockfd, msg, 5, 0);
     if(sendfd == -1){
	perror("send1 error");
      }
  freeaddrinfo(res);
  close(sockfd);
//cout << "Captain 1 message sent!" << endl;
	if(apple2){
		goto here1;
	}
	apple2 = 1;
}

//*****************This message is for Captain2
if(apple2){
 memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;    // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; //TCP stream sockets

  status = getaddrinfo("nunki.usc.edu", "21430", &hints, &res); //hardcodes Captain2's port address = 21300 + 130

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

     connectfd = connect(sockfd, res->ai_addr, res->ai_addrlen);
     if(connectfd == -1){
	perror("connect error");
      }

     sleep(7);

     sendfd = send(sockfd, msg, 5, 0);
     if(sendfd == -1){
	perror("send1 error");
      }
  freeaddrinfo(res);
  close(sockfd);


//cout << "Captain2 messages sent!" << endl;

if(!apple1){
apple1 = 1;
goto here;
}
}// else if loop

    //}
  

here1:
  

  cout << "End of Phase 3 for <General>" << endl;
  cout << endl;



     return 0; //return 0 for int main funciton
     
}
