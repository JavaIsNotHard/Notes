ring buffer are circular queue, which is a fixed sized buffer that wraps around when it reaches the end

used in producer-consumer type communication where the producer writes new data at the head and consumer reads data from the tail 

Network interface cards (NICs) maintain **TX and RX ring buffers**, which are just specialized FIFO queues for packets

