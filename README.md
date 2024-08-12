# 2D-Convolution

<h2>Convolution</h2>
Convolution is a concept used in signal and image processing. Convolution can be used to construct the system's output for any input where we know the impulse response.
The two different data structures (i.e. the convolution files convolution1.c and convolution2.c) were implemented to perform the convolution of a 1024x1024 matrix. This report will analyse the memory management and cache-conscious techniques used in both programs and provide a runtime comparison.

<b>Memory Management</b>
In convolution 1, the input data is stored in a matrix (an array of structures). The results from the iterations are also stored in the matrix, where a convolution matrix is produced through every row and column by using 5x5 filters.
Since we are dealing with integers in our results and input data, each data requires 4 bytes cache line, where each cache line has 32/64/128 bytes. Therefore, we can calculate that 8 matrix structures can be loaded into each cache line (64/(4*2)).
‘Struct’ was used to store o_val (original value) and n_val (new value) data. Because the convolution result data and input data are stored in the same matrix struct (i.e. same cache line), the program is fast when updating the input data to produce the convolution results, as no jump between cache lines will take place. Generally, storing matrix struct on a cache line requires double the amount of space; therefore, more jumps are needed to access data from other cache lines. This, in turn, will impact the performance of the convolution1 program, where it takes more time to access and search data on each iteration.
Memory allocation is reserved for a data structure known as "Matrix," which essentially represents an array of pointers. Initially, 1024 pointers are reserved in the memory before the loop commences. Within the loop, each row of the 'data' array is provided with memory allocation, ultimately forming a 1024x1024 matrix. Importantly, during the convolution operation, no additional memory allocation is necessary, as the program leverages the existing memory from the 'data' array to store the results of the operation. This approach ensures that memory allocation is conducted at the program's outset and that memory is properly released at the conclusion of the process using the 'free()' method. This proactive approach to memory management is vital for preventing memory leaks.

In Convolution 1, input data and convolution results are stored in a matrix using a custom data structure. This approach uses a 2D array of structures, where each structure holds the original value (o_val) and the new value (n_val). Because both data and results share the same matrix structure, memory jumps between cache lines are minimised, leading to better program efficiency. However, this approach requires more memory due to the overhead of the data structure.
Convolution 2, on the other hand, uses a simpler approach by storing input data and results in two separate 2D arrays of integers. This approach is more memory-efficient since integers require less space than structures. However, updating the data for the next iteration in Convolution 2 may involve more memory jumps, impacting program performance. In convolution 2, the input data is stored in a matrix of integers. It allocates memory for the input data, the result of each iteration and the output as a 2D integer array. Where again, the results are computed by using a 5x5 filter.
Each integer data requires 4 bytes cache line, where each cache line has 32/64/128 bytes. Here, we can calculate that 16 integers can be loaded into each cache (64/4).
Memory was allocated to store data and rlt. Unlike matrix struct as a datatype, storing integers requires half the amount of space, and therefore, fewer jumps are needed, which in turn, the program convolution2 requires less time to access data.
However, convolution2 is slower when updating the data of the current iteration to gather the convolution results for the next iteration. This is because the 2D array has jumps and different pointers within the same row and column, where they are required to collect data and store it in the input data array whilst switching between the input and output array pointers.

<b>Cache-conscious programmes</b>
To improve cache performance and efficiency, both programs have implemented cache-conscious techniques such as merging arrays and loop interchange.
Merging arrays are used by convolution1 and convolution2 to store input data, and the iteration results in 2D arrays such as data and rlt. It improves cache utilisation by sequentially storing the consecutive elements in memory. This maximises spatial locality.
Loop interchange has also been applied in both convolutions to optimise cache access patterns. The loops are well organised so that neighbouring elements are accessed together, and the innermost loop can iterate through the data for better performance and cache locality.
Convolution1 may have increased cache misses due to different memory locations than convolution2, where fewer cache lines are needed to gather data, as accessing consecutive elements in memory is more efficient.

<b>Runtime comparison</b>
The following Runtimes are for convolution1 using data1.txt, filter1.txt
<img width="391" alt="convolution1" src="https://github.com/user-attachments/assets/41747480-5bd5-4bcc-8182-b52c1b291109">

The following Runtimes are for convolution2 using data1.txt, filter1.txt
<img width="399" alt="convolution2" src="https://github.com/user-attachments/assets/45924f0d-67f0-4685-87f2-5039be8e4376">

Convolution 2 is expected to perform better in terms of execution time.
Convolution 2 uses separate 2D arrays for input data and results. This design allows for more efficient memory access patterns and reduces cache misses, resulting in better performance.
Convolution 2 uses a simpler data structure (integers) compared to the custom structure used in Convolution 1. This simplicity reduces memory overhead and may lead to faster program execution.
Both programs implement cache-conscious techniques, but Convolution 2's memory layout is more cache-friendly due to separate arrays, leading to improved efficiency.
Due to the variation and differences between the two convolutions programs, by comparing the advantages and disadvantages, we can say that convolution2 will perform better than convolution1 in terms of execution time.
