#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "libft.h"
#include "test_utils.h"

// Required by Unity (even if empty)
void setUp(void) {
    // Clean state before each test
}

void tearDown(void) {
    // Cleanup after each test
}

static void	fill_pattern(unsigned char *p, size_t n)
{
	for (size_t i = 0; i < n; i++)
		p[i] = (unsigned char)(i * 7 + 3);
}

/* ========================================================================== */
/*  ft_isalpha / ft_isdigit / ft_isalnum / ft_isascii / ft_isprint            */
/* ========================================================================== */

static void	test_isalpha_all_bytes(void)
{
	CHECK_BOOL_FN(ft_isalpha, exp_isalpha, 0, 255);
}

static void	test_isalpha_boundaries(void)
{
	TEST_ASSERT_TRUE(ft_isalpha('a'));
	TEST_ASSERT_TRUE(ft_isalpha('z'));
	TEST_ASSERT_TRUE(ft_isalpha('A'));
	TEST_ASSERT_TRUE(ft_isalpha('Z'));
	TEST_ASSERT_FALSE(ft_isalpha('@'));
	TEST_ASSERT_FALSE(ft_isalpha('['));
	TEST_ASSERT_FALSE(ft_isalpha('`'));
	TEST_ASSERT_FALSE(ft_isalpha('{'));
	TEST_ASSERT_FALSE(ft_isalpha('0'));
	TEST_ASSERT_FALSE(ft_isalpha(' '));
	TEST_ASSERT_FALSE(ft_isalpha(0));
}

static void	test_isdigit_all_bytes(void)
{
	CHECK_BOOL_FN(ft_isdigit, exp_isdigit, 0, 255);
}

static void	test_isdigit_boundaries(void)
{
	TEST_ASSERT_TRUE(ft_isdigit('0'));
	TEST_ASSERT_TRUE(ft_isdigit('9'));
	TEST_ASSERT_TRUE(ft_isdigit('5'));
	TEST_ASSERT_FALSE(ft_isdigit('/'));
	TEST_ASSERT_FALSE(ft_isdigit(':'));
	TEST_ASSERT_FALSE(ft_isdigit('a'));
	TEST_ASSERT_FALSE(ft_isdigit(0));
}

static void	test_isalnum_all_bytes(void)
{
	CHECK_BOOL_FN(ft_isalnum, exp_isalnum, 0, 255);
}

static void	test_isalnum_samples(void)
{
	TEST_ASSERT_TRUE(ft_isalnum('a'));
	TEST_ASSERT_TRUE(ft_isalnum('Z'));
	TEST_ASSERT_TRUE(ft_isalnum('0'));
	TEST_ASSERT_TRUE(ft_isalnum('9'));
	TEST_ASSERT_FALSE(ft_isalnum('_'));
	TEST_ASSERT_FALSE(ft_isalnum('-'));
	TEST_ASSERT_FALSE(ft_isalnum(' '));
	TEST_ASSERT_FALSE(ft_isalnum('\n'));
}

static void	test_isascii_all_bytes(void)
{
	CHECK_BOOL_FN(ft_isascii, exp_isascii, 0, 255);
}

static void	test_isascii_boundaries(void)
{
	TEST_ASSERT_TRUE(ft_isascii(0));
	TEST_ASSERT_TRUE(ft_isascii(127));
	TEST_ASSERT_FALSE(ft_isascii(128));
	TEST_ASSERT_FALSE(ft_isascii(255));
}

static void	test_isprint_all_bytes(void)
{
	CHECK_BOOL_FN(ft_isprint, exp_isprint, 0, 255);
}

static void	test_isprint_boundaries(void)
{
	TEST_ASSERT_FALSE(ft_isprint(31));
	TEST_ASSERT_TRUE(ft_isprint(32));
	TEST_ASSERT_TRUE(ft_isprint('~'));
	TEST_ASSERT_FALSE(ft_isprint(127));
	TEST_ASSERT_FALSE(ft_isprint('\n'));
	TEST_ASSERT_FALSE(ft_isprint('\t'));
	TEST_ASSERT_FALSE(ft_isprint(0));
}

/* ========================================================================== */
/*  ft_strlen                                                                 */
/* ========================================================================== */

static void	test_strlen_empty(void)
{
	TEST_ASSERT_EQUAL_UINT(0, (unsigned)ft_strlen(""));
}

static void	test_strlen_single(void)
{
	TEST_ASSERT_EQUAL_UINT(1, (unsigned)ft_strlen("a"));
}

static void	test_strlen_regular(void)
{
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlen("hello"));
	TEST_ASSERT_EQUAL_UINT(11, (unsigned)ft_strlen("hello world"));
}

static void	test_strlen_stops_at_nul(void)
{
	TEST_ASSERT_EQUAL_UINT(2, (unsigned)ft_strlen("ab\0cd"));
}

static void	test_strlen_whitespace_and_specials(void)
{
	TEST_ASSERT_EQUAL_UINT(4, (unsigned)ft_strlen(" \t\n\r"));
	TEST_ASSERT_EQUAL_UINT(3, (unsigned)ft_strlen("\x80\xff\x01"));
}

static void	test_strlen_long(void)
{
	char	*s = malloc(100001);

	TEST_ASSERT_NOT_NULL(s);
	memset(s, 'a', 100000);
	s[100000] = '\0';
	TEST_ASSERT_EQUAL_UINT(100000, (unsigned)ft_strlen(s));
	free(s);
}

/* ========================================================================== */
/*  ft_memset / ft_bzero                                                      */
/* ========================================================================== */

static void	test_memset_matches_libc(void)
{
	int	values[] = {0, 'x', 1, 127, 128, 255};

	for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
	{
		unsigned char	a[64];
		unsigned char	b[64];

		memset(a, 0xAA, sizeof(a));
		memset(b, 0xAA, sizeof(b));
		memset(a + 8, values[i], 20);
		ft_memset(b + 8, values[i], 20);
		TEST_ASSERT_EQUAL_MEMORY(a, b, sizeof(a));
	}
}

static void	test_memset_returns_destination(void)
{
	char	buf[16];

	TEST_ASSERT_EQUAL_PTR(buf, ft_memset(buf, 'a', sizeof(buf)));
}

static void	test_memset_zero_length(void)
{
	char	buf[8];

	memset(buf, 'z', sizeof(buf));
	ft_memset(buf, 'a', 0);
	for (size_t i = 0; i < sizeof(buf); i++)
		TEST_ASSERT_EQUAL_CHAR('z', buf[i]);
}

static void	test_memset_converts_to_unsigned_char(void)
{
	unsigned char	buf[4];

	ft_memset(buf, 256 + 65, sizeof(buf));
	for (size_t i = 0; i < sizeof(buf); i++)
		TEST_ASSERT_EQUAL_UINT8(65, buf[i]);
	ft_memset(buf, -1, sizeof(buf));
	for (size_t i = 0; i < sizeof(buf); i++)
		TEST_ASSERT_EQUAL_UINT8(255, buf[i]);
}

static void	test_memset_does_not_overflow(void)
{
	unsigned char	buf[10];

	memset(buf, 0, sizeof(buf));
	ft_memset(buf + 2, 'x', 5);
	TEST_ASSERT_EQUAL_UINT8(0, buf[1]);
	TEST_ASSERT_EQUAL_UINT8('x', buf[2]);
	TEST_ASSERT_EQUAL_UINT8('x', buf[6]);
	TEST_ASSERT_EQUAL_UINT8(0, buf[7]);
}

static void	test_memset_large(void)
{
	size_t			n = 100000;
	unsigned char	*p = malloc(n);

	TEST_ASSERT_NOT_NULL(p);
	ft_memset(p, 0x5A, n);
	for (size_t i = 0; i < n; i++)
		if (p[i] != 0x5A)
			TEST_FAIL_MESSAGE("ft_memset large buffer mismatch");
	free(p);
}

static void	test_bzero_basic(void)
{
	unsigned char	buf[16];
	unsigned char	zeros[16] = {0};

	memset(buf, 0xFF, sizeof(buf));
	ft_bzero(buf, sizeof(buf));
	TEST_ASSERT_EQUAL_MEMORY(zeros, buf, sizeof(buf));
}

static void	test_bzero_partial(void)
{
	unsigned char	buf[10];

	memset(buf, 0xFF, sizeof(buf));
	ft_bzero(buf + 2, 4);
	TEST_ASSERT_EQUAL_UINT8(0xFF, buf[1]);
	for (int i = 2; i < 6; i++)
		TEST_ASSERT_EQUAL_UINT8(0, buf[i]);
	TEST_ASSERT_EQUAL_UINT8(0xFF, buf[6]);
}

static void	test_bzero_zero_length(void)
{
	unsigned char	buf[4];

	memset(buf, 0x42, sizeof(buf));
	ft_bzero(buf, 0);
	for (size_t i = 0; i < sizeof(buf); i++)
		TEST_ASSERT_EQUAL_UINT8(0x42, buf[i]);
}

/* ========================================================================== */
/*  ft_memcpy / ft_memmove                                                    */
/* ========================================================================== */

static void	test_memcpy_basic(void)
{
	char	dst[16] = {0};

	ft_memcpy(dst, "hello", 6);
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

static void	test_memcpy_returns_destination(void)
{
	char	dst[8];

	TEST_ASSERT_EQUAL_PTR(dst, ft_memcpy(dst, "abc", 4));
}

static void	test_memcpy_zero_length(void)
{
	char	dst[4] = "abc";

	ft_memcpy(dst, "xyz", 0);
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

static void	test_memcpy_with_embedded_nul(void)
{
	unsigned char	src[] = {1, 0, 2, 0, 3};
	unsigned char	dst[5] = {0};

	ft_memcpy(dst, src, sizeof(src));
	TEST_ASSERT_EQUAL_MEMORY(src, dst, sizeof(src));
}

static void	test_memcpy_partial_copy(void)
{
	char	dst[8];

	memset(dst, 'X', sizeof(dst));
	ft_memcpy(dst, "abcdef", 3);
	TEST_ASSERT_EQUAL_CHAR('a', dst[0]);
	TEST_ASSERT_EQUAL_CHAR('c', dst[2]);
	TEST_ASSERT_EQUAL_CHAR('X', dst[3]);
}

static void	test_memcpy_large(void)
{
	unsigned char	src[4096];
	unsigned char	dst[4096];

	fill_pattern(src, sizeof(src));
	memset(dst, 0, sizeof(dst));
	ft_memcpy(dst, src, sizeof(src));
	TEST_ASSERT_EQUAL_MEMORY(src, dst, sizeof(src));
}

static void	test_memmove_no_overlap(void)
{
	char	dst[16] = {0};

	ft_memmove(dst, "hello", 6);
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

static void	test_memmove_returns_destination(void)
{
	char	dst[8];

	TEST_ASSERT_EQUAL_PTR(dst, ft_memmove(dst, "abc", 4));
}

static void	test_memmove_overlap_dst_after_src(void)
{
	char	buf[] = "0123456789";

	ft_memmove(buf + 2, buf, 5);
	TEST_ASSERT_EQUAL_STRING("0101234789", buf);
}

static void	test_memmove_overlap_dst_before_src(void)
{
	char	buf[] = "0123456789";

	ft_memmove(buf, buf + 2, 5);
	TEST_ASSERT_EQUAL_STRING("2345656789", buf);
}

static void	test_memmove_overlap_by_one(void)
{
	char	buf[] = "abcdef";

	ft_memmove(buf + 1, buf, 5);
	TEST_ASSERT_EQUAL_STRING("aabcde", buf);
}

static void	test_memmove_same_pointer(void)
{
	char	buf[] = "abcdef";

	ft_memmove(buf, buf, 6);
	TEST_ASSERT_EQUAL_STRING("abcdef", buf);
}

static void	test_memmove_zero_length(void)
{
	char	buf[] = "abc";

	ft_memmove(buf, "xyz", 0);
	TEST_ASSERT_EQUAL_STRING("abc", buf);
}

static void	test_memmove_large_overlap_matches_libc(void)
{
	unsigned char	a[2048];
	unsigned char	b[2048];

	fill_pattern(a, sizeof(a));
	memcpy(b, a, sizeof(b));
	memmove(a + 100, a + 10, 1500);
	ft_memmove(b + 100, b + 10, 1500);
	TEST_ASSERT_EQUAL_MEMORY(a, b, sizeof(a));
	fill_pattern(a, sizeof(a));
	memcpy(b, a, sizeof(b));
	memmove(a + 10, a + 100, 1500);
	ft_memmove(b + 10, b + 100, 1500);
	TEST_ASSERT_EQUAL_MEMORY(a, b, sizeof(a));
}

/* ========================================================================== */
/*  ft_strlcpy / ft_strlcat                                                   */
/* ========================================================================== */

static void	test_strlcpy_fits(void)
{
	char	dst[20];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", sizeof(dst)));
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

static void	test_strlcpy_truncates(void)
{
	char	dst[10];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", 3));
	TEST_ASSERT_EQUAL_CHAR('h', dst[0]);
	TEST_ASSERT_EQUAL_CHAR('e', dst[1]);
	TEST_ASSERT_EQUAL_CHAR('\0', dst[2]);
	TEST_ASSERT_EQUAL_CHAR('X', dst[3]);
}

static void	test_strlcpy_size_zero(void)
{
	char	dst[4];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", 0));
	TEST_ASSERT_EQUAL_CHAR('X', dst[0]);
}

static void	test_strlcpy_size_one(void)
{
	char	dst[4];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", 1));
	TEST_ASSERT_EQUAL_CHAR('\0', dst[0]);
	TEST_ASSERT_EQUAL_CHAR('X', dst[1]);
}

static void	test_strlcpy_exact_fit(void)
{
	char	dst[10];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", 6));
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

static void	test_strlcpy_one_short(void)
{
	char	dst[10];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcpy(dst, "hello", 5));
	TEST_ASSERT_EQUAL_STRING("hell", dst);
}

static void	test_strlcpy_empty_source(void)
{
	char	dst[4];

	memset(dst, 'X', sizeof(dst));
	TEST_ASSERT_EQUAL_UINT(0, (unsigned)ft_strlcpy(dst, "", sizeof(dst)));
	TEST_ASSERT_EQUAL_CHAR('\0', dst[0]);
}

static void	test_strlcat_basic(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(6, (unsigned)ft_strlcat(dst, "def", sizeof(dst)));
	TEST_ASSERT_EQUAL_STRING("abcdef", dst);
}

static void	test_strlcat_size_zero(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(3, (unsigned)ft_strlcat(dst, "def", 0));
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

static void	test_strlcat_size_smaller_than_dst(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcat(dst, "def", 2));
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

static void	test_strlcat_size_equals_dst_len(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(6, (unsigned)ft_strlcat(dst, "def", 3));
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

static void	test_strlcat_only_room_for_nul(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(6, (unsigned)ft_strlcat(dst, "xyz", 4));
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

static void	test_strlcat_truncates(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(8, (unsigned)ft_strlcat(dst, "defgh", 6));
	TEST_ASSERT_EQUAL_STRING("abcde", dst);
}

static void	test_strlcat_empty_dst(void)
{
	char	dst[20] = "";

	TEST_ASSERT_EQUAL_UINT(5, (unsigned)ft_strlcat(dst, "hello", sizeof(dst)));
	TEST_ASSERT_EQUAL_STRING("hello", dst);
}

static void	test_strlcat_empty_src(void)
{
	char	dst[20] = "abc";

	TEST_ASSERT_EQUAL_UINT(3, (unsigned)ft_strlcat(dst, "", sizeof(dst)));
	TEST_ASSERT_EQUAL_STRING("abc", dst);
}

/* ========================================================================== */
/*  ft_toupper / ft_tolower                                                   */
/* ========================================================================== */

static void	test_toupper_all_bytes(void)
{
	CHECK_INT_FN(ft_toupper, toupper, 0, 255);
}

static void	test_toupper_samples(void)
{
	TEST_ASSERT_EQUAL_INT('A', ft_toupper('a'));
	TEST_ASSERT_EQUAL_INT('Z', ft_toupper('z'));
	TEST_ASSERT_EQUAL_INT('A', ft_toupper('A'));
	TEST_ASSERT_EQUAL_INT('@', ft_toupper('@'));
	TEST_ASSERT_EQUAL_INT('{', ft_toupper('{'));
	TEST_ASSERT_EQUAL_INT('5', ft_toupper('5'));
}

static void	test_tolower_all_bytes(void)
{
	CHECK_INT_FN(ft_tolower, tolower, 0, 255);
}

static void	test_tolower_samples(void)
{
	TEST_ASSERT_EQUAL_INT('a', ft_tolower('A'));
	TEST_ASSERT_EQUAL_INT('z', ft_tolower('Z'));
	TEST_ASSERT_EQUAL_INT('a', ft_tolower('a'));
	TEST_ASSERT_EQUAL_INT('@', ft_tolower('@'));
	TEST_ASSERT_EQUAL_INT('[', ft_tolower('['));
	TEST_ASSERT_EQUAL_INT('5', ft_tolower('5'));
}

/* ========================================================================== */
/*  ft_strchr / ft_strrchr                                                    */
/* ========================================================================== */

static void	test_strchr_first_occurrence(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 2, ft_strchr(s, 'l'));
}

static void	test_strchr_first_and_last_char(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s, ft_strchr(s, 'h'));
	TEST_ASSERT_EQUAL_PTR(s + 4, ft_strchr(s, 'o'));
}

static void	test_strchr_nul_terminator(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 5, ft_strchr(s, '\0'));
}

static void	test_strchr_not_found(void)
{
	TEST_ASSERT_NULL(ft_strchr("hello", 'z'));
}

static void	test_strchr_empty_string(void)
{
	const char	*s = "";

	TEST_ASSERT_EQUAL_PTR(s, ft_strchr(s, '\0'));
	TEST_ASSERT_NULL(ft_strchr(s, 'a'));
}

static void	test_strchr_int_converted_to_char(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 2, ft_strchr(s, 'l' + 256));
}

static void	test_strchr_matches_libc(void)
{
	const char	*s = "the quick brown fox";

	for (int c = 0; c < 128; c++)
		TEST_ASSERT_EQUAL_PTR(strchr(s, c), ft_strchr(s, c));
}

static void	test_strrchr_last_occurrence(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 3, ft_strrchr(s, 'l'));
}

static void	test_strrchr_single_occurrence(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 1, ft_strrchr(s, 'e'));
	TEST_ASSERT_EQUAL_PTR(s, ft_strrchr(s, 'h'));
}

static void	test_strrchr_nul_terminator(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 5, ft_strrchr(s, '\0'));
}

static void	test_strrchr_not_found(void)
{
	TEST_ASSERT_NULL(ft_strrchr("hello", 'z'));
}

static void	test_strrchr_empty_string(void)
{
	const char	*s = "";

	TEST_ASSERT_EQUAL_PTR(s, ft_strrchr(s, '\0'));
	TEST_ASSERT_NULL(ft_strrchr(s, 'a'));
}

static void	test_strrchr_matches_libc(void)
{
	const char	*s = "the quick brown fox";

	for (int c = 0; c < 128; c++)
		TEST_ASSERT_EQUAL_PTR(strrchr(s, c), ft_strrchr(s, c));
}

/* ========================================================================== */
/*  ft_strncmp                                                                */
/* ========================================================================== */

static void	test_strncmp_equal(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("hello", "hello", 5));
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("hello", "hello", 100));
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("", "", 5));
}

static void	test_strncmp_n_zero(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("abc", "xyz", 0));
}

static void	test_strncmp_difference_value(void)
{
	TEST_ASSERT_EQUAL_INT('c' - 'x', ft_strncmp("abc", "abx", 3));
	TEST_ASSERT_EQUAL_INT('a' - 'b', ft_strncmp("a", "b", 1));
}

static void	test_strncmp_limit_before_difference(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("abcdef", "abcxyz", 3));
	TEST_ASSERT_TRUE(ft_strncmp("abcdef", "abcxyz", 4) < 0);
}

static void	test_strncmp_prefix(void)
{
	TEST_ASSERT_TRUE(ft_strncmp("abc", "abcd", 4) < 0);
	TEST_ASSERT_TRUE(ft_strncmp("abcd", "abc", 4) > 0);
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("abc", "abcd", 3));
}

static void	test_strncmp_unsigned_comparison(void)
{
	TEST_ASSERT_TRUE(ft_strncmp("\200", "\0", 1) > 0);
	TEST_ASSERT_TRUE(ft_strncmp("\0", "\200", 1) < 0);
	TEST_ASSERT_TRUE(ft_strncmp("a\377", "a\177", 2) > 0);
}

static void	test_strncmp_stops_at_nul(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_strncmp("ab\0cd", "ab\0ef", 5));
}

static void	test_strncmp_matches_libc(void)
{
	static const struct
	{
		const char	*a;
		const char	*b;
		size_t		n;
	}	cases[] = {
		{"", "", 1}, {"a", "", 1}, {"", "a", 1}, {"abc", "abd", 3},
		{"abc", "abd", 2}, {"abc", "ab", 5}, {"ab", "abc", 5},
		{"Hello", "hello", 5}, {"test\n", "test", 5}, {"1", "2", 1},
		{"zzz", "aaa", 3}, {"\x7f", "\x80", 1}
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
		TEST_ASSERT_EQUAL_INT_MESSAGE(
			SIGN(strncmp(cases[i].a, cases[i].b, cases[i].n)),
			SIGN(ft_strncmp(cases[i].a, cases[i].b, cases[i].n)),
			"sign mismatch against libc strncmp");
}

/* ========================================================================== */
/*  ft_memchr / ft_memcmp                                                     */
/* ========================================================================== */

static void	test_memchr_found(void)
{
	const char	*s = "hello world";

	TEST_ASSERT_EQUAL_PTR(s + 6, ft_memchr(s, 'w', 11));
	TEST_ASSERT_EQUAL_PTR(s, ft_memchr(s, 'h', 11));
}

static void	test_memchr_first_occurrence(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s + 2, ft_memchr(s, 'l', 5));
}

static void	test_memchr_limit_respected(void)
{
	const char	*s = "hello world";

	TEST_ASSERT_NULL(ft_memchr(s, 'w', 6));
	TEST_ASSERT_EQUAL_PTR(s + 6, ft_memchr(s, 'w', 7));
}

static void	test_memchr_n_zero(void)
{
	TEST_ASSERT_NULL(ft_memchr("hello", 'h', 0));
}

static void	test_memchr_not_found(void)
{
	TEST_ASSERT_NULL(ft_memchr("hello", 'z', 5));
}

static void	test_memchr_binary_data(void)
{
	unsigned char	buf[] = {1, 2, 0, 3, 0xFF, 4};

	TEST_ASSERT_EQUAL_PTR(buf + 2, ft_memchr(buf, 0, sizeof(buf)));
	TEST_ASSERT_EQUAL_PTR(buf + 4, ft_memchr(buf, 0xFF, sizeof(buf)));
}

static void	test_memchr_does_not_stop_at_nul(void)
{
	const char	s[] = "ab\0cd";

	TEST_ASSERT_EQUAL_PTR(s + 3, ft_memchr(s, 'c', 5));
}

static void	test_memchr_int_converted_to_unsigned_char(void)
{
	const char	*s = "hello";

	TEST_ASSERT_EQUAL_PTR(s, ft_memchr(s, 'h' + 256, 5));
}

static void	test_memcmp_equal(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_memcmp("hello", "hello", 5));
	TEST_ASSERT_EQUAL_INT(0, ft_memcmp("abc", "xyz", 0));
}

static void	test_memcmp_difference(void)
{
	TEST_ASSERT_TRUE(ft_memcmp("abc", "abd", 3) < 0);
	TEST_ASSERT_TRUE(ft_memcmp("abd", "abc", 3) > 0);
	TEST_ASSERT_EQUAL_INT(0, ft_memcmp("abc", "abd", 2));
}

static void	test_memcmp_embedded_nul(void)
{
	TEST_ASSERT_TRUE(ft_memcmp("ab\0cd", "ab\0ce", 5) < 0);
	TEST_ASSERT_EQUAL_INT(0, ft_memcmp("ab\0cd", "ab\0cd", 5));
}

static void	test_memcmp_unsigned_comparison(void)
{
	unsigned char	a[] = {0x80};
	unsigned char	b[] = {0x7F};

	TEST_ASSERT_TRUE(ft_memcmp(a, b, 1) > 0);
	TEST_ASSERT_TRUE(ft_memcmp(b, a, 1) < 0);
}

static void	test_memcmp_difference_value(void)
{
	TEST_ASSERT_EQUAL_INT(1, SIGN(ft_memcmp("b", "a", 1)));
	TEST_ASSERT_EQUAL_INT('c' - 'a', ft_memcmp("abc", "aba", 3));
}

static void	test_memcmp_matches_libc(void)
{
	unsigned char	a[32];
	unsigned char	b[32];

	fill_pattern(a, sizeof(a));
	memcpy(b, a, sizeof(b));
	TEST_ASSERT_EQUAL_INT(0, ft_memcmp(a, b, sizeof(a)));
	for (size_t i = 0; i < sizeof(a); i++)
	{
		b[i] ^= 0x01;
		TEST_ASSERT_EQUAL_INT(SIGN(memcmp(a, b, sizeof(a))),
			SIGN(ft_memcmp(a, b, sizeof(a))));
		b[i] ^= 0x01;
	}
}

/* ========================================================================== */
/*  ft_strnstr                                                                */
/* ========================================================================== */

static void	test_strnstr_found(void)
{
	const char	*h = "hello world";

	TEST_ASSERT_EQUAL_PTR(h + 6, ft_strnstr(h, "world", 11));
	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "hello", 11));
	TEST_ASSERT_EQUAL_PTR(h + 4, ft_strnstr(h, "o w", 11));
}

static void	test_strnstr_len_too_small(void)
{
	const char	*h = "hello world";

	TEST_ASSERT_NULL(ft_strnstr(h, "world", 10));
	TEST_ASSERT_NULL(ft_strnstr(h, "world", 5));
	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "hello", 5));
	TEST_ASSERT_NULL(ft_strnstr(h, "hello", 4));
}

static void	test_strnstr_empty_needle(void)
{
	const char	*h = "hello";

	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "", 5));
	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "", 0));
	TEST_ASSERT_NOT_EQUAL_PTR(h, ft_strnstr("", "", 0));
}

static void	test_strnstr_len_zero(void)
{
	TEST_ASSERT_NULL(ft_strnstr("hello", "h", 0));
}

static void	test_strnstr_needle_longer_than_haystack(void)
{
	TEST_ASSERT_NULL(ft_strnstr("abc", "abcd", 10));
	TEST_ASSERT_NULL(ft_strnstr("", "a", 10));
}

static void	test_strnstr_len_larger_than_haystack(void)
{
	const char	*h = "hello";

	TEST_ASSERT_EQUAL_PTR(h + 3, ft_strnstr(h, "lo", 1000));
}

static void	test_strnstr_needle_equals_haystack(void)
{
	const char	*h = "abc";

	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "abc", 3));
	TEST_ASSERT_NULL(ft_strnstr(h, "abc", 2));
}

static void	test_strnstr_requires_backtracking(void)
{
	const char	*h = "aaabc";

	TEST_ASSERT_EQUAL_PTR(h + 1, ft_strnstr(h, "aabc", 5));
	TEST_ASSERT_NULL(ft_strnstr(h, "aabc", 4));
}

static void	test_strnstr_first_occurrence(void)
{
	const char	*h = "abcabcabc";

	TEST_ASSERT_EQUAL_PTR(h, ft_strnstr(h, "abc", 9));
	TEST_ASSERT_EQUAL_PTR(h + 2, ft_strnstr(h, "cab", 9));
}

static void	test_strnstr_partial_match_then_mismatch(void)
{
	const char	*h = "mississippi";

	TEST_ASSERT_EQUAL_PTR(h + 4, ft_strnstr(h, "issip", 11));
	TEST_ASSERT_NULL(ft_strnstr(h, "issipi", 11));
}

/* ========================================================================== */
/*  ft_atoi                                                                   */
/* ========================================================================== */

static void	test_atoi_matches_libc(void)
{
	static const char	*inputs[] = {
		"0", "1", "42", "-42", "+42", "0042", "-0", "+0", "12345678",
		"  42", "\t\n\v\f\r 42", "   -42", "\n+7", "42abc", "-42abc",
		"abc42", "abc", "", " ", "-", "+", "--1", "++1", "+-1", "-+1",
		"- 1", "+ 1", "1 2", "2147483647", "-2147483648", "0x1A", "1e5",
		"   +000123xyz"
	};

	for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
		TEST_ASSERT_EQUAL_INT_MESSAGE(atoi(inputs[i]), ft_atoi(inputs[i]),
			inputs[i]);
}

static void	test_atoi_explicit_values(void)
{
	TEST_ASSERT_EQUAL_INT(42, ft_atoi("42"));
	TEST_ASSERT_EQUAL_INT(-42, ft_atoi("-42"));
	TEST_ASSERT_EQUAL_INT(42, ft_atoi("+42"));
	TEST_ASSERT_EQUAL_INT(42, ft_atoi("   \t\n42"));
	TEST_ASSERT_EQUAL_INT(0, ft_atoi("abc"));
	TEST_ASSERT_EQUAL_INT(12, ft_atoi("12abc34"));
	TEST_ASSERT_EQUAL_INT(0, ft_atoi("--5"));
	TEST_ASSERT_EQUAL_INT(0, ft_atoi("+-5"));
	TEST_ASSERT_EQUAL_INT(0, ft_atoi("- 5"));
}

static void	test_atoi_int_limits(void)
{
	TEST_ASSERT_EQUAL_INT(INT32_MAX, ft_atoi("2147483647"));
	TEST_ASSERT_EQUAL_INT(INT32_MIN, ft_atoi("-2147483648"));
}

/* ========================================================================== */
/*  ft_calloc / ft_strdup                                                     */
/* ========================================================================== */

static void	test_calloc_zeroed(void)
{
	int	*p = ft_calloc(10, sizeof(int));

	TEST_ASSERT_NOT_NULL(p);
	for (int i = 0; i < 10; i++)
		TEST_ASSERT_EQUAL_INT(0, p[i]);
	free(p);
}

static void	test_calloc_large_zeroed(void)
{
	size_t			n = 1000 * 1000;
	unsigned char	*p = ft_calloc(1000, 1000);

	TEST_ASSERT_NOT_NULL(p);
	for (size_t i = 0; i < n; i++)
		if (p[i] != 0)
			TEST_FAIL_MESSAGE("ft_calloc memory not zeroed");
	free(p);
}

static void	test_calloc_writable(void)
{
	char	*p = ft_calloc(6, sizeof(char));

	TEST_ASSERT_NOT_NULL(p);
	strcpy(p, "hello");
	TEST_ASSERT_EQUAL_STRING("hello", p);
	free(p);
}

static void	test_calloc_zero_size_is_freeable(void)
{
	/* NULL or a unique pointer are both acceptable: it must simply not crash
	** and be safe to free. */
	void	*p = ft_calloc(0, 1);

	free(p);
	p = ft_calloc(1, 0);
	free(p);
	TEST_PASS();
}

static void	test_calloc_overflow_returns_null(void)
{
	size_t	big = SIZE_MAX;
	void	*p = ft_calloc(big, 2);

	TEST_ASSERT_NULL(p);
	free(p);
}

static void	test_strdup_basic(void)
{
	const char	*src = "hello";
	char		*dup = ft_strdup(src);

	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_STRING("hello", dup);
	TEST_ASSERT_TRUE(src != dup);
	free(dup);
}

static void	test_strdup_empty(void)
{
	char	*dup = ft_strdup("");

	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_STRING("", dup);
	free(dup);
}

static void	test_strdup_is_independent_copy(void)
{
	char	src[] = "hello";
	char	*dup = ft_strdup(src);

	src[0] = 'J';
	TEST_ASSERT_EQUAL_STRING("hello", dup);
	dup[1] = 'E';
	TEST_ASSERT_EQUAL_STRING("Jello", src);
	free(dup);
}

static void	test_strdup_long(void)
{
	char	*src = malloc(50001);
	char	*dup;

	TEST_ASSERT_NOT_NULL(src);
	memset(src, 'q', 50000);
	src[50000] = '\0';
	dup = ft_strdup(src);
	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_STRING(src, dup);
	free(src);
	free(dup);
}

/* ========================================================================== */
/*  Runner                                                                    */
/* ========================================================================== */

void	run_libc_tests(void)
{
	Unity.TestFile = __FILE__;
	/* ctype-like */
	RUN_TEST(test_isalpha_all_bytes);
	RUN_TEST(test_isalpha_boundaries);
	RUN_TEST(test_isdigit_all_bytes);
	RUN_TEST(test_isdigit_boundaries);
	RUN_TEST(test_isalnum_all_bytes);
	RUN_TEST(test_isalnum_samples);
	RUN_TEST(test_isascii_all_bytes);
	RUN_TEST(test_isascii_boundaries);
	RUN_TEST(test_isprint_all_bytes);
	RUN_TEST(test_isprint_boundaries);
	/* strlen */
	RUN_TEST(test_strlen_empty);
	RUN_TEST(test_strlen_single);
	RUN_TEST(test_strlen_regular);
	RUN_TEST(test_strlen_stops_at_nul);
	RUN_TEST(test_strlen_whitespace_and_specials);
	RUN_TEST(test_strlen_long);
	/* memset / bzero */
	RUN_TEST(test_memset_matches_libc);
	RUN_TEST(test_memset_returns_destination);
	RUN_TEST(test_memset_zero_length);
	RUN_TEST(test_memset_converts_to_unsigned_char);
	RUN_TEST(test_memset_does_not_overflow);
	RUN_TEST(test_memset_large);
	RUN_TEST(test_bzero_basic);
	RUN_TEST(test_bzero_partial);
	RUN_TEST(test_bzero_zero_length);
	/* memcpy / memmove */
	RUN_TEST(test_memcpy_basic);
	RUN_TEST(test_memcpy_returns_destination);
	RUN_TEST(test_memcpy_zero_length);
	RUN_TEST(test_memcpy_with_embedded_nul);
	RUN_TEST(test_memcpy_partial_copy);
	RUN_TEST(test_memcpy_large);
	RUN_TEST(test_memmove_no_overlap);
	RUN_TEST(test_memmove_returns_destination);
	RUN_TEST(test_memmove_overlap_dst_after_src);
	RUN_TEST(test_memmove_overlap_dst_before_src);
	RUN_TEST(test_memmove_overlap_by_one);
	RUN_TEST(test_memmove_same_pointer);
	RUN_TEST(test_memmove_zero_length);
	RUN_TEST(test_memmove_large_overlap_matches_libc);
	/* strlcpy / strlcat */
	RUN_TEST(test_strlcpy_fits);
	RUN_TEST(test_strlcpy_truncates);
	RUN_TEST(test_strlcpy_size_zero);
	RUN_TEST(test_strlcpy_size_one);
	RUN_TEST(test_strlcpy_exact_fit);
	RUN_TEST(test_strlcpy_one_short);
	RUN_TEST(test_strlcpy_empty_source);
	RUN_TEST(test_strlcat_basic);
	RUN_TEST(test_strlcat_size_zero);
	RUN_TEST(test_strlcat_size_smaller_than_dst);
	RUN_TEST(test_strlcat_size_equals_dst_len);
	RUN_TEST(test_strlcat_only_room_for_nul);
	RUN_TEST(test_strlcat_truncates);
	RUN_TEST(test_strlcat_empty_dst);
	RUN_TEST(test_strlcat_empty_src);
	/* toupper / tolower */
	RUN_TEST(test_toupper_all_bytes);
	RUN_TEST(test_toupper_samples);
	RUN_TEST(test_tolower_all_bytes);
	RUN_TEST(test_tolower_samples);
	/* strchr / strrchr */
	RUN_TEST(test_strchr_first_occurrence);
	RUN_TEST(test_strchr_first_and_last_char);
	RUN_TEST(test_strchr_nul_terminator);
	RUN_TEST(test_strchr_not_found);
	RUN_TEST(test_strchr_empty_string);
	RUN_TEST(test_strchr_int_converted_to_char);
	RUN_TEST(test_strchr_matches_libc);
	RUN_TEST(test_strrchr_last_occurrence);
	RUN_TEST(test_strrchr_single_occurrence);
	RUN_TEST(test_strrchr_nul_terminator);
	RUN_TEST(test_strrchr_not_found);
	RUN_TEST(test_strrchr_empty_string);
	RUN_TEST(test_strrchr_matches_libc);
	/* strncmp */
	RUN_TEST(test_strncmp_equal);
	RUN_TEST(test_strncmp_n_zero);
	RUN_TEST(test_strncmp_difference_value);
	RUN_TEST(test_strncmp_limit_before_difference);
	RUN_TEST(test_strncmp_prefix);
	RUN_TEST(test_strncmp_unsigned_comparison);
	RUN_TEST(test_strncmp_stops_at_nul);
	RUN_TEST(test_strncmp_matches_libc);
	/* memchr / memcmp */
	RUN_TEST(test_memchr_found);
	RUN_TEST(test_memchr_first_occurrence);
	RUN_TEST(test_memchr_limit_respected);
	RUN_TEST(test_memchr_n_zero);
	RUN_TEST(test_memchr_not_found);
	RUN_TEST(test_memchr_binary_data);
	RUN_TEST(test_memchr_does_not_stop_at_nul);
	RUN_TEST(test_memchr_int_converted_to_unsigned_char);
	RUN_TEST(test_memcmp_equal);
	RUN_TEST(test_memcmp_difference);
	RUN_TEST(test_memcmp_embedded_nul);
	RUN_TEST(test_memcmp_unsigned_comparison);
	RUN_TEST(test_memcmp_difference_value);
	RUN_TEST(test_memcmp_matches_libc);
	/* strnstr */
	RUN_TEST(test_strnstr_found);
	RUN_TEST(test_strnstr_len_too_small);
	RUN_TEST(test_strnstr_empty_needle);
	RUN_TEST(test_strnstr_len_zero);
	RUN_TEST(test_strnstr_needle_longer_than_haystack);
	RUN_TEST(test_strnstr_len_larger_than_haystack);
	RUN_TEST(test_strnstr_needle_equals_haystack);
	RUN_TEST(test_strnstr_requires_backtracking);
	RUN_TEST(test_strnstr_first_occurrence);
	RUN_TEST(test_strnstr_partial_match_then_mismatch);
	/* atoi */
	RUN_TEST(test_atoi_matches_libc);
	RUN_TEST(test_atoi_explicit_values);
	RUN_TEST(test_atoi_int_limits);
	/* calloc / strdup */
	RUN_TEST(test_calloc_zeroed);
	RUN_TEST(test_calloc_large_zeroed);
	RUN_TEST(test_calloc_writable);
	RUN_TEST(test_calloc_zero_size_is_freeable);
	RUN_TEST(test_calloc_overflow_returns_null);
	RUN_TEST(test_strdup_basic);
	RUN_TEST(test_strdup_empty);
	RUN_TEST(test_strdup_is_independent_copy);
	RUN_TEST(test_strdup_long);
}
// The actual entry point the linker is looking for
int main(void)
{
    UNITY_BEGIN();

    run_libc_tests(); // Calls all your tests

    return UNITY_END(); // Prints summary and returns exit code (0 if all passed)
}
