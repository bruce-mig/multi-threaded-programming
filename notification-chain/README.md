# notification chain

This project involves building a networking route table from scratch using glue thread (doubly linked list data structures). Subscriber threads are created then subscribe to updates/additions or deletions to  entries of the routing table. The subscribers subscribe to any entries in the route table to  form a notification chain of glue thread data structure. 

When an update is done to the route table, a notification is published to the subscriber threads via a callback function invoked via function pointers, along the route table notification chain.

# Structure of route table

| Destination | Mask | Gateway IP | oif | 
| ----------- | ----------- | ----------- | ----------- |
| 122.1.1.1 | 32 | 10.1.1.1 | eth1  |
| 122.1.1.2 | 32 | 10.1.1.2 | eth1  |
| 122.1.1.3 | 32 | 10.1.1.3 | eth1  |

## Compile project

Run the shell script `compile.sh`

```bash
./compile.sh
```

In the directory, there will be files `main.exe`. Run `main.exe` in CLI using `./main.exe`.

## Program walkthrough

- Subscriber threads are created  

```bash
Subscriber 1 created
Subscriber 2 created
Subscriber 3 created
```
- Publisher thread is created

```bash
Publisher thread created
```   
- Subscriber threads are notified of additions to route table via callback function pointer called `test_cb()` and opcode `NFC_ADD`.

```bash
test_cb() client : 2, Notified with opcode NFC_ADD
122.1.1.1            32

test_cb() client : 2, Notified with opcode NFC_ADD
122.1.1.5            32

test_cb() client : 2, Notified with opcode NFC_ADD
122.1.1.6            32

test_cb() client : 3, Notified with opcode NFC_ADD
122.1.1.1            32

test_cb() client : 3, Notified with opcode NFC_ADD
122.1.1.5            32

test_cb() client : 3, Notified with opcode NFC_ADD
122.1.1.6            32

```
- Subscriber threads are notified of updates to route table entries via callback function pointer called `test_cb()` and opcode `NFC_MOD`.

```bash
test_cb() client : 3, Notified with opcode NFC_MOD
122.1.1.1            32   10.1.1.1             eth1

test_cb() client : 2, Notified with opcode NFC_MOD
122.1.1.1            32   10.1.1.1             eth1

test_cb() client : 1, Notified with opcode NFC_MOD
122.1.1.1            32   10.1.1.1             eth1
```

- Publisher Menu

```bash
Publisher Menu
1. Add/Update rt table entry
2. Delete rt table entry
3. Dump rt table
Enter Choice :
```

