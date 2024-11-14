- good locality referes to computer system that references data items that are near other recently referenced data items or were recently referenced themselves. 
- Two distinct types of locality: spatial locality & temporal locality 
- spatial locality, if a memory location is referenced once, then the program is likely to reference a nearby memory location in the near future
- temporal locality, memory location that is referenced once is likely to be reference again in the near future.
- programs that have good locality will run faster than the one that does not have good locality.
- if a function has both good temporal locality and good spatial locality, we can say that a function has good locality


- stride-1 reference pattern (sequential access of memory location one after another)
- stride K reference pattern if the program visits kth element of an contiguous vector. 


```c
int sumarrayrows (int alM] [N])
{
	int i, j, sum = 0;
	for (i = 0; i ‹ M; i++) for (j= 0: j< N; j+t)
		sum += ali][j];
	return sum;
}
```

program 1.1

```c
int sumarraycols (int a[M] [N])
{
	int i, j, sum = 0;
		for (j= 0; j < N; j++) 
			for (i = 0; i ‹ M; i++) 
				sum += a[illj];
	return sum;
}
```

program 1.2

- program 1.1 has good spatial locality but program 1.2 has poor spatial locality. Why?
- vector elements are laid out row-based one after another. Program 1.1 access the element row by row whereas program 1.2 accesses elements column first which accesses not sequentially with respect to how they are laid in the memory.
