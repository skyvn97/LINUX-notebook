struct Node {
    Node * child[2], * parent;
    bool reverse;
    int value, size;
    long long sum;
};

Node * nil, * root;

void initTree() {
    nil = new Node();
    nil->child[0] = nil->child[1] = nil->parent = nil;
    nil->value = nil->size = nil->sum = 0;
    nil->reverse = false;
    root = nil;
}

void pushDown(Node * x) {
    if(x == nil) return;
    if(x->reverse) {
        swap(x->child[0], x->child[1]);
        x->child[0]->reverse = !x->child[0]->reverse;
        x->child[1]->reverse = !x->child[1]->reverse;
        x->reverse = false;
    }
}

void update(Node * x) {
    pushDown(x->child[0]); pushDown(x->child[1]);
    x->size = x->child[0]->size + x->child[1]->size + 1;
    x->sum = x->child[0]->sum + x->child[1]->sum + x->value;
}

void setLink(Node * x, Node * y, int d) {
    x->child[d] = y;
    y->parent = x;
}

int getDir(Node * x, Node * y) {
    return x->child[0] == y ? 0 : 1;
}

void rotate(Node * x, int d) {
    Node * y = x->child[d], * z = x->parent;
    setLink(x, y->child[d ^ 1], d);
    setLink(y, x, d ^ 1);
    setLink(z, y, getDir(z, x));
    update(x); update(y);
}

void splay(Node * x) {
    while(x->parent != nil) {
        Node * y = x->parent, * z = y->parent;
        int dy = getDir(y, x), dz = getDir(z, y);
        if(z == nil) rotate(y, dy);
        else if(dy == dz) rotate(z, dz), rotate(y, dy);
        else rotate(y, dy), rotate(z, dz);
    }
}

Node * nodeAt(Node * x, int pos) {
    while(pushDown(x), x->child[0]->size != pos)
        if(pos < x->child[0]->size) x = x->child[0];
        else pos -= x->child[0]->size + 1, x = x->child[1];
    return splay(x), x;
}

void split(Node * x, int left, Node * &t1, Node * &t2) {
    if(left == 0) t1 = nil, t2 = x;
    else {
        t1 = nodeAt(x, left - 1);
        t2 = t1->child[1];
        t1->child[1] = t2->parent = nil;
        update(t1);
    }
}

Node * join(Node * x, Node * y) {
    if(x == nil) return y;
    x = nodeAt(x, x->size - 1);
    setLink(x, y, 1);
    update(x);
    return x;
}
