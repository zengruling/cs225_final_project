# CS 225 Data Structures
##  Final Project Proposal (hh18-tsha3-rylanmt2-zeng28)
**Leading Question:**
 Given a dataset of people’s preferences in various music genres, our goal is to discover and link commonly associated genres and subgenres, common and uncommon.
 It can be used as a music genre recommendation/general search tool for those who want to listen to something new but are wondering where to start.
 
**Dataset Acquisition and Processing:**
The dataset we will use is the The AcousticBrainz Genre Dataset [https://mtg.github.io/acousticbrainz-genre-dataset/]. Development and validation versions of this dataset are publicly available. The downloaded file is in TSV format. The first element starting at the third entity, each line is what we will be processing. We will be downloading the data to disk, hence we may have to cut down on the size of the dataset. For now, it might be best for the code-base to organize the data by how often certain genres are mentioned alongside others (we assume that subgenres will be most often mentioned with their parent genres) in a simple binary tree, as the other data structures don’t seem particularly useful for such a purpose on a surface-level. For potential errors or blanks, we intend for the code-base that will organize this dataset to be able to handle or otherwise ignore missing parts, since our purpose is to illustrate links between genres. Erroneous data that does not contribute to the creation of the graph data structure can only be ignored. While we could employ a seperate program to sort and remove blank or erroneous data, it should be fairly simple to build such a function directly into the code-base.

**Graph Algorithms:**
To begin with, since we will be searching for genres and their closest relatives, breadth-first search (O(n + connections)) is likely to be most useful in this endeavor; we will use it to return a searched genre’s recommended genres, up to a certain limit. This way, the search output could be specified by the user (number of related genres, etc.). The shortest path Dijkstra’s Algorithm (O(n^2)) would also be preferred in order to return how related two genres are by the distance of their shortest path. Our second graph algorithm would be to visualize our graph using a force-directed graph drawing. This will have a runtime of O(n^3), but by excluding subgenres our number of genres decreases significantly to make this manageable.

**Proposed Timeline:**
* Week 1 (Nov 8th):
  1. Complete Team Contract
  2. Get a working Final Project Proposal, if approved, starting work on Thursday
  3. Start data structure construction code-base
* Week 2 (Nov 15th):
  1. Complete data structure construction code-base
  2. Start working on graph algorithms (Shortest path, Graph coloring algorithm, Breadth-first search)
* Week 3 (Nov 22nd):
   1. Continue work on graph algorithms (Shortest Path (wrap-up), Graph coloring algorithm, Breadth-first search (wrap-up))
* Week 4 + Mid-Project Checkin (Nov 29th - Dec 1):
  1. Begin wrapping up work on code-base portion of the project
  2. Start production of final deliverables (written project report, final presentation)
* Week 5 (Dec 6th):
  1. Continue work on final deliverables.
* Final Project Submission (Dec 13th):
  1. Complete all work and hand everything in

 

