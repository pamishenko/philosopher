NAME	= philo

HEADERS_FOLDER	= ./

HEADER_FILES	=	$(HEADER_FOLDER)philosopher.h

SRC			= \
			checker.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isdigit.c \
			ft_memset.c \
			main.c \
			philosopher.c \
			thread_utils.c\
			utils.c

SRCS_OBJS	= ${SRC:.c=.o}
DEPS		= ${SRC:.c=.d}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I ${HEADERS_FOLDER} -MMD -MP

RM			= rm -f

all:		
			make ${NAME}

-include $(DEPS)

${NAME}:	${SRCS_OBJS}	
			${CC} ${CFLAGS} ${SRCS_OBJS} -o ${NAME}

clean:
			${RM} ${SRCS_OBJS}
			${RM} ${DEPS}

fclean: 	clean
			${RM} ${NAME}

re:         fclean all

.PHONY:        all clean fclean re
