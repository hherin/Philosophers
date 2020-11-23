HDRS	=	philo1.h \

SRCS	=	main.c \
			init.c \
			msg.c \
			routine.c \
			utils.c \

OBJS	= ${SRCS:.c=.o}


NAME	= philo_one

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} \
	${CFLAGS} \

${OBJS}: ${HDRS}

all: ${NAME}

clean:
	rm -f *.o
	rm -f *.gch

fclean:
	rm -f *.o
	rm -f *.gch
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	all clean fclean re \