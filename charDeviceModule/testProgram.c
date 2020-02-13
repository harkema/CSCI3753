#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>


#define BUFF_SIZE 1024

int main()
{
  bool keepRunning = true;
  char command;
  int bytesToRead;
  int file = open("pa2_character_device",  O_RDWR);
  char buffer[BUFF_SIZE];

  while(keepRunning)
  {
    printf("Press r to read from device\n");
  	printf("Press w to write to the device\n");
  	printf("Press s to seek into the device\n");
  	printf("Press e to exit from the device\n");
  	printf("Press anything else to keep reading or writing from the device\n");
    printf("Enter Command:\n");

    command = getchar();

    if(command == 'r')
    {
      printf("Enter the number of bytes you want to read: \n");
      scanf("%d", &bytesToRead);
      read(file, buffer, bytesToRead);
      printf("Data read from the device: %s]\n", buffer);
    }
    else if(command == 'w')
    {
      keepRunning = false;
    }
    else if(command == "s")
    {
      keepRunning = false;
    }
    else if(command == "e")
    {
      keepRunning = false;
    }
    else
    {
      keepRunning = false;
    }
  }


  return 0;
}
