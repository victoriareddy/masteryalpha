# cs429-mastery-assignment
## [IMPORTANT] After you SSH into a lab machine: Note that
- **ALL git commands must be in the command line.**
- **ALL gdb debugging must be in the command line.**
- **ALL file system actions (eg. creating a file, navigating a file, etc) must be in the command line**

You are allowed to utilize the terminal of your choice for these actions, but they must be accomplished in-terminal.

*Note: SSHing and opening *this* repo via VS Code or another GUI is acceptable provided that the above actions are then accomplished via a terminal therein.*

# What this repo contains:
- `trie.c` and its corresponding header files.
- A Makefile
- Some testcases in the `testcases` folder
- a reference executable called `trie_ref`

# What this code does:
The given code is the main workings of a autocomplete suggestion feature using a trie as the dictionary. insertions will
be represented in the test files as `a <word>` and prefixes to search for completion suggestions will be represented by
`f <prefix>` the insert function inserts new words into the trie. the autocomplete function traverses the trie and 
prints all words that have the given prefix. Unfortunately this implementation of trie.c is broken. If you dont know what
a trie is, refer to the bottom of the readme.

To run an individual testcase use
`bin/second_trie -w <file>`. Use `trie_ref -w <file>` for the reference output.

# Instructions:
1. ssh into your favorite UTCS lab machine
2. Clone this repository
3. Read then use the Makefile
4. Debug the test cases using gdb; you must use gdb to pass this mastery assessment.
5. To the best of your ability, ensure your output matches the reference exactly.
6. Write the outputs of the `history` command to a file in this repo called `shell_logs.txt`
7. Commit and push your changes. Do not forget to add `shell_logs.txt` to git.
8. Delete your local copy of this repository (you will need to use the r and f flags). If this results in any errors, please notify your proctor before leaving the room.
9. Please do not leave before your proctors tell you to do so. 


A trie is a fat tree that represents a dictionary of all words, each node in the trie represents a letter.
The root node represents a blank string. To check if a word exists in a trie, simply traverse downwards and index into
the trie's children list using the ascii character, keeping track of each character used. Trie's store a flag that mark
whether or not the current node marks the end of a word. The end of a word does not mean that a node has no more children.
Consider the word `apple`, it can still have an `s` child as `apples` is also a word. A trie's children are all null if no
other words can be made with the current prefix. below is an example of a trie, each node is represented by a letter and
a boolean eg a(0) is the letter a and not a word.
```
           a(1)   a(0) - t(1)
        /       /
root()  - b(0) - y(1)
        \
          h(0) - i(1) - p(1)
            \
              a(0) - t(1)
```
therefore the trie contains the words a, bat, by, hi, hip, hat. while the trie contains paths to b, h, ha, and ba, 
these are not valid words in the trie.
