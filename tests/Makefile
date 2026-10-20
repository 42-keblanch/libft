CC       := gcc
LIBDIR   := ..
LIB      := $(LIBDIR)/libft.a
CFLAGS   := -Wall -Wextra -Werror -g -I$(LIBDIR) -Iunity -fsanitize=address,undefined

TEST_SRC := $(wildcard test_*.c)
TEST_BIN := $(TEST_SRC:%.c=build/%)

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do echo "== $$t"; ./$$t || exit 1; done

# Always ask the root Makefile to rebuild the lib (it decides if anything changed)
$(LIB): FORCE
	$(MAKE) -C $(LIBDIR)

# One executable per test_*.c, linked against the library
build/test_%: test_%.c unity/unity.c $(LIB)
	@mkdir -p build
	$(CC) $(CFLAGS) test_$*.c unity/unity.c $(LIB) -o $@

clean:
	rm -rf build

FORCE:
.PHONY: test clean FORCE