SILENT		?= @

DEFAULT_SYSTEM	=  host
THE_TESTS	=  check_toggle
THE_LIBRARY	=  led.a
THE_PROGRAM	=  do_toggle

TARGET_SYSTEM	?= ${DEFAULT_SYSTEM}
ifeq (rpi, ${TARGET_SYSTEM})
MAKE_TARGET	=  deploy
DEPLOY_COMMAND	?= scp ${THE_PROGRAM} pet-piercer.local:
EXT_TREES_ROOT	?= ${HOME}/Documents/trees
NETBSDSRCDIR	?= ${EXT_TREES_ROOT}/netbsd-src
CROSS_ROOT	?= ${EXT_TREES_ROOT}/rpi
CROSS_ARCH	?= evbearmv6hf-el
CFLAGS		+= --sysroot=${CROSS_ROOT}/distrib/${CROSS_ARCH}
TOOLDIR		?= ${CROSS_ROOT}/tools
TARGET_PREFIX	= armv6--netbsdelf-eabihf-
else
MAKE_TARGET	=  check
TOOLDIR		?= /usr
TARGET_PREFIX	?=
endif

CC		= ${TOOLDIR}/bin/${TARGET_PREFIX}gcc
LD		= ${TOOLDIR}/bin/${TARGET_PREFIX}ld
AR		= ${TOOLDIR}/bin/${TARGET_PREFIX}ar
RANLIB		= ${TOOLDIR}/bin/${TARGET_PREFIX}ranlib

CFLAGS		+= -g -O0 -Wall -Werror -Wextra -std=c99
CHECK_CFLAGS	:= $(shell pkg-config --cflags check 2>/dev/null)
CHECK_LIBS	:= $(shell pkg-config --libs check 2>/dev/null)
TEST_LIBS	+= -lm

all: ${CC}
	${SILENT}${MAKE} ${MAKE_TARGET}

${NETBSDSRCDIR}:
	${SILENT}mkdir -p ${NETBSDSRCDIR} && cd ${NETBSDSRCDIR} && git clone https://github.com/jsonn/src.git .

${CC}: ${NETBSDSRCDIR}
	${SILENT}cd ${NETBSDSRCDIR} && git checkout netbsd_7_0 && env PATH="/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin" MAKECONF="/dev/null" ./build.sh -m ${CROSS_ARCH} -u -U -T ${TOOLDIR} -R ${CROSS_ROOT}/release -O ${CROSS_ROOT}/obj/${CROSS_ARCH} -D ${CROSS_ROOT}/distrib/${CROSS_ARCH} distribution

check: ${THE_TESTS}
	${SILENT}./${THE_TESTS}

clean:
	${SILENT}rm -f *.o *.a syscalls.h .has_check ${THE_TESTS} ${THE_PROGRAM}
	${SILENT}rm -rf *.dSYM *.gcda *.gcno *.gcov

deploy: ${THE_PROGRAM}
	${SILENT}${DEPLOY_COMMAND}

.PHONY: all check clean deploy

${THE_TESTS}: ${THE_PROGRAM} .has_check ${THE_LIBRARY} check_toggle.c acceptance.c unit.c
	${SILENT}${CC} ${CFLAGS} ${CHECK_CFLAGS} -o ${THE_TESTS} acceptance.c unit.c check_toggle.c ${CHECK_LIBS} ${TEST_LIBS} ${THE_LIBRARY}

${THE_LIBRARY}: led.h led.c syscalls.h ${TARGET_SYSTEM}_syscalls.h ${TARGET_SYSTEM}_syscalls.c
	${SILENT}${CC} ${CFLAGS} -c led.c
	${SILENT}${CC} ${CFLAGS} -c ${TARGET_SYSTEM}_syscalls.c
	${SILENT}${AR} rc ${THE_LIBRARY} led.o ${TARGET_SYSTEM}_syscalls.o
	${SILENT}${RANLIB} ${THE_LIBRARY}

${THE_PROGRAM}: ${THE_LIBRARY} led.h do_toggle.c
	${SILENT}${CC} ${CFLAGS} -o ${THE_PROGRAM} do_toggle.c ${THE_LIBRARY}

syscalls.h: ${TARGET_SYSTEM}_syscalls.h
	${SILENT}echo '#include "${TARGET_SYSTEM}_syscalls.h"' > syscalls.h

.has_check:
ifeq (, ${CHECK_LIBS})
	${SILENT}echo "Please install Check (https://libcheck.github.io/check/)." && false
else
	${SILENT}touch .has_check
endif
