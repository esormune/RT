NAME	=	RT
#TODO change to RT
#compiler/linker
CC	=	gcc
LFLAGS	= -flto -Wall -Wextra -L./libft/ -lft $(SDL_LDFLAGS) #-g -fsanitize=address #TODO add -Werror also to CFLAGS
CFLAGS = -flto -c -Wall -Wextra $(SDL_CFLAGS) $(addprefix -I, $(INCL)) $(SDL_CFLAGS) #-g -fsanitize=address
CPPFLAGS = -D_REENTRANT

#sources & object files
SRC_DIR =	src/
OBJ_DIR =	build/
SRC_LIST = main.c \
		init.c \
		keys.c \
		shape_sphere.c \
		shape_plane.c \
		shape_cylinder.c \
		shape_cone.c \
		shape_cc_shared.c \
		render.c \
		colour.c \
		ray.c \
		utils.c \
		lights.c \
		matrix_apply.c \
		parser.c \
		parse_obj.c \
		parse_light.c \
		parse_cam.c \
		parse_image.c \
		parse_scene.c \
		parse_texture.c \
		parse_line.c \
		camera.c \
		materials.c \
		print.c \
		draw.c \
		uv_manipulation.c \
		uv_utils.c \
		textures.c \
		tex_wood.c \
		tex_marble.c \
		tex_checkers.c \
		tex_cloud.c \
		tex_perlin.c \
		tex_wave.c \
		tex_rainbow.c \
		m3_math.c \
		m3_inverse.c \
		image.c \
		mat_refraction.c \
		mat_reflection.c \
		mat_highlight.c \
		ambient.c \
		filters.c \
		antialiasing.c \
		screenshot.c \
		bitmap.c \
		max_colour.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_LIST))
OBJS = $(addprefix $(OBJ_DIR),$(SRC_LIST:.c=.o))
INCL = include/ build/libsdl2/include/SDL2 libft/includes

#libft
LIBFT = libft/libft.a

#SDL2
SDL_SRC_DIR = SDL2-2.0.14
SDL_DIR = libsdl2
SDL_BUILD_DIR_PATH = $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS = `$(OBJ_DIR)$(SDL_DIR)/bin/sdl2-config --cflags`
SDL_LDFLAGS = `$(OBJ_DIR)$(SDL_DIR)/bin/sdl2-config --libs`
SDL_BIN = $(OBJ_DIR)$(SDL_DIR)/lib/libSDL2.a
SDL_MAKEFILE = $(SDL_SRC_DIR)/Makefile

#header dependencies
dependency_files = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.dep))
dependency_flags = -MT $(@) -MMD -MP -MF $(OBJ_DIR)$(*).dep

.PHONY: all clean fclean re clean_dep

all: $(NAME)

$(NAME): $(OBJS) | $(OBJ_DIR)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT) | $(OBJ_DIR)%.dep 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(dependency_flags) -o $(@) $(<)

$(dependency_files):

$(OBJS): $(SDL_BIN)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	make -C libft

$(SDL_MAKEFILE):
	if test -d $(OBJ_DIR); then echo exists; else mkdir $(OBJ_DIR); fi
	tar xzf SDL2-2.0.14.tar.gz
	@echo "Extracting SDL archives..."
	cd $(SDL_SRC_DIR) && ./configure --prefix=$(abspath $(OBJ_DIR)libsdl2) --disable-shared --disable-video-wayland
	$(MAKE) -j6 --directory=$(SDL_SRC_DIR)

$(SDL_BIN): $(SDL_MAKEFILE) | $(OBJ_DIR)
	$(MAKE) --directory=$(SDL_SRC_DIR) install

clean_dep:
	rm -rf $(dependency_files)

clean:
	make clean -C libft
	rm -rf $(OBJS)
	rm -rf DATA

fclean: clean
	rm -f $(NAME)
	if test -f $(SDL_MAKEFILE); then $(MAKE) AUTOMAKE=: --directory=$(SDL_SRC_DIR) distclean; fi
	rm -rf $(OBJ_DIR)
	rm -rf $(SDL_SRC_DIR)
	make fclean -C libft

re: fclean all

include $(wildcard $(dependency_files))
