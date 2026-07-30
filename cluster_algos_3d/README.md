# cluster_algos_3d

<pre>Currently in use:

_cluster_algo_3d_06_:
    - This is an improved version of number 5 using HLS DATAFLOW.
    - The only functionality it has is assigning cluster IDs to local maxima.
    - Other things that should be added are energy addition, cluster centroid coordinates, and conditions for being considered a cluster.
    - Largely due to the limited functionality, this version is the fastest in terms of interval and latency (~50 and 70 cycles, 340 MHz).

_cluster_algo_3d_07_:
    - This version is equivalent to version 06, but it includes the cluster condition that a cluster must cover at least 4 layers.
    - This version is highly unoptimized and has not been worked with beyond its initial creation.
    - Because of this, version 07 is incredibly slow (~7000 cycles, 340 MHz).
    - This condition is also applied after all clustering is done;
        there may be a much faster way by working the condition into the creation of the clusters themselves.

__

No longer in use: (Although some of these version use ideas that may be useful for new versions.)

_cluster_algo_3d_01_
_cluster_algos_3d_02_
_cluster_algos_3d_03_
_cluster_algo_3d_05_: This version may still be useful. There may be a more efficient way of parallelizing the
                      forwards and backwards propagations than HLS DATAFLOW as implemented in version 06.
