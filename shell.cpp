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

    int pipefd[2]; //creating pipe, pipefd[0] is read, pipefd[1] is write
    pid_t cpid1;//process ID for children
    pid_t cpid2;

    pipe(pipefd);
    cpid1 = fork();

    if (cpid1 == 0) {    //child writes to pipe
        dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
        close(pipefd[0]);
        execlp(cmd1[0], cmd1[0], cmd1[1], cmd1[2]);	
    }
    else //when else executes, we are in parent
    {
         cpid2=fork(); 

	 if(cpid2 == 0){ //read output from first child
		 dup2(pipefd[0], STDIN_FILENO);
		 close(pipefd[0]);
		 close(pipefd[1]);
		 execlp(cmd2[0], cmd2[0], cmd2[1], cmd2[2] );
	 }
	 else{
		 close(pipefd[0]);//close parent 
		 close(pipefd[1]);
	 }
    }


    // Create child to run first command
    // In child, redirect output to write end of pipe
    // Close the read end of the pipe on the child side.
    // In child, execute the command

    // Create another child to run second command
    // In child, redirect input to the read end of the pipe
    // Close the write end of the pipe on the child side.
    // Execute the second command.

    // Reset the input and output file descriptors of the parent.
}
