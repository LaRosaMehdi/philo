NAME = philo

SRCS = sources/main.c sources/utils.c sources/philo.c sources/init.c sources/routine.c 

INCLUDES = includes/

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

LIBS = -pthread

.c.o:
	${CC} -I ${INCLUDES} ${FLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${SRCS} ${LIBS} -I ${INCLUDES} ${FLAGS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
