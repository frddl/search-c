# search.c
Midterm Project on CSCI 3614 - Systems Programming course of ADA University, Fall 2017.
  
# Task
Write a program search that helps you search for files. The program may have different options, but only
a single one at a time. Options, which describe the searching criteria, will be given as command line arguments. By default (10 points), if the program is being run without any command line arguments, it should
recursively list all files and directories (including . and ..) in the current directory, in any order, by simply
writing their names on separate lines.  

Options are going to refine the search by adding some criteria, but the output format of the program should
remain same in all cases (just full names of files on separate lines):  
```
-N NAME - search recursively for files with name containing given string. (10 points)  
– NAME is a simple string without any space characters that filename should contain.

-L - search recursively for symbolic links. (10 points)  

-U USERNAME - search recursively for files that belong to the given user. (10 points)  
– USERNAME is a valid linux user name.

-G GROUPNAME - search recursively for files that belong to the given group. (10 points)  
– GROUPNAME is a valid linux group name.

-S CMP SIZE - search recursively for files by size. (20 points)  
– CMP stands for compare option and can be L for less, E for equal or G for greater.
– SIZE is a non-negative integer number.

-W WORD - search recursively for files containing given string. (30 points)  
– WORD is a simple string without any space characters that a file should contain.
```

# Examples
```
./search: should recursively search for all files and directories, beginning from the current directory.
./search -N txt: should recursively search for files and directories with name containing the string
”txt”.
./search -U root: should recursively search for all files and directories belonging to the ”root” user.
./search -G mygroup: should recursively search for all files and directories belonging to the ”mygroup” group.
./search -L: should recursively list all files of the type ”symbolic link”.
./search -S L 5000: should recursively search for files (also non-regular files, but excluding directories) with size less than 5000 bytes.
./search -S E 512: should recursively search for files (also non-regular files, but excluding directories) with size equal to 512 bytes.
./search -S G 10000: should recursively search for files (also non-regular files, but excluding directories) with size greater than 10000 bytes.
./search -W hello: should recursively search for all files (also non-regular files, but excluding directories) containing the word ”hello” at least once.
```

# Bonus
You can receive extra 20 points if you have implemented at least three different options and any combination
of these is accepted by your program (the order should not be important). Example: ./search -S G 10
-W hello -U root - should recursively search for all files (excluding directories, including non-regular files,
such as symbolic links) of size greater than 10 bytes, containing the word ”hello” and that belong to user
”root”.

