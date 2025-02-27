#ifndef _AVL_TREE_H
#define _AVL_TREE_H


template <typename TKey_, typename TData_>
class AVLTree {
private:
    struct Node {
        TKey_  key;    // Key
        TData_ data;   // 数据
        Node*  left;   // 左子树
        Node*  right;  // 右子树
        int    height; // 树高度
    };

    Node* head_;

public:
    AVLTree() : head_(nullptr) {}

    // 查找
    const Node* Find(TKey_ key) {
        if (nullptr == head_) {
            return nullptr;
        }

        if (key == head_->key) {
            return head_;
        }

        if (key < head_->key) {
            return Find(head_->left, key);
        }

        return Find(head_->right, key);
    }

    // 插入
    const Node* Insert(TKey_ key, TData_ data) {
        return InsertUtil(head_, key, data);
    }

    Node* InsertUtil(Node* head, TKey_ key, TData_ data) {
        if (head == nullptr) {
            return new Node{key, data, nullptr, nullptr, 1};
        }

        if (key == head->key) {
            // Key相等，不插入
            head->data = data;
            return head;
        } else if (key < head->key) {
            head->left = InsertUtil(head->left, key, data);
        } else {
            head->right = InsertUtil(head->right, key, data);
        }

        // 更新树的高度
        head->height = std::max(GetHeight(head->left), GetHeight(head->right)) + 1;
        return head;
    }

    // 删除
    const Node* Delete(TKey_ key) {
        // TODO
    }

private:
    // 获取树高度
    int GetHeight(Node* head) {
        return (nullptr != head) ? head->height : 0;
    }

    // 左旋
    Node* LeftRotate(Node* head) {
        Node* new_head = head->right;
        head->right = new_head->left;
        new_head->left = head;
        head->height = std::max(GetHeight(head->left), GetHeight(head->right)) + 1;
        new_head->height = std::max(GetHeight(new_head->left), GetHeight(new_head->right)) + 1;
        return new_head;
    }

    // 右旋
    Node* RightRotate(Node* head) {
        Node* new_head = head->left;
        head->left = new_head->right;
        new_head->right = head;
        head->height = std::max(GetHeight(head->left), GetHeight(head->right)) + 1;
        new_head->height = std::max(GetHeight(new_head->left), GetHeight(new_head->right)) + 1;
        return new_head;
    }

    // 左右旋
    Node* LeftRightRotate(Node* head) {
        head->left = LeftRotate(head->left);
        return RightRotate(head);
    }

    // 右左旋
    Node* RightLeftRotate(Node* head) {
        head->right = RightRotate(head->right);
        return LeftRotate(head);
    }

    Node* Rotate(Node* head) {
        if (nullptr == head) {
            return nullptr;
        }

        int height_diff = GetHeight(head->left) - GetHeight(head->right);
        if (height_diff > 1) {
            Node* child = head->left;
            if (GetHeight(child->left) > GetHeight(child->right)) {
                // LL情况
                head = RightRotate(head);
            } else {
                // LR情况
                head = LeftRightRotate(head);
            }
        } else if (height_diff < -1) {
            Node* child = head->right;
            if (GetHeight(child->right) > GetHeight(child->left)) {
                // RR情况
                head = LeftRotate(head);
            } else {
                // RL情况
                head = RightLeftRotate(head);
            }
        }

        return head;
    }
};


#endif // _AVL_TREE_H