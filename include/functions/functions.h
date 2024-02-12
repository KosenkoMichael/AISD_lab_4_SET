#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <exception>


using namespace std;
    namespace rnd {
        class Rand {
        private:
            int _seed;
            int _min;
            int _max;
        public:
            Rand() : _seed(0), _min(0), _max(1) {};
            Rand(int seed, int min, int max) : _seed(seed), _min(min), _max(max) {};
            void set_seed(int val);
            void set_min(int val);
            void set_max(int val);
            int generate_random_number();
        };	
    }
	namespace set {
        template<typename T>
        class Node {
        public:
            T data;
            Node<T>* left;
            Node<T>* right;
            Node(T value) : data(value), left(nullptr), right(nullptr) {}
        };
        template<typename T>
        class MySet {
        private:
            Node<T>* root;
            void clear(Node<T>* node) {
                if (node) {
                    clear(node->left);
                    clear(node->right);
                    delete node;
                }
            }
            Node<T>* copy(Node<T>* node) {
                if (node) {
                    Node<T>* new_node = new Node<T>(node->data);
                    new_node->left = copy(node->left);
                    new_node->right = copy(node->right);
                    return new_node;
                }
                return nullptr;
            }
            void print(Node<T>* node) { //ËÊÏ
                if (node) {
                    print(node->left);
                    std::cout << node->data << " ";
                    print(node->right);
                }
            }
            bool insert(Node<T>*& node, T value) {
                if (!node) {
                    node = new Node<T>(value);
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
            bool contains(Node<T>* node, T value) {
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
            bool erase(Node<T>*& node, T value) {
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
                        Node<T>* temp = node->right;
                        delete node;
                        node = temp;
                    }
                    else if (!node->right) {
                        Node<T>* temp = node->left;
                        delete node;
                        node = temp;
                    }
                    else {
                        Node<T>* temp = node->right;
                        while (temp->left) {
                            temp = temp->left;
                        }
                        node->data = temp->data;
                        erase(node->right, temp->data);
                    }
                    return true;
                }
            }
        public:
            MySet() : root(nullptr) {}
            MySet(const MySet<T>& other) {
                root = copy(other.root);
            }
            ~MySet() {
                clear(root);
            }
            MySet<T>& operator=(const MySet<T>& other) {
                if (this != &other) {
                    clear(root);
                    root = copy(other.root);
                }
                return *this;
            }
            void print() {
                print(root);
                std::cout << std::endl;
            }
            bool insert(T value) {
                return insert(root, value);
            }
            bool contains(T value) {
                return contains(root, value);
            }
            bool erase(T value) {
                return erase(root, value);
            }
        };
	}