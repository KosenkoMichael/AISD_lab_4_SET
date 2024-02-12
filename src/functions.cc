#include <functions/functions.h>

int rnd::Rand::generate_random_number() {
	mt19937 mt(_seed);
	uniform_int_distribution<int> distribution(_min, _max);
    _seed++;
	return distribution(mt);
}

void rnd::Rand::set_seed(int val) {
    _seed == val;
}

void rnd::Rand::set_min(int val) {
    _min == val;
}

void rnd::Rand::set_max(int val) {
    _max == val;
}

void set::MySet::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

set::Node* set::MySet::copy(Node* node) {
    if (node) {
        Node* new_node = new Node(node->data);
        new_node->left = copy(node->left);
        new_node->right = copy(node->right);
        return new_node;
    }
    return nullptr;
}

void set::MySet::print(Node* node) { //ËÊÏ
    if (node) {
        print(node->left);
        std::cout << node->data << " ";
        print(node->right);
    }
}

bool set::MySet::insert(Node*& node, int value) {
    if (!node) {
        node = new Node(value);
        return true;
    }
    if (value < node->data) {
        return insert(node->left, value);
    }
    else if (value > node->data) {
        return insert(node->right, value);
    }
    return false;
}

bool set::MySet::contains(Node* node, int value) {
    if (!node) {
        return false;
    }
    if (value < node->data) {
        return contains(node->left, value);
    }
    else if (value > node->data) {
        return contains(node->right, value);
    }
    return true;
}

bool set::MySet::erase(Node*& node, int value) {
    if (!node) {
        return false;
    }
    if (value < node->data) {
        return erase(node->left, value);
    }
    else if (value > node->data) {
        return erase(node->right, value);
    }
    else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else {
            Node* temp = node->right;
            while (temp->left) {
                temp = temp->left;
            }
            node->data = temp->data;
            erase(node->right, temp->data);
        }
        return true;
    }
}

set::MySet::MySet(const MySet& other) {
    root = copy(other.root);
}

set::MySet::~MySet() {
    clear(root);
}

set::MySet& set::MySet::operator=(const MySet& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

void set::MySet::print() {
    print(root);
    std::cout << std::endl;
}

bool set::MySet::insert(int value) {
    return insert(root, value);
}

bool set::MySet::contains(int value) {
    return contains(root, value);
}

bool set::MySet::erase(int value) {
    return erase(root, value);
}