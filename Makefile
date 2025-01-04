NAME			= out
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
BUILD_PATH		?= ./build

DEPENDENCIES		= libtrue libft libftprintf
DEPENDENCIES_DIR	= ./dependencies
DEPENDENCIES_FLAGS	= $(foreach lib,$(DEPENDENCIES),-L$(BUILD_PATH)/$(lib)) \
						$(foreach lib,$(patsubst lib%,%, $(DEPENDENCIES)),-l$(lib))
INCLUDE_FLAGS		= -Iinclude $(foreach lib,$(DEPENDENCIES),-Iinclude/$(lib))

SRCS			= src/main.c
OBJS			= $(SRCS:src/%.c=$(BUILD_PATH)/obj/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a)
	$(CC) $(CFLAGS) $(OBJS) $(DEPENDENCIES_FLAGS) $(INCLUDE_FLAGS) -o $(NAME)

$(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a):
	$(MAKE) -C $(DEPENDENCIES_DIR)/$(basename $(@F)) BUILD_PATH=../../$(BUILD_PATH)/$(basename $(@F)) all

$(BUILD_PATH)/obj/%.o: src/%.c
	@mkdir -p $(BUILD_PATH)/obj
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_PATH)/obj
	@rm -rf $(BUILD_PATH)/lib*/obj

copy_include:
	@for lib in $(DEPENDENCIES); do \
		rm -rf include/$$lib; \
		mkdir -p include/$$lib; \
		cp $(DEPENDENCIES_DIR)/$$lib/include/* include/$$lib/; \
		echo "#include \"$$lib/$$lib.h\"" >> include/header.h; \
	done

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BUILD_PATH)

re: fclean all

.PHONY: all clean re fclean copy_include
