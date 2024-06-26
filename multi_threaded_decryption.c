#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


char* decrypt(char* str_message, int key){
  
  int len = strlen(str_message);

  for(int i = 0; i < len; i++) {
    if(str_message[0] >= 'a' && str_message[0] <= 'z') {
      str_message[i] = (str_message[i] - 'a' - key + 26) % 26 + 'a';
    } 
    else if(str_message[0] >= 'A' && str_message[0] <= 'Z') {
      str_message[i] = (str_message[i] - 'A' - key + 26) % 26 + 'A';
    }
    else if(str_message[0] >= '0' && str_message[0] <= '9') { 
    // I asked Giray Hocaya and wanted to encrypt the numbers, but it doesn't work on my computer.
      str_message[i] = (str_message[i] - '0' - key + 10) % 10 + '0';
    }
  }

  return str_message;
}

void *decrypt_thread(void *arg)
{
  int key = 2; // shift 2 times to decrypt the message
  char *str_message = (char *)arg;
  
  decrypt(str_message, key);
  void *usr = malloc(strlen(str_message) + 1); // +1 for null terminator
  strcpy(usr, str_message);

  pthread_exit(usr);

}
// Hint 1: You can use strlen function to find the length of the string for malloc function.
// Hint 2: You can use strcpy function to copy the decrypted message to the allocated memory.
// Notice: Do not use return pthread_exit function to return the decrypted message.

int main(){
	pthread_t t1,t2; //THREAD YAPISI IÇIN MEMORY DE YER AÇTIM

  char *str_message1 = strdup("FKUEQXGTA");
  char *str_message2 = strdup("OKUUKQP");


  void *first; // it will be used to store the return value of the first thread
	void *second; // it will be used to store the return value of the second thread

	/*
    Fill in this part... 
    1. Create threads
    2. join threads
    3. print the decrypted messages
    4. free memory
  */ 

   pthread_create(&t1, NULL, decrypt_thread, (void*)str_message1);
   pthread_create(&t2, NULL, decrypt_thread, (void*)str_message2);

   pthread_join(t1, &first);
   pthread_join(t2, &second);

   printf("%s ",(char*)first);
   printf("%s ",(char*)second);

  free(str_message1);
  free(str_message2);

	pthread_exit(NULL);
}
