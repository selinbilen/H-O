# H-O
Imagine that threads represent atoms and that two kinds of atoms, oxygen and hydrogen. In order to assemble these threads into water molecules, we have to create a barrier that makes each thread wait until a complete molecule is ready to proceed. As each thread passes the barrier, it should invoke bond. You must guarantee that all the threads from one molecule invoke bond before any of the threads from the next molecule do. If an oxygen thread arrives at the barrier when no hydrogen threads are present, it has to wait for two hydrogen threads. If a hydrogen thread arrives at the barrier when no other threads are present, it has to wait for an oxygen thread and another hydrogen thread.

Program Input
Program inputs are the number of oxygen atoms(n) and the number of hydrogen atoms(m). These inputs should be received as a command line argument. To evaluate your programs, multiple options will be used.
./yourprogram n m
Example command: ./yourprogram 5 6
