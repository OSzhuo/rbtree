#ifndef _RB_TREE_H_
#define _RB_TREE_H_

/*
 * Left-Leaning Red-Black Tree (bottom-up 2-3 tree)
 */

/*
 * insert: skip insert the node that has the same key
 *
 */

#define RB_RED		0
#define RB_BLACK	1

struct rb_node {
	struct		rb_node *r;	/* right */
	struct		rb_node *l;	/* left */
	int		color;
	const void	*data;
};

struct rb_root {
	struct rb_node *root;
};

#define RB_ROOT (struct rb_root) { NULL, }


#endif	/* _RB_TREE_H_ */
