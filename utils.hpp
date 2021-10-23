/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:22:05 by isfernan          #+#    #+#             */
/*   Updated: 2021/10/23 21:14:00 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <list>
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include "user.hpp"
#include <errno.h>
#include <stdio.h>

bool	find_command(std::string command, std::list<std::string> commands);
void	send_error(std::string error, std::string str, int fd);
void	send_reply(std::string replay, std::string str, int fd);
char	**ft_split(char const *s, char c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
bool	ft_isspecial(char c);
char	*ft_substr(char const *s, char c);
void    send_message(std::string & message, int & fd, User * usr);
void    send_message_channel(std::string & message, User * usr, Channel * chnl);
std::vector<std::string>    split(char * buff, char c);



#endif