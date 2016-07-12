struct Key {
    int value;
};
struct RBTNode {
    Key key;
    int lcount;
    int rcount;
    RBTNode* lchild;
    RBTNode* rchild;
    RBTNode* parent;
    bool color;
};
class RBT {
private:
    const static bool RED = true;
    const static bool BLACK = false;
    RBTNode* m_null;
    RBTNode* m_root;
    void clear() {//
        RBTNode* p = m_root;
        while (p != m_null) {
            if (p->lchild != m_null) {
                p = p->lchild;
            }else if (p->rchild != m_null) {
                p = p->rchild;
            }else {
                RBTNode* temp = p;
                p = p->parent;
                if (temp == p->lchild) {
                    p->lchild = m_null;
                }else {
                    p->rchild = m_null;
                }
                delete temp;
            }
        }
        m_root = m_null;
    }
    void delFixup(RBTNode* delNode) {
        RBTNode* p = delNode;
        while (p != m_root && p->color == BLACK) {
            if (p == p->parent->lchild) {
                RBTNode* sibling = p->parent->rchild;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    p->parent->color = RED;
                    leftRotate(p->parent);
                    sibling = p->parent->rchild;
                }
                if (sibling->lchild->color == BLACK
                    && sibling->rchild->color == BLACK
                    ) {
                        sibling->color = RED;
                        p = p->parent;
                }else {
                    if (sibling->rchild->color == BLACK) {
                        sibling->lchild->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = sibling->parent;
                    }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->rchild->color = BLACK;
                    leftRotate(sibling->parent);
                    p = m_root;
                }
            }else {
                RBTNode* sibling = p->parent->lchild;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    p->parent->color = RED;
                    rightRotate(p->parent);
                    sibling = p->parent->lchild;
                }
                if (sibling->lchild->color == BLACK
                    && sibling->rchild->color == BLACK
                    ) {
                        sibling->color = RED;
                        p = p->parent;
                }else {
                    if (sibling->lchild->color == BLACK) {
                        sibling->rchild->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = sibling->parent;
                    }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->lchild->color = BLACK;



                    rightRotate(sibling->parent);
                    p = m_root;
                }
            }
        }
        p->color = BLACK;
    }
    void insertFixup(RBTNode* insertNode) {
        RBTNode* p = insertNode;
        while (p->parent->color == RED) {
            if (p->parent == p->parent->parent->lchild) {
                RBTNode* parentRight = p->parent->parent->rchild;
                if (parentRight->color == RED) {
                    p->parent->color = BLACK;
                    parentRight->color = BLACK;
                    p->parent->parent->color = RED;
                    p = p->parent->parent;
                }else {
                    if (p == p->parent->rchild) {
                        p = p->parent;
                        leftRotate(p);
                    }
                    p->parent->color = BLACK;
                    p->parent->parent->color = RED;
                    rightRotate(p->parent->parent);
                }
            }else {
                RBTNode* parentLeft = p->parent->parent->lchild;
                if (parentLeft->color == RED) {
                    p->parent->color = BLACK;
                    parentLeft->color = BLACK;
                    p->parent->parent->color = RED;
                    p = p->parent->parent;
                }else {
                    if (p == p->parent->lchild) {
                        p = p->parent;
                        rightRotate(p);
                    }
                    p->parent->color = BLACK;
                    p->parent->parent->color = RED;
                    leftRotate(p->parent->parent);
                }
            }
        }
        m_root->color = BLACK;
    }

    inline int keyCmp(const Key& key1, const Key& key2) {
        //比较两个Key的大小。这里可能有更复杂的比较，如字符串比较等。
        return key1.value - key2.value;
    }

    inline void leftRotate(RBTNode* node) {
        //把一个节点向左下方移一格，并让他原来的右子节点代替它的位置。
        RBTNode* right = node->rchild;
        node->rchild = right->lchild;
        node->rcount = right->lcount;
        node->rchild->parent = node;
        right->parent = node->parent;
        if (right->parent == m_null) {
            m_root = right;
        }else if (node == node->parent->lchild) {
            node->parent->lchild = right;
        }else {
            node->parent->rchild = right;
        }
        right->lchild = node;
        right->lcount += node->lcount + 1;
        node->parent = right;
    }

    inline void rightRotate(RBTNode* node) {
        //把一个节点向右下方移一格，并让他原来的左子节点代替它的位置。
        RBTNode* left = node->lchild;
        node->lchild = left->rchild;
        node->lcount = left->rcount;
        node->lchild->parent = node;
        left->parent = node->parent;
        if (left->parent == m_null) {
            m_root = left;
        }else if (node == node->parent->lchild) {
            node->parent->lchild = left;
        }else {
            node->parent->rchild = left;
        }
        left->rchild = node;
        left->rcount += node->rcount + 1;
        node->parent = left;
    }

    RBTNode* treeMax(RBTNode* root) {//找到子树中最大的一个节点
        RBTNode* result = root;
        while (result->rchild != m_null) {
            result = result->rchild;
        }
        return result;
    }

    RBTNode* treeMin(RBTNode* root) {//找到子树中最小的一个节点
        RBTNode* result = root;
        while (result->lchild != m_null) {
            result = result->lchild;
        }
        return result;
    }
public:
    RBT() {
        m_null = new RBTNode;
        m_null->color = BLACK;
        m_null->lchild = m_null->rchild = m_null;
        m_root = m_null;
    }
    ~RBT() {
        clear();
        delete m_null;
    }

    RBTNode* atIndex(int i) {//找到从小到大排序后下标为i的节点。i从0开始。
        RBTNode* result = m_root;
        if (i > result->lcount + result->rcount) {
            result = NULL;
        }else {
            while (i != result->lcount) {
                if (i < result->lcount) {
                    result = result->lchild;
                }else {
                    i -= result->lcount + 1;
                    result = result->rchild;
                }
            }
        }
        return result;
    }

    void del(RBTNode* node) {//删除一个节点
        RBTNode* toDel = node;
        if (node->lchild != m_null && node->rchild != m_null) {
            toDel = treeNext(node);//找到中序后继：即右子树最左节点
        }
        RBTNode* temp = toDel;
        while (temp->parent != m_null) {
            if (temp == temp->parent->lchild) {
                temp->parent->lcount--;
            }else {
                temp->parent->rcount--;
            }
            temp = temp->parent;
        }
        RBTNode* replace = toDel->lchild != m_null? toDel->lchild: toDel->rchild;
        replace->parent = toDel->parent;
        if (replace->parent == m_null) {
            m_root = replace;
        }else if (toDel == toDel->parent->lchild) {
            replace->parent->lchild = replace;
        }else {
            replace->parent->rchild = replace;
        }
        if (toDel != node) {
            node->key = toDel->key;
        }
        if (toDel->color == BLACK) {
            //修改树，以保持平衡。
            delFixup(replace);
        }
        delete toDel;
    }

    void insert(const Key& key) {//插入一个节点
        RBTNode* node = new RBTNode;

        node->key = key;
        node->lcount = 0;
        node->rcount = 0;
        node->lchild = m_null;
        node->rchild = m_null;
        node->color = RED;

        RBTNode* p = m_root;
        RBTNode* leaf = m_null;
        while (p != m_null) {
            leaf = p;
            if (keyCmp(node->key, p->key) < 0) {
                p->lcount++;
                p = p->lchild;
            }else {
                p->rcount++;
                p = p->rchild;
            }
        }
        node->parent = leaf;
        if (leaf == m_null) {//如果是空树。
            m_root = node;
        }else if (keyCmp(node->key, leaf->key) < 0) {
            leaf->lchild = node;
        }else {
            leaf->rchild = node;
        }
        //修改树，以保持平衡。
        insertFixup(node);
    }
    int nodeCount() {
        return m_root != m_null? m_root->lcount + m_root->rcount + 1: 0;
    }

    RBTNode* search(const Key& key) {//按照key查找一个节点。
        RBTNode* result = m_root;
        while (result != m_null && keyCmp(key, result->key) != 0) {
            result = keyCmp(key, result->key) < 0 ? result->lchild : result->rchild;
        }
        return result == m_null? NULL: result;
    }

    void toArray(int* array) {//把树中节点的值放进一个数组。
        RBTNode* p = treeMin(m_root);
        int i = 0;
        while (p != m_null) {
            array[i] = p->key.value;
            i++;
            p = treeNext(p);
        }
    }

    RBTNode* treeNext(RBTNode* node) {//一个节点在中序遍列中的下一个节点。后继
        RBTNode* result;
        if (node->rchild != m_null) {
            result = treeMin(node->rchild);
        }else {
            result = node->parent;
            RBTNode* temp = node;
            while (result != m_null && temp == result->rchild) {
                temp = result;
                result = result->parent;
            }
        }
        return result;
    }

    RBTNode* treePre(RBTNode* node) {//一个节点在中序遍列中的前一个节点。前驱
        RBTNode* result;
        if (node->lchild != m_null) {
            result = treeMax(node->lchild);
        }else {
            result = node->parent;
            RBTNode* temp = node;
            while (result != m_null && temp == result->lchild) {
                temp = result;
                result = result->parent;
            }
        }
        return result;
    }
};
