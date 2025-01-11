# Search Engine with BST and Hash Table Implementation
A C++ search engine implementation comparing Binary Search Tree (BST) and Hash Table data structures for efficient text document searching.

## Features
- Document preprocessing and word indexing
- Case-insensitive word searching
- Performance comparison between BST and Hash Table implementations
- Supports multiple document searching
- Real-time performance metrics

## Data Structures
### Binary Search Tree (BST)
- Self-balancing tree implementation
- O(log n) search complexity
### Hash Table
- Dynamic resizing with rehashing
- Load factor management (0.25 < λ < 0.9)
- Collision handling

## Usage
Compile and run the program
Enter the number of input files
Provide file names
Enter search queries
View results and performance metrics
```bash
./search_engine
Enter number of input files: 2
Enter 1. file name: document1.txt
Enter 2. file name: document2.txt
Enter queried words in one line: search example
```

## Sample Output
```bash
After preprocessing, the unique word count is 8475. 
Current load ratio is 0.57838

Enter queried words in one line: above
in Document a.txt, above found 12 times.

Time (BST): 9896 ns
Time (HashTable): 1797 ns
Speed Up: 5.50544

```

## Performance
- Hash Table implementation consistently outperforms BST
- Automatic rehashing maintains optimal performance
- Load factor balancing ensures efficient memory usage

## Implementation Details
- Word tokenization with non-alphabetic separators
- Case-insensitive word matching
- Document frequency tracking
- Performance timing over multiple runs

## Limitations
- Text documents only
- Memory-based (no persistent storage)
- Single-threaded implementation

## Future Improvements
- Multi-threading support
- Persistent storage
- Ranking algorithm
- Advanced query operations
