#pragma once

#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int elem_;
    Node* next_;
} Node;

typedef Node* List;

Node* new_node() {
    return (Node*)malloc(sizeof(Node));
}

void print_list(List list) {
    Node* node = list;
    while (node) {
        printf("%d ", node->elem_);
        node = node->next_;
    }
}

List create_list(int num) {
    List prev_node = nullptr;
    List node = nullptr;
    for (int i = 0; i < num; ++i) {
        node = (Node*)malloc(sizeof(Node));
        node->elem_ = i;
        node->next_ = prev_node;
        prev_node = node;
    }
    return node;
}

void delete_list(List list) {
    if (!list) {
        return;
    }
    Node* node = list;
    Node* node_next = nullptr;
    while (node) {
        node_next = node->next_;
        free(node);
        node = node_next;
    }
}

List reverse(List list) {
     // 前向节点，初始指向null
    Node* prev = nullptr;
    // node初始指向第一个节点
    Node* node = list;
    // next指向第二个节点
    Node* next = node->next_;
    while (node) {
        // node指向的节点的next指向前向节点
        node->next_ = prev;
        // 若干next节点指向了nullptr，表示node节点也已经完成了指向反转
        // 将node作为头结点返回
        if (!next) {
            return node;
        }
        // 使前向节点指向node，即前向节点后移一个节点
        prev = node;
        // node节点指向next，即node后移一个节点，此时node和next的指向同一个节点
        node = next;
        // next节点指向下一个节点
        next = node->next_;
        // 上述步骤完成后，只将一个节点的next_指向关系反转了，并开始操作下一个节点。
        // 切记每次只操作一个节点，不要试图操作两个节点的指向关系
    }

    return list;
}

List reverse_recursive(List list, Node* prev) {
    // node指向链表的第一个节点
    Node* node = list;
    // next指向node的下一个节点
    Node* next = node->next_;
    // 执行反转操作，使链表的第一个节点指向前向节点
    node->next_ = prev;
    if (next != nullptr)
        // 如果next不是nullptr，则以node为前向节点，next作为链表的头结点递归反转
        node = reverse_recursive(next, node);
    // 最后返回node节点即可
    return node;
}
