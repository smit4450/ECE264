#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

void write_coding_table(TreeNode* root, BitWriter* a_writer) {
	if(root != NULL) {
		write_coding_table(root -> left, a_writer);
		if(root -> character == '\0') {
			write_bits(a_writer, 0, 1);
		}
		else {
			write_bits(a_writer, 0xff, 1);
			write_bits(a_writer, root -> character, 8);
		}
		write_coding_table(root -> right, a_writer);
	}
}

static int _cmp_tree(void const* tree_node, void const* head) {
	Node const* head_node = head;
	TreeNode const* tree_node1 = head_node -> a_value;
	int tree_int1 = tree_node1 -> frequency;
	
	TreeNode const* tree_node2 = tree_node;
	int tree_int2 = tree_node2 -> frequency;
	if(tree_int2 - tree_int1 != 0) {
		return tree_int2  - tree_int1;
	}
	else {
		if((tree_node1 -> character == '\0') || (tree_node2 -> character == '\0')) {
			return tree_node1 -> character - tree_node2 -> character;
		}
		else {
			return tree_node2 -> character - tree_node1 -> character;
		}
	}
}

Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;
	for(unsigned char ch = 0; ch < 255; ch++) {
		if(freqs[ch] != 0) {
			TreeNode* tree_node = malloc(sizeof(*tree_node));
			*tree_node = (TreeNode) { .character = ch, .frequency = freqs[ch], .left = NULL, .right = NULL };
			pq_enqueue(&head, tree_node, _cmp_tree);
		}
	}
	return head;
}

TreeNode* make_huffman_tree(Node* head) {
	TreeNode* root = NULL;
	if(head == NULL) {
		return root;
	}
	while(head -> next != NULL) {	
		TreeNode* node1 = head -> a_value;
		TreeNode* node2 = head -> next -> a_value;
		int frequency = node1 -> frequency + node2 -> frequency;
		TreeNode* tree_node = malloc(sizeof(*tree_node));
		*tree_node = (TreeNode) { .character = '\0', .frequency = frequency, .left = node1, .right = node2 };
		for(int i = 0; i < 2; i++) {
			Node* removed_node = pq_dequeue(&head);
			destroy_list(&removed_node, NULL);
		}
		pq_enqueue(&head, tree_node, _cmp_tree);
	}
	root = head -> a_value;
	destroy_list(&head, NULL);
	return root;
}


void destroy_huffman_tree(TreeNode** a_root) {
	//TreeNode* current_node = *a_root;
	while(*a_root != NULL) {
		destroy_huffman_tree(&((*a_root) -> left));
		destroy_huffman_tree(&((*a_root) -> right));
		free(*a_root);
		*a_root = NULL;
	}
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

