# Data Structure Implementations
**Written by Bryce Hart September 4th, 2026**

Below I have provided some resources on what I believe to be useful implementations of 
data structures needed for competitive programming / technical problems. These are only
implementations for C++. I will briefly explain each and leave resources cited. This should be used as a guide along with self learning, as I do not teach how they work internally.

## Array 

Array is the most basic version of data structures in C++. You can achieve one in 2 ways:

```C++
using namespace std;

// both declare an array of size 3.

array<int, 3> data; //safer, throws exceptions, can check bounds.

int data[3] = {}; //C style, no bounds checking, no exception safety.

```
I recommend the bounds checked, standard library array. Provides safety with the same performance.

### Adding elements 

Elements are 0 indexed, so the last element is element 9.

```C++
using namespace std;

array<int, 10> data;

data.at(9) = 64;
cout << data.at(10) << endl; //throws exception!

//you can also use brackets:
data[6] = 47;

int cData[3] = {4, 5, 6};

cout << cData[4] << endl; //creates segmentation fault

```

### Erasing elements

This is where array and the standard library array show their biggest weakness. Since both are a fixed size at compile time, you cannot actually remove an element. There is nowhere for the array to shrink to. The best you can do is overwrite the value with some kind of default or sentinel value.

```C++
using namespace std;

array<int, 10> data = {};

data.at(6) = 47;

//"erasing" just means resetting it back to a default value
data.at(6) = 0;

//you can reset the whole array at once too
data.fill(0);

```

If you actually need to add and remove elements at will, keep reading. That is exactly what vector is for.

## Vector

Vector is one of the most versatile data structures in the standard library. It works as an array, but is resizable at runtime. This provides huge flexibility for varying size inputs.

```C++
using namespace std;

vector<int> data; //declaration

```

### Adding elements

Elements can be added a few different ways in vector, given that it is resizable.

**Push Back:**
Pushes element to the back of the vector. This is the standard way of adding elements.
```C++
using namespace std;

vector<int> data;

int a = 90;
int b = 45;

data.push_back(a);
data.push_back(b);

cout << data.at(0) << endl; //prints 90

cout << data.at(1) << endl; //prints 45

```

**Insert:**
Inserts an element at a specific position, shifting everything after it back by one.
```C++
using namespace std;

vector<int> data = {10, 20, 30};

data.insert(data.begin() + 1, 15);

cout << data.at(1) << endl; //prints 15

```

### Erasing elements

Unlike array, vector can actually shrink.

**Pop Back:**
Removes the last element. This is the fastest way to erase from a vector.
```C++
using namespace std;

vector<int> data = {10, 20, 30};

data.pop_back();

cout << data.size() << endl; //prints 2

```

**Erase:**
Removes an element from anywhere in the vector using an iterator. Everything after it shifts forward by one, so this is slower than pop_back.
```C++
using namespace std;

vector<int> data = {10, 20, 30};

data.erase(data.begin() + 1); //removes 20

cout << data.at(1) << endl; //prints 30

```

## Iteration:

### Range based Iteration

These perform similarly to how they work in Python. This can perform a 
`for each` operation on all elements. This works on C style arrays, standard library array, and vector alike.

The important takeaway from this is to get the element **by reference** (&) instead of copying. This will have an actual performance difference on your code.

```C++
using namespace std;

array<int, 10> data;

for(int element : data){ //copies every element 
    if(element > 60){
        element++;
    }
}

for(int& element : data){ //takes the reference to every element
    if(element > 60){
        element++;
    }
}

```

### Iteration with a scoped variable

Sometimes you need the index itself, maybe you are comparing neighboring elements, or you need to erase while you iterate. For that, a normal indexed for loop works better than a range based one.

```C++
using namespace std;

vector<int> data = {10, 20, 30, 40};

for(int i = 0; i < data.size(); i++){
    cout << data.at(i) << endl;
}

```

Keep the scope of `i` limited to the loop itself unless you need it afterwards. Declaring it inside the for loop like above keeps your code cleaner and avoids naming collisions later on.

## Set

Set is a container that holds unique elements in sorted order. Internally it is implemented as a balanced binary search tree (a red black tree), so adding, erasing, and searching are all O(log n).

```C++
using namespace std;

set<int> data; //declaration

```

### Adding elements

```C++
using namespace std;

set<int> data;

data.insert(30);
data.insert(10);
data.insert(20);

//duplicates are ignored
data.insert(10);

cout << data.size() << endl; //prints 3

```

### Erasing elements

```C++
using namespace std;

set<int> data = {10, 20, 30};

data.erase(20);

cout << data.size() << endl; //prints 2

```

### Iterating

Since a set keeps its elements sorted, iterating over one will always print the elements in ascending order.

```C++
using namespace std;

set<int> data = {30, 10, 20};

for(int element : data){
    cout << element << endl; //prints 10, then 20, then 30
}

```

## Queue

Queue is a first in first out structure (FIFO). The first element you add is the first one that comes back out. It is technically a container adapter, meaning it is built on top of another container (deque by default) rather than being its own data structure.

```C++
using namespace std;

queue<int> data; //declaration

```

### Adding elements

```C++
using namespace std;

queue<int> data;

data.push(10);
data.push(20);
data.push(30);

cout << data.front() << endl; //prints 10

```

### Erasing elements

```C++
using namespace std;

queue<int> data;

data.push(10);
data.push(20);

data.pop(); //removes 10, the front element

cout << data.front() << endl; //prints 20

```

### Iterating

This is where queue is different from everything above it. Queue does not support iteration, there is no begin() or end(), since it is only meant to be accessed from the front and back. If you need to look at every element, you have to pop them one at a time.

```C++
using namespace std;

queue<int> data;

data.push(10);
data.push(20);
data.push(30);

while(!data.empty()){
    cout << data.front() << endl;
    data.pop();
}

```

## Trees

The standard library does not give you a tree, so if you need one you have to build it yourself with structs. The main danger here is memory management. If you use raw pointers and forget to delete them, you leak memory, and if you delete something twice you crash. I use `unique_ptr` for the child pointers below so the compiler cleans up after you automatically. This is available starting in C++11, and `make_unique` was added in C++14, so we are safe to use both here.

### Binary Tree

A binary tree node holds a value and up to two children, a left and a right.

```C++
using namespace std;

struct BinaryTreeNode {
    int data;
    unique_ptr<BinaryTreeNode> left;
    unique_ptr<BinaryTreeNode> right;

    BinaryTreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

```

#### Adding elements

Here I am inserting like a binary search tree, smaller values go left, larger values go right.
```C++
using namespace std;

void insert(unique_ptr<BinaryTreeNode>& node, int value){
    if(node == nullptr){
        node = make_unique<BinaryTreeNode>(value);
        return;
    }

    if(value < node->data){
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

```

#### Erasing elements

Removing a node from a binary search tree has 3 cases: no children, one child, or two children. With two children, you swap the value with the smallest value in the right subtree, then erase that instead.
```C++
using namespace std;

unique_ptr<BinaryTreeNode>& findMin(unique_ptr<BinaryTreeNode>& node){
    if(node->left == nullptr){
        return node;
    }
    return findMin(node->left);
}

void erase(unique_ptr<BinaryTreeNode>& node, int value){
    if(node == nullptr){
        return;
    }

    if(value < node->data){
        erase(node->left, value);
    } else if(value > node->data){
        erase(node->right, value);
    } else if(node->left != nullptr && node->right != nullptr){
        node->data = findMin(node->right)->data;
        erase(node->right, node->data);
    } else {
        node = (node->left != nullptr) ? move(node->left) : move(node->right);
    }
}

```

#### Iterating

In order traversal visits the left subtree, then the current node, then the right subtree. For a binary search tree, this prints every value in sorted order.
```C++
using namespace std;

void inOrder(const unique_ptr<BinaryTreeNode>& node){
    if(node == nullptr){
        return;
    }

    inOrder(node->left);
    cout << node->data << endl;
    inOrder(node->right);
}

```

### Tree

A general tree is not limited to two children. A node can have any number of children, so I store them in a vector instead of naming each one.

```C++
using namespace std;

struct TreeNode {
    int data;
    vector<unique_ptr<TreeNode>> children;

    TreeNode(int value) : data(value) {}
};

```

#### Adding elements

```C++
using namespace std;

void addChild(TreeNode& parent, int value){
    parent.children.push_back(make_unique<TreeNode>(value));
}

```

#### Erasing elements

Erasing here just means removing a child from its parent's list. The unique_ptr takes care of deleting the whole subtree underneath it automatically.
```C++
using namespace std;

void eraseChild(TreeNode& parent, int value){
    for(auto it = parent.children.begin(); it != parent.children.end(); it++){
        if((*it)->data == value){
            parent.children.erase(it);
            return;
        }
    }
}

```

#### Iterating

A depth first traversal visits a node, then recurses into every one of its children.
```C++
using namespace std;

void depthFirst(const TreeNode& node){
    cout << node.data << endl;

    for(const auto& child : node.children){
        depthFirst(*child);
    }
}

```

### Trie

A trie is a tree built specifically for storing strings efficiently. Each node represents a single character, and a path from the root down to a node marked as the end of a word spells out that word. I am only supporting lowercase letters here, so each node has 26 possible children.

```C++
using namespace std;

struct TrieNode {
    array<unique_ptr<TrieNode>, 26> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

```

#### Adding elements

```C++
using namespace std;

void insert(TrieNode& root, const string& word){
    TrieNode* current = &root;

    for(char c : word){
        int index = c - 'a';

        if(current->children.at(index) == nullptr){
            current->children.at(index) = make_unique<TrieNode>();
        }

        current = current->children.at(index).get();
    }

    current->isEndOfWord = true;
}

```

#### Erasing elements

The safest way to erase a word is to just unmark it as the end of a word. This keeps the rest of the trie intact in case other words still depend on those same nodes.
```C++
using namespace std;

void erase(TrieNode& root, const string& word){
    TrieNode* current = &root;

    for(char c : word){
        int index = c - 'a';

        if(current->children.at(index) == nullptr){
            return; //word was never in the trie
        }

        current = current->children.at(index).get();
    }

    current->isEndOfWord = false;
}

```

#### Iterating

There is no built in way to iterate a trie, but you can search for whether a word exists by walking down the same path you use to insert.
```C++
using namespace std;

bool contains(TrieNode& root, const string& word){
    TrieNode* current = &root;

    for(char c : word){
        int index = c - 'a';

        if(current->children.at(index) == nullptr){
            return false;
        }

        current = current->children.at(index).get();
    }

    return current->isEndOfWord;
}

```