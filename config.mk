# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 13:42:52 by alan              #+#    #+#              #
#    Updated: 2019/10/20 01:17:13 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library
LIBRARY :=		ft
LIB_NAME :=		libft.a
LIB_DIR :=		./libft
# My libft has multiple makefiles. This should be relative to LIB_DIR
LIB_MAKEFILE :=	Makefile
LIB_SRCS :=		$(shell find $(LIB_DIR) -name "*.c")

# Project
NAME :=			ft_select
SRC_DIR :=		./srcs
INCLUDE_DIRS :=	./includes $(LIB_DIR)/includes

# Compiling
CC :=			gcc
CFLAGS +=		-Wall -Wextra -Werror $(foreach INC, $(INCLUDE_DIRS), -I$(INC))
LDFLAGS +=		-L$(LIB_DIR) -l$(LIBRARY) -lcurses
