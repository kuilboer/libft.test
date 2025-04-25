# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: okuilboe <okuilboe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/04/25 16:17:43 by okuilboe      #+#    #+#                  #
#    Updated: 2025/04/25 20:11:42 by okuilboe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG ====

NAME		:= libtester

LIB_SRC_DIR	:= ../srcs		# default symlink target used if not provided
LIB_LNK_TGT	:= $(CURDIR)/libft

LIBRARY		= $(LIB_LNK_TGT)/libft.a

CC 			:= cc
CFLAGS		:= -Wall -Werror -Wextra
CPPFLAGS	:= -Ilibft

# ==== FILES ====

SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:.c=.o)

# ==== RULES =====

.PHONY = all link-lib clean fclean

all: $(LIBRARY) $(NAME)

$(LIBRARY): $(LIB_LNK_TGT)
	@$(MAKE) -C $(LIB_LNK_TGT)

$(LIB_LNK_TGT):
	@echo "re-creating symlink to the target library."
	@ln -snf $(LIB_SRC_DIR) $(LIB_LNK_TGT) # Create symbolic link to the libft directory

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_LNK_TGT) -lft -o $(NAME)

%.o: %.c
	@echo $?
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

# link-lib:
# 	@if [ ! -L lib ] && [ ! -d lib ]; then \
# 		ln -s $(LIB_SRC_DIR) $(LIB_LINK_TGT); \
# 		echo "Symlink created: $(LIB_LINK_TGT) -> $(LIB_SRC_DIR)"; \
# 	else \
# 		echo "Link or directory '$(LIB_LINK_TGT)' already exists, skipping."; \
# 	fi

clean:
	@$(MAKE) -C $(LIB_LNK_TGT) clean
	@echo "Purging object files"
	rm -f $(OBJS)


fclean: clean
	@$(MAKE) -C $(LIB_LNK_TGT) fclean
	rm -f $(NAME)
	rm -f $(LIB_LNK_TGT)

re: fclean all

