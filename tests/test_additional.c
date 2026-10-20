#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "unity.h"
#include "libft.h"
#include "test_utils.h"

/* ========================================================================== */
/*  Helpers                                                                   */
/* ========================================================================== */

static int	g_pipe[2];

/* Opens a pipe; the write end is g_pipe[1]. */
static void	pipe_open(void)
{
	TEST_ASSERT_EQUAL_INT(0, pipe(g_pipe));
}

/* Closes the write end, reads everything and returns the byte count. */
static size_t	pipe_collect(char *buf, size_t size)
{
	ssize_t	n;

	close(g_pipe[1]);
	n = read(g_pipe[0], buf, size - 1);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	close(g_pipe[0]);
	return ((size_t)n);
}

static void	free_split(char **tab)
{
	if (!tab)
		return ;
	for (size_t i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

static void	assert_split(const char *s, char c, const char **expected, size_t n)
{
	char	**res = ft_split(s, c);

	TEST_ASSERT_NOT_NULL(res);
	for (size_t i = 0; i < n; i++)
	{
		TEST_ASSERT_NOT_NULL_MESSAGE(res[i], "ft_split returned too few words");
		TEST_ASSERT_EQUAL_STRING(expected[i], res[i]);
	}
	TEST_ASSERT_NULL_MESSAGE(res[n], "ft_split result is not NULL-terminated");
	free_split(res);
}

/* ========================================================================== */
/*  ft_substr                                                                 */
/* ========================================================================== */

static void	test_substr_basic(void)
{
	char	*r = ft_substr("hello world", 6, 5);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("world", r);
	free(r);
}

static void	test_substr_from_start(void)
{
	char	*r = ft_substr("hello world", 0, 5);

	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_substr_len_larger_than_remaining(void)
{
	char	*r = ft_substr("hello", 2, 100);

	TEST_ASSERT_EQUAL_STRING("llo", r);
	free(r);
}

static void	test_substr_start_past_end(void)
{
	char	*r = ft_substr("hello", 10, 5);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_substr_start_at_end(void)
{
	char	*r = ft_substr("hello", 5, 3);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_substr_len_zero(void)
{
	char	*r = ft_substr("hello", 1, 0);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_substr_full_string(void)
{
	char	*r = ft_substr("hello", 0, 5);

	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_substr_empty_source(void)
{
	char	*r = ft_substr("", 0, 5);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_substr_is_new_allocation(void)
{
	const char	*s = "hello";
	char		*r = ft_substr(s, 0, 5);

	TEST_ASSERT_TRUE(r != s);
	free(r);
}

/* ========================================================================== */
/*  ft_strjoin                                                                */
/* ========================================================================== */

static void	test_strjoin_basic(void)
{
	char	*r = ft_strjoin("foo", "bar");

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("foobar", r);
	free(r);
}

static void	test_strjoin_with_space(void)
{
	char	*r = ft_strjoin("hello ", "world");

	TEST_ASSERT_EQUAL_STRING("hello world", r);
	free(r);
}

static void	test_strjoin_first_empty(void)
{
	char	*r = ft_strjoin("", "bar");

	TEST_ASSERT_EQUAL_STRING("bar", r);
	free(r);
}

static void	test_strjoin_second_empty(void)
{
	char	*r = ft_strjoin("foo", "");

	TEST_ASSERT_EQUAL_STRING("foo", r);
	free(r);
}

static void	test_strjoin_both_empty(void)
{
	char	*r = ft_strjoin("", "");

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_strjoin_does_not_modify_inputs(void)
{
	char	a[] = "abc";
	char	b[] = "def";
	char	*r = ft_strjoin(a, b);

	TEST_ASSERT_EQUAL_STRING("abc", a);
	TEST_ASSERT_EQUAL_STRING("def", b);
	TEST_ASSERT_TRUE(r != a && r != b);
	free(r);
}

static void	test_strjoin_long(void)
{
	char	*a = malloc(10001);
	char	*b = malloc(10001);
	char	*r;

	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	memset(a, 'a', 10000);
	a[10000] = '\0';
	memset(b, 'b', 10000);
	b[10000] = '\0';
	r = ft_strjoin(a, b);
	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_UINT(20000, (unsigned)strlen(r));
	TEST_ASSERT_EQUAL_CHAR('a', r[9999]);
	TEST_ASSERT_EQUAL_CHAR('b', r[10000]);
	free(a);
	free(b);
	free(r);
}

/* ========================================================================== */
/*  ft_strtrim                                                                */
/* ========================================================================== */

static void	test_strtrim_basic(void)
{
	char	*r = ft_strtrim("  hello  ", " ");

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_strtrim_multiple_set_chars(void)
{
	char	*r = ft_strtrim(" \t\n hello world \n\t ", " \t\n");

	TEST_ASSERT_EQUAL_STRING("hello world", r);
	free(r);
}

static void	test_strtrim_nothing_to_trim(void)
{
	char	*r = ft_strtrim("hello", " ");

	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_strtrim_only_start(void)
{
	char	*r = ft_strtrim("xxhello", "x");

	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_strtrim_only_end(void)
{
	char	*r = ft_strtrim("helloxx", "x");

	TEST_ASSERT_EQUAL_STRING("hello", r);
	free(r);
}

static void	test_strtrim_middle_untouched(void)
{
	char	*r = ft_strtrim("xxhixxhixx", "x");

	TEST_ASSERT_EQUAL_STRING("hixxhi", r);
	free(r);
}

static void	test_strtrim_everything_trimmed(void)
{
	char	*r = ft_strtrim("xxxx", "x");

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_strtrim_empty_string(void)
{
	char	*r = ft_strtrim("", "x");

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_strtrim_empty_set(void)
{
	char	*r = ft_strtrim("  hello  ", "");

	TEST_ASSERT_EQUAL_STRING("  hello  ", r);
	free(r);
}

static void	test_strtrim_set_is_a_set_not_a_substring(void)
{
	char	*r = ft_strtrim("abcHELLOcba", "abc");

	TEST_ASSERT_EQUAL_STRING("HELLO", r);
	free(r);
}

static void	test_strtrim_single_char_remains(void)
{
	char	*r = ft_strtrim("xxaxx", "x");

	TEST_ASSERT_EQUAL_STRING("a", r);
	free(r);
}

static void	test_strtrim_is_new_allocation(void)
{
	const char	*s = "hello";
	char		*r = ft_strtrim(s, "x");

	TEST_ASSERT_TRUE(r != s);
	free(r);
}

/* ========================================================================== */
/*  ft_split                                                                  */
/* ========================================================================== */

static void	test_split_basic(void)
{
	const char	*exp[] = {"hello", "world", "foo"};

	assert_split("hello world foo", ' ', exp, 3);
}

static void	test_split_leading_and_trailing_delimiters(void)
{
	const char	*exp[] = {"hello", "world"};

	assert_split("   hello world   ", ' ', exp, 2);
}

static void	test_split_consecutive_delimiters(void)
{
	const char	*exp[] = {"a", "b", "c"};

	assert_split("a,,,b,,c", ',', exp, 3);
}

static void	test_split_no_delimiter_in_string(void)
{
	const char	*exp[] = {"hello"};

	assert_split("hello", ' ', exp, 1);
}

static void	test_split_empty_string(void)
{
	assert_split("", ' ', NULL, 0);
}

static void	test_split_only_delimiters(void)
{
	assert_split("     ", ' ', NULL, 0);
}

static void	test_split_single_word_with_delimiters(void)
{
	const char	*exp[] = {"word"};

	assert_split("   word   ", ' ', exp, 1);
}

static void	test_split_single_chars(void)
{
	const char	*exp[] = {"a", "b", "c", "d"};

	assert_split("a b c d", ' ', exp, 4);
}

static void	test_split_other_delimiters(void)
{
	const char	*exp[] = {"one", "two", "three"};

	assert_split("one\ttwo\tthree", '\t', exp, 3);
	assert_split("one-two-three", '-', exp, 3);
	assert_split("one\nthree\ntwo", '\n', (const char *[]){"one", "three", "two"}, 3);
}

static void	test_split_nul_delimiter_returns_whole_string(void)
{
	const char	*exp[] = {"hello world"};

	assert_split("hello world", '\0', exp, 1);
}

static void	test_split_words_are_independent_allocations(void)
{
	char	**res = ft_split("abc def", ' ');

	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_NOT_NULL(res[0]);
	TEST_ASSERT_NOT_NULL(res[1]);
	res[0][0] = 'X';
	TEST_ASSERT_EQUAL_STRING("def", res[1]);
	free_split(res);
}

static void	test_split_many_words(void)
{
	char	input[2048];
	char	**res;
	size_t	count = 0;

	input[0] = '\0';
	for (int i = 0; i < 500; i++)
		strcat(input, "ab ");
	res = ft_split(input, ' ');
	TEST_ASSERT_NOT_NULL(res);
	while (res[count])
	{
		TEST_ASSERT_EQUAL_STRING("ab", res[count]);
		count++;
	}
	TEST_ASSERT_EQUAL_UINT(500, (unsigned)count);
	free_split(res);
}

/* ========================================================================== */
/*  ft_itoa                                                                   */
/* ========================================================================== */

static void	assert_itoa(int n, const char *expected)
{
	char	*r = ft_itoa(n);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING(expected, r);
	free(r);
}

static void	test_itoa_zero(void)
{
	assert_itoa(0, "0");
}

static void	test_itoa_positive(void)
{
	assert_itoa(1, "1");
	assert_itoa(42, "42");
	assert_itoa(123456, "123456");
}

static void	test_itoa_negative(void)
{
	assert_itoa(-1, "-1");
	assert_itoa(-42, "-42");
	assert_itoa(-123456, "-123456");
}

static void	test_itoa_powers_of_ten(void)
{
	assert_itoa(10, "10");
	assert_itoa(100, "100");
	assert_itoa(1000000, "1000000");
	assert_itoa(-10, "-10");
	assert_itoa(-1000, "-1000");
}

static void	test_itoa_int_max(void)
{
	assert_itoa(INT_MAX, "2147483647");
}

static void	test_itoa_int_min(void)
{
	assert_itoa(INT_MIN, "-2147483648");
}

static void	test_itoa_near_limits(void)
{
	assert_itoa(INT_MAX - 1, "2147483646");
	assert_itoa(INT_MIN + 1, "-2147483647");
}

static void	test_itoa_matches_snprintf(void)
{
	int	values[] = {0, 7, -7, 99, -99, 100, -100, 12345, -12345, 999999999,
		-999999999};

	for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
	{
		char	expected[16];

		snprintf(expected, sizeof(expected), "%d", values[i]);
		assert_itoa(values[i], expected);
	}
}

/* ========================================================================== */
/*  ft_strmapi / ft_striteri                                                  */
/* ========================================================================== */

static char	upper_on_even_index(unsigned int i, char c)
{
	return ((i % 2 == 0) ? (char)toupper((unsigned char)c) : c);
}

static char	add_index(unsigned int i, char c)
{
	return ((char)(c + i));
}

static char	identity(unsigned int i, char c)
{
	(void)i;
	return (c);
}

static void	iter_upper_on_odd_index(unsigned int i, char *c)
{
	if (i % 2 == 1)
		*c = (char)toupper((unsigned char)*c);
}

static void	iter_add_index(unsigned int i, char *c)
{
	*c = (char)(*c + i);
}

static void	iter_set_x(unsigned int i, char *c)
{
	(void)i;
	*c = 'x';
}

static void	test_strmapi_uses_index_and_char(void)
{
	char	*r = ft_strmapi("abcdef", upper_on_even_index);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("AbCdEf", r);
	free(r);
}

static void	test_strmapi_index_offsets(void)
{
	char	*r = ft_strmapi("aaaa", add_index);

	TEST_ASSERT_EQUAL_STRING("abcd", r);
	free(r);
}

static void	test_strmapi_empty_string(void)
{
	char	*r = ft_strmapi("", upper_on_even_index);

	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING("", r);
	free(r);
}

static void	test_strmapi_does_not_modify_source(void)
{
	char	src[] = "abc";
	char	*r = ft_strmapi(src, add_index);

	TEST_ASSERT_EQUAL_STRING("abc", src);
	TEST_ASSERT_TRUE(r != src);
	free(r);
}

static void	test_strmapi_long_identity(void)
{
	char	*src = malloc(5001);
	char	*r;

	TEST_ASSERT_NOT_NULL(src);
	for (int i = 0; i < 5000; i++)
		src[i] = (char)('a' + (i % 26));
	src[5000] = '\0';
	r = ft_strmapi(src, identity);
	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL_STRING(src, r);
	free(src);
	free(r);
}

static void	test_striteri_modifies_in_place(void)
{
	char	s[] = "abcdef";

	ft_striteri(s, iter_upper_on_odd_index);
	TEST_ASSERT_EQUAL_STRING("aBcDeF", s);
}

static void	test_striteri_index_offsets(void)
{
	char	s[] = "aaaa";

	ft_striteri(s, iter_add_index);
	TEST_ASSERT_EQUAL_STRING("abcd", s);
}

static void	test_striteri_empty_string(void)
{
	char	s[] = "";

	ft_striteri(s, iter_set_x);
	TEST_ASSERT_EQUAL_STRING("", s);
}

static void	test_striteri_does_not_touch_terminator(void)
{
	char	s[] = "abc\0zzz";

	ft_striteri(s, iter_set_x);
	TEST_ASSERT_EQUAL_STRING("xxx", s);
	TEST_ASSERT_EQUAL_CHAR('\0', s[3]);
	TEST_ASSERT_EQUAL_CHAR('z', s[4]);
}

/* ========================================================================== */
/*  ft_put*_fd                                                                */
/* ========================================================================== */

static void	test_putchar_fd_basic(void)
{
	char	buf[16];

	pipe_open();
	ft_putchar_fd('A', g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(1, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("A", buf);
}

static void	test_putchar_fd_multiple_calls(void)
{
	char	buf[16];

	pipe_open();
	ft_putchar_fd('4', g_pipe[1]);
	ft_putchar_fd('2', g_pipe[1]);
	ft_putchar_fd('\n', g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(3, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("42\n", buf);
}

static void	test_putchar_fd_nul_byte(void)
{
	char	buf[16];

	pipe_open();
	ft_putchar_fd('\0', g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(1, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_CHAR('\0', buf[0]);
}

static void	test_putchar_fd_high_byte(void)
{
	char	buf[16];

	pipe_open();
	ft_putchar_fd((char)0xFF, g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(1, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_UINT8(0xFF, (unsigned char)buf[0]);
}

static void	test_putstr_fd_basic(void)
{
	char	buf[64];

	pipe_open();
	ft_putstr_fd("hello world", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(11, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("hello world", buf);
}

static void	test_putstr_fd_empty(void)
{
	char	buf[16];

	pipe_open();
	ft_putstr_fd("", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(0, (unsigned)pipe_collect(buf, sizeof(buf)));
}

static void	test_putstr_fd_no_trailing_newline(void)
{
	char	buf[16];

	pipe_open();
	ft_putstr_fd("abc", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(3, (unsigned)pipe_collect(buf, sizeof(buf)));
}

static void	test_putstr_fd_with_newlines_inside(void)
{
	char	buf[32];

	pipe_open();
	ft_putstr_fd("a\nb\nc", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("a\nb\nc", buf);
}

static void	test_putstr_fd_long(void)
{
	char	src[4001];
	char	buf[4101];

	memset(src, 'z', 4000);
	src[4000] = '\0';
	pipe_open();
	ft_putstr_fd(src, g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(4000, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING(src, buf);
}

static void	test_putendl_fd_basic(void)
{
	char	buf[32];

	pipe_open();
	ft_putendl_fd("hello", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(6, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("hello\n", buf);
}

static void	test_putendl_fd_empty(void)
{
	char	buf[32];

	pipe_open();
	ft_putendl_fd("", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(1, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("\n", buf);
}

static void	test_putendl_fd_exactly_one_newline(void)
{
	char	buf[32];

	pipe_open();
	ft_putendl_fd("a\n", g_pipe[1]);
	TEST_ASSERT_EQUAL_UINT(3, (unsigned)pipe_collect(buf, sizeof(buf)));
	TEST_ASSERT_EQUAL_STRING("a\n\n", buf);
}

static void	assert_putnbr(int n, const char *expected)
{
	char	buf[32];

	pipe_open();
	ft_putnbr_fd(n, g_pipe[1]);
	pipe_collect(buf, sizeof(buf));
	TEST_ASSERT_EQUAL_STRING(expected, buf);
}

static void	test_putnbr_fd_zero(void)
{
	assert_putnbr(0, "0");
}

static void	test_putnbr_fd_positive(void)
{
	assert_putnbr(7, "7");
	assert_putnbr(42, "42");
	assert_putnbr(123456, "123456");
}

static void	test_putnbr_fd_negative(void)
{
	assert_putnbr(-1, "-1");
	assert_putnbr(-42, "-42");
	assert_putnbr(-123456, "-123456");
}

static void	test_putnbr_fd_powers_of_ten(void)
{
	assert_putnbr(10, "10");
	assert_putnbr(1000, "1000");
	assert_putnbr(-100, "-100");
}

static void	test_putnbr_fd_int_max(void)
{
	assert_putnbr(INT_MAX, "2147483647");
}

static void	test_putnbr_fd_int_min(void)
{
	assert_putnbr(INT_MIN, "-2147483648");
}

static void	test_put_functions_can_be_chained(void)
{
	char	buf[64];

	pipe_open();
	ft_putstr_fd("n=", g_pipe[1]);
	ft_putnbr_fd(-12, g_pipe[1]);
	ft_putchar_fd(' ', g_pipe[1]);
	ft_putendl_fd("done", g_pipe[1]);
	pipe_collect(buf, sizeof(buf));
	TEST_ASSERT_EQUAL_STRING("n=-12 done\n", buf);
}

/* ========================================================================== */
/*  Runner                                                                    */
/* ========================================================================== */

void	run_additional_tests(void)
{
	Unity.TestFile = __FILE__;
	/* substr */
	RUN_TEST(test_substr_basic);
	RUN_TEST(test_substr_from_start);
	RUN_TEST(test_substr_len_larger_than_remaining);
	RUN_TEST(test_substr_start_past_end);
	RUN_TEST(test_substr_start_at_end);
	RUN_TEST(test_substr_len_zero);
	RUN_TEST(test_substr_full_string);
	RUN_TEST(test_substr_empty_source);
	RUN_TEST(test_substr_is_new_allocation);
	/* strjoin */
	RUN_TEST(test_strjoin_basic);
	RUN_TEST(test_strjoin_with_space);
	RUN_TEST(test_strjoin_first_empty);
	RUN_TEST(test_strjoin_second_empty);
	RUN_TEST(test_strjoin_both_empty);
	RUN_TEST(test_strjoin_does_not_modify_inputs);
	RUN_TEST(test_strjoin_long);
	/* strtrim */
	RUN_TEST(test_strtrim_basic);
	RUN_TEST(test_strtrim_multiple_set_chars);
	RUN_TEST(test_strtrim_nothing_to_trim);
	RUN_TEST(test_strtrim_only_start);
	RUN_TEST(test_strtrim_only_end);
	RUN_TEST(test_strtrim_middle_untouched);
	RUN_TEST(test_strtrim_everything_trimmed);
	RUN_TEST(test_strtrim_empty_string);
	RUN_TEST(test_strtrim_empty_set);
	RUN_TEST(test_strtrim_set_is_a_set_not_a_substring);
	RUN_TEST(test_strtrim_single_char_remains);
	RUN_TEST(test_strtrim_is_new_allocation);
	/* split */
	RUN_TEST(test_split_basic);
	RUN_TEST(test_split_leading_and_trailing_delimiters);
	RUN_TEST(test_split_consecutive_delimiters);
	RUN_TEST(test_split_no_delimiter_in_string);
	RUN_TEST(test_split_empty_string);
	RUN_TEST(test_split_only_delimiters);
	RUN_TEST(test_split_single_word_with_delimiters);
	RUN_TEST(test_split_single_chars);
	RUN_TEST(test_split_other_delimiters);
	RUN_TEST(test_split_nul_delimiter_returns_whole_string);
	RUN_TEST(test_split_words_are_independent_allocations);
	RUN_TEST(test_split_many_words);
	/* itoa */
	RUN_TEST(test_itoa_zero);
	RUN_TEST(test_itoa_positive);
	RUN_TEST(test_itoa_negative);
	RUN_TEST(test_itoa_powers_of_ten);
	RUN_TEST(test_itoa_int_max);
	RUN_TEST(test_itoa_int_min);
	RUN_TEST(test_itoa_near_limits);
	RUN_TEST(test_itoa_matches_snprintf);
	/* strmapi / striteri */
	RUN_TEST(test_strmapi_uses_index_and_char);
	RUN_TEST(test_strmapi_index_offsets);
	RUN_TEST(test_strmapi_empty_string);
	RUN_TEST(test_strmapi_does_not_modify_source);
	RUN_TEST(test_strmapi_long_identity);
	RUN_TEST(test_striteri_modifies_in_place);
	RUN_TEST(test_striteri_index_offsets);
	RUN_TEST(test_striteri_empty_string);
	RUN_TEST(test_striteri_does_not_touch_terminator);
	/* put*_fd */
	RUN_TEST(test_putchar_fd_basic);
	RUN_TEST(test_putchar_fd_multiple_calls);
	RUN_TEST(test_putchar_fd_nul_byte);
	RUN_TEST(test_putchar_fd_high_byte);
	RUN_TEST(test_putstr_fd_basic);
	RUN_TEST(test_putstr_fd_empty);
	RUN_TEST(test_putstr_fd_no_trailing_newline);
	RUN_TEST(test_putstr_fd_with_newlines_inside);
	RUN_TEST(test_putstr_fd_long);
	RUN_TEST(test_putendl_fd_basic);
	RUN_TEST(test_putendl_fd_empty);
	RUN_TEST(test_putendl_fd_exactly_one_newline);
	RUN_TEST(test_putnbr_fd_zero);
	RUN_TEST(test_putnbr_fd_positive);
	RUN_TEST(test_putnbr_fd_negative);
	RUN_TEST(test_putnbr_fd_powers_of_ten);
	RUN_TEST(test_putnbr_fd_int_max);
	RUN_TEST(test_putnbr_fd_int_min);
	RUN_TEST(test_put_functions_can_be_chained);
}
