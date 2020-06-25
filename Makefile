# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 18:34:41 by niboute           #+#    #+#              #
#    Updated: 2020/06/24 16:56:47 by mwragg           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=wolf3d

SRC=	main.c \
		dda_algo.c \
		display.c \
		events.c \
		init.c \
		init_sdl.c \
		loadbmp.c \
		loop.c \
		parsing.c \
		parsing_map.c \
		parsing_portals.c \
		player_controls.c \
		raycast_portals.c \
		textures.c \
		wipeout.c

HEADER=	header.h \
		bitmap.h

INC=./inc/

HEADERS= $(addprefix $(INC), $(HEADER))

SRCDIR= src/

SRCS= $(addprefix $(SRCDIR), $(SRC))

OBJ= $(SRCS:.c=.o)

DEP= $(SRCS:.c=.d)

LIBFT= libft/libft.a

FT= -L ./libft/ -lft

INC_LIBFT= libft/

INC_SDL2= SDL2/include/SDL2/

LIBSDL2= SDL2/lib/libSDL2.a

SDL2= -L./SDL2/lib -lSDL2

LIB_DEPENDENCIES= $(shell  ./SDL2/bin/sdl2-config --libs)

CC= clang
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I $(INC_SDL2)
CFLAGS += -I $(INC)
LDFLAGS += $(FT)
LDFLAGS += $(SDL2)

all: buildft $(NAME)

buildft:
	make --no-print-directory -C libft/

$(NAME): $(LIBSDL2) $(LIBSDL2_TTF) $(OBJ) $(LIBFT)
	$(CC) -o $@ $(OBJ) $(MLX) $(FT) $(SDL2) $(LIB_DEPENDENCIES)

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBSDL2):
	(cd SDL2-2.0.12 \
	&& ./configure --prefix=$(shell pwd)/SDL2 --enable-static --disable-shared \
	&& make \
	&& make install)

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: clean fclean all

.PHONY: all clean fclean re
