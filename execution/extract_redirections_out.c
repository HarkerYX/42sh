/*
** extract_redirections.c for minishell2 in /home/serraj_y//c/minishell2/shell
** 
** Made by younes serraj
** Login   <serraj_y@epitech.net>
** 
** Started on  Wed Sep 29 22:26:21 2010 younes serraj
** Last update Sun Dec 19 22:11:10 2010 younes serraj
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include "ll.h"
#include "config.h"
#include "shell.h"
#include "memory.h"

static int		check_cases(char **wt, int i, int *fd)
{
  if (!my_strcmp(wt[i], ">"))
    {
      if ((*fd = open(wt[i + 1], OPEN_MODE_WRITE, OPEN_PERMISSIONS)) == -1)
	my_printf_err("'%s': Permission denied\n", wt[i + 1]);
      return (0);
    }
  else if (!my_strcmp(wt[i], ">>"))
    {
      if ((*fd = open(wt[i + 1], OPEN_MODE_APPEND, OPEN_PERMISSIONS)) == -1)
	my_printf_err("'%s': Permission denied\n", wt[i + 1]);
      return (0);
    }
  return (-1);
}

int			extract_redirection_out(t_ll_list *list)
{
  int			fd;
  char			**wt;
  int			i;

  if ((wt = my_split((char *)list->tail->data, " ")) == NULL)
    {
      my_wt_free(wt);
      x_free(wt);
      return (-1);
    }
  fd = -1;
  i = 0;
  while (wt[i])
    {
      if (!check_cases(wt, i, &fd))
	break;
      i += 1;
    }
  my_wt_free(wt);
  x_free(wt);
  return (fd);
}
