#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <exception>
#include <chrono> 
#include <cmath> 
#include <functional>
#include <vector>

/*
clock_t start = clock();
clock_t end = clock();
double seconds = (double)(end - start) / CLOCKS_PER_SEC;
cout << "The time >> " << seconds << " seconds";
*/


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
        struct Node {
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
            Node<T>* getroot() {
                return root;
            }
            MySet<T>& fill(size_t count) {
                size_t cur_count = 0;
                rnd::Rand test_seed(0, 0, count * 10);
                while (cur_count != count) {
                    if (insert(test_seed.generate_random_number()))
                        cur_count++;
                }
                return *this;
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
        double get_time_fill(size_t count) {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i <= 100; i++) {
                MySet<int> test_set;
                test_set.fill(count);
            }
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/100;
        }
        double get_time_contains(MySet<int>& test_set, size_t count) {
            rnd::Rand test_seed(0, 0, count * 10);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i <= 1000; i++) {
                test_set.contains(test_seed.generate_random_number());
            }
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000;
        }
        double get_time_erase(MySet<int>& test_set, size_t count) {
            rnd::Rand test_seed(0, 0, count * 10);
            MySet test_set_copy(test_set);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i <= 1000; i++) {
                test_set_copy.erase(test_seed.generate_random_number());
            }
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000;
        }
        double get_time_insert(MySet<int>& test_set, size_t count) {
            rnd::Rand test_seed(0, 0, count * 10);
            MySet test_set_copy(test_set);
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i <= 1000; i++) {
                test_set_copy.insert(test_seed.generate_random_number());
            }
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        template<typename T>
        MySet<T> logic_or(MySet<T>& set1, MySet<T>& set2) {
            MySet<T> result;
            std::function<void(Node<T>*)> m_union = [&](Node<T>* node) {
                if (node != nullptr) {
                    m_union(node->left);
                    result.insert(node->data);
                    m_union(node->right);
                }
            };
            m_union(set1.getroot());
            m_union(set2.getroot());
            return result;
        }
        template<typename T>
        MySet<T> logic_xor(MySet<T>& set1, MySet<T>& set2) {
            MySet<T> result;
            std::function<void(Node<T>*)> m_xor = [&](Node<T>* node) {
                if (node != nullptr) {
                    m_xor(node->left);
                    if(!(set1.contains(node->data)&&set2.contains(node->data)))
                        result.insert(node->data);
                    m_xor(node->right);
                }
            };
            m_xor(set2.getroot());
            m_xor(set1.getroot());
            return result;
        }
    }
    double get_time_fill_V(size_t count) {
        rnd::Rand test_seed(0, 0, count * 10);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i <= 100; i++) {
            vector<int> test_vec;
            for (int i = 0; i <= count; i++)
                test_vec.push_back(test_seed.generate_random_number());
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 100;
    }
    double get_time_contains_V(vector<int>& arr, size_t count) {
        rnd::Rand test_seed(0, 0, count * 10);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i <= 1000; i++) {
            find(arr.begin(), arr.end(), test_seed.generate_random_number());
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000;
    }
    double get_time_erase_V(vector<int>& test_set, size_t count) {
        rnd::Rand test_seed(0, 0, count * 10);
        vector<int> test_vec_copy(test_set);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i <= 1000; i++) {
            const auto del_obj = remove(test_vec_copy.begin(), test_vec_copy.end(), test_seed.generate_random_number());
            test_vec_copy.erase(del_obj, test_vec_copy.end());
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000;
    }
    double get_time_insert_V(vector<int>& test_set, size_t count) {
        rnd::Rand test_seed(0, 0, count * 10);
        vector<int> test_vec_copy = test_set;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i <= 1000; i++) {
            test_vec_copy.push_back(test_seed.generate_random_number());
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }