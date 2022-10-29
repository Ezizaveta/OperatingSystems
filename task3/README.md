Create a data file that only the owner can write and read (this can be done with the shell chmod 600 file command).
This program :
1) Opens the file using fopen(3). If fopen() is successful, the file should be closed using fclose(3). 
2) Prints an error message using perror(3C) if the file could not be opened.
3) Use setuid(2) fot matching the real and effective user IDs 

Check the operation of this program:
1) Execute the program and see the output
2) Make the program available for the members of your group to run and let your classmates execute the program.
3) With the "chmod u+s prog" command, set the user ID setting bit and let your classmates execute this program again.
