#! /usr/bin/bash
scp main.c mpiuser12@192.168.237.129:/home/users/mpiuser12/Devoir3 #Node 1
scp main.c mpiuser12@192.168.237.130:/home/users/mpiuser12/Devoir3 #Node 2
scp main.c mpiuser12@192.168.237.131:/home/users/mpiuser12/Devoir3 #Node 3
scp main.c mpiuser12@192.168.237.132:/home/users/mpiuser12/Devoir3 #Node 4
scp main.c mpiuser12@192.168.237.133:/home/users/mpiuser12/Devoir3 #Node 5
scp main.c mpiuser12@192.168.237.134:/home/users/mpiuser12/Devoir3 #Node 6
scp main.c mpiuser12@192.168.237.135:/home/users/mpiuser12/Devoir3 #Node 7
scp main.c mpiuser12@192.168.237.136:/home/users/mpiuser12/Devoir3 #Node 8
scp main.c mpiuser12@192.168.237.137:/home/users/mpiuser12/Devoir3 #Node 9
scp main.c mpiuser12@192.168.237.138:/home/users/mpiuser12/Devoir3 #Node 10
scp main.c mpiuser12@192.168.237.139:/home/users/mpiuser12/Devoir3 #Node 11
scp main.c mpiuser12@192.168.237.140:/home/users/mpiuser12/Devoir3 #Node 12
scp main.c mpiuser12@192.168.237.141:/home/users/mpiuser12/Devoir3 #Node 13
scp main.c mpiuser12@192.168.237.142:/home/users/mpiuser12/Devoir3 #Node 14
scp main.c mpiuser12@192.168.237.143:/home/users/mpiuser12/Devoir3 #Node 15

echo "Compilation working..."

#Compile the code and move it on root
ssh mpiuser12@192.168.237.129 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 1
ssh mpiuser12@192.168.237.130 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 2
ssh mpiuser12@192.168.237.131 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 3
ssh mpiuser12@192.168.237.132 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 4
ssh mpiuser12@192.168.237.133 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 5
ssh mpiuser12@192.168.237.134 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 6
ssh mpiuser12@192.168.237.135 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 7
ssh mpiuser12@192.168.237.136 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 8
ssh mpiuser12@192.168.237.137 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 9
ssh mpiuser12@192.168.237.138 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 10
ssh mpiuser12@192.168.237.139 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 11
ssh mpiuser12@192.168.237.140 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 12
ssh mpiuser12@192.168.237.141 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 13
ssh mpiuser12@192.168.237.142 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 14
ssh mpiuser12@192.168.237.143 "mpicc -lm -o main_mpi ./Devoir3/main.c;" # Node 15

echo "Compilation done."