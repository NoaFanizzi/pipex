NAME		= pipex

DIR			= mandatory
SRC_DIR		= $(DIR)/srcs
INC_DIR		= $(DIR)/includes

SRCS		= main.c first_cmd.c second_cmd.c utils.c
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))


vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)