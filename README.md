# LS4W
This is just ls from linux. But with a janky implementation :)\
[Link for the file system that I'm using because the one from C++ is big doodoo](https://github.com/gulrak/filesystem)

# Useful information

### Why did I make this?

Out of boredom.

### Can this replace the "dir" command?

No, but you are welcome to use it if you wish to. (BTW, dir is faster).

### Does this include the whole command? Such as: functionality, arguments you can pass, etc.

No, this is limited to the name of the file or directory/folder you are searching for.

The only argument you can pass is: the name (file.txt), extension (\*.txt) and the file that you are searching for, but don't know the extension (file).

# Requirements

- Any C++ compiler


# How do I run it?

## [Cmake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

Create a "build" folder and run 
```bash
cmake -B . -S ..
```

inside the "build" folder

## [Premake5](https://premake.github.io/docs/)

Simply run:

- Windows

```bash
premake5 vs2022
```

- UNIX-like (Linux, Mac, etc.)
```bash
premake5 gmake2
```

