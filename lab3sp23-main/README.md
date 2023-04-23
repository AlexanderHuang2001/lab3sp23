# Lab 3: TeraSort -- Final Project

In this lab, your task is to implement a distributed sorting algorithm along the lines discussed in the lesson videos.  You will be writing your program using the Chapel programming language. Please see the [official Chapel 1.27.0 documentation](https://chapel-lang.org/docs/1.27/index.html) as a starting point for answering language questions.  Your algorithm design should be based on the assumption that the data will *not* fit in the physical memory of any one computer in your cluster but that it *will* fit in the union of all the physical memories.  This assumption makes your task slightly different from classical [distributed disk sorting benchmarks](http://sortbenchmark.org/), but many of the same principles apply.

## Getting Started
Begin by obtaining the starter code from the github repository.

<pre><code>
    git clone https://github.gatech.edu/omscse6220/lab3sp23.git
</code></pre>

Note that this is the [GT github server](https://github.gatech.edu), so you will need to authenticate with your GT credentials.

Optionally, you may choose use a git hosting service for your code.  As always, please **do not make your repository public** on Github or another git hosting service.  Anyone will be able to see it.  If you feel the need to use a hosting service for your project, please keep your repository private.  Your GT account allows you to create free private repositories on [the GT github server](https://github.gatech.edu).

The Chapel documentation provides an [excellent tutorial resource](https://chapel-lang.org/docs/1.27/primers/learnChapelInYMinutes.html) to get up to speed on using the language. We **strongly recommend** working through this tutorial. Many of the features of the language will not be required to complete this project, since tasks like distributing the data across the locales have already been implemented for you.

## Programming
The data type you will sorting is similar to the one used in [Hadoop's Terasort benchmark](https://hadoop.apache.org/docs/current/api/org/apache/hadoop/examples/terasort/package-summary.html#package_description).  It consists of a 10-byte key and an 88-byte value.  Procedures for input/output and comparison of these records are provided for you in the **terarec.chpl** file in the *utils* directory.  Your only task is to complete the implementation of the terasort function, which has the signature

<pre><code>
proc terasort(ref keys, ref values, ref keys_out, ref values_out, ref counts_out)
</code></pre>

Here, keys and values are the data initially stored in memory as 2D arrays distributed across the participating Locales.  The remaining parameters are for return values.  The arrays keys_out and values_out reference allocated space in which to store each node's sorted keys and values within the whole.  Because space has been provided to you, the counts_out array stores the number of logical records (key-value pairs) which are local to each Locale. Thus, the data returned to Locale's slice of keys_out and values_out represents the sorted sequence with length counts_out[here.id].

This function can be found in **terasort.chpl** in the *student* directory. An example of the function's usage can be found in the **terasort_main.chpl** in *utils*.

Your code is expected to work with up to 8 nodes and 8 cores per node.

**Note** that Chapel does provide a parallel Radix sort. The data types we have provided do not work with this sort out of the box, but if you can find a way to use it in your code you are free to do so.Nonetheless, any attempt to repackage the data to use the built-in parallel sort as your *entire* sorting algorithm will result in a score of 0 on this assignment.

## First-Time Cluster Setup ##

Chapel spawns runtimes on the nodes allocated to your PACE job by using passwordless ssh to quickly open up connections to the other nodes. Before running your first Chapel programs on PACE, please run the following command to allow Chapel to open ssh sessions inside PACE:

<pre><code>
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
</code></pre>

Passwordless SSH also requires that both your home directory and your .ssh directory have appropriately restrictive access permissions. If you're still having trouble with running distributed jobs on PACE after doing passwordless SSH setup, you may need to verify that your permissions are not too open.

## Testing Your Code and Measuring Performance
Performance tests will be a large part of your evaluation. You are encouraged share your ideas and results on the discussion forum.

The programs to generate and validate the unsorted and sorted data, respectively, are provided in C source files, to be executed with MPI as detailed below. The concept of a Locale in Chapel is distinct from the concept of a Process in MPI. You may always assume that the number of Locales evenly divides the number of records to be sorted. This also means that you can use the same number of MPI processes to validate your output as Locales used to generate it.

An example how to check the correctness of your code locally on 10,000 records per locale would be:
<pre><code>
$ make clean
$ make all
$ ./teragen -c 40000
$ ./terasort -nl 4
$ mpirun -np 4 ./teravalidate
</code></pre>

We've also included the *terametrics* utility to assist with performance testing:
<pre><code>
$ make clean
$ make teragen terametrics
$ ./teragen -c 40000
$ ./terametrics -nl 4
</code></pre>

The following OpenPBS jobs and interactive sessions are provided for your testing and development on the cluster:

* metrics.pbs (multiple nodes and cores - 8x8)
* correctness.pbs (runs ./grader.sh from within a PBS job on an 8x4 allocation)
* pace_interactive.sh (gives an interactive session for manual running of jobs and examining of output.)
  * *Remember* to `source pace_env.sh` from the project directory once you have entered the interactive session.

To ensure fair allocation of resources among students, we ask that you limit the usage of any number of nodes greater than 4 to PBS jobs *only*. You are free to create your own PBS jobs to test other combinations of node and core count, and may use metrics.pbs and correctness.pbs as references for these jobs.

You can get the usage of every generated executable file (e.g. teragen, terasort, teravalidate, terametrics) by running `./tera[xx] -h`.

## Submission

Lab submissions for this class will be through Canvas under the appropriate assignment.

The file you need to submit for this lab is:

```sh
   terasort.chpl
```
This file should exist in the **student** directory of your lab folder.

Do **not** submit or modify any other files.

## Grading

Your grade on this lab will consist of the following:

* Successful compilation
* Provided test cases
* Additonal test cases
* Performance score

The point totals of each are listed in the forum announcement post.
