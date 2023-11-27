//
// Created by Renat Yakublevich on 18.11.23.
//

#ifndef KURS_COLLECTION_H
#define KURS_COLLECTION_H

#define MAX_COUNT_ENTITIES 1028

#include <iostream>

template<typename T>
class Tree
{
private:
    Tree* left;
    Tree* right;
    T object;
public:

    Tree();

    Tree(T object);

    ~Tree();

    T* GetObject();

    void add(T value);

    Tree* search(T value);

    Tree* remove(T object, Tree* root);

    void dfs(T* entities, int& index, Tree<T>* node);

    Tree* findMinNode(Tree* root);
};

template <typename T>
class Entities {
public:
    T* entities;
    int length;

    Entities(T* entities, int length);
    Entities();

    void sort();
//    ~Entities();
};

template<typename T>
Entities<T>::Entities(T* entities, int length) : entities(entities), length(length) {};

template<typename T>
Entities<T>::Entities() {}


template<typename T>
class Collection {
public:
    Collection();

    Entities<T> select_all();

    void insert(T object);

    T* select(T object);

    void del(T object);
private:
    Tree<T>* root;
    int count;
};



#endif //KURS_COLLECTION_H
