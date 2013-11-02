#include "sorted-list.h"

Node *CreateNode(void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->iterList = NULL;
    return node;
}

/* Complete */
SortedListPtr SLCreate(CompareFuncT cf) {
    SortedListPtr list = malloc(sizeof(SortedList));
    list->root = CreateNode(NULL);
    list->cmp = cf;
    return list;
}

/* Complete */
void SLDestroy(SortedListPtr list) {
    Node *ptr, *next;
    SortedListIteratorPtr iterPtr, iterNext;
    if (list == NULL) {
        return;
    }
    /* garbage collect */
    for (ptr = list->root; ptr != NULL; ptr = next) {
        next = ptr->next;
        for (iterPtr = ptr->iterList; iterPtr != NULL; iterPtr = iterNext) {
            iterNext = iterPtr->next;
            free(iterPtr);
        }
        free(ptr);
    }
    free(list);
}

/* Complete */
int SLInsert(SortedListPtr list, void *newObj) {
    Node *ptr, *insertable;
    if (list == NULL || newObj == NULL) {
        return 0;
    }
    insertable = CreateNode(NULL);
    /* find the spot */
    for (ptr = list->root; ptr->data != NULL; ptr = ptr->next) {
        int cmp = list->cmp(newObj, ptr->data);
        if (cmp > 0) {
            SortedListIteratorPtr iterPtr, iterNext;
            insertable->data = ptr->data;
            ptr->data = newObj;
            insertable->next = ptr->next;
            ptr->next = insertable;
            for (iterPtr = ptr->iterList; iterPtr != NULL; iterPtr = iterNext) {
                iterNext = iterPtr->next;
                /* this situation is when the Node's data is greater than the last item */
                if (iterPtr->lastItem != NULL && list->cmp(iterPtr->lastItem, newObj) <= 0) {
                    if (iterPtr->prev != NULL) {
                        iterPtr->prev->next = iterNext;
                    } else {
                        iterPtr->ptr->iterList = iterPtr->next;
                    }
                    if (iterNext != NULL) {
                        iterPtr->next->prev = iterPtr->prev;
                    }
                    iterPtr->next = iterPtr->ptr->next->iterList;
                    if (iterPtr->next != NULL) {
                        iterPtr->next->prev = iterPtr;
                    }
                    iterPtr->ptr->next->iterList = iterPtr;
                    iterPtr->ptr = iterPtr->ptr->next;
                }
            }
            return 1;
        } else if (cmp == 0) {
            printf("The item already exists in the list.\n");
            free(insertable);
            return 1;
        }
    }
    ptr->data = newObj;
    ptr->next = insertable;
    return 1;
}

/* Complete */
int SLRemove(SortedListPtr list, void *newObj) {
    Node *ptr, *prev = NULL;
    if (list == NULL || newObj == NULL) {
        return 0;
    }
    for (ptr = list->root; ptr->data != NULL; ptr = ptr->next) {
        if (list->cmp(newObj, ptr->data) == 0) {
            /* iteration list moved over */
            if (ptr->iterList != NULL) {
                SortedListIteratorPtr iterPtr, iterPrev = NULL;
                for (iterPtr = ptr->iterList; iterPtr != NULL; iterPtr = iterPtr->next) {
                    iterPtr->ptr = ptr->next;
                    iterPrev = iterPtr;
                }
                iterPrev->next = ptr->next->iterList;
                if (iterPrev->next != NULL) {
                    iterPrev->next->prev = iterPrev;
                }
                ptr->next->iterList = ptr->iterList;
            }
            /* move prev to connect to next */
            if (prev == NULL) {
                list->root = ptr->next;
            } else {
                prev->next = ptr->next;
            }
            free(ptr);
            return 1;
        }
        prev = ptr;
    }
    return 0;
}

/* Complete */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
    SortedListIteratorPtr iter;
    if (list == NULL) {
        return NULL;
    }
    iter = malloc(sizeof(SortedListIterator));
    iter->ptr = list->root;
    iter->lastItem = NULL;
    iter->next = list->root->iterList;
    if (iter->next != NULL) {
        iter->next->prev = iter;
    }
    list->root->iterList = iter;
    return iter;
}

/* Complete */
void SLDestroyIterator(SortedListIteratorPtr iter) {
    if (iter == NULL) {
        return;
    }
    if (iter->prev != NULL) {
        iter->prev->next = iter->next;
    } else {
        iter->ptr->iterList = iter->next;
    }
    if (iter->next != NULL) {
        iter->next->prev = iter->prev;
    }
    free(iter);
}

/* Complete */
void *SLNextItem(SortedListIteratorPtr iter) {
    void *data;
    if (iter == NULL || iter->ptr->data == NULL) {
        return NULL;
    }
    data = iter->ptr->data;
    /* Remove iter from ptr->iterList */
    if (iter->prev != NULL) {
        iter->prev->next = iter->next;
    } else {
        iter->ptr->iterList = iter->next;
    }
    if (iter->next != NULL) {
        iter->next->prev = iter->prev;
    }
    /* Add to the iterList of ptr->next */
    iter->next = iter->ptr->next->iterList;
    if (iter->next != NULL) {
        iter->next->prev = iter;
    }
    iter->ptr->next->iterList = iter;
    iter->ptr = iter->ptr->next;
    iter->lastItem = data;
    return data;
}
