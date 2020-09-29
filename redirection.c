#include "headers.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h> 

char fullcommand[1000];
char inputfile[1000];
char outputfile[1000];
char *args[1000];

void redirection(char *command)
{

    int input_redirec_flag = 0;
    int output_redirec_flag = 0;
    
    for(int i=0;i<999;i++)
    {
        inputfile[i] = '\0';
        outputfile[i] = '\0';
        args[i] = '\0';
    }

    // Tokenizing full Command to get Flags

    strcpy(fullcommand, command);
    char *withincommands[1000];
    withincommands[0] = strtok(fullcommand, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        if(strcmp(withincommands[numwithincom], "<") == 0)
        {
            input_redirec_flag = 1;
        }
        if(strcmp(withincommands[numwithincom], ">") == 0)
        {
            output_redirec_flag = 1;
        }
        if(strcmp(withincommands[numwithincom], ">>") == 0)
        {
            output_redirec_flag = 2;
        }
    
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 

    // Getting Output File 

    if(output_redirec_flag != 0)
    {
        int oflag=0;
        for(int i = 0; i < numwithincom; i++)
        {
            if(oflag==1)
            {
                strcpy(outputfile, withincommands[i]);
            }
            if(strcmp(withincommands[i], ">") == 0 || strcmp(withincommands[i], ">>") == 0)
            {
                oflag=1;
            }    
        }

        // Getting Input File 

        if(input_redirec_flag != 0)
        {
            int iflag=0;
            int oflag=0;
            for(int i = 0; i < numwithincom; i++)
            {
                if(strcmp(withincommands[i], ">") == 0 || strcmp(withincommands[i], ">>") == 0)
                {
                    oflag=1;
                }  
                if(iflag==1 && oflag==0)
                {
                    strcpy(inputfile, withincommands[i]);
                }
                if(strcmp(withincommands[i], "<") == 0)
                {
                    iflag=1;
                }  
                
            }
        }
    }

    else
    {
        // Getting Input File 

        if(input_redirec_flag != 0)
        {
            int iflag=0;
            for(int i = 0; i < numwithincom; i++)
            {
                if(iflag==1)
                {
                    strcpy(inputfile, withincommands[i]);
                }
                if(strcmp(withincommands[i], "<") == 0)
                {
                    iflag=1;
                }    
            }
        }
    }

    // Getting command in new array args

    int oflag=0;
    int iflag=0;
    for(int i = 0; i < numwithincom; i++)
    {
        if(strcmp(withincommands[i], "<") == 0)
        {
            iflag = 1;
        }
        if(strcmp(withincommands[i], ">") == 0 || strcmp(withincommands[i], ">>") == 0)
        {
            oflag = 1;
        }
        
        if(oflag == 0 && iflag == 0)
        {
            args[i] = withincommands[i];
            // printf("%s\n", args[i]);
        }
    }

    // Saving stdin and stdout

    int stdin_pointer = dup(STDIN_FILENO);
    int stdout_pointer = dup(STDOUT_FILENO);

    pid_t pid = fork();

    // Fork failure
    if(pid < 0)
    {
        perror("Forking Failed");
        return;
    }

    // Child Process shall execute
    else if(pid == 0)
    {

        // If input file present dup2 stdin to this file
        if(input_redirec_flag == 1)
        {
            int input_fd = open(inputfile, O_RDONLY);
            if(input_fd < 0) 
            {
                printf("Input File does not exist\n");
                return;
            }   

            dup2(input_fd, 0);
            close(input_fd);
        }

        // If output files are present dup2 stdout to this file
        if(output_redirec_flag == 1)
        {
            int output_fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(output_fd < 0) 
            {
                printf("Output File does not exist\n");
                return;
            }

            dup2(output_fd, 1);         
            close(output_fd);

        }

        // If output files are present dup2 stdout to this file
        if(output_redirec_flag == 2)
        {
            int output_fd = open(outputfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(output_fd < 0) 
            {
                printf("Output File does not exist\n");
                return;
            }

            dup2(output_fd, 1);         
            close(output_fd);

        }

        // Execute the command
        int exec_flag = execvp(args[0], args);
        if ( exec_flag < 0) 
        {     
            printf("Command not found\n");
            return;
        }
        
        // Return original pointers to stdin and stdout
        dup2(stdout_pointer, 1);
        dup2(stdin_pointer, 0);
        close(stdout_pointer);
        close(stdin_pointer);
        
    }       

    // Parent process waits for child to end
    else 
    {
        int check_child;
        while (wait(&check_child) != pid);
    }

}
