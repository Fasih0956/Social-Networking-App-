# Quick Start Guide - Social Media Analytics Engine

## Build & Run

### Prerequisites:
- CMake 3.10 or higher
- C++20 compatible compiler (GCC, MSVC, Clang)
- (Optional) Graphviz for graph visualization

### Build Steps:
```bash
cd Social-Networking-App-
cd build
cmake ..
ninja
```

### Run the Application:
```bash
./Social-Networking-App.exe
```

## Usage

The application presents a menu with the following options:

### 1. Show User Info
- Display user details (name, city, friends list)
- Shows degree (number of friends)
- Shows clustering coefficient (measure of friend interconnectedness)
- Shows influence score (number of reachable users in network)

**Input**: User ID (1-100)

### 2. Find Shortest Path
- Calculates the shortest connection path between two users
- Uses BFS (Breadth-First Search) algorithm
- Shows the path and path length

**Input**: User1 ID, User2 ID

### 3. Find Mutual Connections
- Lists all common friends between two users
- Shows count of mutual connections

**Input**: User1 ID, User2 ID

### 4. Generate Graph (2 Traversals)
- Generates a visual network showing all users connected within 2 hops
- Creates `graph.dot` (Graphviz format)
- Creates `graph.png` (visual image - requires Graphviz)

**Input**: User ID

### 5. Generate Shortest Path Graph
- Visualizes the shortest path between two users
- Highlights path nodes and edges
- Creates `path.dot` and `path.png`

**Input**: User1 ID, User2 ID

### 6. Generate Mutual Connections Graph
- Visualizes mutual friend relationships
- Color codes nodes: blue (user1), green (user2), yellow (mutual friends)
- Creates `mutual.dot` and `mutual.png`

**Input**: User1 ID, User2 ID

## Data Files

Located in `assets/` folder:
- `names.txt` - User names (format: ID: Name)
- `cities.txt` - User cities (format: ID: City)
- `friends.txt` - Friendship connections (format: ID: Friend1 Friend2 ...)

## Technical Details

### Graph Representation:
- **Primary**: Adjacency List (map<int, User>)
- **Alternative**: Adjacency Matrix (generated via Parser)

### Algorithms Implemented:
- **BFS** - Shortest path finding
- **DFS** - Influence score calculation (network reachability)
- **Graph Traversal** - 2-hop network visualization

### Time Complexity:
- Shortest Path: O(V + E) where V = users, E = friendships
- Mutual Connections: O(degree(u) + degree(v))
- Influence Score: O(V + E)

## Example Session:

```
==== Social Media Analytics Engine ====
Data loaded successfully!

=== MENU ===
1: Show User Info (Degree, Clustering, Influence)
2: Find Shortest Path Between Two Users
3: Find Mutual Connections
4: Generate Graph (2 traversals from user)
5: Generate Shortest Path Graph
6: Generate Mutual Connections Graph
0: Exit
Choice: 1
UserID: 1
User 1: Ahsan Khan (Karachi)
Friends: 65 86 24 48 33 38 59 67 76 43 78 2 5 7 13 16 33 36 46 47 48 50 53 83 87 95
Degree: 26
Clustering Coefficient: 0.430769
Influence Score: 99
```

## Project Structure:

```
Social-Networking-App-/
├── CMakeLists.txt          # Build configuration
├── README.md               # Original documentation
├── PROJECT_STATUS.md       # Project status
├── build/                  # Build directory
│   ├── Social-Networking-App.exe
│   ├── assets/             # Data files (copied)
│   ├── *.png              # Generated graphs
│   └── *.dot              # Graphviz DOT files
├── include/                # Header files
│   ├── graph.h            # Graph class
│   ├── User.h             # User class
│   ├── parser.h           # Data parsing
│   ├── SocialNetwork.h    # Social network manager
│   ├── Graphviz.h         # Visualization
│   └── ...
├── src/                    # Source files
│   └── main.cpp           # Main application
└── assets/                 # Data files
    ├── names.txt
    ├── cities.txt
    ├── friends.txt
    └── [images, fonts, etc.]
```

## Troubleshooting

**Issue**: "Cannot open names.txt"
- **Solution**: Ensure assets folder exists in the build directory or current working directory

**Issue**: "Graph generation failed"
- **Solution**: Install Graphviz (available on graphviz.org)

**Issue**: Build fails with "Command not found: ninja"
- **Solution**: Use `cmake --build .` instead of `ninja`

**Issue**: No PNG images generated
- **Solution**: Graphviz is optional. DOT files are always created.
