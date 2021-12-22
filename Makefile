SRCSDIR			=	srcs

INCDIR			=	./includes

HEADER			=	$(INCDIR)/pipex.h

HEADER_BONUS	=	$(HEADER)\
					$(INCDIR)/pipex_bonus.h

NAME			=	pipex

MAIN			=	main.c

MAIN_BONUS		=	main_bonus.c\
					here_doc.c\
					$(SRCSDIR)/ft_strcmp.c\
					$(SRCSDIR)/ft_strncmp.c\
					$(SRCSDIR)/get_next_line.c

SRCS			=	$(SRCSDIR)/ft_strlen.c\
					$(SRCSDIR)/ft_strcpy.c\
					$(SRCSDIR)/ft_strdup.c\
					$(SRCSDIR)/ft_strchr.c\
					$(SRCSDIR)/ft_strstr.c\
					$(SRCSDIR)/ft_strnjoin.c\
					$(SRCSDIR)/ft_split.c\
					$(SRCSDIR)/ft_free.c\
					$(SRCSDIR)/ft_getenv.c\
					$(SRCSDIR)/ft_cmdpath.c\
					$(SRCSDIR)/ft_execve_argv.c\
					$(SRCSDIR)/ft_perror.c

OBJS			=	$(SRCS:.c=.o)\
					$(MAIN:.c=.o)

OBJS_BONUS		=	$(SRCS:.c=.o)\
					$(MAIN_BONUS:.c=.o)

GCC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				$(GCC) $(CFLAGS) -I$(INCDIR) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
				$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:			$(OBJS_BONUS) $(HEADER_BONUS)
				$(GCC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

all:			$(NAME)

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re