class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build graph and compute in-degrees.
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (const auto &p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        
        // Process courses using a topological sort approach.
        for (int i = 0; i < numCourses; i++) {
            int course = -1;
            // Find a course with no remaining prerequisites.
            for (int j = 0; j < numCourses; j++) {
                if (indegree[j] == 0) {
                    course = j;
                    break;
                }
            }
            // If no such course exists, a cycle is present.
            if (course == -1) return false;
            // Mark the course as processed.
            indegree[course] = -1;
            // Reduce indegrees for dependent courses.
            for (int next : graph[course]) {
                indegree[next]--;
            }
        }
        return true;
    }
};