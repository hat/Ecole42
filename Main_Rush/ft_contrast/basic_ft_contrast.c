/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ft_contrast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:33:27 by thendric          #+#    #+#             */
/*   Updated: 2017/04/09 17:59:14 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_tpool.h"

void ft_write_image(t_image_data *contrast_data)
{
  int fd;
  int line_count;

  line_count = 0;
  fd = open(contrast_data->output_image, O_CREAT | O_WRONLY);
  if (fd < 0)
  {
    ft_printf("Could not create file\n");
    return ;
  }
  while (line_count < 3)
  {
    write(fd, contrast_data->file_chars[line_count], ft_strlen(contrast_data->file_chars[line_count]));
    write(fd, "\n", 1);
    line_count++;
  }
  line_count--;
  while (line_count < contrast_data->total_lines)
  {
    write(fd, contrast_data->file_chars[line_count], ft_strlen(contrast_data->file_chars[line_count]));
    write(fd, "\n", 1);
    line_count++;
  }
}

void ft_read_image(t_image_data *contrast_data)
{
  int fd;
  int line_count;
  char *line;
  char *full;

  line_count = 0;
  full = ft_strnew(1);
  fd = open(contrast_data->input_image, O_RDONLY);
  if (fd > 0)
  {
    while (get_next_line(fd, &line) == 1 && line_count < 10000)
    {
      line = ft_strjoin(line, "!");
      full = ft_strjoin(full, line);
      ft_strdel(&line);
      line_count++;
    }
  }
  else
    ft_printf("Unable to open: %s\n", contrast_data->input_image);
  contrast_data->total_lines = --line_count;
  contrast_data->file_chars = ft_strsplit(full, '!');
  ft_strdel(&full);
}

void ft_parsedata(char *argv[], t_image_data *contrast_data)
{
    contrast_data->input_image = ft_strdup(argv[2]);
    contrast_data->output_image = ft_strdup(argv[6]);
    if (ft_atoi(argv[4]) >= 0 && ft_atoi(argv[4]) <= 100)
      contrast_data->change_contrast = ft_atoi(argv[4]);
    else
      ft_printf("ERROR: contrast must be between 0-100\n");
    ft_printf("Input: %s Contrast: %d Output: %s\n", contrast_data->input_image, contrast_data->change_contrast, contrast_data->output_image);
}

int   main(int argc, char *argv[])
{
  t_image_data *contrast_data;

  contrast_data = (t_image_data *)ft_memalloc(sizeof(t_image_data));
  if (argc == 7)
  {
    ft_parsedata(argv, contrast_data);
    ft_read_image(contrast_data);
    ft_write_image(contrast_data);
  }
  else
    ft_printf("USAGE: /.ft_contrast -f image.pgm -c 100 -o output.pgm\n");
  return (0);
}
