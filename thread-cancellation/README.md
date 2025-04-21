# Thread Cancellation

## Compile program

Using `gnu make`

```bash 
make master_slave_async_cancellation

make master_slave_deferred_cancellation
```

## Run program

```bash 
# for the async cancellation
./master_slave_async_cancellation

----
# for the deferred cancellation

./master_slave_deferred_cancellation
```

You can view the files being written in real time using the commands:  

```bash
tail -f thread_0.txt

tail -f thread_1.txt

tail -f thread_2.txt

tail -f thread_3.txt

tail -f thread_4.txt

```

## Main Menu

```bash
1. Cancel the thread
```
Entering option 1. gives:

```bash
Enter slave thread id [0-4] :
```

On termination, the thread invokes the thread cleanup handlers:

```bash
file_cleanup_handler invoked...
memory_cleanup_handler invoked...
```