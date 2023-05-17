#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "json.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <string>

using json = nlohmann::json;
using namespace std;


char *extract_cookies(std::string text) {
    const unsigned start = text.find("Cookie: ");
    const unsigned end = text.find("; Path");
    if (start != std::string::npos && end != std::string::npos) {
        char* substring =  (char*) malloc(end - start + 1);
        strncpy(substring, text.c_str() + start, end - start);
        substring[end - start] = '\0';
        return substring;
    }
    return nullptr;
}


bool digit(std::string str){

  bool isdig = false;
  for(char ch:str){
    if(std::isdigit(ch)){
      isdig = true;
      break;
    }

  }
  return isdig;
}

bool isspace(std::string str){

  bool isspace = false;
  
  for(char ch:str){
    if(ch == ' '){
      isspace= true;
      break;
    }

  }
  return isspace;

}

bool digits(std::string str){

  bool isdig = true;
  for(char ch:str){
    if(!std::isdigit(ch)){
      isdig = false;
      break;
    }

  }
  return isdig;
}

nlohmann::json receive_json(std::string str) {

            unsigned first = str.find("[{");
            unsigned last = str.find("}]");
            string to_print = str.substr(first, last - first + 2);
            json to_print1 = json::parse(to_print);

    return to_print1;

}

nlohmann::json receive_json_one_book(std::string str) {

            unsigned first = str.find("{");
            unsigned last = str.find("}");
            string to_print = str.substr(first, last - first + 2);
            json to_print1 = json::parse(to_print);

    return to_print1;

}
int main() {

  int sockfd;
  
  char *message;
  char *response;
  string autorization = "NU";
  string token_JWT = "NU";
  std::map<std::string, int> count;

  while (1) {

    char *command = (char *)malloc(50 * sizeof(char));
    fgets(command, 50, stdin);

    //exit
    if (!strncmp(command, "exit\n", 5)) {
      std::cout << "Good bye!" << endl;
      break;
    }
    //register
    else if (!strncmp(command, "register", 8)) {
      string username;
      std::cout << "username=";
      std::getline(std::cin, username);


      string password;
      std::cout << "password=";
      std::getline(std::cin, password);

      if(username.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
       if(isspace(username) == true){
        std::cout<<"Error! Username contains whitespace.\n";
        continue;

      }

      if(password.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;
      }

      if(isspace(password) == true){
        std::cout<<"Error! Password contains whitespace.\n";
        continue;

      }

        json credentiale = {
          {"username", username},
          {"password", password},
         };
  
        message = compute_post_request((char*)"34.254.242.81", (char*)"/api/v1/tema/auth/register", (char*)"application/json", credentiale, 1, NULL, 0);

        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);


      send_to_server(sockfd, message);

      response = receive_from_server(sockfd);

      if (strstr(response, "error") != NULL) {
        std::cout << "400 - Bad Request - Username indisponibil\n";
        continue;
      } else {
        std::cout << "200 - OK - User registered successfully\n" ;
        continue;
      }
        close_connection(sockfd);

    }
    //login
     else if (!strncmp(command, "login", 5)) {

      string username;
      std::cout << "username=";
      std::getline(std::cin, username);


      string password;
      std::cout << "password=";
      std::getline(std::cin, password);

      if(username.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
       if(isspace(username) == true){
        std::cout<<"Error! Username contains whitespace.\n";
        continue;

      }

      if(password.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;
      }
       if(isspace(password) == true){
        std::cout<<"Error! Password contains whitespace.\n";
        continue;

      }

        json credentiale_login = {
          {"username", username},
          {"password", password},
         };


        string credentiale_str_login = credentiale_login.dump();
  
        message = compute_post_request((char*)"34.254.242.81", (char*)"/api/v1/tema/auth/login", (char*)"application/json", credentiale_login, 1, NULL, 0);


        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);


        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);

        char *err = strstr(response, "error");
      
         if (err != NULL) {

            char *not_reg = strstr(response,"No account with this username!");

            if(not_reg != NULL) {
              std::cout<< "Error! No account with this username!\n";
              continue;
            }
             else {
              std::cout << "Error! Credentials are not good!\n";
             continue;}
        } else {
        std::cout << "200 - OK - Bun venit!\n";
         autorization = extract_cookies(response);
      
      } 
        close_connection(sockfd);

    }
    //enter library
     else if (!strncmp(command, "enter_library\n", 14)){

        if (autorization.compare("NU") == 0) {
        cout << "Error! You are not logged in!\n";
        continue;
      } else {
         std::cout << "Ok-Welcome\n";

        string cookies[1];
        cookies[0] = autorization;

        message = compute_get_request((char*)"34.254.242.81", (char*)"/api/v1/tema/library/access", NULL, cookies, 1);
       
        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);

        char *err = strstr(response, "error");
        if (err != NULL) {
             std::cout << "Error! Please login in first!\n";
             continue;
          } else {
            
          std::string str(response);
          unsigned first = str.find("token");
          unsigned last = str.find("}");
          size_t n = strlen("token:");
          std::string token = str.substr(first + n + 2, last - first - n - 3);
          token_JWT = "Authorization: Bearer " + token;
          
        
     }
      close_connection(sockfd);

     }

  }
  //get books
   else if (!strncmp(command, "get_books\n", 9)) {

    if(token_JWT == "NU") {
      std::cout<<"Error! You don't have access to the library.\n";
      continue;
    }
    else {

        string token[1];
        token[0] = token_JWT;

        message = compute_get_request((char*)"34.254.242.81", (char*)"/api/v1/tema/library/books", NULL, token, 1);

        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);

       if(strstr(response,"error") != NULL) {

          std::cout << "Error! Something bad happened!\n";
          continue;
        }
      else {
      

          if (strstr(response, "[{") == NULL &&
                  strstr(response, "}]") == NULL) {
            std::cout<<"There are no books!\n";
            continue;
          }

          else {
              std::string string_from_response(response);
              json raspuns = receive_json(string_from_response);
              for(const auto&elem : raspuns) {
                std::cout << "id: " << elem["id"] << "\n" << "title: " << elem["title"] << "\n\n";
              }
          }
      }
        close_connection(sockfd);

    }


   }

   //add book
   else if(!strncmp(command, "add_book\n", 9)) {

    if(token_JWT.compare("NU") == 0) {
      std::cout<<"Error! You don't have access to the library.\n";
      continue;
    }
    else {

      string title;
      std::cout<<"title=";
      std::getline(std::cin,title);


      string author;
      std::cout<<"author=";
      std::getline(std::cin, author);

      string genre;
      std::cout<<"genre=";
      std::getline(std::cin, genre);

      string publisher;
      std::cout<<"publisher=";
      std::getline(std::cin, publisher);

      string page_count;
      std::cout<<"page_count=";
      std::getline(std::cin,page_count);

      if(title.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digit(title) == true) {
        std::cout<<"Error! Title contains digit!\n";
        continue;
        }

        if(author.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digit(author) == true) {
        std::cout<<"Error! Author contains digit!\n";
        continue;
      }
         if(genre.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digit(genre) == true) {
        std::cout<<"Error! Genre contains digit !\n";
        continue;
      }


       if(publisher.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
    
       if(page_count.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digits(page_count) == false) {
        std::cout<<"Error! Page_count must be a number!\n";
        continue;
      }

       if(isspace(page_count) == true){
        std::cout<<"Error! Page_count contains whitespace, it must be a number.\n";
        continue;

      }

     json book = {
        {"title", title},         
        {"author", author},
        {"genre", genre}, 
        {"publisher", publisher},        
        {"page_count", page_count},
     };

        string token1[1];
        token1[0] = token_JWT;
      
        message = compute_post_request((char *)" 34.254.242.81", (char *) "/api/v1/tema/library/books",
                                                    (char *)"application/json", book , 1, token1, 1);

        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);


        if(strstr(response, "HTTP/1.1 200") != NULL) {
          
          std::cout<<"The book was added\n";
        }

         else {
           
           std::cout << "Error! Something bad happened!\n";
           continue;
       }

         close_connection(sockfd);

    }

   }
   //get book
   else if (!strncmp(command, "get_book\n", 8)){

      std::string id;
      std::cout<<"id=";
      std::cin>>id;
      if(id.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digits(id) == false) {
        std::cout<<"Error! ID must be a number!\n";
        continue;
      }

       if(isspace(id) == true){
        std::cout<<"Error! ID contains whitespace.\n";
        continue;

      }
    if(token_JWT == "NU") {
      std::cout<<"Error! You don't have access to the library.\n";
      continue;
    }
    else {

        string token3[1];
        token3[0] = token_JWT;

          char id_copy[32];
          strcpy(id_copy, id.c_str());
          char url[51]= "/api/v1/tema/library/books/";
          strcat(url, id_copy);

          message = compute_get_request((char*)"34.254.242.81",(char*) url, NULL, token3, 1);

          
          sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
          send_to_server(sockfd, message);

          response = receive_from_server(sockfd);

          if(strstr(response,"error") != NULL) {

          if(strstr(response, "404 Not Found") != NULL){
            std::cout<<"Please try another id, because this is not found or is invalid.\n";
            continue;
          }

         else {std::cout << "Error! Something bad happened!\n";
          continue;
         }
          }
          else {

          if (strstr(response, "{") == NULL &&
                  strstr(response, "}") == NULL) {
            std::cout<<"There are no books!\n";
            continue;
          }
          else {
              std::string string_from_response(response);
              json raspuns = receive_json_one_book(string_from_response);
              std::cout<<raspuns<<endl;
            }
      }
        close_connection(sockfd);
      }
    }
    
    //delete book
     else if (!strncmp(command, "delete_book\n", 11)) {

      std::string id;
      std::cout<<"id=";
      std::cin>>id;
      if(id.empty()) {
        std::cout<<"Error! Please introduce a non-empty data.\n";
        continue;

      }
      if(digits(id) == false) {
        std::cout<<"Error! ID must be a number!\n";
        continue;
      }

       if(isspace(id) == true){
        std::cout<<"Error! ID contains whitespace.Please give a valid number\n";
        continue;

      }

      if(token_JWT == "NU") {
      std::cout<<"Error! You don't have access to the library.\n";
      continue;
    }

    else {
       
        string token3[1];
        token3[0] = token_JWT;

        char id_copy[32];
        strcpy(id_copy, id.c_str());

        string tokens4[1];
        tokens4[0] = token_JWT;

        char id_copy1[32];
        strcpy(id_copy1, id.c_str());
        char url1[51]= "/api/v1/tema/library/books/";
        strcat(url1, id_copy1);
        message = compute_delete_request((char*)"34.254.242.81",(char*) url1, NULL, tokens4, 1);

        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);

        if(strstr(response,"error") != NULL) {

          if(strstr(response, "404 Not Found") != NULL){
            std::cout<<"Please try another id, because this is not found or is invalid.\n";
            continue;
          }

         else {std::cout << "Error! Something bad happened!\n";
          continue;
         }
        }
        else {
          std::cout<<"Book deleted.\n";
          continue;
        }


    }

  }

      //logout
      else if (!strncmp(command, "logout\n", 7)){
        if (autorization == "NU") {
        cout << "Error! You are not logged in!\n";
        continue;
      } else {
        string cookies1[1];
        cookies1[0] = autorization;

        message = compute_get_request((char*)"34.254.242.81", (char*)"/api/v1/tema/auth/logout", NULL, cookies1, 1);

        sockfd = open_connection((char*)"34.254.242.81", 8080, PF_INET, SOCK_STREAM, 0);
        
        send_to_server(sockfd, message);

        response = receive_from_server(sockfd);
     

        char *err = strstr(response, "error");
        if (err != NULL) {
             std::cout << "Error! Please login in first!\n";
             continue;
          } else {
            std::cout<<"Logout with success.\n";
          }

      }
       autorization = "NU";
        token_JWT = "NU";
        close_connection(sockfd);
      }
  }
    return 0;
}