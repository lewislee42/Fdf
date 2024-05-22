
NAME = test
LINK_FLAGS = -LC:\Dev\lib -lmingw32 -lSDL2 -lSDL2main
INCLUDES = -I$(SRC_PATH) -IC:\Dev\include\SDL2
CFLAGS = -Wall -Wextra
FSAN = -fsanitize=address ggdb
SRC_PATH = src
BUILD_PATH = bin

SOURCE := $(wildcard src/*.c)

OBJECTS := $(subst $(SRC_PATH), $(BUILD_PATH)/obj, $(SOURCE:.c=.o))

UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

# RM = Unknown

# ifeq ($(UNAME_S),Linux)
# 	RM = rm -rf
# else ifeq ($(UNAME_S),Darwin)
# 	RM = rm -rf
# else ifeq ($(UNAME_S),Windows)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/obj/%.o: $(SRC_PATH)/%.c
	@echo "Compiling: $< -> $@"
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

# %.o: %.c
# 	@echo "Compiling: $< -> $@"
# 	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

# Main rule, checks the executable and symlinks to the output
all: $(OBJECTS) $(BUILD_PATH)/$(NAME)
# @echo "Making symlink: $(NAME) -> $<"
# # @ln -s $(BUILD_PATH)/$(NAME) $(NAME)

# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting $(NAME) symlink"
	@rm $(BUILD_PATH)/$(NAME).exe 2>/dev/null
	@rm $(OBJECTS) 2>/dev/null

.PHONY: check
check:
	echo $(OBJECTS)
	uname -s

.PHONY: re
re:	clean all

# Link the executable
$(BUILD_PATH)/$(NAME): $(OBJECTS)
	@echo "Compiling: $@"
	@gcc $(OBJECTS) $(INCLUDES) $(LINK_FLAGS) -o $@
