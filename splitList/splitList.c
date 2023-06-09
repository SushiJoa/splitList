#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;
typedef struct ListNode { // 노드 타입을 구조체로 정의한다. 
    element data;
    struct ListNode* prev; // 자기참조구조체 
    struct ListNode* next; // 자기참조구조체 
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
// 삭제할 노드의 앞,뒤 노드를 연결한후 삭제한뒤 반환하는 함수
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
// 노드를 삭제하고 해당노드의 값을 반환하는 함수
element delete_only(ListNode* cur)
{
    element rdata;
    if (cur == NULL)
        return NULL;
    rdata = cur->data;
    free(cur);
    return rdata;
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
// 특정단어를 찾아 해당노드의 주소값 반환
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
// 삭제할 단어를 기준으로 리스트 앞, 뒤로 나누는 함수
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

    // head -> APPLE -> KIWI -> BANANA -> LEMON -> MANGO -> MELON -> PEACH 
    // 단어들을 리스트에 추가
    head1 = insert_first(head1, "PEACH");
    head1 = insert_first(head1, "MELON");
    head1 = insert_first(head1, "MANGO");
    head1 = insert_first(head1, "LEMON");
    head1 = insert_first(head1, "BANANA");
    head1 = insert_first(head1, "KIWI");
    head1 = insert_first(head1, "APPLE");

    printf("head -> ");
    print_list(head1);

    cur = search(head1, "LEMON");
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
        cur = cur->next;
        free(tmp);
    }
    cur = head2;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    return 0;
}


