#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

//struct rb_root *rb_init(void)
//{
//	return NULL;
//}
static struct rb_node *__insert(struct rb_node *this, int (*cmp_func)(const void *in, const void *data), const void *data);

struct rb_node *__new_node(const void *data)
{
	struct rb_node *n = malloc(sizeof(struct rb_node));

	if (!n) {
		perror("malloc(struct rb_node)");
		exit(1);
	}

	n->r = n->l = NULL;
	n->color = RB_RED;
	n->data = data;

	return n;
}

/*
 * NULL node is black
 */
int __is_red(struct rb_node *n)
{
	if (n && n->color == RB_RED)
		return 1;
	return 0;
}

struct rb_node *__rotate_left(struct rb_node *h)
{
	struct rb_node *p = h->r;

	h->r = p->l;
	p->l = h;
	p->color = h->color;
	h->color = RB_RED;

	return p;
}

struct rb_node *__rotate_right(struct rb_node *h)
{
	struct rb_node *p = h->l;

	h->l = p->r;
	p->r = h;
	p->color = h->color;
	h->color = RB_RED;

	return p;
}

void __filp_color(struct rb_node *h)
{
	h->color = !h->color;
	h->l->color = !h->l->color;
	h->r->color = !h->r->color;
}

/*
 * @cmp_func if return zero, data will be replace new data, do not forget free it if nessary
 *
 */
struct rb_root *rb_insert(struct rb_root *root,
		int (*cmp_func)(const void *in_tree, const void *data), const void *data)
{
	root->root = __insert(root->root, cmp_func, data);
	root->root->color = RB_BLACK;

	/* TODO error */
	//if (error) return NULL;

	return root;
}

/*
 * return the root node of the rbtree after insert
 *
 */
struct rb_node *__insert(struct rb_node *this,// struct rb_node *node,
		int (*cmp_func)(const void *in, const void *data), const void *data)
{
	/* if this is NULL, insert a red node into here */
	if (!this)
		return __new_node(data);

	int r = cmp_func(this->data, data);

	if (0 == r)
		/* update the pointor of data */
		this->data = data;
	else if (r < 0)
		this->l = __insert(this->l, cmp_func, data);
	else
		this->r = __insert(this->r, cmp_func, data);

	/* two steps to fix the new node */
	/* 1. rotate left if get the right-leaning 3-node */
	if (!__is_red(this->l) && __is_red(this->r))
		this = __rotate_left(this);

	/* 2. rotate right if get two red nodes */
	/* do not need to judge if left is exsit */
	if (__is_red(this->l) && __is_red(this->l->l))
		this = __rotate_right(this);

	/* split the 4-node */
	if (__is_red(this->l) && __is_red(this->r))
		__filp_color(this);

	return this;
}

void __inorder(struct rb_node *t, void (*prt)(const void *d), int x, int y, int dep);

#define MAX_H 4

void rb_print(struct rb_root *root, void (*prt)(const void *d))
{
	__inorder(root->root, prt, 0, 0, 1);
	printf("\n");
}

void __inorder(struct rb_node *t, void (*prt)(const void *d), int x, int y, int dep)
{
	if (!t)
		return;

	__inorder(t->l, prt, x - ((0x01 << (MAX_H-dep)) - (0x01 << (MAX_H - dep - 1))), y - 1, dep+1);

	prt(t->data);
	printf("[%d,%d](%c)", x, y, t->color == RB_RED ? 'R' : 'B');
	__inorder(t->r, prt, x+ ((0x01 << (MAX_H-dep)) - (0x01 << (MAX_H - dep - 1))), y-1, dep+1);
}

int cmp_int(const void *in, const void *d)
{
	return d - in;
}

void prt_f(const void *d)
{
	printf(" %d", (int)d);
}

int main(void)
{
	struct rb_root T = RB_ROOT;

	rb_insert(&T, cmp_int, (void *)5);
	rb_print(&T, prt_f);
	rb_insert(&T, cmp_int, (void *)6);
	rb_print(&T, prt_f);
	rb_insert(&T, cmp_int, (void *)7);
	rb_print(&T, prt_f);
	rb_insert(&T, cmp_int, (void *)15);
	rb_print(&T, prt_f);
	rb_insert(&T, cmp_int, (void *)3);
	rb_print(&T, prt_f);
	rb_insert(&T, cmp_int, (void *)13);
	rb_insert(&T, cmp_int, (void *)14);
	rb_insert(&T, cmp_int, (void *)18);
	rb_insert(&T, cmp_int, (void *)19);
	rb_insert(&T, cmp_int, (void *)10);
	rb_print(&T, prt_f);

	return 0;
}
