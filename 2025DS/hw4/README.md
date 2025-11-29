

## Fibonacci heap
Doubly linked list (no cicular here) in root list and child list. <br>
Root node can be marked but never can trigger cut. <br>
Decrease is lazy, only if it is smaller than parent, then add it to root list.
<br>

| Operation   | Triggers Consolidation? | Triggers Cascading Cut? |
| ------------| ------------------------|-------------------------|
| Insert      |            No           |            No           |
| Delete      |            Yes          |           Yes           |
| Decrease    |           No            |           Yes           |
| Extract-Min |           Yes           |            No           |

<br>

## Common Major bug
### 1. consolidate() Strategy
The specification requires an implementation prioritizing a specific deterministic structure over efficiency. It forces merges to happen in a specific order based on sorted keys.
<br>

| Feature     | Original Logic                 | Required Logic (Reference-style)               |
| ----------- | ------------------------------------- | ---------------------------------------------- |
| Complexity  | ~O(N) one pass                        | ~O(N²) (due to restart + re-sort)              |
| Root order  | Whatever current linked list order is | Always **sorted by key** before merge          |
| On merge    | Continue from current node            | **Stop, compact, re-sort, restart** whole scan |

<br>
<br>

Original Logic:
```c
// Linear Scan
initialize degree_table[] = {NULL}

foreach (node in root_list) {
    d = node.degree
    while (degree_table[d] != NULL) {
        other = degree_table[d]
        node = unite(node, other) // Merge and continue with same node
        degree_table[d] = NULL
        d++
    }
    degree_table[d] = node // Place and move to next node
}
// Rebuild root list from degree_table
```

Required Logic:
```c
// Sort - Scan - Restart
do {
    merged_flag = false
    
    // 1. Snapshot and Sort
    roots_array = get_all_roots()
    SORT(roots_array, by_KEY_ascending) // Crucial Step
    
    degree_table[] = {NULL}
    
    // 2. Scan
    foreach (node in roots_array) {
        d = node.degree
        if (degree_table[d] == NULL) {
            degree_table[d] = node
        } else {
            // 3. Collision Found
            other = degree_table[d]
            unite(node, other)
            
            merged_flag = true 
            BREAK Loop // STOP immediately! Structure changed.
        }
    }
} while (merged_flag == true) // If we merged anything, RESTART the whole process
```
<br> 
<br> 

### 2. Add to Root List/Unite Direction: Head vs. Tail
This affects the order of children within a tree. Since the assignment requires outputting trees in certain order. Go with Origin one would affects which child is promoted first during a delete.

<br> 

| Feature         | Origin (Insert at head)          | Required (Insert Tail)           |
| --------------- | --------------------------------------- | ------------------------------------------------- |
| Child order     | LIFO: Newest child becomes the head.  | FIFO: Newest child goes to the end. |åå
| Time Complexity | $O(1)$ (Constant Time) | $O(\text{Degree})$ (Linear Time) |å


<br> 
<br>

```c
void add_head(Node *parent, Node *child) {
    child->next = parent->child_head
    if (parent->child_head) parent->child_head->prev = child
    parent->child_head = child 
}
```

```c
void add_tail(Node *parent, Node *child) {
    if (parent->child_head == NULL) parent->child_head = child
    else {
        curr = parent->child_head
        while (curr->next != NULL) curr = curr->next
        curr->next = child
        child->prev = curr
    }
}
```

<br>

## Reference:
CLRS 

Another Code style: 
[To typedef structs or not](https://www.reddit.com/r/C_Programming/comments/kr4i80/to_typedef_structs_or_not/)

It's an opinion. Follow your coding standard. The Linux kernel says no while OpenSSL says yes (Chapter 5)
