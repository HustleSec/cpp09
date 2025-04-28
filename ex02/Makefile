CC = c++
CC += -Wall -Wextra -Werror -fsanitize=address -g -std=c++98
RM = rm -f
NAME = PmergeMe

SRC_FILE = main.cpp PmergeMe.cpp
SRC_HEADER = PmergeMe.hpp

all: $(NAME) 

OBJS = $(SRC_FILE:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(SRC_FILE) -o $(NAME)

%.o: %.cpp $(SRC_HEADER)
	$(CC) -c $< -o $@

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) -rf PmergeMe
re: clean all