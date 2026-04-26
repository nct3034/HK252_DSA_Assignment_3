#include "MusicGraph.h"

// =============================================================================
// PRIVATE HELPER METHODS
// =============================================================================

int MusicGraph::getSongIndex(const string &id) const
{
    // Implement linear search to find the index of a song by its ID
    for (size_t index = 0; index < songsList.size(); index++)
    {
        if (songsList[index].id == id)
        {
            return index;
        }
    }
    return -1;
}

bool MusicGraph::isVisited(const string &id, const vector<string> &visitedList) const
{
    // Check if the given ID exists in the visitedList
    for (size_t index = 0; index < visitedList.size(); index++)
    {
        if (visitedList[index] == id)
        {
            return true;
        }
    }
    return false;
}

// =============================================================================
// PUBLIC METHODS
// =============================================================================

void MusicGraph::addSong(const string &id, const string &title, const string &artist, const string &genre)
{
    // Add a new song to the system and add its ID as a vertex in the graph
    if (getSongIndex(id) != -1)
    {
        return;
    }

    Song newSong = {id, title, artist, genre};
    SongEntry newEntry = {id, newSong};

    songsList.push_back(newEntry);
    addVertex(id);
}

void MusicGraph::printSongInfo(const string &id) const
{
    // TODO: Print the song information in the required format
}

// =============================================================================
// REQUIREMENT 1: Recommend related songs (BFS)
// =============================================================================
void MusicGraph::recommendRelatedSongs(const string &startId) const
{
    if (!this->hasVertex(startId))
        return;

    cout << "\n[1] SUGGEST RELATED SONGS FOR: ";
    printSongInfo(startId);
    cout << "\n-------------------------------------------------\n";

    // TODO: Implement Breadth-First Search (BFS) to recommend related songs
}

// =============================================================================
// REQUIREMENT 2: Create playlist by clusters (Connected Components using BFS)
// =============================================================================
void MusicGraph::generatePlaylistsByClusters() const
{
    cout << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Find connected components and print each cluster as a playlist
}

// =============================================================================
// REQUIREMENT 3: Smooth song transition (Dijkstra's Algorithm)
// =============================================================================
void MusicGraph::findSmoothTransition(const string &startId, const string &endId) const
{
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

    if (startIdx == -1 || endIdx == -1)
    {
        cout << "Error: Song not found!\n";
        return;
    }

    // TODO: Implement Dijkstra's algorithm to find the shortest path between startId and endId
}

// =============================================================================
// REQUIREMENT 4: Find the network hub song (In-degree Calculation)
// =============================================================================
void MusicGraph::findMostPopularSong() const
{
    cout << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Calculate the in-degree of all vertices and find the one with the maximum value
}

// =============================================================================
// REQUIREMENT 5: Detect music loop (DFS Cycle Detection)
// =============================================================================

// DFS recursive helper function
bool MusicGraph::dfsCycleHelper(int idx, vector<bool> &visited, vector<bool> &recursionStack,
                                vector<int> &parent, bool &found) const
{
    // TODO: Implement the recursive DFS logic to detect cycles
    return false;
}

void MusicGraph::detectMusicLoop() const
{
    cout << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Initialize required arrays and start DFS to detect a music loop
}