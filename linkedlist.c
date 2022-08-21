#include <stdlib.h>
#include <stdbool.h>

struct Link{
    struct Link* next;
    void* p;
};

bool has_next(struct Link link){
    return link.next != NULL;
}

void del_chain(struct Link l){
    if(has_next(l))
        del_chain(*(l.next));
    free(l.p);
}

//Append new link containing p at end of chain.
struct Link* append(void* p, struct Link* before){
    if(has_next(*before)){
        return append(p, before->next);
    }else{
        struct Link* link = malloc(sizeof(struct Link));
        link->next = NULL;
        link->p = p;
        before->next = link;
        return link;
    }
}


