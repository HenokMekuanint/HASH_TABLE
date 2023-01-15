# HASH_TABLE using c programming language

Part I: Hash Table In this part you will implement the hash table data structure. 
You should use the separate chaining technique which is described in the COS 217 ‑ Data structures Lecture. Pay close attention to the linked list part as well, as the implementation of the hash table depends on it. You are required to use a linked list to implement the hash bucket list. Your struct implementations can look like this: const BUCKET_COUNT = 1024;
struct Binding{ const char* key; int value; struct Binding* next; }
struct HashTable{ struct Binding* buckets[BUCKET_COUNT] }Your hash table should have the following interfaces: 
//This function should create and initialize a HashTable and return it. struct HashTable* create(); 
//This function hashes the key and returns an integer mod BUCKET_COUNT unsigned int hash(const char* key); /***This function associates the value 'value' using the key 'key'. Two cases to consider.

Case I: The key does not already exists in the HashTable. Then you should
create a struct Binding with key 'key' and value 'value', hash the key
and insert the binding into the table using the hash value of the key.
The function then should return true.
↪↪↪
Case II: The key already exists in the HashTable. Then you should update
the Bindings old value to the new supplied 'value'. The function should
return false.
↪↪
*/
bool add(struct HashTable* table, const char* key, int value);
/**
* This function should search for the key 'key' in the HashTable and return
the Binding if it finds one with the key. Otherwise it should return
null.
↪↪
*/
struct Binding* find(struct HashTable* table, const char* key);
/**
* This function should try to remove a binding with key 'key' from the
HashTable. It should return true if it was able to remove/delete the
binding otherwise it should return false.
↪↪
Hint: Be sure not to leak any dynamically allocated memory for the deleted
binding, you should remember to free any dynamically allocated memory
for the binding.
↪↪
*/
bool remove(struct HashTable* table, const char* key);
/**
* This should free all dynamically allocated memory for the HashTable
'table'. ↪
Hint: You might want to traverse the bindings and free them too.
