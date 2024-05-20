
NAME = test
LINK_FLAGS = -LC:\Dev\lib -lmingw32 -lSDL2 -lSDL2main
INCLUDES = -I$(SRC_PATH) -IC:\Dev\include\SDL2
CFLAGS = -Wall -Wextra
FSAN = -fsanitize=address ggdb
SRC_PATH = ./src
BUILD_PATH = ./bin

SOURCE := $(wildcard src/*.c)

OBJECTS := $(subst $(SRC_PATH), $(BUILD_PATH), $(SOURCE:.c=.o))

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
# $(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
# 	@echo "Compiling: $< -> $@"
# 	echo $(OBJECTS)
# 	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	@echo "Compiling: $< -> $@"
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

# Main rule, checks the executable and symlinks to the output
all: $(BUILD_PATH)/$(NAME)
# @echo "Making symlink: $(NAME) -> $<"
# # @ln -s $(BUILD_PATH)/$(NAME) $(NAME)

# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting $(NAME) symlink"
	@Remove-Item $(BUILD_PATH)/$(NAME)*
	@Remove-Item $(OBJECTS)

.PHONY: re
re:	clean all

# Link the executable
$(BUILD_PATH)/$(NAME): $(OBJECTS)
	@echo "Compiling: $@"
	@gcc $(OBJECTS) $(INCLUDES) $(LINK_FLAGS) -o $@
