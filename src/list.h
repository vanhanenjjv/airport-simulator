#ifndef LIST_H
#define LIST_H

#include <cstddef>

#include "node.h"

template<typename T>
class List {
  private:
    Node<T> *head_ = NULL;
    Node<T> *tail_ = NULL;

    Node<T> *NodeAt(int index) {
      Node<T> *node = head_;

      for (int i = 0; i < index; ++i)
        node = node->next;

      return node; 
    }
  
  public:
    List() {}
    
    ~List() {
      Clear();
    }

    T &operator [](int index) {
      return NodeAt(index)->value;
    }

    T &At(int index) {
      return operator[](index);
    }

    int Count() {
      int count = 0;

      for (Node<T> *current = head_; current != NULL; current = current->next)
        ++count;

      return count;
    }

    void Clear() {
      while (head_ != NULL) {
        Node<T> *current = head_;
        Node<T> *next    = head_->next;

        delete current;

        head_ = next;
      }
    }

    bool Contains(T value) {
      for (Node<T> *current = head_; current != NULL; current = current->next)
        if (current->value == value)
          return true;

      return false;
    }

    void Add(T value) {
      auto *node = new Node<T>;
      node->next = NULL;
      node->value = value;
      
      if (head_ == NULL) {
        head_ = node;
        tail_ = node;
      }
      else {
        tail_->next = node;
        tail_ = tail_->next;
      }
    }

    template<typename F>
    void ForEach(F action) {
      for (Node<T> *current = head_; current != NULL; current = current->next)
        action(current->value);
    }  

    template<typename F>
    bool Exists(F match) {
      for (Node<T> *current = head_; current != NULL; current = current->next)
        if (match(current->value))
          return true;

      return false;
    }

    void RemoveAt(int index) {
      if (head_ == NULL)
        return;

      /* Only head is removed so no need to mess with other nodes.
      */
      if (index == 0) {
        Node<T> *removed = head_;
        head_ = head_->next;
        delete removed;

        return;
      }    

      /* Get the node before the node-to-be-removed and set it's  
         next to point over the removed node. After that delete 
         the node.
      */ 
      Node<T> *previous = NodeAt(index - 1);
      Node<T> *removed = previous->next;

      previous->next = removed->next;

      if (removed->next == NULL)
        tail_ = previous;

      delete removed;
    }

    template<typename F>
    void RemoveAll(F match) {
      if (head_ == NULL)
        return;

      /* Find the new head */
      while (match(head_->value)) {
        Node<T> *next = head_->next;
        delete head_;

        /* All of the nodes were deleted */
        if (next == NULL)
          return;

        head_ = next;
      }

      Node<T> *previous = head_;
      Node<T> *current = previous->next;

      while (current != NULL) {
        Node<T> *next = current->next;

        if (match(current->value)) {
          previous->next = next;
          delete current;
        }
        else
          previous = current;

        current = next;
      }

      tail_ = previous;
    }

    template<typename F>
    T Find(F match) {
      for (Node<T> *current = head_; current != NULL; current = current->next)
        if (match(current->value))
          return *(current->value);

      return NULL;
    }
};

#endif