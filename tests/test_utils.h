#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <stdio.h>
# include "unity.h"

/* Sign of a number: -1, 0 or 1. Used to compare strcmp-like return values. */
# define SIGN(x) (((x) > 0) - ((x) < 0))

/* Reference implementations (portable, locale independent). */
static inline int	exp_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static inline int	exp_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline int	exp_isalnum(int c)
{
	return (exp_isalpha(c) || exp_isdigit(c));
}

static inline int	exp_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

static inline int	exp_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
** Checks that ft_fn and exp_fn agree (as booleans) on every value in
** [lo, hi]. On failure, reports the offending value.
*/
# define CHECK_BOOL_FN(ft_fn, exp_fn, lo, hi) \
	do { \
		for (int c_ = (lo); c_ <= (hi); c_++) \
		{ \
			if ((ft_fn(c_) != 0) != (exp_fn(c_) != 0)) \
			{ \
				char msg_[64]; \
				snprintf(msg_, sizeof(msg_), #ft_fn " wrong for c = %d", c_); \
				TEST_FAIL_MESSAGE(msg_); \
			} \
		} \
	} while (0)

/* Same idea for functions returning an int that must match exactly. */
# define CHECK_INT_FN(ft_fn, std_fn, lo, hi) \
	do { \
		for (int c_ = (lo); c_ <= (hi); c_++) \
		{ \
			if (ft_fn(c_) != std_fn(c_)) \
			{ \
				char msg_[64]; \
				snprintf(msg_, sizeof(msg_), #ft_fn " wrong for c = %d", c_); \
				TEST_FAIL_MESSAGE(msg_); \
			} \
		} \
	} while (0)

#endif
