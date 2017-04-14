#ifndef FT_TPOOL
# define FT_TPOOL

# include <fcntl.h>
# include "libft.h"

typedef struct s_image_data {
  char  *input_image;
  char  *output_image;
  int   change_contrast;
  int   total_lines;
  char  **file_chars;
} t_image_data;

typedef struct s_my_data_struct {
  int ret;
  char info_to_pass;
} t_my_data_struct;

#endif
