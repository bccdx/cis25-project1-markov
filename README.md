# Project: Markov Chain Text Generator

## Step-by-Step Instructions

## Overview

In this project, you will build a program that reads text from a file, learns the patterns of which words follow which, and then generates new text based on those patterns. This technique is called a Markov chain.

Your program will ask the user for three things: the name of the input file, the "order" of the Markov chain, and the number of words to generate.

## What is a Markov Chain?

A Markov chain is a system that predicts what comes next by looking only at what just happened. For text, this means: given the current word (or words), what word is likely to follow?
The idea is to analyze real text and record patterns. If we read a whole book, we can count how often each word follows each other word. Then we use those patterns to generate new text that "sounds like" the original.

## Worked Example: Building a Markov Chain (Order 1)

Let's say our training text is this paragraph from a children's story:
"The cat sat on the mat. The cat saw the dog. The dog ran away. The cat sat down."
We scan through this text word by word and record what follows each word. We store this as pairs: a "prefix" (the current word) and a "suffix" (the word that came after it). With order 1, each prefix is a single word.

```
Position 1:  prefix = "The"    suffix = "cat"
Position 2:  prefix = "cat"    suffix = "sat"
Position 3:  prefix = "sat"    suffix = "on"
Position 4:  prefix = "on"     suffix = "the"
Position 5:  prefix = "the"    suffix = "mat."
Position 6:  prefix = "mat."   suffix = "The"
Position 7:  prefix = "The"    suffix = "cat"
Position 8:  prefix = "cat"    suffix = "saw"
Position 9:  prefix = "saw"    suffix = "the"
Position 10: prefix = "the"    suffix = "dog."
Position 11: prefix = "dog."   suffix = "The"
Position 12: prefix = "The"    suffix = "dog"
Position 13: prefix = "dog"    suffix = "ran"
Position 14: prefix = "ran"    suffix = "away."
Position 15: prefix = "away."  suffix = "The"
Position 16: prefix = "The"    suffix = "cat"
Position 17: prefix = "cat"    suffix = "sat"
Position 18: prefix = "sat"    suffix = "down."
```

Notice that we store every occurrence, including duplicates. Let's group them to see the patterns:
"The" → ["cat", "cat", "dog", "cat"] (75% chance of "cat", 25% chance of "dog")
"cat" → ["sat", "saw", "sat"] (67% chance of "sat", 33% chance of "saw")
"sat" → ["on", "down."] (50/50)
"the" → ["mat.", "dog."] (50/50)

The duplicates are what give us probability! When we randomly pick from "The"'s list, we're 3x more likely to get "cat" than "dog" because "cat" appears 3 times.
Generating Text from the Chain

To generate new text, we "walk" the chain:

1. Start with a word, say "The".
2. Find all entries where prefix = "The". We have four: ["cat", "cat", "dog", "cat"].
3. Randomly pick one. Let's say we get "cat" (75% likely).
4. Now our current word is "cat". Find all entries where prefix = "cat": ["sat", "saw", "sat"].
5. Randomly pick one. Let's say we get "saw" (33% likely).
6. Now our current word is "saw". Find entries: ["the"].
7. Only one choice, so we get "the".
8. Now look up "the": ["mat.", "dog."]. Say we pick "dog."
9. Continue until we've generated enough words...

### Possible generated output: "The cat saw the dog. The cat sat down."

This exact sentence was never in our original text, but it sounds like it could have been! The Markov chain captured the "flavor" and vocabulary of the original while creating something new.

### Understanding the "Order" Parameter

The order (also called "prefix length" or "state size") controls how many words the chain looks at when predicting the next word.

### Order 1:

The chain looks at only the previous 1 word to decide what comes next.
Example: If the current word is "the", we look up all words that ever followed "the" in our training text.
Result: More random and chaotic output. Grammatically awkward but very "creative."

### Order 2:

The chain looks at the previous 2 words together.
Example: If the current words are "the cat", we look up all words that ever followed "the cat" together.
Result: Good balance of novelty and coherence. This is the most commonly used order.

### Order 3 or higher:

The chain looks at 3+ previous words.

### Example:

If the current words are "the cat sat", we look up what followed that exact phrase.

### Result:

Very coherent output, but often just reproduces chunks of the original text verbatim.

### The tradeoff:

Lower order = more random. Higher order = more similar to the original. For this project, your program should support orders 1, 2, and 3.

### Worked Example: Order 1 vs Order 2

Let's see how order affects the chain with a longer text. Consider this training text:

```
"I went to the store. I went to the park. I walked to the store. She went to the movies."
With Order 1 (single-word prefixes):
Key entries from the chain:
"I" → ["went", "went", "walked"]
"went" → ["to", "to", "to"]
"to" → ["the", "the", "the", "the"]
"the" → ["store.", "park.", "store.", "movies."]
"walked" → ["to"]
With order 1, the chain loses important context. Notice that "the" can lead to "store.", "park.", or "movies." – but the chain doesn't remember WHO went or HOW they got there. We might generate:
```

### Possible output:

```
"She walked to the park. I went to the movies."
```

This is grammatically fine, but notice "She walked to the park" and "I went to the movies" never appeared in the original! The chain mixes and matches freely because it only looks at one word at a time.

### With Order 2 (two-word prefixes):

Now each prefix is TWO words joined together:

```
"I went" → ["to", "to"]
"went to" → ["the", "the", "the"]
"to the" → ["store.", "park.", "store.", "movies."]
"I walked" → ["to"]
"walked to" → ["the"]
"She went" → ["to"]
"the store." → ["I", "She"]
"the park." → ["I"]
```

Now the chain remembers more context. "I went" leads to "to", and "She went" also leads to "to" – they're tracked separately even though they both contain "went". The phrase "to the" can still lead to multiple places, giving us variety, but only in combinations that appeared in the original.

### Possible output:

```
"I went to the park. I walked to the store. She went to the movies."
```

This output rearranges the original sentences but doesn't create impossible combinations like "She walked" (which never appeared). Order 2 preserves more of the original structure while still allowing creative recombination.

#### The key insight:

Higher order = more context = more coherent but less creative. Lower order = less context = more creative but potentially nonsensical. For most text, order 2 hits a sweet spot.

### What is a Header File?

A header file (ending in .h) is a file that contains declarations – it tells the compiler "these functions exist" without providing the actual code. Think of it as a menu at a restaurant: it lists what's available, but doesn't include the recipes.
When you write a program across multiple .cpp files, the compiler processes each file separately. If main.cpp wants to call a function defined in markov.cpp, the compiler needs to know that function exists – what it's called, what parameters it takes, and what it returns. The header file provides this information.
What are Include Guards?

Sometimes a header file might accidentally get included more than once (for example, if file A includes file B, and file B includes file C, and file C includes file A again). This can cause errors because the compiler sees the same declarations twice.
Include guards prevent this problem. They're a pattern that looks like this:

```cpp
#ifndef MARKOV_H
#define MARKOV_H

// Your declarations go here

#endif
```

### Here's how it works:

- #ifndef MARKOV_H means "if MARKOV_H is NOT defined, continue."
- #define MARKOV_H defines MARKOV_H so it now exists.
- #endif marks the end of the conditional section.

The first time the header is included, MARKOV_H isn't defined, so the compiler processes everything between #ifndef and #endif. It also defines MARKOV_H. If the header gets included again, MARKOV_H is already defined, so the compiler skips everything – preventing duplicate declarations.

The name (MARKOV_H) can be anything, but by convention we use the filename in ALL_CAPS with underscores. Always include guards in every header file you write!

## Required File Structure

Your project must be organized into three files:

- main.cpp – Contains main(), handles user input/output, and calls your Markov functions.
- markov.h – Contains function signatures (declarations) and any constants.
- markov.cpp – Contains the function definitions (implementations).

Compile with: g++ main.cpp markov.cpp -o markov
Required Functions
Your markov.h file must declare the following functions. Put these signatures in your header file, then implement them in markov.cpp.

## Function 1: joinWords (helper)

```cpp
std::string joinWords(const std::string words[], int startIndex, int count);
```

### What it does:

This helper function takes several words from an array and glues them together into one string with spaces between them. You'll use this to create prefixes when order > 1.

### Parameters explained:

- words[] – The array of words to pull from.
- startIndex – Which position to start from.
- count – How many words to join together.

### Returns:

A single string with the words joined by spaces.

### How to implement it:

1. Create an empty result string.
2. Loop from i = 0 to count - 1:
   - Add words[startIndex + i] to result
   - If this isn't the last word, also add a space
3. Return result.

### Example:

```
If words = ["the", "cat", "sat", "down"]
joinWords(words, 0, 2) returns "the cat"
joinWords(words, 1, 2) returns "cat sat"
joinWords(words, 1, 3) returns "cat sat down"
```

## Function 2: readWordsFromFile

```cpp
int readWordsFromFile(std::string filename, std::string words[], int maxWords);
```

### What it does:

This function opens a text file and reads every word from it into an array. Think of it like pouring all the words from a book into a bucket (the array).

### Parameters explained:

- filename – The name of the file to read (like "alice.txt").
- words[] – An empty array that you will fill with words from the file.
- maxWords – The maximum number of words the array can hold. Stop reading if you hit this limit.

### Returns:

The number of words you actually read. If the file couldn't be opened, return -1.

### How to implement it:

1. Create an ifstream object and open the file.
2. Check if the file opened. If not, return -1.
   - If your ifstream object is called inputFile, you can use inputFile.is_open() to get a bool that will be true if the file is open and false if not
3. Create a counter variable, set it to 0.
4. Use a while loop: while (counter < maxWords && inFile >> words[counter])
5. Inside the loop, just increment the counter.
6. After the loop, close the file.
7. Return the counter.

## Function 3: buildMarkovChain

```cpp
int buildMarkovChain(const std::string words[], int numWords, int order, std::string prefixes[], std::string suffixes[], int maxChainSize);
```

### What it does:

This function scans through all the words and records "what comes after what." It's like making flashcards: on the front of each card you write a word (or words), and on the back you write the word that came after it.

### Parameters explained:

- words[] – The array of words you read from the file (from Function 1).
- numWords – How many words are in that array.
- order – How many words to use as the prefix. Order 1 means one word, order 2 means two words joined together.
- prefixes[] – An empty array where you'll store the "front of the flashcard" (the word or words before).
- suffixes[] – An empty array where you'll store the "back of the flashcard" (the word that came after).
- maxChainSize – Maximum number of entries the arrays can hold.

### Returns:

The number of prefix-suffix pairs you added.

> Important: You WILL have duplicates, and that's good! If "the" is followed by "cat" twice and "dog" once, you'll have three entries. This is how we track probability.

### How to implement it:

1. Create a counter variable called count, set it to 0.
2. Loop with i from 0 to (numWords - order - 1). Why? Because we need
   'order' words for the prefix PLUS one more word for the suffix.
3. Inside the loop:
   - Create the prefix by calling joinWords(words, i, order)
   - The suffix is simply words[i + order]
   - Store: prefixes[count] = prefix; suffixes[count] = suffix;
   - Increment count
   - If count reaches maxChainSize, break out of the loop
4. Return count.

### Example with order = 1:

```
If words = ["the", "cat", "sat"], then:
i=0: prefix = "the", suffix = "cat"
i=1: prefix = "cat", suffix = "sat"
Example with order = 2:
If words = ["the", "cat", "sat", "down"], then:
i=0: prefix = "the cat", suffix = "sat"
i=1: prefix = "cat sat", suffix = "down"
```

## Function 4: getRandomSuffix

```cpp
std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[], int chainSize, std::string currentPrefix);
```

### What it does:

Given a prefix like "the cat", this function finds ALL the entries in the chain that have that prefix, then randomly picks one of the corresponding suffixes. It's like flipping through your flashcards, finding all the ones with "the cat" on the front, and randomly picking one to see what's on the back.

### Parameters explained:

- prefixes[] – The array of prefixes from buildMarkovChain.
- suffixes[] – The array of suffixes from buildMarkovChain.
- chainSize – How many entries are in the chain.
- currentPrefix – The prefix to look up (like "the" or "the cat").

### Returns:

A randomly chosen suffix. If the prefix isn't found anywhere, return an empty string "".

### How to implement it:

1. First, count how many times currentPrefix appears in the prefixes array.
   Loop through prefixes[0] to prefixes[chainSize-1].
   If prefixes[i] == currentPrefix, increment a matchCount.
2. If matchCount is 0, return "" (empty string - prefix not found).
3. Pick a random number: int pick = rand() % matchCount;
   This gives you a number from 0 to matchCount-1.
4. Loop through the prefixes array again. Keep a counter for matches.
   When you find the 'pick'-th match, return the corresponding suffix.
5. If somehow nothing was found, return "".

### Example:

```
If prefixes = ["the", "cat", "the", "the"] and suffixes = ["cat", "sat", "dog", "bird"]
And we call getRandomSuffix with currentPrefix = "the":
```

- We find "the" at positions 0, 2, 3 → matchCount = 3
- pick = rand() % 3 might give us 0, 1, or 2
- We return suffixes[0], suffixes[2], or suffixes[3] → "cat", "dog", or "bird"

## Function 5: getRandomPrefix

```cpp
std::string getRandomPrefix(const std::string prefixes[], int chainSize);
```

### What it does:

This function just picks a random prefix from your chain to use as the starting point for text generation. It's like closing your eyes and pointing at a random flashcard to start with.

### Parameters explained:

- prefixes[] – The array of prefixes.
- chainSize – How many entries are in the chain.

### Returns:

A randomly selected prefix string.

### How to implement it:

1. Generate a random index: int index = rand() % chainSize;
2. Return prefixes[index];
   That's it! This is the easiest function.

## Function 6: generateText

```cpp
std::string generateText(const std::string prefixes[], const std::string suffixes[],
int chainSize, int order, int numWords);
```

### What it does:

This is the fun one! It "walks" the Markov chain to generate new text. It picks a random starting point, then keeps asking "what word comes next?" over and over, building up a sentence word by word.

### Parameters explained:

- prefixes[] – The array of prefixes.
- suffixes[] – The array of suffixes.
- chainSize – How many entries are in the chain.
- order – The chain order (1, 2, or 3). You need this to know how to update the prefix.
- numWords – How many words to generate.

### Returns:

A string containing all the generated text.

### How to implement it:

1. Call getRandomPrefix to get a starting prefix.
2. Start your result string with this prefix.
3. Store the current prefix in a variable (you'll update this each step).
4. Loop numWords times:
   - Call getRandomSuffix with your current prefix.
   - If it returns "" (empty), break out of the loop (dead end).
   - Add a space and the new word to your result string.
   - Update currentPrefix (see below).
5. Return the result string.

### How to update the prefix:

For order 1: The new prefix is just the new word. Easy!

currentPrefix = newWord;

For order 2 or 3: You need to drop the first word and add the new word. The easiest way is to keep an array of the last N words, update it each step, then use joinWords to rebuild the prefix string.

### Example walkthrough (order 1):

```
Starting prefix: "The"
result = "The"
Loop iteration 1: getRandomSuffix("The") returns "cat"
result = "The cat", currentPrefix = "cat"
Loop iteration 2: getRandomSuffix("cat") returns "sat"
result = "The cat sat", currentPrefix = "sat"
...and so on until you've generated numWords words.
```

## Git Commands Reference

You are required to use git to track your progress. Here are the essential commands you'll need:
Setting Up (only if not using Codespaces)
If you're using Codespaces, your repository is already set up – skip this section. If you're working locally, you'll need one of these commands to get started:

```
git init
```

Creates a new git repository in your current folder.

```
git clone <repository-url>
```

Downloads an existing repository from GitHub to your computer.

Checking Status

```
git status
```

Shows which files have been modified, which are staged for commit, and which are untracked. Run this often to see what's going on!

Staging Files

```
git add <filename>
```

Stages a specific file to be included in the next commit.

```
git add .
```

Stages ALL modified and new files. Use with caution – make sure you're not adding files you don't want!

Committing Changes

```
git commit -m "Your commit message here"
```

Saves your staged changes with a descriptive message. Write messages that describe WHAT you did, like "Implemented file reading function" or "Fixed bug in text generation".

Pushing to GitHub

```
git push
```

Uploads your commits to GitHub (or another remote repository). Your code isn't backed up until you push!

If this is your first push to a new repository, you may need:

```
git push -u origin main
```

### Typical Workflow

After completing a piece of work:

```
git status # See what changed
git add main.cpp markov.cpp markov.h # Stage the files
git commit -m "Implemented buildMarkovChain"
git push # Upload to GitHub
```

## Step-by-Step Implementation Guide

Follow these steps in order. The detailed instructions for each function are in the "Required Functions" section above – refer back to them as you implement! Complete and test each step before moving on. Make a git commit after each step.

## Step 1: Set Up Your Files

Create your three files:
markov.h – Add include guards and copy all six function signatures from above.
markov.cpp – Add #include "markov.h" and create empty function bodies that just return 0 or "".
main.cpp – Add #include "markov.h" and a main() that prints "Hello".

### Test:

```
g++ main.cpp markov.cpp -o markov
./markov
```

If it prints "Hello" with no errors, you're ready!

> ✓ Git commit. Run these commands:

```
git status
git add .
git commit -m "Set up project file structure"
git push
```

## Step 2: Implement joinWords

Start with this easy helper function. Follow the implementation guide in Function 6 above.

### Test:

In main(), create a small array of words and call joinWords with different parameters:

```cpp
std::string testWords[] = {"the", "cat", "sat", "down"};
std::cout << joinWords(testWords, 0, 2) << std::endl; // Should print: the cat
std::cout << joinWords(testWords, 1, 3) << std::endl; // Should print: cat sat down
```

> ✓ Git commit: "Implemented joinWords"

## Step 3: Implement readWordsFromFile

Follow the implementation guide in Function 1 above.

> NOTE: If your ifstream object is called inputFile, you can use inputFile.is_open() to get a bool that will be true if the file is open and false if not

### Test

Create a small test file (like "test.txt") with a few sentences. Then in main():

```cpp
std::string words[1000];
int count = readWordsFromFile("test.txt", words, 1000);
std::cout << "Read " << count << " words" << std::endl;
for (int i = 0; i < 10 && i < count; i++) {
	std::cout << words[i] << std::endl;
}
```

> ✓ Git commit: "Implemented readWordsFromFile"

## Step 4: Implement buildMarkovChain

This is the trickiest function. Follow the implementation guide in Function 2 above carefully!

### Test:

Build a chain and print the first 20 pairs to see if they look right:

```cpp
std::string prefixes[10000], suffixes[10000];
int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 10000);
for (int i = 0; i < 20 && i < chainSize; i++) {
std::cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << std::endl;
}
```

Try with order 1 first, then test with order 2. The prefixes should be two words joined with a space.

> ✓ Git commit: "Implemented buildMarkovChain"

## Step 5: Implement getRandomSuffix

Follow the implementation guide in Function 3 above.

### Test:

Pick a prefix you saw in your chain printout. Call getRandomSuffix 10 times:

```cpp
for (int i = 0; i < 10; i++) {
   std::cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << std::endl;
}
```

You should see different suffixes appear. If "the" is followed by "cat" twice and "dog" once in your text, you should see "cat" roughly twice as often as "dog".

✓ Git commit: "Implemented getRandomSuffix"

## Step 6: Implement getRandomPrefix

This is the easiest function – just two lines! See Function 4 above.

### Test:

for (int i = 0; i < 5; i++) {
std::cout << getRandomPrefix(prefixes, chainSize) << std::endl;
}
You should see different prefixes each time.

> ✓ Git commit: "Implemented getRandomPrefix"

## Step 7: Implement generateText

This is the fun one! Follow the implementation guide in Function 5 above.

### Test:

std::string output = generateText(prefixes, suffixes, chainSize, 1, 20);
std::cout << output << std::endl;
Run it several times – you should get different output each time!

> ✓ Git commit: "Implemented generateText"

## Step 8: Complete main()

Now put it all together! Your main() should:

1. Add srand(time(0)); at the very beginning (for randomness).
2. Ask the user for the filename, order, and number of words.
3. Declare your arrays (make them big – 100000 is good for books).
4. Call readWordsFromFile.
5. Call buildMarkovChain.
6. Call generateText.
7. Print the result.

> ✓ Git commit: "Completed main program"

## Step 9: Test and Polish

15. Test with different files. Try downloading a book from Project Gutenberg (gutenberg.org)!
16. Test with orders 1, 2, and 3. Notice how the output changes.
17. Add error handling: What if the file doesn't exist? What if the chain is empty?

> ✓ Git commit: "Final polish"

### Tips and Hints

#### Array sizes:

Use large arrays. A typical book has 50,000-100,000 words. Declare arrays like: std::string words[100000]; and std::string prefixes[100000];

#### Random numbers:

Include <cstdlib> and <ctime>. Call srand(time(0)) once at the start of main(). Use rand() % n to get a random number from 0 to n-1.

#### String comparison:

You can compare strings directly with ==. For example: if (prefixes[i] == currentPrefix)

#### Updating the prefix:

For order 2+, the trickiest part is updating the prefix. One approach: keep an array of the last N words (where N = order), and use joinWords to rebuild the prefix string after each step.

### Sample Program Output

```
Enter input filename: alice.txt
Enter order (1, 2, or 3): 2
Enter number of words to generate: 30
```

#### Generated text:

The Queen said to Alice in a great hurry to change the subject of conversation. Are you fond of cats said the Caterpillar sternly. Explain yourself!

## Requirements Checklist

- Project uses three files: main.cpp, markov.h, markov.cpp
- Header file has proper include guards
- All six required functions are implemented
- Program compiles with g++ main.cpp markov.cpp -o markov
- Program reads from any user-specified text file
- Program supports order 1, 2, and 3
- Program generates the requested number of words
- Output is different on different runs (randomness works)
- Git repository has multiple meaningful commits

## How to Submit

When you have completed the project:

1. Make sure all your changes have been committed and pushed to GitHub.
2. Go to your repository on GitHub.
3. Copy the URL from your browser's address bar. It should look something like:
   https://github.com/yourusername/your-repo-name
4. Go to Canvas and find this assignment.
5. Paste the link to your repository and submit.
   Important: Make sure your repository is not set to private, or I won't be able to see your code!
