#include "../server/Server.hpp"
#include "../utils.hpp"

void    Server::join_channel(std::string str1, User *usr)
{

    int j = 1;
    std::string s;

    if (usr->getMaxChannels())
        return (send_error(ERR_TOOMANYCHANNELS, usr->getNick() + " :You have joined too many channels", usr));
    if (str1 == "0")
    {
        str1 = "part " +  usr->getChannelsString();
        std::vector<std::string> vec = parser(str1);
        return (part_command(vec, usr));
    }
    else if (this->_name_channel.count(str1))
    {
        Channel *chann = this->_name_channel[str1];

        if (chann->getIsFull())
            return (send_error(ERR_CHANNELISFULL, str1 + " :Cannot join channel (+l)", usr));
        if (chann->isBanned(usr))
            return (send_error(ERR_BANNEDFROMCHAN, str1 + " :Cannot join channel (+b)", usr));
        if (chann->isInvite() && !chann->isInvited(usr->getNick()) && !usr->getmode('o'))
            return (send_error(ERR_INVITEONLYCHAN, str1 + " :Cannot join channel (+i)", usr));
        // User join channel
        if (chann->isUser(usr->getNick()))
            return (send_error("", str1 + " :You are already on channel", usr));
        s = "JOIN " + chann->getName();
        send_message_channel(s, usr, chann);
        chann->addUser(usr);
        usr->addChannel(chann);
        //this->names_command(&chann->getName()[0], usr);     FALTA EL NAMES
        if (chann->getTopic().size() > 0)
            send_reply(RPL_TOPIC, " JOIN :" + str1 + " " + chann->getTopic(), usr);
        else
            send_reply(RPL_NOTOPIC, " JOIN :" + str1, usr);
    }
    else
    {
        if (str1[0] != '#')
            return (send_error(ERR_NOSUCHCHANNEL, str1 + " :No such channel", usr));
        if (str1.size() > 12)
            return (send_error(ERR_NOSUCHCHANNEL, str1 + " :No such channel", usr));
        while (str1[j])
        {
            if (!ft_isalnum(str1[j]) && !ft_isspecial(str1[j]) && str1[j] != '-')
                return (send_error(ERR_NOSUCHCHANNEL, str1 + " :No such channel", usr));
            j++;
        }
        // Create and join channel
        this->_name_channel[str1] = new Channel(str1, usr);
        this->_name_channel[str1]->addUser(usr);
        usr->addChannel(this->_name_channel[str1]);
        send_reply(RPL_NOTOPIC, " JOIN :" + str1, usr);
        //this->names_command(&this->_name_channel[str1]->getName()[0], fd);    ACCCCOOOOOOORRRRDDDAAAAAAAAAAAAAAAAARRRRSEEEEEEEEEEEEEEEEE!!!
    }
}

void    Server::join_command(std::vector<std::string> parse, User *usr)
{
    std::vector<std::string> parse1;
    
	if (parse.size() < 1)
		return (send_error(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters", usr));
    parse1 = split(parse[1], ',');
    vector_str_it   start = parse1.begin();
    vector_str_it   end = parse1.end();
	for (; start != end; start++)
    {
		Server::join_channel(*start, usr);
        this->reStartSendMsg();
    }
}
