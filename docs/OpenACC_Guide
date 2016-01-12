OpenACC_Guide

# Using Profiling
   use gprof for sequential code
   use nvprof / nvvp for parallel code
   
   set *PGI_ACC_TIME* environment variable
   add a flag *-Mprof=ccff* while compiling


# Pragmas

_kernels_  | tries to analyze for data independence in the loops present in the current
           | block and build kernel for device
           | if no independence then no kernel function is generated
           | works on a code block and tries to parallelize all the loops in the block
           | stores data on the device for the entire block
           | *usage* #pragma acc kernels

_parallel_ | region of code that will be parallelized across OpenACC gangs
           | should be specified before required loop
           | relies on programmer to have correctly identified parallelism
           | *usage* #pragma acc parallel ; use before a loop

_loop_     | gives additional information
           | 1. Correctness
           | 1. _private_
           | Tells the compiler that current loop requires its own copy of the listed variables
           | So, different threads executing will not create race condition
           | loop iterators and variables inside a loop are always private
           | *usage*  private(variable)
           | 2. _reduction_
           | Same as private but also reduces all of the private copies into one final result
           | performs operator on the variable
           | *usage* #pragma acc loop independent reduction(operator:variable)
           | 2. Optimization
           | 1. _gang_
           | 2. _vector_
           | 3. _worker_
           | When used with kernel directive they can have an extra integer, that tells
           | compiler how to partition that level of parallelism.
           | *usage* #pragma acc kernel
           | #pragma acc loop { gang | vector | worker}(integer)
           | When used with parallel
           | These clauses are used with the parallel directive itself rather than on
           | individual loop, with slight modification as
           | *usage* #pragman acc parallel loop { gang | vector | worker } vector_length /
           | num_gangs / num_workers(integer)
           | As these parameters are accelarator dependent we can append one more clause
           | device_type( acc_device_radeon | acc_device_nvidia ) which will be ignored in
           | case of conflicting hardware
           | 4._collapse_
           | Used to collapse two loops into single loop. They provide more scope for
           | parallelism. Also some hardware require longer vectors for higher performance.
           | *usage* #pragma parallel loop { gang | vector | worker } collapse (num_loops)


_routine_  | routine directive gives the compiler the necessary information about the function
           | or subroutine and the loops it contains in order to parallelize the calling
           | parallel region
           | *usage* #pragma acc routine seq
           | In some cases routine may contain parallelism that must be mapped to the
           | device
           | *usage* #pragma acc routine { vector | worker | gang }

_atomic_   | to get around with race conditions
           | Supports following clauses
           | 1. _read_
           | No two iterations will read from the same region
           | 2. _write_
           | No two iterations will write to the same region
           | 3. _update_
           | Combination of booth read and write
           | 4. _capture_
           | Performs an update but saves values calculated in that region to use in the code
           | that follows
           | *usage* #pragma acc atomic update

_data_     | facilitates the sharing of data between multiple parallel regions
           | It is a structured construct i.e should start and end in the same scope
           | Supports following clauses
           | 1. _copy_
           | Create space for listed variable, initialize the variable by copying data
           | from the host. Copy results back to the host at the end of the region and
           | finally release the space on the device
           | 2. _copyin_
           | Create space for listed variable, initialize the variable by copying the data
           | from the host and release the space on the device when done, without copying
           | the data back to host
           | 3. _copyout_
           | Create space for listed variable, without initializing and copy the results
           | back to host and release the space
           | 4. _create_
           | Create space for listed variables but do not copy to or from device
           | 5. _present_
           | The listed variables are already present on the device no acction needs to be
           | taken. When data region exists in a higher-level routine
           | 6. _deviceptr_
           | When listed variables are been managed by devices outside of OpenACC. Used
           | when OpenAcc is mixed with other programming languages
           | NOTE: It also has present_or_* (e.g present_or_copy) which checks whether the
           | variable is already present on the device. Also abbreviated as pcopyin
           | *usage* #pragma acc data pcreate(X)
           | use array shaping to describe the array dimensions. so the above usage can be
           | modified to
           | *usage* #pragma acc data pcreate(X[0:N])
           | With object oriented programs we need to use
           | enter data {create | copyin}
           | exit data {delete | copyout}

_update_   | Provides a way to explicitly update values of the host or device memory with the
           | values of the other
           | Supports following clauses
           | 1. _device_
           | copy data from host to device
           | 2._self_
           | updating data from device to host
           | *usage* #pragma acc update {self | device}(variable[start : end])

_async_    | Once the associated operation has been sent to the device the CPU can do some
           | other work
           | can be used with parallel, kernel, update directives
           | *usage* #pragma acc { parallel | kernel | update } <some_directive> async
           | #pragma acc wait ; wait for all the previously enqueued operations

# Loop optimizations 
NOTE: The more the number of of loop optimizations, the less portable the code is.

## OpenACC’s 3 levels of Parallelsim
 _Gang_ Has a cache, few workers and in turn vectors, Outermost loops
 _Worker_ Has vectors, Intermidiate loops
 _Vector_ They are the innermost loops


# Best Practices
Use following constructs in the code to get more optimized code
const    | to use read-only memory
restrict | to inform about [pointer aliasing]
Update   | to have proper synchronization

 • Sometimes it is beneficial to run small sequential on the accelerators, than to copy data
to the host and operate
 • Always go for data related optimizations first and then for loop optimizations
 • Ensure that the innermost loop of a loop nest iterates on the fastes varying array
   dimension and each successive loop outward access the next fastest varying dimensions
 • 

# MultiGPU
acc_get_device_num()  : query the current device and return the integer identifier of that
                      : device
acc_set_device_num()  : accepts two parameters (device number and device type) once the
                      : number is set all opertaions will be performed on that device
acc_get_device_type() : returns device type of the current device
acc_set_device_type() : specifies which device should be used for acclerator opertaions at
                      : runtime

# References 

Search for:
   OpenACC Specification
   Work Queues

Links:
   http://www.pgroup.com/lit/articles/insider/v4n2a1.htm

                                          * * *


