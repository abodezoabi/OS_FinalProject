# Multithreaded Server Framework

## Overview
This project is a high-performance multithreaded server framework leveraging **Leader-Follower**, **Pipeline**, and **Active Object** design patterns. It handles client requests, executes tasks asynchronously, and processes workflows across multiple stages, ideal for real-time applications like graph analysis.

## Key Features
- **Leader-Follower**: Efficient thread pool management for handling client connections dynamically.
- **Pipeline**: Sequential task processing across stages, augmenting results at each stage.
- **Active Object**: Thread-safe asynchronous task execution using encapsulated queues.
- **Graph Analysis**: Real-time MST computation and dynamic graph processing.

## Project Structure
src/ ├── Model/ │ ├── Graph.cpp / Graph.hpp │ ├── MSTFactory.cpp / MSTFactory.hpp ├── Network/ │ ├── ActiveObject.cpp / ActiveObject.hpp │ ├── LeaderFollowers.cpp / LeaderFollowers.hpp │ ├── Pipeline.cpp / Pipeline.hpp │ ├── Server_LF.cpp / Server_PL.cpp main.cpp

markdown
Copy code

## Usage

### Requirements
- C++17 or later
- `g++` with `-pthread` support

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
Build the project:
bash
Copy code
make
Run the server:
bash
Copy code
./server
Example Commands
create <number_of_vertices>: Create a graph with specified vertices.
add <u> <v> <weight>: Add an edge to the graph.
remove <u> <v>: Remove an edge from the graph.
algo <prim/kruskal/boruvka/tarjan>: Choose an MST algorithm.
analyze: Analyze the graph via pipeline.
shutdown: Shut down the server.
License
This project is licensed under the MIT License.
