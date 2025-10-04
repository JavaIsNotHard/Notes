similar to [[Iterator Model]] but instead of a single tuple, the entire dataset if possible is returned to the calling operator such that it doesn't have to call the next method on the child operator again

one of the main disadvantage of this model is that if two operators in the same pipeline requires the similar set of data and if the data is large in size then we are passing large data through the pipeline multiple times creating performance issues

we can use operator fusion where we perform the action of two operation into a single one, suppose we have a select and a filter operation in a pipeline then instead of performing them separately and each sending a large set of data to the other what we can do instead is combine both the operation in one