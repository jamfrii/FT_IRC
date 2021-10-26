SRCS 		= main.cpp channel.cpp	./server/Server.cpp	user.cpp utils.cpp split.cpp \
				./command/pingPong.cpp ./command/quit.cpp ./command/userCmd.cpp ./command/part.cpp \
				./command/privmsg.cpp ./command/nick.cpp ./command/join.cpp

OBJS 		= $(SRCS:.cpp=.o)

CXX			= clang++ 

CXXFLAGS	= -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

NAME		= IRC

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
			-@rm -f $(OBJS)

fclean: 	clean
			-@rm -f $(NAME)

re:			fclean all

.PHONY: all clea fclean re test