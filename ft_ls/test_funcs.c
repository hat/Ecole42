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

int		main(void)
{
	void			*dir;
	struct dirent	*rdir;
	struct stat		file_info;

	dir = opendir(".");
	if (dir != NULL)
	{
		while ((rdir = readdir(dir)) != NULL)
		{
			if (*rdir->d_name != '.')
			{
				printf("%s ", rdir->d_name);
				lstat(rdir->d_name, &file_info);
				if ((file_info.st_mode & S_IFMT) == S_IFREG)
					puts(" regular file");
				else if ((file_info.st_mode & S_IFMT) == S_IFDIR)
					puts(" directory");
				else if ((file_info.st_mode & S_IFMT) == S_IFCHR)
					puts(" character device");
				else if ((file_info.st_mode & S_IFMT) == S_IFBLK)
					puts(" block device");
				else
					puts(" unknown");
			}
		}
	}

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