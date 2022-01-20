
struct LinkNode {
    int data;
    LinkNode* next;
    LinkNode* prev;
};

LinkNode* remove_min(LinkNode* head) {
    LinkNode* cur = head;
    LinkNode* min = head;
    while (cur != nullptr) {
        if (cur->data < min->data) {
            min = cur;
        }
        cur = cur->next;
    }
    if (min == head) {
        head = head->next;
    } else {
        min->prev->next = min->next;
        min->next->prev = min->prev;
    }
    delete min;
    return head;
}

int main(int argc, char const *argv[]) {
    LinkNode* head = new LinkNode();
    head->data = 0;
    head->prev = nullptr;
    head->next = nullptr;
    LinkNode* tail = head;
    int arr[] = {3, 2, 9, 7, 1, 5, 6, 8, 4};
    for (int i = 0; i < 9; ++i) {
        LinkNode* cur = new LinkNode();
        cur->data = arr[i];
        cur->next = nullptr;
        cur->prev = tail;
        tail->next = cur;
        tail = cur;
    }
    while (head) {
        head = remove_min(head);
    }
    return 0;
}
