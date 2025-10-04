we need this operator to coalesce results from the child operator and wait until they produce the entire output before moving to the next operator. this is basically used as a pipeline breaker which basically stops the execution of the pipeline and doesn't let data flow onto the next operator in the query plan


Variations of exchange operator of types of exchange operator includes:
1. Gather : Combine the results of multiple workers into a single output stream
2. Distribute : Distribute the output stream from previous workers into multiple worker stream in the next stage
3. Repartition : Combination of both gather and distribute where it gathers the input from multiple workers and then partitions them or distributes them based on the some logic to multiple output worker. The input stream is not a one to one mapping to the output stream meaning that if 3 worker produced the input stream then there can be a single or 2 worker that processes the output stream

