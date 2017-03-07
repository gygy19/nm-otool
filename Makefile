# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/25 15:18:38 by jguyet            #+#    #+#              #
#    Updated: 2017/03/06 17:42:15 by jguyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	nm-otool

OTOOL		=	ft_otool

NM			=	ft_nm

NAMEBASE    =   $(shell basename $(NAME) .a)

LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`

MAX_COLS	=	$$(echo "$$(tput cols)-20-$(LENGTHNAME)"|bc)

CC			=	gcc -m32

FLAGS		=	-Wall -Wextra -Werror -O3 -ggdb

SRCDIR		=	

OBJDIR		=	.objs/

INCDIR		=	includes/

LIBFTDIR	=	libft/

INCDIRLIBFT	=	$(LIBFTDIR)/includes/

SRCOTOOL	=	\
				srcs/otool/main.c											\
				srcs/otool/h.c												\
				srcs/otool/t.c												\
				srcs/otool/version.c										\
				srcs/otool/errors.c											\
				srcs/lib/file/is_regular.c									\
				srcs/lib/file/file_exists.c									\
				srcs/lib/file/isdir.c										\
				srcs/lib/file/isdevice.c									\
				srcs/lib/ft_mmap.c											\
				srcs/lib/ft_osswap.c										\
				srcs/lib/print_hex.c										\
				srcs/lib/swap_mach_header.c									\
				srcs/lib/print_addr.c										\
				srcs/lib/print_section.c									\
				srcs/lib/print_32bits.c										\
				srcs/lib/is_magic_64.c										\
				srcs/lib/get_magic.c										\
				srcs/lib/getsection.c										\
				srcs/lib/getptr_section.c
				

SRCSOTOOL	=	$(addprefix $(SRCDIR), $(SRCOTOOL))

OBJSOTOOL	=	$(addprefix $(OBJDIR), $(SRCOTOOL:.c=.o))

SRCNM		=	\
				srcs/nm/main.c												\
				srcs/nm/parse_sym.c											\
				srcs/nm/parse_list.c										\
				srcs/nm/getname.c											\
				srcs/nm/cmp.c												\
				srcs/nm/default.c											\
				srcs/nm/errors.c											\
				srcs/lib/file/is_regular.c									\
				srcs/lib/file/file_exists.c									\
				srcs/lib/file/isdir.c										\
				srcs/lib/file/isdevice.c									\
				srcs/lib/ft_mmap.c											\
				srcs/lib/ft_osswap.c										\
				srcs/lib/print_hex.c										\
				srcs/lib/swap_mach_header.c									\
				srcs/lib/print_addr.c										\
				srcs/lib/print_section.c									\
				srcs/lib/print_32bits.c										\
				srcs/lib/is_magic_64.c										\
				srcs/lib/get_magic.c										\
				srcs/lib/getsection.c										\
				srcs/lib/getptr_section.c

SRCSNM		=	$(addprefix $(SRCDIR), $(SRCNM))

OBJSNM		=	$(addprefix $(OBJDIR), $(SRCNM:.c=.o))

.SILENT:

all:
	if test -f $(NM) && test -f $(OTOOL) ; then								\
		echo "make: Nothing to be done for \`all\`.";						\
	else																	\
		$(MAKE) -j $(NAME);													\
	fi

$(NAME):
	make -C $(LIBFTDIR)
	$(MAKE) $(NM)
	$(MAKE) $(OTOOL)

$(NM):	$(OBJDIR) $(OBJSNM)
	$(CC) $(FLAGS) -o $(NM) $(OBJSNM) -L $(LIBFTDIR) -lftprintf
	echo "MAKE   [$(NM)]"

$(OTOOL):	$(OBJDIR) $(OBJSOTOOL)
	$(CC) $(FLAGS) -o $(OTOOL) $(OBJSOTOOL) -L $(LIBFTDIR) -lftprintf
	echo "MAKE   [$(OTOOL)]"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(dir $(OBJSOTOOL))
	mkdir -p $(dir $(OBJSNM))

$(OBJDIR)%.o : $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR) -I $(INCDIRLIBFT)
	printf "\r\033[38;5;117m%s%*.*s\033[0m\033[K"							\
	"MAKE   "$(NAMEBASE)" plz wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@)))"

clean:
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo -en "\r\033[38;5;101mCLEAN  "									\
		"[\033[0m$(NAMEBASE)\033[38;5;101m]\033[K";							\
	else																	\
		printf "\r";														\
	fi
	make -C $(LIBFTDIR) fclean

fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\r\033[38;5;124mFCLEAN "									\
		"[\033[0m$(NAMEBASE)\033[38;5;124m]\033[K";							\
	else																	\
		printf "\r";														\
	fi
	make -C $(LIBFTDIR) fclean
	rm -rf $(NM)
	rm -rf $(OTOOL)
	rm -rf $(OBJDIR)

libre:
	make -C $(LIBFTDIR) re
	echo "lalalla"

re:			fclean all

.PHONY:		fclean clean re

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
