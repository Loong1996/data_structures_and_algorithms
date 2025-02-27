#include <iostream>

#include "avl_tree.h"

int main() {
    AVLTree<int, int> tree;
    tree.Insert(1, 1);
    tree.Insert(2, 2);
    tree.Insert(3, 3);

    return 0;
}