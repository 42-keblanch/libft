CC       := cc
LIBDIR   := ..
LIB      := $(LIBDIR)/libft.a
CFLAGS   := -Wall -Wextra -g -I$(LIBDIR) -Iunity -fsanitize=address,undefined

NEUTRAL = \033[0;0m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m

TEST_SRC := test_libc.c \
			test_additional.c \
			test_list.c
TEST_BIN := $(TEST_SRC:%.c=build/%)

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do echo "== $$t"; ./$$t || exit 1; done

list: build/test_list
	./build/test_list

# One executable per test_*.c, linked against the library
build/test_%: test_%.c unity/unity.c $(LIB)
	@mkdir -p build
	@$(CC) $(CFLAGS) test_$*.c unity/unity.c $(LIB) -o $@
	@printf "${YELLOW}Compiling test ${BLUE}$*\n${NEUTRAL}"

# Always ask the root Makefile to rebuild the lib (it decides if anything changed)
$(LIB): FORCE
	$(MAKE) -C $(LIBDIR)

clean:
	@rm -rf build
	@printf "${RED}Deleting tests/build\n${NEUTRAL}"

FORCE:
.PHONY: test clean FORCE
