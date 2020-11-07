// Simple utility program: copies the contents of a source file to a target file
// Objectives: to learn UNIX system calls open(), create(), read(), write(), and exit()
// ******************************************
// * To compile: command?                   *
// *     To run: command?                   *
// ******************************************

#include <iostream>
#include <fcntl.h>		// what for? Answer it contains file control options

using namespace std;

void copy(int, int);		// What are passed? Answer: File descriptors

char buffer[2048];		// What is the buffer used for? Answer: For the document to be read in to
						// What does “2048” mean? Answer: The size of the buffer, 2048 character(bytes)

int main(int argc, char *argv[])
{
   int fd_source, fd_target; // file descriptors; What are they used for? Answer: To refer to files in the program

   if (argc != 3) {		  // make sure command is correct with three arguments
      cout << "Need two arguments!" << endl;
      exit(1);
   }
   fd_source = open(argv[1], O_RDONLY);	// What is argv[1]? Answer: a pointer to the name of the file being copied
										// What is "O_RDONLY"  Answer: The file will be opened for read only
   if (fd_source == -1) {			// make sure "open" call is successful
      cout << "Cannot open " << argv[1] << " file!" << endl;
      exit(1);
   }
   fd_target = creat(argv[2], 0666);	// What does 0666 mean? Answer: set permissions 110 110 110 rw- rw- rw-
   if (fd_target == -1) {			// make sure "create" call is successful
      cout << "Cannot create " << argv[2] << " file!" << endl; // What is argv[2]? Answer: a pointer to the name of the file being made
      exit(1);
   }
   copy(fd_source, fd_target);   
 
   exit(0);   
}
void copy(int source, int target)
{
   int count;
   while ((count = read(source, buffer, 2048)) > 0)
      write(target, buffer, 2048);
}
