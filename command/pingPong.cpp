/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingPong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:50:59 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/25 17:01:57 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Server.hpp"
#include "../utils.hpp"

static std::string generatePing()
{
	char ping[13];
    srand( time( NULL ) );
    for( size_t i = 0; i <= 11; i++ )
        ping[ i ] = 33 + rand() % ( 126 - 33 );
	ping[ 12 ] = '\0';
	return static_cast<std::string>( ping );
}


void	Server::sendPing()
{
	typedef std::map<int , User *>::iterator iterator;
	std::string ping = "PING : ";
	
	iterator start = this->_fd_users.begin();
	iterator end = this->_fd_users.end();
	
	for ( ;  start != end; ++start )
	{
		if ( ( getTime() - start->second->getLastTime() ) > start->second->getTimePing() ) 
		{
			if ( this->_fd_users[ start->first ]->getPingStatus()
				&& ( getTime() - start->second->getLastTime() ) > ( start->second->getTimePing() + 30000 ) ) // si a los 30 segundo ha devuelto el pong 
			{
					this->close_fd( start->first );
					this->_connected_users.remove( start->second );
					this->_fd_users.erase( start->first);
					std::cout << std::endl;
					return ;
			}
			else if ( this->_fd_users[ start->first ]->getPingStatus() == false
				&& this->_fd_users[ start->first ]->getRegistered() )
			{
				this->_fd_users[ start->first ]->setPing( generatePing() );
				ping += this->_fd_users[ start->first ]->getPing() + "\n";
				this->_fd_users[ start->first ]->setPingStatus( true );
				send( start->first, ping.c_str(), ping.length(), 0);
				std::cout << std::endl;
				displayTimestamp();
				std::cout << " : Ping send,           IP: " << this->getIpUser() << " Socket: " << start->first << std::endl;;
			}
		}
	}
}

void	Server::pong_command( int fd, char *buffer)
{
	std::vector<std::string> token = split( buffer, ' ' );
	
	if ( token[1] == this->_fd_users[fd]->getPing() )
		{
			this->_fd_users[fd]->setPingStatus( false );
			this->_fd_users[fd]->setTimePing( 120000 );
			std::cout << std::endl;
			displayTimestamp();
			std::cout << " : Ping received,       IP: " << this->getIpUser() << " Socket: " << fd;
		}

}