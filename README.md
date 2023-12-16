# DataStructures-Lab3-Trees
This lab consisted of three parts focusing on the data structures: AVL-Tree, B-tree and priority queue.

# AVL-TREE

This lab task focuses on implementing deletion operations in AVL trees, specifically in the right sub-tree. The task includes studying AVL tree balancing techniques through rotations (R0, R-1, and R1, similar to LL and LR rotations) and integrating these concepts into a deletion function. The assignment involves modifying the provided AVL tree code to add deletion functionality, using test cases to validate the implementation. The goal is to gain a deep understanding of how AVL trees maintain balance through rotations after node deletions.

# B-TREE
This lab task involves implementing and testing a search operation on B-trees. The assignment includes writing an algorithm to search a B-tree, based on an example provided in the course material. Students are required to create a function in C to implement this search algorithm, extending a previous task's program. The search function should return the node where the key is found or NULL if not found. The deliverables include the pseudocode algorithm and the working source code with the search function, demonstrating its functionality with various test cases.

# Printer
Lab 3 in Data Structures, titled "Printer Simulation 2," involves simulating a laboratory printer using priority queueing. This simulation aims to process printing tasks with the smallest number of pages first. Key components include:

* Initializing the printer as empty.
* Creating a queue for print tasks.
* Implementing a loop that adds new print tasks to the queue and assigns tasks to the printer if it's not busy.
* Each task is processed for one second at a time, with the printer becoming free once a task is completed.

The lab requires the implementation of printer ADT, task ADT, and a priority queue ADT using a min binary heap represented as an array. The heap implementation builds upon the max binary heap concept learned previously. Students must also integrate prior lab implementations into this task. The final output of the program should align with given parameters and produce results similar to an example provided.
