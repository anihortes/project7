// treesorter.h  SKELETON
// Glenn G. Chappell
// 2021-11-08
//
// For CS 311 Fall 2021
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORTER_H_INCLUDED
#define FILE_TREESORTER_H_INCLUDED

#include <iterator>
// For std::iterator_traits

// *******************************************************
// * YOU MIGHT WANT TO GET RID OF THE FOLLOWING INCLUDES *
// *******************************************************

#include <algorithm>
// For std::stable_sort, std::move
#include <vector>
// For std::vector
#include <iterator>
// For std::distance
#include <tuple>
// For std::tuple
#include <memory>
// For std::unique_ptr
#include <utility>
// For std::move


// struct Node
// Binary Search tree node with client specified data type
// Invariants:
//     Node is empty on creation
//      _nextRightChild, _nextLeftChild are empty on creation
// Requirements on Types:
//     ValueType must have a copy ctor and a (non-throwing) dctor.
// Exception safety guarantee:
//     No-Throw Guarantee
template<typename ValueType>
struct Node{
    ValueType _data;
    std::unique_ptr<Node> _nextRightChild;
    std::unique_ptr<Node> _nextLeftChild;

    explicit Node(const ValueType & data)
              :_data(data)
    {}

    ~Node() = default;

    // No default ctor, no copy/move operations.
    Node() = delete;
    Node(const Node & other) = delete;
    Node & operator=(const Node & other) = delete;
    Node(Node && other) = delete;
    Node & operator=(Node && other) = delete;
};

// insert
// Recursively insert data into a Binary Search tree
// Pre:
//     item must point to an array
// Requirements on Types:
//     FDIter must be an iterator
// Exception safety guarantee:
//     No-Throw Guarantee
template<typename Value>
void insert(std::unique_ptr<Node<Value>> & node, const Value & value){
    if(node == nullptr){
        node = std::make_unique<Node<Value>>(value);
        return;
    }
    // check == condition
    else if(!(value < node->_data) && !(node->_data < value)){
        insert(node->_nextRightChild, value);
    }
    else if(value < node->_data){
        insert(node->_nextLeftChild, value);
    }
    else {
        insert(node->_nextRightChild, value);
    }
}

// traverse
// Recursively copy sorted binary tree data into an array.
// Pre:
//     Node<Value> must be a node in a sorted binary tree
//     item must point to an array
// Requirements on Types:
//     FDIter must be an iterator
// Exception safety guarantee:
//     No-Throw Guarantee
template<typename Value, typename FDIter>
void traverse(const std::unique_ptr<Node<Value>> & head, FDIter & item){
    if(head == nullptr){
        return;
    }
    traverse(head->_nextLeftChild, item);
    *item++ = head->_data;
    traverse(head->_nextRightChild, item);
}

// treesort
// Sort a given range using Treesort.
// Pre:
//     first must point to start of an array
//     last must point to just past the end of array
// Requirements on Types:
//     FDIter must be an iterator
// Exception safety guarantee:
//     Exception neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Value is the type that FDIter points to
    using Value = typename std::iterator_traits<FDIter>::value_type;
    //auto p = std::make_unique<Node<Value>>(*first, first);
    std::unique_ptr<Node<Value>> head;
    FDIter iter = first;
    while(iter != last) {
        insert(head, *iter);
        iter++;
    }
    traverse(head, first);



    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS, BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE PROJECT.
    std::vector<Value> buff(std::distance(first, last));
    std::move(first, last, buff.begin());
    std::stable_sort(buff.begin(), buff.end());
    std::move(buff.begin(), buff.end(), first);
}

#endif //#ifndef FILE_TREESORTER_H_INCLUDED