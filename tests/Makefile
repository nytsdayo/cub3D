# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#              #
#    Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Test executables
TEST_PARSE_CONFIG = test_parse_config
TEST_PARSE_MAP = test_parse_map

# Compiler and flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++11
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I../includes -I../includes/parse -I../includes/utils -I../libraries/minilibx-linux -I./

# Directories
SRC_DIR = ../srcs
TEST_DIR = .

# C++ test source
PARSE_CONFIG_CPP = $(TEST_DIR)/parse/config/test_parse_config.cpp \
				   $(TEST_DIR)/test_utils.cpp

# C source files (library code)
PARSE_CONFIG_C_SRCS = $(SRC_DIR)/parse/config/parse_config.c \
					  $(SRC_DIR)/parse/config/detect_identifier.c \
					  $(SRC_DIR)/parse/config/validate_format.c \
					  $(SRC_DIR)/utils/ft_strlen.c \
					  $(SRC_DIR)/utils/ft_strcmp.c \
					  $(SRC_DIR)/utils/ft_strncmp.c \
					  $(SRC_DIR)/utils/ft_strndup.c \
					  $(SRC_DIR)/utils/ft_isspace.c \
					  $(SRC_DIR)/utils/ft_isdigit.c \
					  $(SRC_DIR)/utils/is_blank_line.c \
					  $(SRC_DIR)/utils/read_map.c \
					  $(SRC_DIR)/utils/free_map.c

# Object files
PARSE_CONFIG_CPP_OBJ = $(PARSE_CONFIG_CPP:.cpp=.o)
PARSE_CONFIG_C_OBJS = $(PARSE_CONFIG_C_SRCS:.c=.o)

TEST_MAP_CXX_SRCS = $(TEST_DIR)/parse/map/test_parse_map.cpp \
					$(TEST_DIR)/parse/map/test_map_file.cpp
TEST_MAP_C_SRCS = $(SRC_DIR)/parse/map/parse_map.c \
				  $(SRC_DIR)/parse/map/load_map.c \
				  $(SRC_DIR)/utils/ft_strlen.c \
				  $(SRC_DIR)/utils/ft_strndup.c \
				  $(SRC_DIR)/utils/read_map.c \
				  $(SRC_DIR)/utils/free_map.c
TEST_MAP_CXX_OBJS = $(TEST_MAP_CXX_SRCS:.cpp=.o)
TEST_MAP_C_OBJS = $(TEST_MAP_C_SRCS:.c=.o)
TEST_MAP_OBJS = $(TEST_MAP_CXX_OBJS) $(TEST_MAP_C_OBJS)

# Rules
all: parse_config parse_map

parse_config: $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS)
	$(CXX) $(CXXFLAGS) $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS) -o $(TEST_PARSE_CONFIG)
	./$(TEST_PARSE_CONFIG)

parse_map: $(TEST_MAP_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_MAP_OBJS) -o $(TEST_PARSE_MAP)
	./$(TEST_PARSE_MAP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS) $(TEST_MAP_CXX_OBJS) $(TEST_MAP_C_OBJS)

fclean: clean
	rm -f $(TEST_PARSE_CONFIG)

re: fclean all

.PHONY: all clean fclean re parse_map parse_config