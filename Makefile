NAME			=	philo

source			=	main.c \
					utils.c \
					init.c \
					utils2.c \
					processes.c

HEAD			=	philo.h

OBJS			=	${addprefix ,${source:.c=.o}}

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -g -I $(HEAD)

.c.o			:
					${CC} ${CFLAGS}  -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS} ${HEAD}
					${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME}

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean 
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
