NAME			=	philo

source			=	main.c \
					philosophers.c \
					routines.c \
					utils.c \
					print.c

HEAD			=	philosophers.h

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
