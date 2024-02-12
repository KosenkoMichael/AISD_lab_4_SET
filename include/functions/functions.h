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
        class Node {
        public:
            int data;
            Node* left;
            Node* right;
            Node(int value) : data(value), left(nullptr), right(nullptr) {}
        };
        class MySet {
        private:
            Node* root;
            void clear(Node* node);
            Node* copy(Node* node);
            void print(Node* node);
            bool insert(Node*& node, int value);
            bool contains(Node* node, int valu);
            bool erase(Node*& node, int valu);
        public:
            MySet() : root(nullptr) {}
            MySet(const MySet& other);
            ~MySet();
            MySet& operator=(const MySet& other);
            void print();
            bool insert(int value);
            bool contains(int value);
            bool erase(int value);
        };
	}