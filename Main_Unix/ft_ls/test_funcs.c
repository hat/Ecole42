#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// struct dirent {
//    ino_t          d_ino;       /* Inode number */
//    off_t          d_off;       /* Not an offset; see below */
//    unsigned short d_reclen;    /* Length of this record */
//    unsigned char  d_type;      /* Type of file; not supported
//                                   by all filesystem types */
//    char           d_name[256]; /* Null-terminated filename */
// };

// struct stat 
// { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//          dev_t    st_dev;    /* device inode resides on */
//          ino_t    st_ino;    /* inode's number */
//          mode_t   st_mode;   /* inode protection mode */
//          nlink_t  st_nlink;  /* number of hard links to the file */
//          uid_t    st_uid;    /* user-id of owner */
//          gid_t    st_gid;    /* group-id of owner */
//          dev_t    st_rdev;   /* device type, for special file inode */
//          struct timespec st_atimespec;  /* time of last access */
//          struct timespec st_mtimespec;  /* time of last data modification */
//          struct timespec st_ctimespec;  /* time of last file status change */
//          off_t    st_size;   /* file size, in bytes */
//          quad_t   st_blocks; /* blocks allocated for file */
//          u_long   st_blksize;/* optimal file sys I/O ops blocksize */
//          u_long   st_flags;  /* user defined flags for file */
//          u_long   st_gen;    /* file generation number */
// };


x == (x | Math.Pow(2, y));

int x = 5;

x == (x | Math.Pow(2, 0) //Bit 0 is ON;
x == (x | Math.Pow(2, 1) //Bit 1 is OFF;
x == (x | Math.Pow(2, 2) //Bit 2 is ON;


    if(argc != 2)    
        return 1;

    struct stat fileStat;
    if(stat(argv[1],&fileStat) < 0)    
        return 1;

    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    printf("Number of Links: \t%d\n",fileStat.st_nlink);
    printf("File inode: \t\t%d\n",fileStat.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

    return 0;

int		main(void)
{
	void			*dir;
	struct dirent	*rdir;
	struct stat		file_info;

	dir = opendir(".");
	lst->dir = ft_strcpy(".");
	if (dir != NULL)
	{
		while ((rdir = readdir(dir)) != NULL)
		{
			if (*rdir->d_name != '.')
			{
				printf("%s ", rdir->d_name);
				lstat(rdir->d_name, &file_info);
				// if ((file_info.st_mode & S_IFMT) == S_IFREG)
				// 	puts(" regular file");
				// else if ((file_info.st_mode & S_IFMT) == S_IFDIR)
				// 	puts(" directory");
				// else if ((file_info.st_mode & S_IFMT) == S_IFCHR)
				// 	puts(" character device");
				// else if ((file_info.st_mode & S_IFMT) == S_IFBLK)
				// 	puts(" block device");
				// else
				// 	puts(" unknown");
			}
		}
	}

	printf("\n");

	printf("%-35s\t", "a.out");

	closedir(dir);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	DIR *dir;
// 	struct dirent *dent;

// 	if (argc > 1)
// 	{
// 		dir = opendir(argv[1]);
// 		if (dir != NULL)
// 		{
// 			while ((dent=readdir(dir)) != NULL)
// 			{
// 				if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0 || (*dent->d_name) == '.')
// 				{

// 				} 
// 				else
// 				{
// 					printf(dent->d_name);
// 					printf("\n");
// 				}
// 			}
// 			closedir(dir);
// 		}
// 	}
// 	else
// 		printf("Must pass argument\n");
// 	return (0);
// }