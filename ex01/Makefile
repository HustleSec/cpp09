CC = c++
CC += -Wall -Wextra -Werror -std=c++98
RM = rm -f
NAME = RPN

SRC_FILE = main.cpp RPN.cpp
SRC_HEADER = RPN.hpp

all: $(NAME) 

OBJS = $(SRC_FILE:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(SRC_FILE) -o $(NAME)

%.o: %.cpp $(SRC_HEADER)
	$(CC) -c $< -o $@

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) -rf RPN
re: clean all