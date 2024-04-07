EXE	= xz-backdoor-scan

SRCS	=
SRCS	+=	main.c
SRCS	+=	xz-backdoor-signature.c
SRCS	+=	xz-backdoor-signature.h
SRCS	+=	scan-file.c
SRCS	+=	scan-file.h
SRCS	+=	usage.c
SRCS	+=	usage.h

OBJS	=	$(patsubst %.c,%.o,$(filter %.c,${SRCS}))

DEPS	=	$(patsubst %.o,%.d,${OBJS})

LIBS	=

CC	=	gcc

CFLAGS	=
CFLAGS	+=	-MMD
CFLAGS	+=	-O3
CFLAGS	+=	-Wall
CFLAGS	+=	-Werror
CFLAGS	+=	-Wextra

LD	=	gcc

LDFLAGS	=

all:	${EXE}

.PHONY:	all

clean:
	rm -f ${OBJS}
	rm -f ${DEPS}

.PHONY:	clean

distclean:	clean
	rm -f ${EXE}

.PHONY:	distclean

${EXE}:	${OBJS}
	${LD} ${LDFLAGS} $^ ${LIBS} -o $@

%.o:	%.c
	${CC} ${CFLAGS} -c $< -o $@

-include ${DEPS}
