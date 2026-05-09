using the `open()` system call

we pass the `O_CREAT` flag to the `open()` system call

```
int fd = open("foo", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
```

create a new file in the current working directory

O_CREAT : creates the file if it does not exists
O_WRONGLY : lets us write to the file
O_TRUNC : overwrites it to size of zero bytes thus removing all previous content of the file if there was a file previously

the `open()` system call returns a [[file descriptor]]