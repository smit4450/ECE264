#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include <stdlib.h>
#include "frequencies.h"
#include "priority_queue.h"
#include "bit_writer.h"

typedef struct _TreeNode { 
	unsigned char character;
	size_t frequency;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;


Node* make_huffman_pq(Frequencies freqs);
TreeNode* make_huffman_tree(Node* head);
void destroy_huffman_tree(TreeNode** a_root);
void write_coding_table(TreeNode* root, BitWriter* a_writer);

#endif

#define HUFFMAN_H_V2
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

