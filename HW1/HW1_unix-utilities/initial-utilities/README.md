
# Unix Utilities

**Before beginning:** Read this [lab tutorial](http://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf); it has some useful tips for programming in the C environment.

In this project, you'll build a few different UNIX utilities, simple versions
of commonly used commands like **cat**, **ls**, etc. We'll call each of them a
slightly different name to avoid confusion; for example, instead of **cat**,
you'll be implementing **wcat** (i.e., "wisconsin" cat).

Objectives:
* Re-familiarize yourself with the C programming language
* Re-familiarize yourself with a shell / terminal / command-line of UNIX
* Learn (as a side effect) how to use a proper code editor such as emacs
* Learn a little about how UNIX utilities are implemented

While the project focuses upon writing simple C programs, you can see from the
above that even that requires a bunch of other previous knowledge, including a
basic idea of what a shell is and how to use the command line on some
UNIX-based systems (e.g., Linux or macOS), how to use an editor such as emacs,
and of course a basic understanding of C programming. If you **do not** have
these skills already, this is not the right place to start.

Summary of what gets turned in:
* A bunch of single .c files for each of the utilities below: **wcat.c**,
  **wgrep.c**, **wzip.c**, and **wunzip.c**.
* Each should compile successfully when compiled with the **-Wall** and
**-Werror** flags.
* Each should (hopefully) pass the tests we supply to you.


For this project, we recommend using the following routines to do file input
and output: **fopen()**, **fgets()**, and **fclose()**. Whenever you use a new
function like this, the first thing you should do is read about it -- how else
will you learn to use it properly?

On UNIX systems, the best way to read about such functions is to use what are
called the **man** pages (short for **manual**). In our HTML/web-driven world,
the man pages feel a bit antiquated, but they are useful and informative and
generally quite easy to use.

To access the man page for **fopen()**, for example, just type the following
at your UNIX shell prompt: 
```
prompt> man fopen
```

Then, read! Reading man pages effectively takes practice; why not start
learning now?

We will also give a simple overview here. The **fopen()** function "opens" a
file, which is a common way in UNIX systems to begin the process of file
access. In this case, opening a file just gives you back a pointer to a
structure of type **FILE**, which can then be passed to other routines to
read, write, etc. 

Here is a typical usage of **fopen()**:

```c
FILE *fp = fopen("main.c", "r");
if (fp == NULL) {
    printf("cannot open file\n");
    exit(1);
}
```



## wzip and wunzip

The next tools you will build come in a pair, because one (**wzip**) is a
file compression tool, and the other (**wunzip**) is a file decompression
tool. 

The type of compression used here is a simple form of compression called
*run-length encoding* (*RLE*). RLE is quite simple: when you encounter **n**
characters of the same type in a row, the compression tool (**wzip**) will
turn that into the number **n** and a single instance of the character.

Thus, if we had a file with the following contents:
```
aaaaaaaaaabbbb
```
the tool would turn it (logically) into:
```
10a4b
```

However, the exact format of the compressed file is quite important; here,
you will write out a 4-byte integer in binary format followed by the single
character in ASCII. Thus, a compressed file will consist of some number of
5-byte entries, each of which is comprised of a 4-byte integer (the run
length) and the single character. 

To write out an integer in binary format (not ASCII), you should use
**fwrite()**. Read the man page for more details. For **wzip**, all
output should be written to standard output (the **stdout** file stream,
which, as with **stdin**, is already open when the program starts running). 

Note that typical usage of the **wzip** tool would thus use shell 
redirection in order to write the compressed output to a file. For example,
to compress the file **file.txt** into a (hopefully smaller) **file.z**,
you would type:

```
prompt> ./wzip file.txt > file.z
```

The "greater than" sign is a UNIX shell redirection; in this case, it ensures
that the output from **wzip** is written to the file **file.z** (instead of
being printed to the screen). You'll learn more about how this works a little
later in the course.

The **wunzip** tool simply does the reverse of the **wzip** tool, taking
in a compressed file and writing (to standard output again) the uncompressed
results. For example, to see the contents of **file.txt**, you would type:

```
prompt> ./wunzip file.z
```

**wunzip** should read in the compressed file (likely using **fread()**)
and print out the uncompressed output to standard output using **printf()**.

**Details**

* Correct invocation should pass one or more files via the command line to the 
  program; if no files are specified, the program should exit with return code
  1 and print "wzip: file1 [file2 ...]" (followed by a newline) or
  "wunzip: file1 [file2 ...]" (followed by a newline) for **wzip** and
  **wunzip** respectively. 
* The format of the compressed file must match the description above exactly
  (a 4-byte integer followed by a character for each run).
* Do note that if multiple files are passed to **wzip*, they are compressed
  into a single compressed output, and when unzipped, will turn into a single
  uncompressed stream of text (thus, the information that multiple files were
  originally input into **wzip** is lost). The same thing holds for
  **wunzip**. 


### Footnotes


<a name="myfootnote1">1</a>: Unfortunately, there is a lot to learn about the
C library, but at some point, you've just got to **read documentation** to
learn what is available. Why not now, when you are young? Or, if you are old,
why not now, before it's ... ahem ... too late?




