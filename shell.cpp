/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};


    // TODO: add functionality
    // Create pipe
    int pipefds[2]; //creating pipe
    
    if(pipe(pipefds) == -1){
	    return 1;
    }
    // Create child to run first command
    // In child, redirect output to write end of pipe
    // Close the read end of the pipe on the child side.
    // In child, execute the command
    pid_t pid1 = fork();

    if(pid1 < 0){
	    return 1;
	}

    if(pid1 == 0){
	    close(pipefds[0]); //closing reading end

	dup2(pipefds[1], STDOUT_FILENO);
	close(pipefds[1]);
	execlp(*cmd1);
	_exit(1);
	}	//
    // Create another child to run second command
    // In child, redirect input to the read end of the pipe
    // Close the write end of the pipe on the child side.
    // Execute the second command.

    // Reset the input and output file descriptors of the parent.
	return 0;
}
