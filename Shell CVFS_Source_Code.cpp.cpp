/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  head file inclusion
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
/////////////////////////////////////////////////////////////////////////////////////////////////

// Max file size
# define MAXFILESIZE 100         

// Maximum number of files that we can open

# define MAXOPENEDFILES 20

// maximum number of files that we can creat             
# define MAXINODE 5                     

# define READ 1                         
# define WRITE 2
# define EXECUTE 4

# define REGULARFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

# define EXECUTE_SUCCESS 0

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for error handling
//
/////////////////////////////////////////////////////////////////////////////////////////////////

# define ERR_INVALID_PARAMETER -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXISTS -3
# define ERR_FILE_NOT_EXIST -4
# define ERR_PERMISSION_DENIED -5
# define ERR_INSUFFICIENT_SPACE -6
# define ERR_INSUFFICIENT_DATA -7

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description:        holds info
//
/////////////////////////////////////////////////////////////////////////////////////////////////


struct BootBlock
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description:        holds informaiton about file system
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalINodes;
    int FreeInodes;

};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock
//  Description:        holds informaiton about the file
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFilesize;
    int FileType;
    int ReferenceCount;
    int Permission;
    int LinkCount;
    char *Buffer;

    struct Inode *next;
}INODE, *PINODE, **PPINODE;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable
//  Description:        holds informaiton about the opened file
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Description:        holds informaiton about the process
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPENEDFILES];
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global variables or bojects used in the projects
//
/////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InitiliseUAREA
//  Description :      It is used to initilise the content of UAREA
//  Author  :          Rishikesh Shinde
//  Date    :          10/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void InitiliseUAREA()
{
    strcpy(uareaobj.ProcessName , "Myexe");

    int i = 0;

    while(i < MAXOPENEDFILES)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    cout<<"Shell CVFS : UAREA initilised Successfully\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InitiliseSuperBlock
//  Description :      It is used to initilise the content of superblock
//  Author  :          Rishikesh Shinde
//  Date    :          10/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void InitiliseSuperBlock()
{
    superobj.TotalINodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;
    cout<<"Shell CVFS : SuperBlock initilised Successfully\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    CreateDILB
//  Description :      It is used to create linked list of Inodes
//  Author  :          Rishikesh Shinde
//  Date    :          10/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFilesize = 0;
        newn->LinkCount = 0;
        newn->Permission = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->next = newn;
            temp = temp->next;
        }

        i++;
    }
    cout<<"Shell CVFS : DILB created Successfully\n";
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    StartAuxilarryDataInitilisation
//  Description :      It is used to initilise the auxilary data
//  Author  :          Rishikesh Shinde
//  Date    :          10/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////



void StartAuxilaryDataInitilisation()
{
    
    strcpy(bootobj.Information , "Boot process of Oprating System done");

    cout<<bootobj.Information<<"\n";

    InitiliseSuperBlock();
    CreateDILB();
    InitiliseUAREA();

    cout<<"Shell CVFS : Auxilary data initilised Successfully\n";

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DisplayHelp
//  Description :      It is used to display the info about commands
//  Author  :          Rishikesh Shinde
//  Date    :          11/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-------------------------------------------------------------------------------------\n");
    printf("-------------------------Command Manual of Shell CVFS--------------------------------\n");
    printf("-------------------------------------------------------------------------------------\n");


    printf("man : It is used to display specific man page of command\n");
    printf("exit : It is use to terminate the shell of CVFS\n");
    printf("clear : It used to clear the console of Marvellous CVFS\n");
    printf("creat : It is used to creat regular file\n");
    printf("unlink : It is used to delete file\n");
    printf("stat : It used to display statistical information about files\n");
    printf("ls : It used to list all files from directory\n");
    printf("write : It is used to write the data into the file\n");
    printf("read : It is used to read the data from the file\n");

    // Add more options here


    printf("-------------------------------------------------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    ManPage
//  Description :      It is used to display the manual page of the command
//  Input   :          It Accepts the command name
//  Output  :          Displays the manual details of the command
//  Author  :          Rishikesh Shinde
//  Date    :          11/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void ManPage(
                char *name          // Name of Command
            )
{
    if(strcmp(name, "creat") == 0)
    {
        printf("Description : This command is used to create new regular file on our file system\n");
        printf("Usage : Create File_name Permission\n");
        printf("File_name : The name of file that you want to create");
        printf("Permissions : \n1 : Read : \n2 : Write : \n3 : Read + Write\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This command is used to terminate the CVFS\n");
        printf("Usage : exit\n");
    }
    else if(strcmp(name, "unlink") == 0)
    {
        printf("Description : This command is used to delete new regular file on our file system\n");
        printf("Usage : unlink File_name \n");
        printf("File_name : The name of file that you want to delete");
    }
    else if(strcmp(name, "stat") == 0)
    {
        printf("Description : This command is used to display statistical commant about file\n");
        printf("Usage : stat File_name \n");
        printf("File_name : The name of file whose information you want to display\n");
    }
    else if(strcmp(name, "ls") == 0)
    {
        printf("Description : This command is used list all information about the files from directory\n");
        printf("Usage : ls\n");
    }
    else if(strcmp(name, "write") == 0)
    {
        printf("Description : This command is used to write data into an open regular file.\n");
        printf("Usage : write File_descriptor\n");
        printf("File_descriptor : It is a value returned by the 'creat' command, which identifies the open file.\n");
        printf("Note: After executing the command, the shell will prompt you to enter the data to be written.\n");
    }
    else if(strcmp(name, "read") == 0)
    {
        printf("Description : This command is used to read the data from the file\n");
        printf("Usage : read File_discriptor_size\n");
        printf("File_discriptor : Its a value returned by creat system call\n");
        printf("Size : Number of bytes that you want to read");
    }
    // Add more options here
    else
    {
        printf("No Manual of %s\n",name);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    IsFileExists
//  Description :      It is used to check weather the given filename exists or not
//  Input   :          It accepts the file name
//  Output  ;          It returns the boolean value (True if exists or false)
//  Author  :          Rishikesh Shinde
//  Date    :          11/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

bool IsFileExists(
                    char *name      // Name of file that we want to check
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    CreatFile
//  Description :      It is used to creat the file
//  Input   :          It accepts the file name and permission
//  Output  ;          It returns the file Descriptior(fd)
//  Author  :          Rishikesh Shinde
//  Date    :          11/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,             // Name of a file
                    int permission          // Permission to creat file
                )
{
    PINODE temp = head;
    int i = 0;

    printf("current inode remaining : %d\n",superobj.FreeInodes);
    //Filters

    // If file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if entered permission is invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Cheak weather empty inode is there or not
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // Cheak weather file is already exists or not
    if(IsFileExists(name))
    {
        return ERR_FILE_ALREADY_EXISTS;
    }

    // Loop to search free inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    // Inode not found
    if(temp == NULL)
    {
        printf("inode not found\n");
        return ERR_NO_INODES;
    }

    // Search first Non null value from UFDT
    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXINODE)
    {
        printf("Unable to create file as MAX OPENED FILE LIMIT REACHED\n");
        return -1;
    }

    // Allocates memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    //  Initilise elements of file table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Count = 1;
    uareaobj.UFDT[i]->Mode = permission;

    // connect file table with IIT
    uareaobj.UFDT[i]->ptrinode = temp;

    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFilesize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for buffer

    uareaobj.UFDT[i]->ptrinode->Buffer = (char * )malloc(MAXFILESIZE);

    // Decrement the number of free inodes by 1
    superobj.FreeInodes--;
    return i;
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    UnlinkFile
//  Description :      It is used to delete the reg file
//  Input   :          It accepts the file name 
//  Output  ;          It returns nothing
//  Author  :          Rishikesh Shinde
//  Date    :          15/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

// CVFS > unlink
int UnlinkFile(
                    char *name         // name of file
                )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name) == 0)
            {
                // Deallocate the memory of buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);

                // Reset all valuse of Inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFilesize = 0;
                uareaobj.UFDT[i]->ptrinode->LinkCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;   
                
                // Deallocate memory of filetable
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT member
                uareaobj.UFDT[i] = NULL;

                // Increment the valuse of free Inodes count
                superobj.FreeInodes++;

                break;
            }   // End of if
        }   // End of if
    }   // End of for


    return EXECUTE_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    ls_file
//  Description :      It is used to display the info about all files in directory
//  Input   :          nothing
//  Output  ;          nothing
//  Author  :          Rishikesh Shinde
//  Date    :          15/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void ls_file()
{
    PINODE temp = head;

    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%s\n",temp->FileName);
        }
        temp = temp->next;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    stat_file
//  Description :      It is used to display the info about the given files in directory
//  Input   :          File name
//  Output  ;          nothing
//  Author  :          Rishikesh Shinde
//  Date    :          15/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int stat_file(
                    char *name         // name of file
                )
{
    PINODE temp = head;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType != 0))
        {
            printf("----------- Statistical Information of file ------------");

            printf("file name : %s\n",temp->FileName);
            printf("file size is on disk : %d\n",temp->FileSize);
            printf("actual file size : %d\n",temp->ActualFilesize);
            printf("Link Count : %d\n",temp->LinkCount);
            printf("file permission : %d\n",temp->Permission);
            if(temp->Permission == READ)
            {
                printf("Read\n");
            }
            else if(temp->Permission == WRITE)
            {
                printf("Write\n");
            }
            else if(temp->Permission == READ + WRITE)
            {
                printf("Read + Write\n");   
            }

            printf("file type : ");
            if(temp->FileType == REGULARFILE)
            {
                printf("regular file\n");
            }
            else if(temp->FileType == SPECIALFILE)
            {
                printf("special file\n");
            }


            printf("--------------------------------------------------------");
        }
        temp = temp->next;
    }


    return EXECUTE_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    write_file
//  Description :      It is used to write the contents into the files
//  Input   :          File Discriptor
//  Input   :          Address of buffer which contains data
//  Input   :          soze of data that we want to wr\ite
//  Output  ;          Number of bytes successfully written into file
//  Author  :          Rishikesh Shinde
//  Date    :          15/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int write_file(
                    int fd,                 // File descriptor of file
                    char *data,             // Data that we want to writ
                    int size                // Size of data that we want to write
                )
{

    printf("file descripto is : %d\n",fd);
    printf("data that we want to write : %s\n",data);
    printf("number of bytes that we want to write : %d\n",size);

    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // file is not opened or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // if there is no permission to wrtie the data into file
    if(uareaobj.UFDT[fd]->ptrinode->Permission <= WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to write as there is no sufficient space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }
    
    // Calculate the actual offset
    uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset;

    // 
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset,data,size);

    //
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size;

    // update actual size of file after writting the new data
    uareaobj.UFDT[fd]->ptrinode->ActualFilesize = uareaobj.UFDT[fd]->ptrinode->ActualFilesize + size;

    return size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    read_file
//  Description :      It is used to read the contents from the file
//  Input   :          File Discriptor
//  Input   :          Address of empty buffer
//  Input   :          Size of data that we want to read
//  Output  ;          Number of bytes successfully read from the file
//  Author  :          Rishikesh Shinde
//  Date    :          15/8/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int read_file(
                int fd,                     // File descriptor
                char *data,                 // Address of empty buffer
                int size                    // Number of bytes that we want to read
)
{
    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Invalid 
    if(data == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    // file is not opened or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // if there is no permission to wrtie the data into file
    if(uareaobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to read as there is no sufficient data
    if((MAXFILESIZE - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data, uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset, size);
    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;
    return size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function (main)
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {"\0"};
    int iCount = 0;
    char Command[5][80];
    int iRet = 0;
    char InputBuffer[MAXFILESIZE] = {"\0"};
    char *EmptyBuffer = NULL;

    StartAuxilaryDataInitilisation();

    cout<<"-------------------------------------------------------------------------------------\n";
    cout<<"--------------------------Shell CVFS Started Successfully----------------------------\n";
    cout<<"-------------------------------------------------------------------------------------\n";

    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nShell CVFS >");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);
        fflush(stdin);

        if(iCount == 1)
        {
            // CVFS > exit
            if(stricmp(Command[0], "exit") == 0)
            {
                printf("Thankyou for using Shell CVFS\n");
                printf("Deallocating all resources....\n");

                break;
            }

            // CVFS > help
            else if(strcmp(Command[0], "help") == 0)
            {
                DisplayHelp();
            }

            // CVFS > clear
            else if(strcmp(Command[0], "clear") == 0)
            {
                system("cls");
            }

            // CVFS > ls
            else if(strcmp(Command[0], "ls") == 0)
            {
                ls_file();
            }

            else
            {
                printf("Command not found...\n");
                printf("Please refer help option or use man command\n");
            }

        }   //End of if iCount == 1

        else if(iCount == 2)
        {

            // CVFS > man creat
            if(strcmp(Command[0], "man") == 0)
            {
                ManPage(Command[1]);
            }

            // CVFS > unlink demo.txt
            else if(strcmp(Command[0], "unlink") == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Unlink operation is successfuly performed\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to do unlink activity as file is not present");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check man page for more details\n");
                }
            }

            // CVFS > stat Demo.txt
            else if(strcmp(Command[0], "stat") == 0)
            {
                iRet = stat_file(Command[1]);

                
                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to do Display statistics as file is not present");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check man page for more details\n");
                }
            }

            // CVFS > write 3
            if(strcmp(Command[0], "write") == 0)
            {
                printf("Please enter the data that you want to write into the file\n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = write_file(atoi(Command[1]), InputBuffer, strlen(InputBuffer)-1);

                if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Insufficient  Space\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no write permission\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check man page for more details\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FD is invalid\n");
                }
                else
                {
                    printf("%d bytes is successfully written into the file\n",iRet);
                    printf("data from file is : %s\n",uareaobj.UFDT[0]->ptrinode->Buffer);
                }
            }
            else
            {
                printf("Command not found...\n");
                printf("Please refer help option or use man command\n");
            }

        }   //End of if iCount == 2
        else if(iCount == 3)
        {

            // CVFS > man creat Ganesh.txt 3
            if(strcmp(Command[0], "creat") == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check man page for more details\n");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to creat file as there is no Inodes\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXISTS)
                {
                    printf("Error : Unable to  create file is already existing\n");
                }
                else
                {
                    printf("file is successfully created with FD : %d\n",iRet);
                }
            }
            // Marvellous CVFS > read 3 10
            else if(strcmp(Command[0], "read") == 0)
            {
                EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));

                iRet = read_file(atoi(Command[1]), EmptyBuffer, atoi(Command[2]));

                if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Insufficient  data\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to read as there is no read permission\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check man page for more details\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FD is invalid\n");
                }
                else
                {
                    printf("Read operation is successful\n");
                    printf("Data from file is : %s",EmptyBuffer);

                    free(EmptyBuffer);
                }
                
            }

            else
            {
                printf("Command not found...\n");
                printf("Please refer help option or use man command\n");
            }


        }   //End of if iCount == 3
        else if(iCount == 4)
        {

        }   //End of if iCount == 4
        else
        {
            printf("Command not found...\n");
            printf("Please refer help option or use man command\n");

        }   //End of invalid command part

    }      //End of While (Custom Shell)

    return 0;
}   //End of Main