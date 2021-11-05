/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:57:22 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/05 18:10:29 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Server.hpp"

void	Server::user_command( int fd, char *buffer )
{
	buffer  = buffer  + 4;
	while (*buffer  == ' ')
		buffer ++;
	if (*buffer == ':')
		buffer++;

	std::vector<std::string> token = split(buffer, ' ');

	User * usr = this->_fd_users.at(fd);
	if (!usr->getPassState())
		return send_error(ERR_NOPASSWD, "USER :No password entered", fd);
	if ( token.size() < 4 )
		return send_error(ERR_NEEDMOREPARAMS, "USER :Not enough parameters", fd);
	if ( usr->getRegistered() )
		return send_error(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)", fd);
	if ( !ft_isalnum( token[0][0] ) )
		return send_error(ERR_USERNAMEINVALID, " USER :Your username is not valid", fd);
	usr->setUserName(token[0]);
	usr->setmode(token[1][0], true);
	if ( token[3][0] == ':')
	{
		std::string aux = buffer;
		aux = aux.substr(aux.find(':') + 1, aux.length());
		usr->setRealName(aux);
	}
	else
		usr->setRealName(token[3]);
	if ( usr->getNick().size() > 0 && !usr->getRegistered() )
	{
		usr->setRegistered(true);
		usr->setTimePing(0);
		this->_connected_users.push_back( usr );
		displayLog("User created", "", this->_fd_users[fd]);
	}
}