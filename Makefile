# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/12 15:16:17 by jwalsh            #+#    #+#              #
#    Updated: 2018/06/04 14:29:48 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := particle_system

SRCS := main \
		Shader \
		OpenGLWindow \
		OpenCLContext \
		FPS \
		Cmaera \
		Forces \
		ParticleSystem \
		ExceptionMsg

GLADC = include/glad/src/glad.c
GLADO = ./obj/glad.o

EXT  :=.cpp
SRCS := $(addsuffix $(EXT), $(SRCS))
OBJS := $(SRCS:.cpp=.o)
SRCS_DIR := ./src
OBJS_DIR := ./obj
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

HEADERS := header.h
HEADER_DIR := ./include ./include/glad/include ./include/glfw/include
HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

GLFW_LIB_FLAGS := -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework OpenCL
GLFW_LIB := glfw3
GLFW_LIB_H := ./libs/glfw/include

CC := gcc
CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(GLADC)
	@make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L./libs/glfw/src/ $(GLFW_LIB_FLAGS) -I$(GLFW_LIB_H) -l$(GLFW_LIB) $(OBJS) $(GLADO) -o $(NAME)  

$(OBJS): | $(OBJS_DIR)

$(GLADO): $(GLADC) 
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(GLFW_LIB_H) -o $@ -c $<

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(GLFW_LIB_H) -o $@ -c $<
	
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

PHONY: re all clean fclean

.PHONY: all clean fclean re