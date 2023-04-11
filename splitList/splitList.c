#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;
typedef struct ListNode { // ��� Ÿ���� ����ü�� �����Ѵ�. 
    element data;
    struct ListNode* prev; // �ڱ���������ü 
    struct ListNode* next; // �ڱ���������ü 
} ListNode;

ListNode* insert_first(ListNode* head, element value) // int? element? 
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode)); // (1)
    if (head == NULL) {
        p->data = value;
        p->prev = NULL;
        p->next = head;
    }
    else {
        p->data = value;
        p->prev = NULL;
        head->prev = p;
        p->next = head;
    }
    head = p;
    return head;
}
//���pre�ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode)); // (1)
    p->data = value;
    p->next = pre->next;
    pre->next = p;
    return head;
}
ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head; // (1) 
    head = removed->next; //(2) 
    free(removed); // (3) 
    return head;
}
// ��带 �����ϰ� �ش����� ���� ��ȯ�Ѵ�.
element delete(ListNode** head, ListNode* cur)
{
    ListNode* removed;
    element rdata;
    if (*head == NULL) return NULL;

    if (*head == cur) {
        rdata = cur->data;
        removed = *head; // (1) 
        *head = removed->next; //(2) 
        free(removed); // (3)
        return rdata;
    }
    else {
        rdata = cur->data;
        removed = cur; // (1) 
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev; // (2) 
        free(removed); // (3) 
        return rdata;
    }
}
// ��带 �����ϰ� �ش����� ���� ��ȯ�Ѵ�.
element delete_only(ListNode* cur)
{
    element rdata;
    if (cur == NULL)
        return NULL;
    rdata = cur->data;
    free(cur);
    return rdata;
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
ListNode* delete_bak(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre->next; // (1) 
    pre->next = removed->next; // (2) 
    free(removed); // (3) 
    return head;
}
void print_list(ListNode* head) {
    if (head == NULL) {
        printf("NULL \n");
        return;
    }
    for (ListNode* p = head; p != NULL; p = p->next)
        printf("%s -> ", p->data);
    printf("NULL \n");
}
// Ư���ܾ ã�� �ش����� �ּҰ� ��ȯ
ListNode* search(ListNode* head, char* word)
{
    if (head == NULL) {
        printf("head == NULL\n");
        exit(1);
    }

    ListNode* cur = NULL;

    cur = head;
    while (cur != NULL) {
        if (strcmp(cur->data, word) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
// cur��� ���� head1 2�� ������
ListNode* split_list(ListNode** head, ListNode** head_split, ListNode* cur)
{
    if (cur == NULL) return NULL;
    if (*head == cur) {
        *head = NULL;
        *head_split = cur->next;
    }
    else {
        cur->prev->next = NULL;
        *head_split = cur->next;
    }
    return cur;
}


int main(void)
{
    ListNode* head1 = NULL;
    ListNode* head2 = NULL;
    ListNode* cur = NULL;
    ListNode* tmp = NULL;
    element rdata;

    // APPLE -> KIWI -> BANANA -> LEMON -> MANGO -> MELON -> PEACH 

    head1 = insert_first(head1, "PEACH");
    head1 = insert_first(head1, "MELON");
    head1 = insert_first(head1, "MANGO");
    head1 = insert_first(head1, "LEMON");
    head1 = insert_first(head1, "BANANA");
    head1 = insert_first(head1, "KIWI");
    head1 = insert_first(head1, "APPLE");


    printf("head -> ");
    print_list(head1);


    cur = search(head1, "NULL");
    split_list(&head1, &head2, cur);
    rdata = delete_only(cur);
    printf("rdata: %s\n", rdata);

    printf("head1 -> ");
    print_list(head1);

    printf("head2 -> ");
    print_list(head2);

    cur = head1;
    while (cur != NULL) {
        tmp = cur;
        free(tmp);
        cur = cur->next;
    }
    cur = head2;
    while (cur != NULL) {
        tmp = cur;
        free(tmp);
        cur = cur->next;
    }
    return 0;
}


