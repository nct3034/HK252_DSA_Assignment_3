#include "MusicGraph.h"

// =============================================================================
// PRIVATE HELPER METHODS
// =============================================================================

int MusicGraph::getSongIndex(const string &id) const {
  // Implement linear search to find the index of a song by its ID
  for (size_t index = 0; index < songsList.size(); index++) {
    if (songsList[index].id == id) {
      return index;
    }
  }
  return -1;
}

bool MusicGraph::isVisited(const string &id,
                           const vector<string> &visitedList) const {
  // Check if the given ID exists in the visitedList
  for (size_t index = 0; index < visitedList.size(); index++) {
    if (visitedList[index] == id) {
      return true;
    }
  }
  return false;
}

// =============================================================================
// PUBLIC METHODS
// =============================================================================

void MusicGraph::addSong(const string &id, const string &title,
                         const string &artist, const string &genre) {
  // Add a new song to the system and add its ID as a vertex in the graph
  if (getSongIndex(id) != -1) {
    return;
  }

  Song newSong = {id, title, artist, genre};
  SongEntry newEntry = {id, newSong};

  songsList.push_back(newEntry);
  this->addVertex(id);
}

void MusicGraph::printSongInfo(const string &id) const {
  // Print the song information in the required format
  int index = getSongIndex(id);
  if (index == -1) {
    return;
  }

  Song song = songsList[index].data;
  cout << "[" << song.id << "] " << song.title << " - " << song.artist;
}

// =============================================================================
// REQUIREMENT 1: Recommend related songs (BFS)
// =============================================================================
void MusicGraph::recommendRelatedSongs(const string &startId) const {
  if (!this->hasVertex(startId))
    return;

  cout << "\n[1] SUGGEST RELATED SONGS FOR: ";
  printSongInfo(startId);
  cout << "\n-------------------------------------------------\n";

  // Implement Breadth-First Search (BFS) to recommend related songs
  vector<string> visited;
  vector<string> customQueue;
  int head = 0;
  visited.push_back(startId);
  customQueue.push_back(startId);

  while (head < (int)customQueue.size()) {
    for (Edge e : this->getNeighbors(customQueue[head])) {
      string id = e.target;
      if (!isVisited(id, visited)) {
        visited.push_back(id);
        customQueue.push_back(id);

        cout << "-> ";
        printSongInfo(id);
        cout << endl;
      }
    }
    head++;
  }
}

// =============================================================================
// REQUIREMENT 2: Create playlist by clusters (Connected Components using BFS)
// =============================================================================
void MusicGraph::generatePlaylistsByClusters() const {
  cout << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n";
  cout << "-------------------------------------------------\n";

  // Find connected components and print each cluster as a playlist
  vector<string> globalVisited;
  int playlistCount = 0;

  for (AdjacencyNode node : this->adjList) {
    string startIndex = node.vertex;
    if (!isVisited(startIndex, globalVisited)) {
      playlistCount++;
      vector<string> customQueue;
      customQueue.push_back(startIndex);
      globalVisited.push_back(startIndex);
      int head = 0;

      cout << "=== Playlist " << playlistCount << " ===" << endl;

      while (head < (int)customQueue.size()) {
        string current = customQueue[head];
        cout << "  * ";
        printSongInfo(current);
        cout << endl;

        for (Edge e : this->getNeighbors(customQueue[head])) {
          string id = e.target;
          if (!isVisited(id, globalVisited)) {
            globalVisited.push_back(id);
            customQueue.push_back(id);
          }
        }
        head++;
      }
    }
  }
}

// =============================================================================
// REQUIREMENT 3: Smooth song transition (Dijkstra's Algorithm)
// =============================================================================
void MusicGraph::findSmoothTransition(const string &startId,
                                      const string &endId) const {
  cout << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n";
  cout << "From: ";
  printSongInfo(startId);
  cout << "\n";
  cout << "To: ";
  printSongInfo(endId);
  cout << "\n";
  cout << "-------------------------------------------------\n";

  int n = this->adjList.size();
  int startIdx = this->getVertexIndex(startId);
  int endIdx = this->getVertexIndex(endId);

  if (startIdx == -1 || endIdx == -1) {
    cout << "Error: Song not found!\n";
    return;
  }

  // Implement Dijkstra's algorithm
  // to find the shortest path between startId and endId

  double const INF = 999999999.0;
  vector<double> dist(n, INF);
  vector<int> prev(n, -1);
  vector<bool> visited(n, false);

  dist[startIdx] = 0;
  for (int i = 0; i < n; i++) {
    int u = -1;
    double minDist = INF;

    for (int j = 0; j < n; j++) {
      if (!visited[j] && dist[j] < minDist) {
        u = j;
        minDist = dist[u];
      }
    }

    if (u == -1 || u == endIdx) {
      break;
    }
    visited[u] = true;

    for (Edge e : this->adjList[u].neighbors) {
      int v = this->getVertexIndex(e.target);
      if (!visited[v] && dist[u] + e.weight < dist[v]) {
        dist[v] = dist[u] + e.weight;
        prev[v] = u;
      }
    }
  }

  if (dist[endIdx] == INF) {
    cout << "No transition path between these two songs.\n";
    return;
  }

  vector<string> path;
  int cur = endIdx;
  while (cur != -1) {
    path.push_back(this->adjList[cur].vertex);
    cur = prev[cur];
  }

  cout << "Total Deviation: " << dist[endIdx] << "\n";
  cout << "Playback Order:\n";

  int step = 1;
  for (int i = path.size() - 1; i >= 0; i--) {
    cout << "  " << step << ". ";
    printSongInfo(path[i]);
    cout << "\n";
    step++;
  }
}

// =============================================================================
// REQUIREMENT 4: Find the network hub song (In-degree Calculation)
// =============================================================================
void MusicGraph::findMostPopularSong() const {
  cout << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n";
  cout << "-------------------------------------------------\n";

  // Calculate the in-degree of all vertices and
  // find the one with the maximum value

  int n = this->adjList.size();
  if (n == 0)
    return;

  vector<int> inDegree(n, 0);

  for (int i = 0; i < n; i++) {
    for (Edge e : this->adjList[i].neighbors) {
      int v = this->getVertexIndex(e.target);
      if (v != -1) {
        inDegree[v]++;
      }
    }
  }

  int maxInDegree = 0;
  for (int i = 0; i < n; i++) {
    if (maxInDegree < inDegree[i]) {
      maxInDegree = inDegree[i];
    }
  }

  cout << "-> Network Hub Song: \n";
  for (int i = 0; i < n; i++) {
    if (inDegree[i] == maxInDegree) {
      cout << "  ";
      printSongInfo(this->adjList[i].vertex);
      cout << "\n";
    }
  }
  cout << "(In-degree: " << maxInDegree << ")\n";
}

// =============================================================================
// REQUIREMENT 5: Detect music loop (DFS Cycle Detection)
// =============================================================================

// DFS recursive helper function
bool MusicGraph::dfsCycleHelper(int idx, vector<bool> &visited,
                                vector<bool> &recursionStack,
                                vector<int> &parent, bool &found) const {
  // TODO: Implement the recursive DFS logic to detect cycles
  return false;
}

void MusicGraph::detectMusicLoop() const {
  cout << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n";
  cout << "-------------------------------------------------\n";

  // TODO: Initialize required arrays and start DFS to detect a music loop
}