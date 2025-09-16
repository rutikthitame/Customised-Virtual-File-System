//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Header file inclusion 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// User defined Macros 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Max file size
# define MAXFILESIZE 100        

// Maximum number of files that we can open
# define MAXOPENEDFILE 20       

// Maximum number of file that we can creat
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// User defined Macros for error handling
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# define ERR_INVALID_PARAMETER -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXISTS -3
# define ERR_FILE_NOT_EXISTS -4
#define ERR_PERMISSION_DENIED -5
#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Structure Name :     BootBlock
// Description :        Holds information to boot the operating system
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Structure Name :     SuperBlock
// Description :        Holds information about the file system
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Structure Name :     Inode
// Description :        Holds information about the file
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    int LinkCount;
    char *Buffer;
    struct Inode *next;
}INODE, *PINODE, **PPINODE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Structure Name :     FileTable
// Description :        Holds information about the opened file
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffSet;
    int WriteOffSet;
    int Count;
    int Mode;
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Structure Name :     UAREA
// Description :        Holds information about the process
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPENEDFILE];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Global variables or objects used in the project
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BootBlock bootobj;
struct SuperBlock superobj;
PINODE head = NULL;
struct UAREA uareaobj;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseUAREA
//  Description :       It is used to initialise the contents of UAREA
//  Author :            Rutik Shivaji Thitame
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    while(i < MAXOPENEDFILE)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    
    printf("Marvellous CVFS : UAREA initialised succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseSuperblock 
//  Description :       It is used to initialise the contents of super block
//  Author :            Rutik Shivaji Thitame
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperblock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;
    printf("Marvellous CVFS : SuperBlock initialised succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB 
//  Description :       It is used to create linkedlist of Inodes
//  Author :            Rutik Shivaji Thitame
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        newn->InodeNumber = i;
        newn->FileSize = 0; 
        newn->ActualFileSize = 0;
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

    printf("Marvellous CVFS : DILB created succesfully\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxliaryDataInitialisation 
//  Description :       It is used to initialise the Auxliary data
//  Author :            Rutik Shivaji Thitame
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StartAuxliaryDataInitialisation()
{
    
    strcpy(bootobj.Information,"Boot process of Operating System done");

    printf("%s\n",bootobj.Information);

    InitialiseSuperblock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxilary data initialised succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp 
//  Description :       It is used to Display the information about cammond
//  Author :            Rutik Shivaji Thitame
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-----------------------------------------------------------------------------\n");
    printf("--------------------- Command Manual of Marvellous CVFS ---------------------\n");
    printf("-----------------------------------------------------------------------------\n");

    printf("man : It is used to display specific manual page of command\n");
    printf("exit : It is used to terminate the shell of Marvellous CVFS\n");
    printf("clear : It is used to clear the console of Marvellous CVFS\n");
    printf("creat : It is used to create new regular file\n");
    printf("unlink : It is used to delete existing file\n");
    printf("stat : It is used to display statistical information about file\n");
    printf("ls : It is used to display all files in the directory\n");
    printf("write : It is used to write the data into the file\n");
    printf("read : It is used to read the data into the file\n");


    // Add more options here

    printf("-----------------------------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPage
//  Description :       It is used to Display the manual page of the command
//  Input :             It accepts the command name
//  Output :            Displays the manual details of the command
//  Author :            Rutik Shivaji Thitame
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ManPage(
                char *name      // Name of command
            )
{
    if(strcmp(name, "creat") == 0)
    {
        printf("Description : This command is used to create new regular file on our file system \n");

        printf("Usage : creat File_name Permissions\n");
        printf("File_name : The name of file that you want to create\n");
        printf("Permissions : \n1 : Read \n2 : Write \n3 : Read + Write\n");

    }
    else if(strcmp(name, "exit") == 0)
    {
        printf("Description : This command is used to terminate the Marvellous CVFS \n");

        printf("Usage : exit\n");
    }
    else if(strcmp(name, "unlink") == 0)
    {
        printf("Description : This command is used to delete new regular file from our file system \n");

        printf("Usage : unlink File_name\n");
        printf("File_name : The name of file that you want to create\n");
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : This command is used to display the statistical information about the file \n");

        printf("Usage : stat File_name\n");
        printf("File_name : The name of file whose infromaiton you want to display\n");
    }
    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : This command is used to display the all file Names from the directory \n");

        printf("Usage : ls File_name\n");
        printf("File_name : The name of file whose infromaiton you want to display\n");
    }
    else if(strcmp(name, "write") == 0)
    {
        printf("Description : This command is used to write the data into the file \n");

        printf("Usage : write File_Descripter\n");
    }
    else if(strcmp(name, "read") == 0)
    {
        printf("Description : This command is used to read the data from the file \n");

        printf("Usage : read File_Descripter Size\n");
        printf("File_Descripter : Its a value returned by create system call\n");
        printf("Size : Number of bytes that you can read\n");
    }
    // Add more options here
    else
    {
        printf("No manual entry for %s\n",name);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExists
//  Description :       It is used to check whether the given file name is exists or not
//  Input :             It accepts the file name
//  Output :            It returns boolean value (True : if present False : if not present)
//  Author :            Rutik Shivaji Thitame
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateFile
//  Description :       It is used to create a new file
//  Input :             It accepts the file name and permission
//  Output :            It return the file descriptor
//  Author :            Rutik Shivaji Thitame
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                char *name,         // Name of file
                int permission      // Permission to create file
            )
{
    PINODE temp = head;
    int i = 0;

    printf("Current inodes remaining : %d\n",superobj.FreeInodes);

    // Filters

    // If file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If entered permission is invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Check whether empty inode is there or not
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // Check whether file is already present or not
    if(IsFileExists(name) == true)
    {
        return ERR_FILE_ALREADY_EXISTS;
    }

    // Loop to search free Inode
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
        printf("Inode not found\n");
        return ERR_NO_INODES;
    }
    
    // Search first non NULL value from UFDT
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

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise elements of FIleTable
    uareaobj.UFDT[i]->ReadOffSet = 0;
    uareaobj.UFDT[i]->WriteOffSet = 0;
    uareaobj.UFDT[i]->Count = 1;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect FileTable with IIT [incore inode table]
    uareaobj.UFDT[i]->ptrinode = temp;

    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;


    // Allocate memory for buffer
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    // Decrement the number of free inodes by 1
    superobj.FreeInodes--;

    // fd return value;
    return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     UnlinkFile
//  Description :       It is used to delete a regular file
//  Input :             It accepts the file name 
//  Output :            It returns nothing
//  Author :            Rutik Shivaji Thitame
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Marvellous CVFS > unlink Demo.txt
int UnlinkFile(
                    char *name   // Name of file
            )
{
    int i = 0;

    // If file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXISTS;
    }

    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name) == 0)
            {
                // Deallocate the memory of buffer 
                free(uareaobj.UFDT[i]->ptrinode->Buffer);

                // Reset all the value of Inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0; 
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->LinkCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
            
                // Deallocate memory of FileTable
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT member
                uareaobj.UFDT[i] = NULL;

                // Increment the value of FreeInodes Count
                superobj.FreeInodes++;

                break;
            } // End of if
        }   // End of if
        
    } // End of for

    return EXECUTE_SUCCESS;
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ls_File
//  Description :       It is used to display the information about all files in the directory
//  Input :             Nothing
//  Output :            Nothing
//  Author :            Rutik Shivaji Thitame
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Marvellous CVFS > ls
void ls_File()
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     stat_File
//  Description :       It is used to display the information about given files in the directory
//  Input :             Nothing
//  Output :            Nothing
//  Author :            Rutik Shivaji Thitame
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Marvellous CVFS > stat_Demo.txt
int stat_File(char *name)
{
    int i = 0;
    PINODE temp = head;

    // If file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXISTS;
    }

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType != 0))
        {
            printf("------------------------------Statistical information about file--------------------------\n");

            printf("File Name : %s\n",temp->FileName);
            printf("File Size on Disk : %d\n",temp->FileSize);
            printf("Actual File Size : %d\n",temp->ActualFileSize);
            printf("Link Count : %d\n",temp->LinkCount);
            printf("File permission  : ");
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

            printf("File Type : ");
            if(temp->FileType == REGULARFILE)
            {
                printf("Regular File\n");
            }
            else if(temp->FileType == SPECIALFILE)
            {
                printf("Special File\n");
            }
            printf("------------------------------------------------------------------------------------------\n");

        }
        temp = temp->next;
    }

    return EXECUTE_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     wirte_File
//  Description :       It is used to write th e contents into the file
//  Input :             file descripter
//                      Address of the buffer which contains data
//                      Size of the data that we want to write 
//  Output :            Number of bytes succesfully written into the file
//  Author :            Rutik Shivaji Thitame
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int write_file(
                int fd,             //File Descripter
                char *data,         // Data that we want to write
                int size          //  Size of data that we want to write
            )
{
    unsigned long int offset = 0; 
    printf("File descriptor is : %d \n",fd);
    printf("Data that we want to write : %s\n",data);
    printf("Number of bytes that we want to write : %d\n",size);

    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILE)
    {
        return ERR_INVALID_PARAMETER;
    }

    // File ids not opened or created with given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXISTS;
    }

    // If there is no permission to write the data into the file
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // As there is no sufficient space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffSet) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    //offset = uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffSet;


    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffSet,data,size);

    uareaobj.UFDT[fd]->WriteOffSet = uareaobj.UFDT[fd]->WriteOffSet + size;

    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     read_File
//  Description :       It is used to read the contents from the file
//  Input :             file descripter
//                      Address of the empty buffer 
//                      Size of the data that we want to read 
//  Output :            Number of bytes succesfully read into the file
//  Author :            Rutik Shivaji Thitame
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Marevllous CVFS > read 3 10
int read_file(
                int fd,             // File Descripter
                char *data,         // Address of empty buffer
                int size            // Number of bytes that we want to read
            )
{
    // Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILE)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if Buffer is empty or size is invalid
    if(data == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    // File ids not opened or created with given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXISTS;
    }

    // If there is no permission to read the data from the file
    if(uareaobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to read as there is no sufficient data
    if((MAXFILESIZE - uareaobj.UFDT[fd]->ReadOffSet) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffSet,size);

    uareaobj.UFDT[fd]->ReadOffSet = uareaobj.UFDT[fd]->ReadOffSet + size;

    return size;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    int iRet = 0;
    char Command[5][80];
    char InputBuffer[MAXFILESIZE] = {'\0'};

    char *EmptyBUffer = NULL;

    StartAuxliaryDataInitialisation();

    printf("-----------------------------------------------------------------------------\n");
    printf("-------------------- Marvellous CVFS Started Succesfully --------------------\n");
    printf("-----------------------------------------------------------------------------\n");
    
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        fflush(stdin);

        printf("\nMarvellous CVFS > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);


        if(iCount == 1)
        {
            // Marvellous CVFS > exit

            if(strcmp(Command[0], "exit") == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all resources...\n");

                break;
            }

            // Marvellous CVFS > help

            else if(strcmp(Command[0], "help") == 0)
            {
                DisplayHelp();
            }

            // Marvellous CVFS > clear

            else if(strcmp(Command[0], "clear") == 0)
            {
                system("clear");
            }

            // Marvellous CVFS > ls

            else if(strcmp(Command[0], "ls") == 0)
            {
                ls_File();
            }

            else
            {
                printf("Command not found...\n");
                printf("Please refer Help option or use man command\n");
            }  

        }   // End of if iCount == 1
        else if(iCount == 2)
        {
            // Marvellous CVFS > man creat

            if(strcmp(Command[0], "man") == 0)
            {
                ManPage(Command[1]);
            }

            // Marvellous CVFS > unlink demo.txt

            else if(strcmp(Command[0], "unlink") == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Unlink operation is succesfully performed\n");
                }
                else if(iRet == ERR_FILE_NOT_EXISTS)
                {
                    printf("Error : Unable to display statistics as file is not present\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
            }

            else if(strcmp(Command[0],"stat") == 0)
            {
                iRet = stat_File(Command[1]);

                if(iRet == ERR_FILE_NOT_EXISTS)
                {
                    printf("Error : Unable to do unlink activity as file is not present\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
            }

            // Marvellous CVFS > write 3
            else if(strcmp(Command[0],"write") == 0)
            {
                printf("Please enter the data that you want to write into the file : \n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = write_file(atoi(Command[1]),InputBuffer,strlen(InputBuffer)-1);
                if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Isufficient space in the data block for the file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no wirte permission\n");
                }
                else if(iRet == ERR_FILE_NOT_EXISTS)
                {
                    printf("Error : FD is invalid\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
                else
                {
                    printf("%d bytes gets succesfully written into the file\n",iRet);
                    printf("Data from file is : %s\n",uareaobj.UFDT[0]->ptrinode->Buffer);
                }
            }

            else
            {
                printf("Command not found...\n");
                printf("Please refer Help option or use man command\n");
            }  
            
        }   // End of if iCount == 2

        else if(iCount == 3)
        {
            // Marvellous CVFS > creat Ganesh.txt 3

            if(strcmp(Command[0], "creat") == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));         // atoi converts [string] ascii to integer

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no Inodes\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXISTS)
                {
                    printf("Error : Unable to create file as file is already existing\n");
                }
                else
                {
                    printf("File is succesfully created with fd : %d\n",iRet);
                }
            }

            // Marvellous CVFS > read 3 10
            else if(strcmp(Command[0],"read") == 0)
            {
                EmptyBUffer = (char *)malloc(sizeof(atoi(Command[2])));

                iRet = read_file(atoi(Command[1]),EmptyBUffer,atoi(Command[2]));

                if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Isufficient data in the data block for the file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to read as there is no read permission\n");
                }
                else if(iRet == ERR_FILE_NOT_EXISTS)
                {
                    printf("Error : FD is invalid\n");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
                else
                {
                    printf("Read opertion is succesful\n");
                    printf("Data from file is : %s\n",EmptyBUffer);
                    free(EmptyBUffer);
                }
            }

            else
            {
                printf("Command not found...\n");
                printf("Please refer Help option or use man command\n");
            }  

        }   // End of if iCount == 3

        else if(iCount == 4)
        {

        }   // End of if iCount == 4
        else
        {
            printf("Command not found...\n");
            printf("Please refer Help option or use man command\n");
        }   // End of invalid command part

    }   // End of while (Custom shell)

    return 0;

}   // End of main