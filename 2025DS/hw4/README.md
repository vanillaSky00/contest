root list: circular doubly linked list
child list: circular doubly linked list

code style: 
[To typedef structs or not](https://www.reddit.com/r/C_Programming/comments/kr4i80/to_typedef_structs_or_not/)
```
It's an opinion. Follow your coding standard.

The Linux kernel says no.

OpenSSL says yes (Chapter 5)
```


Operation,Triggers Consolidation?,Triggers Cascading Cut?
Insert,No,No
Delete,Yes(Must consolidate after completion),Yes(Via the Decrease-Key step)
Decrease,No,Yes(If parent is marked)
Extract-Min,Yes(Must consolidate after completion),Yes*(As per your input text)