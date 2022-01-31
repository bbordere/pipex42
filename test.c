/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/01/31 15:54:24 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// < file1 cmd1 | cmd2 > file2 :
// read content of  files1
// send it to cmd1
// send cmd1's output to cmd2
// write cmd2's output in file2

// file1 = av[1], cmd1 = av[2], cmd2 = av[3], file2 = av[4]

#include <unistd.h>
#include <stdlib.h>

int main()
{
	char      *argv[] = {"/bin/echo"};
	char *newargv[] = { "/bin/echo", "Test",NULL };
	char      *newenviron[] = { NULL };
 
  execve(argv[0], newargv, newenviron);
	return 0;
}
