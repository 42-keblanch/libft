#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "libft.h"
#include "test_utils.h"

/* ========================================================================== */
/*  Helpers                                                                   */
/*  Nodes are built by hand so these tests don't depend on ft_lstnew or       */
/*  ft_lstadd_back being correct.                                             */
/* ========================================================================== */

static int		g_del_calls;
static void		*g_last_deleted;
static void		*g_deleted[16];

// Required by Unity (even if empty)
void setUp(void) {
    // Clean state before each test
}

void tearDown(void) {
    // Cleanup after each test
}

static void	reset_counters(void)
{
	g_del_calls = 0;
	g_last_deleted = NULL;
	memset(g_deleted, 0, sizeof(g_deleted));
}

static void	counting_del(void *content)
{
	if (g_del_calls < 16)
		g_deleted[g_del_calls] = content;
	g_del_calls++;
	g_last_deleted = content;
}

static void	counting_free_del(void *content)
{
	counting_del(content);
	free(content);
}

static t_list	*mk_node(void *content, t_list *next)
{
	t_list	*node = malloc(sizeof(t_list));

	TEST_ASSERT_NOT_NULL(node);
	node->content = content;
	node->next = next;
	return (node);
}

/* Builds a list whose contents point into vals[] (not owned). */
static t_list	*mk_int_list(int *vals, size_t n)
{
	t_list	*head = NULL;

	for (size_t i = n; i > 0; i--)
		head = mk_node(&vals[i - 1], head);
	return (head);
}

/* Frees the nodes only, never the contents. */
static void	free_nodes(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

static void	incr(void *content)
{
	(*(int *)content)++;
}

static void	*double_int(void *content)
{
	int	*n = malloc(sizeof(int));

	TEST_ASSERT_NOT_NULL(n);
	*n = *(int *)content * 2;
	return (n);
}

static void	*dup_string(void *content)
{
	return (strdup((char *)content));
}

/* ========================================================================== */
/*  ft_lstnew                                                                 */
/* ========================================================================== */

static void	test_lstnew_stores_content(void)
{
	int		value = 42;
	t_list	*node = ft_lstnew(&value);

	TEST_ASSERT_NOT_NULL(node);
	TEST_ASSERT_EQUAL_PTR(&value, node->content);
	TEST_ASSERT_NULL(node->next);
	free(node);
}

static void	test_lstnew_null_content(void)
{
	t_list	*node = ft_lstnew(NULL);

	TEST_ASSERT_NOT_NULL(node);
	TEST_ASSERT_NULL(node->content);
	TEST_ASSERT_NULL(node->next);
	free(node);
}

static void	test_lstnew_string_content(void)
{
	char	*str = "hello";
	t_list	*node = ft_lstnew(str);

	TEST_ASSERT_NOT_NULL(node);
	TEST_ASSERT_EQUAL_STRING("hello", (char *)node->content);
	free(node);
}

static void	test_lstnew_distinct_nodes(void)
{
	t_list	*a = ft_lstnew(NULL);
	t_list	*b = ft_lstnew(NULL);

	TEST_ASSERT_NOT_NULL(a);
	TEST_ASSERT_NOT_NULL(b);
	TEST_ASSERT_TRUE(a != b);
	free(a);
	free(b);
}

/* ========================================================================== */
/*  ft_lstadd_front                                                           */
/* ========================================================================== */

static void	test_lstadd_front_to_empty_list(void)
{
	t_list	*lst = NULL;
	t_list	*node = mk_node(NULL, NULL);

	ft_lstadd_front(&lst, node);
	TEST_ASSERT_EQUAL_PTR(node, lst);
	TEST_ASSERT_NULL(lst->next);
	free(node);
}

static void	test_lstadd_front_becomes_head(void)
{
	int		vals[] = {2, 3};
	t_list	*lst = mk_int_list(vals, 2);
	t_list	*old_head = lst;
	int		one = 1;
	t_list	*node = mk_node(&one, NULL);

	ft_lstadd_front(&lst, node);
	TEST_ASSERT_EQUAL_PTR(node, lst);
	TEST_ASSERT_EQUAL_PTR(old_head, lst->next);
	TEST_ASSERT_EQUAL_INT(2, *(int *)lst->next->content);
	free_nodes(lst);
}

static void	test_lstadd_front_multiple_reverses_order(void)
{
	int		vals[] = {1, 2, 3};
	t_list	*lst = NULL;

	for (int i = 0; i < 3; i++)
		ft_lstadd_front(&lst, mk_node(&vals[i], NULL));
	TEST_ASSERT_EQUAL_INT(3, *(int *)lst->content);
	TEST_ASSERT_EQUAL_INT(2, *(int *)lst->next->content);
	TEST_ASSERT_EQUAL_INT(1, *(int *)lst->next->next->content);
	TEST_ASSERT_NULL(lst->next->next->next);
	free_nodes(lst);
}

/* ========================================================================== */
/*  ft_lstsize / ft_lstlast                                                   */
/* ========================================================================== */

static void	test_lstsize_empty(void)
{
	TEST_ASSERT_EQUAL_INT(0, ft_lstsize(NULL));
}

static void	test_lstsize_one(void)
{
	t_list	*lst = mk_node(NULL, NULL);

	TEST_ASSERT_EQUAL_INT(1, ft_lstsize(lst));
	free_nodes(lst);
}

static void	test_lstsize_several(void)
{
	int		vals[5] = {0};
	t_list	*lst = mk_int_list(vals, 5);

	TEST_ASSERT_EQUAL_INT(5, ft_lstsize(lst));
	free_nodes(lst);
}

static void	test_lstsize_large(void)
{
	t_list	*lst = NULL;

	for (int i = 0; i < 10000; i++)
		lst = mk_node(NULL, lst);
	TEST_ASSERT_EQUAL_INT(10000, ft_lstsize(lst));
	free_nodes(lst);
}

static void	test_lstsize_does_not_modify_list(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*lst = mk_int_list(vals, 3);
	t_list	*head = lst;

	ft_lstsize(lst);
	TEST_ASSERT_EQUAL_PTR(head, lst);
	TEST_ASSERT_EQUAL_INT(3, ft_lstsize(lst));
	free_nodes(lst);
}

static void	test_lstlast_empty(void)
{
	TEST_ASSERT_NULL(ft_lstlast(NULL));
}

static void	test_lstlast_single(void)
{
	t_list	*lst = mk_node(NULL, NULL);

	TEST_ASSERT_EQUAL_PTR(lst, ft_lstlast(lst));
	free_nodes(lst);
}

static void	test_lstlast_several(void)
{
	int		vals[] = {1, 2, 3, 4};
	t_list	*lst = mk_int_list(vals, 4);
	t_list	*last = lst->next->next->next;

	TEST_ASSERT_EQUAL_PTR(last, ft_lstlast(lst));
	TEST_ASSERT_EQUAL_INT(4, *(int *)ft_lstlast(lst)->content);
	free_nodes(lst);
}

/* ========================================================================== */
/*  ft_lstadd_back                                                            */
/* ========================================================================== */

static void	test_lstadd_back_to_empty_list(void)
{
	t_list	*lst = NULL;
	t_list	*node = mk_node(NULL, NULL);

	ft_lstadd_back(&lst, node);
	TEST_ASSERT_EQUAL_PTR(node, lst);
	free(node);
}

static void	test_lstadd_back_appends(void)
{
	int		vals[] = {1, 2};
	t_list	*lst = mk_int_list(vals, 2);
	int		three = 3;
	t_list	*node = mk_node(&three, NULL);

	ft_lstadd_back(&lst, node);
	TEST_ASSERT_EQUAL_INT(3, ft_lstsize(lst));
	TEST_ASSERT_EQUAL_PTR(node, ft_lstlast(lst));
	TEST_ASSERT_EQUAL_INT(1, *(int *)lst->content);
	free_nodes(lst);
}

static void	test_lstadd_back_keeps_head(void)
{
	int		vals[] = {1};
	t_list	*lst = mk_int_list(vals, 1);
	t_list	*head = lst;

	ft_lstadd_back(&lst, mk_node(NULL, NULL));
	TEST_ASSERT_EQUAL_PTR(head, lst);
	free_nodes(lst);
}

static void	test_lstadd_back_preserves_order(void)
{
	int		vals[] = {1, 2, 3};
	t_list	*lst = NULL;

	for (int i = 0; i < 3; i++)
		ft_lstadd_back(&lst, mk_node(&vals[i], NULL));
	TEST_ASSERT_EQUAL_INT(1, *(int *)lst->content);
	TEST_ASSERT_EQUAL_INT(2, *(int *)lst->next->content);
	TEST_ASSERT_EQUAL_INT(3, *(int *)lst->next->next->content);
	TEST_ASSERT_NULL(lst->next->next->next);
	free_nodes(lst);
}

/* ========================================================================== */
/*  ft_lstdelone / ft_lstclear                                                */
/* ========================================================================== */

static void	test_lstdelone_calls_del_on_content(void)
{
	int		*content = malloc(sizeof(int));
	t_list	*node = mk_node(content, NULL);

	reset_counters();
	ft_lstdelone(node, counting_free_del);
	TEST_ASSERT_EQUAL_INT(1, g_del_calls);
	TEST_ASSERT_EQUAL_PTR(content, g_last_deleted);
}

static void	test_lstdelone_with_null_content(void)
{
	t_list	*node = mk_node(NULL, NULL);

	reset_counters();
	ft_lstdelone(node, counting_del);
	TEST_ASSERT_EQUAL_INT(1, g_del_calls);
	TEST_ASSERT_NULL(g_last_deleted);
}

static void	test_lstdelone_does_not_delete_next(void)
{
	int		a = 1;
	int		b = 2;
	t_list	*second = mk_node(&b, NULL);
	t_list	*first = mk_node(&a, second);

	reset_counters();
	ft_lstdelone(first, counting_del);
	TEST_ASSERT_EQUAL_INT(1, g_del_calls);
	TEST_ASSERT_EQUAL_PTR(&a, g_last_deleted);
	TEST_ASSERT_EQUAL_INT(2, *(int *)second->content);
	free(second);
}

static void	test_lstclear_deletes_every_node(void)
{
	int		*c0 = malloc(sizeof(int));
	int		*c1 = malloc(sizeof(int));
	int		*c2 = malloc(sizeof(int));
	t_list	*lst = mk_node(c0, mk_node(c1, mk_node(c2, NULL)));

	reset_counters();
	ft_lstclear(&lst, counting_free_del);
	TEST_ASSERT_EQUAL_INT(3, g_del_calls);
	TEST_ASSERT_NULL(lst);
}

static void	test_lstclear_deletes_in_order(void)
{
	int		a = 1;
	int		b = 2;
	int		c = 3;
	t_list	*lst = mk_node(&a, mk_node(&b, mk_node(&c, NULL)));

	reset_counters();
	ft_lstclear(&lst, counting_del);
	TEST_ASSERT_EQUAL_INT(3, g_del_calls);
	TEST_ASSERT_EQUAL_PTR(&a, g_deleted[0]);
	TEST_ASSERT_EQUAL_PTR(&b, g_deleted[1]);
	TEST_ASSERT_EQUAL_PTR(&c, g_deleted[2]);
}

static void	test_lstclear_single_node(void)
{
	t_list	*lst = mk_node(NULL, NULL);

	reset_counters();
	ft_lstclear(&lst, counting_del);
	TEST_ASSERT_EQUAL_INT(1, g_del_calls);
	TEST_ASSERT_NULL(lst);
}

static void	test_lstclear_empty_list(void)
{
	t_list	*lst = NULL;

	reset_counters();
	ft_lstclear(&lst, counting_del);
	TEST_ASSERT_EQUAL_INT(0, g_del_calls);
	TEST_ASSERT_NULL(lst);
}

static void	test_lstclear_large_list(void)
{
	t_list	*lst = NULL;

	for (int i = 0; i < 10000; i++)
		lst = mk_node(NULL, lst);
	reset_counters();
	ft_lstclear(&lst, counting_del);
	TEST_ASSERT_EQUAL_INT(10000, g_del_calls);
	TEST_ASSERT_NULL(lst);
}

/* ========================================================================== */
/*  ft_lstiter                                                                */
/* ========================================================================== */

static void	test_lstiter_applies_to_every_element(void)
{
	int		vals[] = {1, 2, 3, 4};
	t_list	*lst = mk_int_list(vals, 4);

	ft_lstiter(lst, incr);
	TEST_ASSERT_EQUAL_INT(2, vals[0]);
	TEST_ASSERT_EQUAL_INT(3, vals[1]);
	TEST_ASSERT_EQUAL_INT(4, vals[2]);
	TEST_ASSERT_EQUAL_INT(5, vals[3]);
	free_nodes(lst);
}

static void	test_lstiter_empty_list(void)
{
	ft_lstiter(NULL, incr);
	TEST_PASS();
}

static void	test_lstiter_single_element(void)
{
	int		v = 10;
	t_list	*lst = mk_node(&v, NULL);

	ft_lstiter(lst, incr);
	TEST_ASSERT_EQUAL_INT(11, v);
	free_nodes(lst);
}

static void	test_lstiter_each_element_once(void)
{
	int		vals[] = {0, 0, 0};
	t_list	*lst = mk_int_list(vals, 3);

	ft_lstiter(lst, incr);
	for (int i = 0; i < 3; i++)
		TEST_ASSERT_EQUAL_INT(1, vals[i]);
	free_nodes(lst);
}

static void	test_lstiter_does_not_modify_structure(void)
{
	int		vals[] = {1, 2, 3};
	t_list	*lst = mk_int_list(vals, 3);
	t_list	*second = lst->next;

	ft_lstiter(lst, incr);
	TEST_ASSERT_EQUAL_PTR(second, lst->next);
	TEST_ASSERT_EQUAL_INT(3, ft_lstsize(lst));
	free_nodes(lst);
}

/* ========================================================================== */
/*  ft_lstmap                                                                 */
/* ========================================================================== */

static void	test_lstmap_transforms_contents(void)
{
	int		vals[] = {1, 2, 3};
	t_list	*lst = mk_int_list(vals, 3);
	t_list	*res;

	reset_counters();
	res = ft_lstmap(lst, double_int, counting_free_del);
	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_EQUAL_INT(3, ft_lstsize(res));
	TEST_ASSERT_EQUAL_INT(2, *(int *)res->content);
	TEST_ASSERT_EQUAL_INT(4, *(int *)res->next->content);
	TEST_ASSERT_EQUAL_INT(6, *(int *)res->next->next->content);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_does_not_modify_original(void)
{
	int		vals[] = {1, 2, 3};
	t_list	*lst = mk_int_list(vals, 3);
	t_list	*res = ft_lstmap(lst, double_int, counting_free_del);

	TEST_ASSERT_EQUAL_INT(1, vals[0]);
	TEST_ASSERT_EQUAL_INT(2, vals[1]);
	TEST_ASSERT_EQUAL_INT(3, vals[2]);
	TEST_ASSERT_EQUAL_INT(3, ft_lstsize(lst));
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_creates_new_nodes(void)
{
	int		vals[] = {1, 2};
	t_list	*lst = mk_int_list(vals, 2);
	t_list	*res = ft_lstmap(lst, double_int, counting_free_del);

	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_TRUE(res != lst);
	TEST_ASSERT_TRUE(res->next != lst->next);
	TEST_ASSERT_TRUE(res->content != lst->content);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_preserves_order(void)
{
	int		vals[] = {5, 4, 3, 2, 1};
	t_list	*lst = mk_int_list(vals, 5);
	t_list	*res = ft_lstmap(lst, double_int, counting_free_del);
	t_list	*cur = res;

	for (int i = 0; i < 5; i++)
	{
		TEST_ASSERT_NOT_NULL(cur);
		TEST_ASSERT_EQUAL_INT(vals[i] * 2, *(int *)cur->content);
		cur = cur->next;
	}
	TEST_ASSERT_NULL(cur);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_single_element(void)
{
	int		v = 21;
	t_list	*lst = mk_node(&v, NULL);
	t_list	*res = ft_lstmap(lst, double_int, counting_free_del);

	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_EQUAL_INT(42, *(int *)res->content);
	TEST_ASSERT_NULL(res->next);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_empty_list(void)
{
	TEST_ASSERT_NULL(ft_lstmap(NULL, double_int, counting_free_del));
}

static void	test_lstmap_strings(void)
{
	char	*strs[] = {"alpha", "beta", "gamma"};
	t_list	*lst = mk_node(strs[0], mk_node(strs[1], mk_node(strs[2], NULL)));
	t_list	*res = ft_lstmap(lst, dup_string, counting_free_del);

	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_EQUAL_STRING("alpha", (char *)res->content);
	TEST_ASSERT_EQUAL_STRING("beta", (char *)res->next->content);
	TEST_ASSERT_EQUAL_STRING("gamma", (char *)res->next->next->content);
	TEST_ASSERT_TRUE(res->content != (void *)strs[0]);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

static void	test_lstmap_large(void)
{
	static int	vals[2000];
	t_list		*lst;
	t_list		*res;

	for (int i = 0; i < 2000; i++)
		vals[i] = i;
	lst = mk_int_list(vals, 2000);
	res = ft_lstmap(lst, double_int, counting_free_del);
	TEST_ASSERT_NOT_NULL(res);
	TEST_ASSERT_EQUAL_INT(2000, ft_lstsize(res));
	TEST_ASSERT_EQUAL_INT(3998, *(int *)ft_lstlast(res)->content);
	ft_lstclear(&res, counting_free_del);
	free_nodes(lst);
}

/* ========================================================================== */
/*  Integration                                                               */
/* ========================================================================== */

static void	test_integration_build_iterate_clear(void)
{
	int		*vals[5];
	t_list	*lst = NULL;

	for (int i = 0; i < 5; i++)
	{
		vals[i] = malloc(sizeof(int));
		*vals[i] = i;
		ft_lstadd_back(&lst, ft_lstnew(vals[i]));
	}
	TEST_ASSERT_EQUAL_INT(5, ft_lstsize(lst));
	ft_lstiter(lst, incr);
	for (int i = 0; i < 5; i++)
		TEST_ASSERT_EQUAL_INT(i + 1, *vals[i]);
	TEST_ASSERT_EQUAL_PTR(vals[4], ft_lstlast(lst)->content);
	reset_counters();
	ft_lstclear(&lst, counting_free_del);
	TEST_ASSERT_EQUAL_INT(5, g_del_calls);
	TEST_ASSERT_NULL(lst);
}

static void	test_integration_front_and_back(void)
{
	int		vals[] = {1, 2, 3, 4};
	t_list	*lst = NULL;

	ft_lstadd_back(&lst, ft_lstnew(&vals[1]));
	ft_lstadd_back(&lst, ft_lstnew(&vals[2]));
	ft_lstadd_front(&lst, ft_lstnew(&vals[0]));
	ft_lstadd_back(&lst, ft_lstnew(&vals[3]));
	TEST_ASSERT_EQUAL_INT(4, ft_lstsize(lst));
	for (int i = 0; i < 4; i++)
	{
		TEST_ASSERT_EQUAL_INT(i + 1, *(int *)lst->content);
		t_list *next = lst->next;
		free(lst);
		lst = next;
	}
}

/* ========================================================================== */
/*  Runner                                                                    */
/* ========================================================================== */

void	run_list_tests(void)
{
	Unity.TestFile = __FILE__;
	/* lstnew */
	RUN_TEST(test_lstnew_stores_content);
	RUN_TEST(test_lstnew_null_content);
	RUN_TEST(test_lstnew_string_content);
	RUN_TEST(test_lstnew_distinct_nodes);
	/* lstadd_front */
	RUN_TEST(test_lstadd_front_to_empty_list);
	RUN_TEST(test_lstadd_front_becomes_head);
	RUN_TEST(test_lstadd_front_multiple_reverses_order);
	/* lstsize / lstlast */
	RUN_TEST(test_lstsize_empty);
	RUN_TEST(test_lstsize_one);
	RUN_TEST(test_lstsize_several);
	RUN_TEST(test_lstsize_large);
	RUN_TEST(test_lstsize_does_not_modify_list);
	RUN_TEST(test_lstlast_empty);
	RUN_TEST(test_lstlast_single);
	RUN_TEST(test_lstlast_several);
	/* lstadd_back */
	RUN_TEST(test_lstadd_back_to_empty_list);
	RUN_TEST(test_lstadd_back_appends);
	RUN_TEST(test_lstadd_back_keeps_head);
	RUN_TEST(test_lstadd_back_preserves_order);
	/* lstdelone / lstclear */
	RUN_TEST(test_lstdelone_calls_del_on_content);
	RUN_TEST(test_lstdelone_with_null_content);
	RUN_TEST(test_lstdelone_does_not_delete_next);
	RUN_TEST(test_lstclear_deletes_every_node);
	RUN_TEST(test_lstclear_deletes_in_order);
	RUN_TEST(test_lstclear_single_node);
	RUN_TEST(test_lstclear_empty_list);
	RUN_TEST(test_lstclear_large_list);
	/* lstiter */
	RUN_TEST(test_lstiter_applies_to_every_element);
	RUN_TEST(test_lstiter_empty_list);
	RUN_TEST(test_lstiter_single_element);
	RUN_TEST(test_lstiter_each_element_once);
	RUN_TEST(test_lstiter_does_not_modify_structure);
	/* lstmap */
	RUN_TEST(test_lstmap_transforms_contents);
	RUN_TEST(test_lstmap_does_not_modify_original);
	RUN_TEST(test_lstmap_creates_new_nodes);
	RUN_TEST(test_lstmap_preserves_order);
	RUN_TEST(test_lstmap_single_element);
	RUN_TEST(test_lstmap_empty_list);
	RUN_TEST(test_lstmap_strings);
	RUN_TEST(test_lstmap_large);
	/* integration */
	RUN_TEST(test_integration_build_iterate_clear);
	RUN_TEST(test_integration_front_and_back);
}
// The actual entry point the linker is looking for
int main(void)
{
    UNITY_BEGIN();

    run_list_tests(); // Calls all your tests

    return UNITY_END(); // Prints summary and returns exit code (0 if all passed)
}
