#include "linkedlist.c"
/*
    Each position in the hashmap contains a chain of links that contain entries.
*/

struct Entry
    {
        unsigned int key;
        void* p;
    };

struct HashMap
    {
        size_t size;
        size_t* num_entries;
        struct Link** links;
    };

struct HashMap hash_map(int size){
    struct HashMap map;
    map.size = size;
    map.links = calloc(size, sizeof(struct Link*));
    map.num_entries = calloc(1, sizeof(unsigned int));
    *(map.num_entries) = 0;
    return map;
}

void resize(){

}

void hm_copy(struct HashMap from, struct HashMap to){

}

void hm_free(struct HashMap map, bool free_data){
    for(int i = 0; i<map.size; i++){
        if(map.links[i] != NULL){
            del_chain(*map.links[i]);
            
        }
    }

}


unsigned int hash(unsigned int x){
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned int hash_to_index(unsigned int hash, size_t size){
    return hash%size;
}

unsigned int int_to_index(unsigned int x, struct  HashMap map){
    return hash_to_index(hash(x), map.size);
}

void hm_add(unsigned int key, void* p, struct HashMap map){
    int i = int_to_index(key, map);
    struct Entry* e = malloc(sizeof(struct Entry));
    e->key=key;
    e->p=p;

    if(map.links[i] == NULL){
        struct Link* l = malloc(sizeof(struct Link));
        l->next = NULL;
        l->p = e;
        map.links[i] = l;
    }else{
        append(e, map.links[i]);
    }

    *(map.num_entries) = *(map.num_entries) + 1;
}

void hm_print(struct HashMap map){
    printf("Hashmap: {\n");
    for(int i = 0; i<map.size; i++){
        if(map.links[i] != NULL){
            struct Link* l = map.links[i];
            int link_depth = 0;
            while(true){
                
                struct Entry* e = (struct Entry*) (l->p);
                
                printf("\t%d: %d (link depth %d),\n",e->key, *((int*)(e->p)), link_depth);
                if(has_next(*l)){
                    l = l->next;
                    link_depth++;
                }else{
                    break;
                }
            }
        }
    }
    printf("}\n");
}

// Returns the pointer with the matching key, return NULL if there is no match. 
void* hm_get(unsigned int key, struct HashMap map){
    int i = int_to_index(key, map);
    if(map.links[i] != NULL){
        //Search through the chain for an entry with a matching key.
        struct Link* l = map.links[i];
        while(true){
            struct Entry* e = (struct Entry*) (l->p);

            if(e->key == key){
                return e->p;
            }

           if(has_next(*l)){
            l = l->next;
           }else{
            break;
           }
        }

        return NULL;
    }else{
        return NULL;
    }
}

//Removes the object corresponding to the key and returns it. Returns NULL if there is no Entry with that key.
void* hm_remove(unsigned int key, struct HashMap map){
int i = int_to_index(key, map);
    if(map.links[i] != NULL){
        //Search through the chain for an entry with a matching key.'
        struct Link* old_l = NULL;
        struct Link* l = map.links[i];
        while(true){
            struct Entry* e = (struct Entry*) (l->p);

            //The Entry to remove is found, remove it
            if(e->key == key){
                if(old_l == NULL){
                  map.links[i] = l->next;
                }else{
                    old_l->next = l->next;
                }
                *(map.num_entries) = *(map.num_entries) - 1; 
                return e->p;           
            }

           if(has_next(*l)){
            old_l = l;
            l = l->next;
           }else{
            break;
           }
        }
        return NULL;
    }else{
        return NULL;
    }
}


