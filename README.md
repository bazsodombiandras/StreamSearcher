# StreamSearcher

Searches for multiple search terms across multiple large data streams.

#### Problem statement:

Write a program that given as input:
the path of a dictionary file containing 50'000 words or expressions separated by newline
one or more text file paths, - each containing arbitrarily long text (e.g. hundreds of megabytes)
Should display the words from the dictionary contained in each text file.

For example consider the dictionary containing the words: `["apple", "orange", "bear"]` and a text file `file1.txt` containing the text: `The pineapple is tasty. This burden is unbearable.` The program should display: `file1.txt: apple, bear`.

#### Development requirements:
* C++ 17 compatible compiler