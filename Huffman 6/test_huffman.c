#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

static void _create_file(char const* filename, unsigned char const* contents) {
	FILE* fp = fopen(filename, "w");
	for(int i = 0; contents[i] != '\0'; i++) {
		fputc(contents[i], fp);
	}
	fclose(fp);
}

static void _print_file(char const* filename) {
	FILE* fp = fopen(filename, "r");
	for(unsigned char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
		fputc(ch, stdout);
	}
	fclose(fp);
}

static int _cmp_tree(void const* tree_node, void const* head) {
	Node const* head_node = head;
	TreeNode const* tree_node1 = head_node -> a_value;
	int node_int = tree_node1 -> frequency;
	
	TreeNode const* tree_node2 = tree_node;
	int tree_int = tree_node2 -> frequency;
	return node_int - tree_int;
}

static int _test_pq_enqueue_tree() {
	mu_start();
	Node* head = NULL;
	TreeNode* tree_node = malloc(sizeof(*tree_node));
	*tree_node = (TreeNode) { .character = 'a', .frequency = 2, .left = NULL, .right = NULL };
	pq_enqueue(&head, tree_node, NULL);
	mu_check(head != NULL);

	TreeNode const* head1 = head -> a_value;	
	mu_check(head1 -> frequency == 2);

	TreeNode* tree_node2 = malloc(sizeof(*tree_node));
	*tree_node2 = (TreeNode) { .character = 'b', .frequency = 1, .left = NULL, .right = NULL };
	pq_enqueue(&head, tree_node2, _cmp_tree);

	TreeNode const* head2 = head -> next -> a_value;
	mu_check(head2 -> frequency == 1);
	
	destroy_list(&head, free);

	mu_end();
}

static int _test_abc() {
	mu_start();
	
	char const* error = NULL;
	char const* test = "test_abc.txt";
	unsigned char const contents[4] = {'a', 'b', 'c'};
	char const* path = test;
	Frequencies freqs = { 0 };
	_create_file(path, contents);
	_print_file(path);
	bool did_succeed = calc_frequencies(freqs, path, &error);
	mu_check(did_succeed);
	Node* head = make_huffman_pq(freqs);
	destroy_list(&head, free);
	mu_check(head == NULL);

	mu_end();
}

static int _test_aac() {
	mu_start();
	
	char const* error = NULL;
	char const* test = "test_acc.txt";
	unsigned char const contents[4] = {'a', 'a', 'c'};
	char const* path = test;
	Frequencies freqs = { 0 };
	_create_file(path, contents);
	_print_file(path);
	bool did_succeed = calc_frequencies(freqs, path, &error);
	mu_check(did_succeed);
	Node* head = make_huffman_pq(freqs);
	destroy_list(&head, free);
	mu_check(head == NULL);

	mu_end();
}

static int _test_acc() {
	mu_start();
	
	char const* error = NULL;
	char const* test = "test_acc.txt";
	unsigned char const contents[4] = {'a', 'c', 'c'};
	char const* path = test;
	Frequencies freqs = { 0 };
	_create_file(path, contents);
	_print_file(path);
	bool did_succeed = calc_frequencies(freqs, path, &error);
	mu_check(did_succeed);
	Node* head = make_huffman_pq(freqs);
	destroy_list(&head, free);
	mu_check(head == NULL);

	mu_end();
}

static int _test_make_huffman_tree_empty() {
	mu_start();

	Node* head = NULL;
	TreeNode* tree = make_huffman_tree(head);
	mu_check(tree == NULL);

	mu_end();
}

static int _test_make_huffman_tree_acc() {
	mu_start();
	char const* error = NULL;
	char const* test = "test_acc.txt";
	unsigned char const contents[4] = {'a', 'c', 'c'};
	char const* path = test;
	Frequencies freqs = { 0 };
	_create_file(path, contents);
	_print_file(path);
	bool did_succeed = calc_frequencies(freqs, path, &error);
	mu_check(did_succeed);
	Node* head = make_huffman_pq(freqs);
	
	TreeNode* root = make_huffman_tree(head);
	mu_check(root != NULL);
	mu_check(root -> frequency == 3);
	mu_check(root -> left -> character == 'a');
	mu_check(root -> right -> character == 'c');

	destroy_huffman_tree(&root);
	mu_end();
}

static int _test_make_huffman_tree_hello() {
	mu_start();
	char const* error = NULL;
	char const* test = "test_hello_world.txt";
	unsigned char const contents[25] = {'h', 'u', 'f', 'f', 'm', 'a', 'n', ' ', 'f', 'l', 'u', 'f', 'f', 's', ' ', 'm', 'a', 'n', 'y', ' ', 'm', 'u', 'm', 's'};
	char const* path = test;
	Frequencies freqs = { 0 };
	_create_file(path, contents);
	_print_file(path);
	bool did_succeed = calc_frequencies(freqs, path, &error);
	mu_check(did_succeed);
	Node* head = make_huffman_pq(freqs);

	TreeNode* root = make_huffman_tree(head);
	mu_check(root != NULL);
	mu_check(root -> frequency == 24);
	mu_check(root -> left -> frequency == 10);
	mu_check(root -> right -> frequency == 14);
	mu_check(root -> left -> left -> character == 'f');
	mu_check(root -> left -> right -> frequency == 5);
	mu_check(root -> right -> left -> frequency == 6);
	mu_check(root -> right -> right -> frequency == 8);
	mu_check(root -> left -> right -> left -> frequency == 2);
	mu_check(root -> left -> right -> right -> character == ' ');
	mu_check(root -> left -> right -> left -> left -> character == 'h');
	mu_check(root -> left -> right -> left -> right -> character == 'l');
	mu_check(root -> right -> left -> left -> character == 'u');
	mu_check(root -> right -> left -> right -> frequency == 3);
	mu_check(root -> right -> left -> right -> left -> character == 'y');
	mu_check(root -> right -> left -> right -> right -> character == 'a');
	mu_check(root -> right -> right -> left -> character == 'm');
	mu_check(root -> right -> right -> right -> frequency == 4);
	mu_check(root -> right -> right -> right -> left -> character == 'n');
	mu_check(root -> right -> right -> right -> right -> character == 's');
	
	BitWriter writer = open_bit_writer("huffman_fluffs.bits");
	write_coding_table(root, &writer);

	destroy_huffman_tree(&root);
	mu_check(root == NULL);
	
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_pq_enqueue_tree);
	mu_run(_test_abc);
	mu_run(_test_aac);
	mu_run(_test_acc);
	mu_run(_test_make_huffman_tree_empty);
	mu_run(_test_make_huffman_tree_acc);
	mu_run(_test_make_huffman_tree_hello);


	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

