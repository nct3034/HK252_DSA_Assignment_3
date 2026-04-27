#include "MusicGraph.h"

// =============================================================================
// Helper function to build the sample graph from the assignment description
// =============================================================================
void buildSampleGraph(MusicGraph &botkify) {
  // Add music library (6 songs)
  botkify.addSong("S01", "Chung Ta Cua Tuong Lai", "Son Tung M-TP", "Pop");
  botkify.addSong("S02", "Muon Roi Ma Sao Con", "Son Tung M-TP", "Pop");
  botkify.addSong("S03", "Don't Coi", "RPT Orijinn", "Rap");
  botkify.addSong("S04", "Thuy Trieu", "Quang Hung MasterD", "Pop-Dance");
  botkify.addSong("S05", "Waiting For You", "MONO", "Pop");
  botkify.addSong("S06", "Co Don Tren Sofa", "Ho Ngoc Ha", "Ballad");

  // Define connections
  botkify.addEdge("S01", "S02", 1.5, true);  // Bidirectional
  botkify.addEdge("S02", "S04", 3.0, false); // Unidirectional: S02 -> S04
  botkify.addEdge("S04", "S03", 2.0, true);  // Bidirectional
  botkify.addEdge("S01", "S05", 2.5, true);  // Bidirectional
  botkify.addEdge("S05", "S04", 1.0, true);  // Bidirectional
  // S06 has no connections (isolated vertex)
}

// =============================================================================
// TEST CASE 1: BFS - Recommend related songs
// =============================================================================
void testBFS(MusicGraph &botkify) {
  cout << "============================================================\n";
  cout << "TEST CASE 1: BFS - Recommend related songs\n";
  cout << "============================================================\n";

  // Expected output:
  //   -> [S02] Muon Roi Ma Sao Con - Son Tung M-TP
  //   -> [S05] Waiting For You - MONO
  //   -> [S04] Thuy Trieu - Quang Hung MasterD
  //   -> [S03] Don't Coi - RPT Orijinn
  // (S06 is NOT recommended because it is disconnected from S01)
  botkify.recommendRelatedSongs("S01");

  cout << "\n--- Test BFS from isolated node S06 ---\n";
  // Expected output: no recommendations (S06 has no neighbors)
  botkify.recommendRelatedSongs("S06");

  cout << "\n--- Test BFS from non-existent node ---\n";
  // Expected output: nothing printed (hasVertex returns false)
  botkify.recommendRelatedSongs("S99");
}

// =============================================================================
// TEST CASE 2: Connected Components - Create playlist by clusters
// =============================================================================
void testConnectedComponents(MusicGraph &botkify) {
  cout << "\n============================================================\n";
  cout << "TEST CASE 2: Connected Components - Create playlist by clusters\n";
  cout << "============================================================\n";

  // Expected output:
  //   === Playlist 1 ===
  //     * [S01] Chung Ta Cua Tuong Lai - Son Tung M-TP
  //     * [S02] Muon Roi Ma Sao Con - Son Tung M-TP
  //     * [S05] Waiting For You - MONO
  //     * [S04] Thuy Trieu - Quang Hung MasterD
  //     * [S03] Don't Coi - RPT Orijinn
  //   === Playlist 2 ===
  //     * [S06] Co Don Tren Sofa - Ho Ngoc Ha
  botkify.generatePlaylistsByClusters();
}

// =============================================================================
// TEST CASE 3: Dijkstra - Smooth song transition
// =============================================================================
void testDijkstra(MusicGraph &botkify) {
  cout << "\n============================================================\n";
  cout << "TEST CASE 3: Dijkstra - Smoothest transition\n";
  cout << "============================================================\n";

  // Expected output:
  //   -> Total Deviation (Cost): 5.5
  //   -> Playback Order:
  //      1. [S01] Chung Ta Cua Tuong Lai - Son Tung M-TP
  //      2. [S05] Waiting For You - MONO
  //      3. [S04] Thuy Trieu - Quang Hung MasterD
  //      4. [S03] Don't Coi - RPT Orijinn
  botkify.findSmoothTransition("S01", "S03");

  cout << "\n--- Test Dijkstra to isolated node ---\n";
  // Expected output: "No transition path between these two songs."
  botkify.findSmoothTransition("S01", "S06");
}

// =============================================================================
// TEST CASE 4: In-degree - Find the network hub song
// =============================================================================
void testInDegree(MusicGraph &botkify) {
  cout << "\n============================================================\n";
  cout << "TEST CASE 4: In-degree - Find network hub song\n";
  cout << "============================================================\n";

  // Expected output:
  //   -> Network Hub Song:
  //      [S04] Thuy Trieu - Quang Hung MasterD
  //      (In-degree: 3)
  // Because S04 receives edges from: S02->S04, S03->S04, S05->S04
  botkify.findMostPopularSong();
}

// =============================================================================
// TEST CASE 5: DFS Cycle Detection - Detect music loop
// =============================================================================
void testCycleDetection(MusicGraph &botkify) {
  cout << "\n============================================================\n";
  cout << "TEST CASE 5: DFS Cycle Detection - Detect music loop\n";
  cout << "============================================================\n";

  // Expected output:
  //   -> Music loop detected!
  //   -> Loop:
  //      [S01] Chung Ta Cua Tuong Lai - Son Tung M-TP
  //      [S02] Muon Roi Ma Sao Con - Son Tung M-TP
  //      [S01] Chung Ta Cua Tuong Lai - Son Tung M-TP
  // (Cycle: S01 -> S02 -> S01 due to bidirectional edge)
  botkify.detectMusicLoop();
}

// =============================================================================
// TEST CASE 6: Graph with no cycle (DAG)
// =============================================================================
void testNoCycle() {
  cout << "\n============================================================\n";
  cout << "TEST CASE 6: DAG - Graph with no cycle\n";
  cout << "============================================================\n";

  MusicGraph dag;
  dag.addSong("A01", "Song A", "Artist A", "Pop");
  dag.addSong("A02", "Song B", "Artist B", "Rock");
  dag.addSong("A03", "Song C", "Artist C", "Jazz");

  // A01 -> A02 -> A03 (no back edges, no cycle)
  dag.addEdge("A01", "A02", 1.0, false);
  dag.addEdge("A02", "A03", 2.0, false);

  // Expected output: "No music loop detected."
  dag.detectMusicLoop();
}

// =============================================================================
// MAIN
// =============================================================================
int main() {
  MusicGraph botkify;
  buildSampleGraph(botkify);

  testBFS(botkify);
  testConnectedComponents(botkify);
  testDijkstra(botkify);
  testInDegree(botkify);
  testCycleDetection(botkify);
  testNoCycle();

  cout << "\n============================================================\n";
  cout << "ALL TEST CASES COMPLETED\n";
  cout << "============================================================\n";

  return 0;
}