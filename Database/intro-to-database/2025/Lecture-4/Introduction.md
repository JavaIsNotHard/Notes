How database manages its memory and move data back and forth between disk and memory

- spatial control: where to writes pages on disk
	- goal is to keep pages related to each other on disk close to each other as much as possible so that they can be accessed without much disk access seek time

- temporal control: the goal is to maximize the amount of work done for a single page such that we work on the page as much as possible before sending out to the disk