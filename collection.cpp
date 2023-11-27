//
// Created by Renat Yakublevich on 20.11.23.
//
#include "collection.h"

template<typename T>
Collection<T>::Collection() {
    this->root = new Tree<T>;
    this->count = 0;
}

template<typename T>
Entities<T> Collection<T>::select_all() {
    T entities[MAX_COUNT_ENTITIES];
    int index = 0;
    root->dfs(entities, index, this->root);
    for (int i = 1; i < index; ++i) {
        entities[i - 1] = entities[i];
    }
    return Entities<T>(entities, index - 1);
}


template<typename T>
void Collection<T>::insert(T object) {
    count++;
    this->root->add(object);
}

template<typename T>
T* Collection<T>::select(T object) {
    return root->search(object)->GetObject();
}

template<typename T>
void Collection<T>::del(T object) {
    count--;
    root = root->remove(object, root);
}


template<typename T>
Tree<T>::Tree() {
    this->left = nullptr;
    this->right = nullptr;
}

template<typename T>
void Tree<T>::dfs(T* entities, int& index, Tree<T>* node) {
    if (node == nullptr) return;
    dfs(entities, index, node->left);
    entities[index] = *node->GetObject();
    index += 1;
    dfs(entities, index, node->right);
}

template<typename T>
Tree<T>::Tree(T object) {
    this->object = object;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename T>
Tree<T>::~Tree() {
    delete left;
    delete right;
}


template<typename T>
T* Tree<T>::GetObject()
{
    return &object;
}


template<typename T>
void Tree<T>::add(T value) {
    if (value < object) {
        if (left == nullptr) {
            left = new Tree(value);
        }
        else {
            left->add(value);
        }
    }
    else if (value > object) {
        if (right == nullptr) {
            right = new Tree(value);
        }
        else {
            right->add(value);
        }
    }
}

template<typename T>
Tree<T>* Tree<T>::search(T value) {
    if (value == object) {
        return this;
    }
    else if (value < object) {
        if (left == nullptr) {
            return nullptr;
        }
        else {
            return left->search(value);
        }
    }
    else {
        if (right == nullptr) {
            return nullptr;
        }
        else {
            return right->search(value);
        }
    }
}

template<typename T>
Tree<T>* Tree<T>::findMinNode(Tree* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

template<typename T>
Tree<T>* Tree<T>::remove(T value, Tree* root) {
    if (root == nullptr) {
        return nullptr;
    }

    if (value < *root->GetObject()) {
        root->left = remove(value, root->left);
    } else if (value > *root->GetObject()) {
        root->right = remove(value, root->right);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            Tree* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Tree* temp = root;
            root = root->left;
            delete temp;
        } else {
            Tree* minNode = findMinNode(root->right);
            root->object = minNode->object;
            root->right = remove(*minNode->GetObject(),root->right);
        }
    }
    return root;
}

template <typename T>
void Entities<T>::sort() {
    int left = 0;
    int right = length - 1;
    bool swapped = false;

    do {
        swapped = false;

        for (int i = left; i < right; ++i) {
            if (entities[i] > entities[i + 1]) {
                std::swap(entities[i], entities[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        --right;
        for (int i = right; i > left; --i) {
            if (entities[i] < entities[i - 1]) {
                std::swap(entities[i], entities[i - 1]);
                swapped = true;
            }
        }

        ++left;
    } while (swapped);
}

#include "models.h"

template class Entities<User>;
template class Entities<Artist>;
template class Entities<std::string>;

template Tree<User>* Tree<User>::remove(User value, Tree* root);
template Tree<Artist>* Tree<Artist>::remove(Artist value, Tree* root);

template Tree<User>* Tree<User>::findMinNode(Tree* root);
template Tree<Artist>* Tree<Artist>::findMinNode(Tree* root);

template Tree<User>* Tree<User>::search(User value);
template Tree<Artist>* Tree<Artist>::search(Artist value);

template void Tree<User>::add(User value);
template void Tree<Artist>::add(Artist value);

template User* Tree<User>::GetObject();
template Artist* Tree<Artist>::GetObject();

template Tree<User>::~Tree();
template Tree<Artist>::~Tree();

template Tree<User>::Tree(User object);
template Tree<Artist>::Tree(Artist object);

template void Tree<Artist>::dfs(Artist* entities, int& index, Tree<Artist>* node);
template void Tree<User>::dfs(User* entities, int& index, Tree<User>* node);

template Tree<User>::Tree();
template Tree<Artist>::Tree();

template void Collection<User>::del(User object);
template void Collection<Artist>::del(Artist object);

template User* Collection<User>::select(User object);
template Artist* Collection<Artist>::select(Artist object);

template void Collection<User>::insert(User object);
template void Collection<Artist>::insert(Artist object);

template Entities<User> Collection<User>::select_all();
template Entities<Artist> Collection<Artist>::select_all();

template Collection<User>::Collection();
template Collection<Artist>::Collection();


