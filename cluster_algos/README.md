# cluster_algos

<pre>Currently in use:
  
_maxima_tree_cluster_algo_: This takes 48 energy values from one module and
                            outputs the energy local maxima in a boolean array.
    - This algorithm was taken from _parallel_tree_cluster_algo_.
    - This is what is used to find the local maxima in the 3d clustering algorithms.
_parallel_tree_cluster_algo_: This is the 2d clustering algorithm for a single module.

__

No longer in use:
  
_parallel_cluster_algo_: A slightly slower version of _parallel_tree_cluster_algo_.
