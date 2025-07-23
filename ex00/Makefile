CC = c++
CC += -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g
RM = rm -f
NAME = btc

SRC_FILE = main.cpp BitcoinExchange.cpp
SRC_HEADER = BitcoinExchange.hpp

all: $(NAME) 

OBJS = $(SRC_FILE:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(SRC_FILE) -o $(NAME)

%.o: %.cpp $(SRC_HEADER)
	$(CC) -c $< -o $@

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) -rf btc
re: clean all