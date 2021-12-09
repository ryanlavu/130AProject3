	1. Every input file is associated with the corresponding output file(the names
are similar)
	2. When reading the edge list, you need to insert the newly discovered vertices to
the AVL tree. In case that both of the vertices of edge (x,y) do not exist in the AVL tree,
you should first insert x into the AVL tree, rebalance it if necessary and 
then insert y. (priority from left to right)
	3. Before printing the elements of a component in the graph, sort them in 
non-decreasing order. This would be also helpful for you to compare 
your results with sample output.


Feel free to contact me at jaber@ucsb.edu regarding the issues of Project3 
and input/output file. 
