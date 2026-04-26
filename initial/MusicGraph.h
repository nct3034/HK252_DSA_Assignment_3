#ifndef MUSICGRAPH_H
#define MUSICGRAPH_H

#include "main.h"

class MusicGraph : public Graph<string> {
private:
    struct SongEntry {
        string id;
        Song data;
    };

    vector<SongEntry> songsList;

    // Helper methods
    int getSongIndex(const string& id) const;
    bool isVisited(const string& id, const vector<string>& visitedList) const;
    bool dfsCycleHelper(int idx, vector<bool>& visited, vector<bool>& recursionStack, vector<int>& parent, bool& found) const;

public:
    void addSong(const string& id, const string& title, const string& artist, const string& genre);
    void printSongInfo(const string& id) const;
    
    // Core requirements
    void recommendRelatedSongs(const string& startId) const;
    void generatePlaylistsByClusters() const;
    void findSmoothTransition(const string& startId, const string& endId) const;
    void findMostPopularSong() const;
    void detectMusicLoop() const;
};

#endif // MUSICGRAPH_H