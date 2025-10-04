[[pipeline edges]]

if we want to compute two operators in a pipeline then we need to execute them concurrently such that one operators produces and in the mean time some other operator consumes the data

pipeline stages are executed on at a time but all the operators inside a pipeline stage are execute concurrently