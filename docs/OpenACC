OpenACC

NOTE: All the paths in this file are my installation specific. start using ./startPGI.sh

# Pre-Requisites 
_Hardware_ Nvidia Graphics card
_Software_ gcc Nvidia Graphics driver

# Installation

1 Get the zip from OpenAcc.(2.0) 
2 Enter the necessary details and get the university or student license
3 Open the zip and run ./install
   In my case everything was installed in /opt/pgi/
4 Next thing obviously is to set the path to bin folder
        Now there the tree structure I get is
           /opt/pgi
           ├── linux86-64
           │   ├── 15.10
           │   └── 2015
           └── modulefiles      //TODO find what is this for
               ├── mpich
               ├── pgi
               ├── pgi64
               └── PrgEnv-pgi
        Add the path /opt/pgi/15.10/bin to $PATH
5 After registration at OpenAcc you will get a license key, that will be valid for 3 moths.
   It took 1 day for me to get the license.
6 Once You get the license key place it in file license.dat under /opt/pgi
        Now your tree structure should look like this
            /opt/pgi
            ├── license.dat
            ├── linux86-64
            │   ├── 15.10
            │   └── 2015
            └── modulefiles
                ├── mpich
                ├── pgi
                ├── pgi64
                └── PrgEnv-pgi
# ENV setup
   Use following setup to setup the evironment
   $export PGI=/opt/pgi;
   $export PATH=$PATH:/opt/pgi/linux86-64/15.10/bin;
   $export MANPATH=$MANPATH/opt/pgi/linux86-64/15.10/man;
   $export LM_LICENSE_FILE=$LM_LICENSE_FILE:/opt/pgi/license.dat ;
   I have saved this as startPGI.sh in home folder and every time I need PGI I run this
   script

# Components of PGI group

  • _pgf77_, _pgfortan_ for Fortan
  • _pgcc_ for c programs
  • _pgcpp_ for cpp programs
  • _pgdbg_ for debugger
  • _pgprof_ for profiling


# Prallel programming using the PGI Compilers

   1. Automatic shared memory parallel programs 
      Option: -Mconcur
      These programs run on shared-memory parallel (SMP) systems like dual core and
      multi-processor

   2. OpenMP shared memory parallel programs
      Option: -mp
      Same as above with more speed up*

   3. Distributed compuing using an MPI message-passing library
   4. Accelarated computing using a low-level model such as CUDA Fortan or high-level
      model such as PGI Accelarator to target many core GPU

# Pragma Directives

# Command line options 
  —fast and —fastsse provide a quick route to best performance
  —M set of options provide even more set of options to increase the performance which is
  system and machine dependent
  —tp option is used to target multiple architectures

# Types of optimizations
   • _Local Optimization_
      ◦ Algebraic identity removal
      ◦ Constant folding 
      ◦ Common sub-expression elimination
      ◦ Redundant load and store elimination
      ◦ Scheduling
      ◦ Strength Reduction
      ◦ Peep hole Optimization

   • _Global Optimization_
      ◦ Control flow and data flow analysis
      ◦ Constant propagation
      ◦ Copy propagation
      ◦ Dead store elimination
      ◦ Global register allocation
      ◦ Invariant code motion
      ◦ Induction variable elimination

   • _Loop Optimization_
      ◦ Include use of SSE instructions
   • _Interprocedural Analysis_
   • _Function Inlining_
   • _Profile Feedback Optimization_
      ◦ Use information from previous execution (trace file) to compile optimally
   • Using IPA Inter Procedural Analysis
      ◦ Using compile information to further optimize the builds
# Using PGI and CUDA
   • Use switch -acc and -ta=<target>
   •

## Levels of parallelism
   • An outer do all loop level       (Fully Parallel)
   • An inner synchronous loop level   (SIMD or vector)

# First Program

# Using Profiler
   Generic profiler _pgprof_
   Profiler for Nvidia _Nvprof_
   

# Docs links

## PGI Compiler Users Guide
   Gives the documentation
   [DOC] /opt/pgi/linux86-64/2015/doc/pgi15ug.pdf

## GPU library advisor
   Gives a suggestions if we can use some Nvidia library to accelatare our application
   [DOC] /opt/pgi/linux86-64/2015/OpenACC/doc/GPU_Library_Advisor_Readme.pdf 
   [BINARY] /opt/pgi/linux86•64/2015/OpenACC/bin/gpu-library-advisor
   
