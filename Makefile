NAME = main
INC = -I ./
SRCS =	./main.cpp 

FLAGS = clang++ -std=c++11 -Wall -Wextra -Werror
all: $(NAME)
$(NAME): $(SRCS)
	@$(FLAGS) $(INC) $(SRCS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf *.dSYM
re : fclean $(NAME)