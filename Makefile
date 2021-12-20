SRCSDIR			=	srcs

INCDIR			=	./includes

HEADER			=	$(INCDIR)/pipex.h

NAME			=	pipex

SRCS			=	main.c\
					$(SRCSDIR)/ft_cmdpath.c\
					$(SRCSDIR)/ft_execve_argv.c\
					$(SRCSDIR)/ft_free.c\
					$(SRCSDIR)/ft_getenv.c\
					$(SRCSDIR)/ft_perror.c\
					$(SRCSDIR)/ft_split.c\
					$(SRCSDIR)/ft_strchr.c\
					$(SRCSDIR)/ft_strdup.c\
					$(SRCSDIR)/ft_strlen.c\
					$(SRCSDIR)/ft_strnjoin.c\
					$(SRCSDIR)/ft_strstr.c

OBJS			=	$(SRCS:.c=.o)

GCC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				$(GCC) $(CFLAGS) -I$(INCDIR) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
				$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:			$(NAME)

all:			$(NAME)

clean:
				$(RM) $(OBJS)
			
fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re