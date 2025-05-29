#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;
vector<vector<int>> convertMatrixToList(const string& filename){
    vector<vector<int>> storedata;
    ifstream inputfile (filename);
    if (!inputfile.is_open()){
        cout << "Error (Cannot open file)";
        return storedata;
    }
    int size;
    inputfile >> size;
    storedata.resize(size, vector<int>(size));
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            inputfile >> storedata[i][j];
        }
    }
    cout << "Matrix from Input:\n ";
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            cout << storedata[i][j]<<" ";
        }
        cout << endl;
    }
    vector<vector<int>> adjacencylist;
    for (int i=0 ;i<size;i++){
        int sizelist=0;
        vector<int>line;
        for (int j=0;j<size;j++){
            if (storedata[i][j]==1){
                line.push_back(j);
            }
        }
        if (line.empty()) {
            line.push_back(0);
        }
        adjacencylist.push_back(line);
    }
    return adjacencylist;
}
vector<vector<int>> convertListToMatrix(const string& filename){
    vector<vector<int>> storedata;
    ifstream inputfile (filename);
    if (!inputfile.is_open()){
        cout << "Error (Cannot open file)";
        return storedata;
    }
    int size;
    inputfile >> size;
    inputfile.ignore(1);
    string text;
    while (getline(inputfile,text)){
        istringstream iss(text);
        vector<int> line;
        int num;
        while (iss>>num){
            line.push_back(num);
        }
        storedata.push_back(line);
    }
    cout << "\nAdjacency List From Input:\n";
    for (int i = 0; i < storedata.size(); i++) {
        for (int j = 0; j < storedata[i].size(); j++) {
            cout << storedata[i][j] << " ";
        }
        cout << "\n";
    }
    vector<vector<int>> adjacencymatrix(size,vector<int>(size,0));
    for (int i=0 ;i<storedata.size();i++){
        for (int j=0;j<storedata[i].size();j++){
            if (storedata[i][0]!=0){
            adjacencymatrix[i][storedata[i][j]]=1;
            }
        }
    }
    return adjacencymatrix;
}
bool isDirected(const vector<vector<int>>& adjMatrix) {
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                return true;
            }
        }
    }
    return false; 
}
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix){
    int count=0;
    if (isDirected(adjMatrix)){
        for (int i=0;i<adjMatrix.size();i++){
            for (int j=0;j<adjMatrix[i].size();j++){
                if (adjMatrix[i][j]==1){
                    count++;
                }
            }
        }
    }
    else {
        for (int i = 0; i < adjMatrix.size(); i++) {
            for (int j = i; j < adjMatrix[i].size(); j++) {
                if (adjMatrix[i][j] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    vector<int> res;
    int n = adjMatrix.size();
    for (int i=0;i<n;i++){
        bool is_isolated=true;
        for (int j=0;j<n;j++){
            if (adjMatrix[i][j]!=0 || adjMatrix[j][i]!=0){
                is_isolated=false;
                break;
            }
        }
        if (is_isolated){
            res.push_back(i);
        }
    }
    return res;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    if (isDirected(adjMatrix)){
        return false;
    }
    if (adjMatrix.empty() || adjMatrix.size() != adjMatrix[0].size()) {
        return false;
    }
    for (int i=0;i<adjMatrix.size();i++){
        for (int j=0;j<adjMatrix[i].size();j++){
            if ((i==j && adjMatrix[i][j]!=0) || (i!=j && adjMatrix[i][j]==0)){
                return false;
            }
        }
    }
    return true;
}
bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> group(n, -1); 
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (group[i] == -1) {
            group[i] = 0;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (group[v] == -1) {
                            group[v] = 1 - group[u];
                            q.push(v);
                        } else if (group[v] == group[u]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
vector<vector<int>> MatrixToList(vector<vector<int>> adjMatrix) {
    vector<vector<int>> adjList(adjMatrix.size());
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if (adjMatrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
        vector<int> color(adjMatrix.size(), 0);
    vector<vector<int>> adjList = MatrixToList(adjMatrix);

    for (int i = 0; i < adjMatrix.size(); i++) {
        if (color[i] != 0) continue;
        queue<int> q;
        q.push(i); color[i] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            //neighbor cua cur
            for (int j = 0; j < adjList[cur].size(); j++) {
                int neighbor = adjList[cur][j];
                if (color[neighbor] == 0) {
                    color[neighbor] = 3 - color[cur];
                    q.push(neighbor);
                }
                else if (color[cur] == color[adjList[cur][j]]) return false;
            }
        }
    }

    vector<int> color1, color2;
    for (int i = 0; i < adjMatrix.size(); i++) {
        if (color[i] == 1) color1.push_back(i);
        else color2.push_back(i);
    }

    for (int i = 0; i < color1.size(); i++) {
        for (int j = 0; j < color2.size(); j++) {
            if (adjMatrix[color1[i]][color2[j]] == 0) return false;
        }
    }

    return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> undirected(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (adjMatrix[i][j] || adjMatrix[j][i]) {
                undirected[i][j] = undirected[j][i] = 1;
            }
        }
    }
    return undirected;
}
 vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (i != j && adjMatrix[i][j] == 0) {
                complement[i][j] = 1;
            }
        }
    }
    return complement;
 }
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    if (n == 0) return {}; // Đồ thị rỗng không có chu trình Euler

    // Đảm bảo đồ thị là vô hướng cho thuật toán này
    // Tạo một bản sao đồ thị để chỉnh sửa (xóa cạnh)
    vector<vector<int>> graph_copy = convertToUndirectedGraph(adjMatrix);

    // Bước 1: Kiểm tra bậc của các đỉnh (đồ thị vô hướng)
    // Tất cả các đỉnh phải có bậc chẵn
    for (int i = 0; i < n; ++i) {
        int degree = 0;
        for (int j = 0; j < n; ++j) {
            degree += graph_copy[i][j];
        }
        if (degree % 2 != 0) {
            cout << "Lỗi: Đồ thị không có chu trình Euler (có đỉnh bậc lẻ: " << i << ").\n";
            return {}; // Không có chu trình Euler nếu có đỉnh bậc lẻ
        }
    }

    // Bước 2: Kiểm tra tính liên thông (chỉ các đỉnh có cạnh)
    // Thuật toán chỉ đúng nếu tất cả các đỉnh có bậc dương nằm trong cùng một thành phần liên thông
    vector<bool> visited_connectivity(n, false);
    int start_node_for_check = -1;
    for(int i = 0; i < n; ++i) {
        int degree = 0;
        for(int j = 0; j < n; ++j) degree += graph_copy[i][j];
        if (degree > 0) { // Tìm đỉnh đầu tiên có bậc dương để bắt đầu kiểm tra liên thông
            start_node_for_check = i;
            break;
        }
    }

    if (start_node_for_check != -1) { // Nếu có ít nhất một cạnh trong đồ thị
        queue<int> q_conn;
        q_conn.push(start_node_for_check);
        visited_connectivity[start_node_for_check] = true;
        int visited_count = 0;

        while (!q_conn.empty()) {
            int u = q_conn.front();
            q_conn.pop();
            visited_count++;
            for (int v = 0; v < n; ++v) {
                if (graph_copy[u][v] && !visited_connectivity[v]) {
                    visited_connectivity[v] = true;
                    q_conn.push(v);
                }
            }
        }
        
        // Đảm bảo rằng tất cả các đỉnh có bậc dương đều được thăm
        for (int i = 0; i < n; ++i) {
            int degree = 0;
            for(int j = 0; j < n; ++j) degree += graph_copy[i][j];
            if (degree > 0 && !visited_connectivity[i]) {
                cout << "Lỗi: Đồ thị không có chu trình Euler (không liên thông).\n";
                return {}; // Không liên thông
            }
        }
    } else {
        // Đồ thị rỗng hoặc chỉ toàn đỉnh cô lập (không có cạnh)
        // Không có chu trình Euler nếu không có cạnh
        return {};
    }

    // Bước 3: Tìm chu trình Euler bằng Hierholzer's algorithm
    stack<int> st;
    vector<int> cycle;
    int current_vertex = start_node_for_check; // Bắt đầu từ đỉnh có bậc dương
    if (current_vertex == -1 && n > 0) { // Trường hợp tất cả các đỉnh đều cô lập
        return {};
    }
    if (n == 1 && countEdges(adjMatrix) == 0) { // Đồ thị 1 đỉnh, 0 cạnh không có chu trình Euler
        return {};
    } else if (n==1 && countEdges(adjMatrix) > 0) { // Đồ thị 1 đỉnh, có vòng lặp tự thân
        // Xử lý đặc biệt cho đồ thị 1 đỉnh có vòng lặp tự thân
        if (graph_copy[0][0] > 0) {
            cout << "Lỗi: Đồ thị 1 đỉnh có vòng lặp tự thân, hàm chưa xử lý chu trình Euler cho trường hợp này.\n";
            return {}; // Cần một cách xử lý phức tạp hơn để liệt kê tất cả các vòng lặp
        }
    }

    st.push(current_vertex);

    while (!st.empty()) {
        int u = st.top();
        int next_v = -1;
        for (int v = 0; v < n; ++v) {
            if (graph_copy[u][v]) {
                next_v = v;
                break;
            }
        }

        if (next_v != -1) { // Tìm thấy cạnh
            graph_copy[u][next_v] = 0; // Xóa cạnh từ u đến next_v
            graph_copy[next_v][u] = 0; // Xóa cạnh từ next_v đến u (vì là vô hướng)
            st.push(next_v);
        } else { // Không còn cạnh nào từ đỉnh u
            cycle.push_back(u);
            st.pop();
        }
    }

    reverse(cycle.begin(), cycle.end()); // Đảo ngược để có thứ tự đúng

    // Cuối cùng, kiểm tra lại xem tất cả các cạnh đã được sử dụng hết chưa
    // Mặc dù các kiểm tra trước đã đảm bảo điều kiện, đây là kiểm tra cuối cùng để chắc chắn.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph_copy[i][j] == 1) {
                // Điều này không nên xảy ra nếu các kiểm tra điều kiện tiên quyết là đúng
                cout << "Lỗi: Có cạnh còn lại sau khi tìm chu trình. Có thể đồ thị không liên thông theo định nghĩa Euler.\n";
                return {};
            }
        }
    }

    return cycle;
}
void dfs(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& tree) {
    visited[u] = true;
    for (int v = 0; v < adjMatrix.size(); ++v) {
        if (adjMatrix[u][v] && !visited[v]) {
            tree[u][v] = tree[v][u] = 1;
            dfs(v, adjMatrix, visited, tree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    dfs(start, adjMatrix, visited, tree);
    return tree;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                tree[u][v] = tree[v][u] = 1;
                q.push(v);
            }
        }
    }
    return tree;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == v) return true;
        for (int i = 0; i < n; ++i) {
            if (adjMatrix[curr][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), parent(n, -1);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j)
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if (dist[u] == INT_MAX) break;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0 && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), parent(n, -1);
    dist[start] = 0;
    for (int k = 0; k < n - 1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                cout << "Negative weight cycle detected.\n";
                return {};
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

void printMatrix(const vector<vector<int>>& matrix, const string& name) {
    if (matrix.empty()) {
        cout << name << " is empty.\n";
        return;
    }
    cout << "\n" << name << ":\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}
void printList(const vector<vector<int>>& list, const string& name) {
    if (list.empty()) {
        cout << name << " is empty.\n";
        return;
    }
    cout << "\n" << name << ":\n";
    for (int i = 0; i < list.size(); ++i) {
        cout << "Vertex " << i << ": ";
        if (list[i].empty()) {
            cout << "(no neighbors)";
        } else {
            for (int neighbor : list[i]) {
                cout << neighbor << " ";
            }
        }
        cout << "\n";
    }
}
int main() {
    // Tạo các file input nếu chưa có
    ofstream matrix_file("matrix_input.txt");
    if (matrix_file.is_open()) {
        matrix_file << "9\n";
        matrix_file << "0 0 1 0 0 1 0 0 0\n";
        matrix_file << "0 0 0 0 0 0 1 0 0\n";
        matrix_file << "0 0 0 0 0 0 1 0 0\n";
        matrix_file << "0 0 0 0 1 0 0 0 0\n";
        matrix_file << "0 0 0 0 0 1 0 0 0\n";
        matrix_file << "0 0 0 1 0 0 0 1 0\n";
        matrix_file << "0 0 0 0 0 0 0 0 0\n";
        matrix_file << "0 0 1 0 0 0 0 0 1\n";
        matrix_file << "0 0 0 0 0 0 0 0 0\n";
        matrix_file.close();
        cout << "Created matrix_input.txt\n";
    } else {
        cout << "Unable to open matrix_input.txt for writing.\n";
        return 1;
    }

    ofstream list_file("list_input.txt");
    if (list_file.is_open()) {
        list_file << "9\n";
        list_file << "2 5\n"; // Vertex 0 has neighbors 2 and 5
        list_file << "6\n";   // Vertex 1 has neighbor 6
        list_file << "6\n";   // Vertex 2 has neighbor 6
        list_file << "4\n";   // Vertex 3 has neighbor 4
        list_file << "5\n";   // Vertex 4 has neighbor 5
        list_file << "3 7\n"; // Vertex 5 has neighbors 3 and 7
        list_file << "\n";    // Vertex 6 has no neighbors (empty line)
        list_file << "2 8\n"; // Vertex 7 has neighbors 2 and 8
        list_file << "\n";    // Vertex 8 has no neighbors (empty line)
        list_file.close();
        cout << "Created list_input.txt\n";
    } else {
        cout << "Unable to open list_input.txt for writing.\n";
        return 1;
    }

    cout << "\n--- Bắt đầu Test Cases ---\n";

    bool test_passed; // Biến để theo dõi trạng thái PASS/FAIL

    // Test convertMatrixToList
    cout << "\n--- Test convertMatrixToList ---\n";
    vector<vector<int>> adjListFromMatrix = convertMatrixToList("matrix_input.txt");
    printList(adjListFromMatrix, "Danh sách kề từ Ma trận");
    // Kiểm tra đơn giản: đảm bảo list không rỗng nếu file có dữ liệu
    test_passed = !adjListFromMatrix.empty();
    cout << "Test convertMatrixToList: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test convertListToMatrix
    cout << "\n--- Test convertListToMatrix ---\n";
    vector<vector<int>> adjMatrixFromList = convertListToMatrix("list_input.txt");
    printMatrix(adjMatrixFromList, "Ma trận kề từ Danh sách kề");
    // Kiểm tra đơn giản: đảm bảo matrix không rỗng nếu file có dữ liệu
    test_passed = !adjMatrixFromList.empty();
    cout << "Test convertListToMatrix: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Sử dụng adjMatrixFromList cho các test case tiếp theo để đảm bảo tính nhất quán
    vector<vector<int>> currentAdjMatrix = adjMatrixFromList;

    // Test isDirected
    cout << "\n--- Test isDirected ---\n";
    test_passed = isDirected(currentAdjMatrix); // Dựa vào input.txt của bạn, đồ thị là có hướng
    cout << "Đồ thị có hướng? " << (test_passed ? "Có" : "Không") << "\n";
    cout << "Test isDirected: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test countVertices
    cout << "\n--- Test countVertices ---\n";
    int numVertices = countVertices(currentAdjMatrix);
    cout << "Số đỉnh: " << numVertices << "\n";
    test_passed = (numVertices == 9); // Dựa vào input.txt có 9 đỉnh
    cout << "Test countVertices: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test countEdges
    cout << "\n--- Test countEdges ---\n";
    int numEdges = countEdges(currentAdjMatrix);
    cout << "Số cạnh: " << numEdges << "\n";
    // Đếm thủ công từ list_input.txt:
    // 0: 2 cạnh (2, 5)
    // 1: 1 cạnh (6)
    // 2: 1 cạnh (6)
    // 3: 1 cạnh (4)
    // 4: 1 cạnh (5)
    // 5: 2 cạnh (3, 7)
    // 6: 0 cạnh
    // 7: 2 cạnh (2, 8)
    // 8: 0 cạnh
    // Tổng cộng: 2+1+1+1+1+2+0+2+0 = 10 cạnh
    test_passed = (numEdges == 10); 
    cout << "Test countEdges: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test getIsolatedVertices
    cout << "\n--- Test getIsolatedVertices ---\n";
    vector<int> isolatedVertices = getIsolatedVertices(currentAdjMatrix);
    cout << "Các đỉnh cô lập: ";
    test_passed = true;
    if (isolatedVertices.empty()) {
        cout << "Không có.\n";
        test_passed = false; // Đỉnh 6 và 8 phải cô lập
    } else {
        bool found_6 = false, found_8 = false;
        for (int v : isolatedVertices) {
            cout << v << " ";
            if (v == 6) found_6 = true;
            if (v == 8) found_8 = true;
        }
        cout << "\n";
        test_passed = (isolatedVertices.size() == 2 && found_6 && found_8);
    }
    cout << "Test getIsolatedVertices: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test isCompleteGraph
    cout << "\n--- Test isCompleteGraph ---\n";
    test_passed = isCompleteGraph(currentAdjMatrix); // Đồ thị của bạn không phải là đồ thị đầy đủ
    cout << "Có phải đồ thị đầy đủ? " << (test_passed ? "Có" : "Không") << "\n";
    test_passed = !test_passed; // Đáng lẽ phải là Không, nên nếu trả về Có thì FAILED
    cout << "Test isCompleteGraph: " << (test_passed ? "PASSED" : "FAILED") << "\n";
    
    // Test isBipartite
    cout << "\n--- Test isBipartite ---\n";
    test_passed = isBipartite(currentAdjMatrix); 
    cout << "Có phải đồ thị lưỡng phân? " << (test_passed ? "Có" : "Không") << "\n";
    // Bạn cần biết đồ thị mẫu của mình có lưỡng phân hay không để kiểm tra đúng
    // Để xác định đồ thị của bạn có lưỡng phân không:
    // Đỉnh 0 -> 2, 5
    // Đỉnh 2 -> 6
    // Đỉnh 5 -> 3, 7
    // Đỉnh 3 -> 4
    // Đỉnh 4 -> 5 (chu trình 3-4-5, dài 3, lẻ -> không lưỡng phân)
    // Vì vậy, kết quả mong đợi là KHÔNG
    test_passed = !test_passed; // Nếu nó báo là Có, thì FAILED
    cout << "Test isBipartite: " << (test_passed ? "PASSED" : "FAILED") << "\n";


    // Test isCompleteBipartite
    cout << "\n--- Test isCompleteBipartite ---\n";
    test_passed = isCompleteBipartite(currentAdjMatrix); // Đồ thị của bạn không phải là lưỡng phân đầy đủ
    cout << "Có phải đồ thị lưỡng phân đầy đủ? " << (test_passed ? "Có" : "Không") << "\n";
    test_passed = !test_passed; // Đáng lẽ phải là Không, nên nếu trả về Có thì FAILED
    cout << "Test isCompleteBipartite: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test convertToUndirectedGraph
    cout << "\n--- Test convertToUndirectedGraph ---\n";
    vector<vector<int>> undirectedGraph = convertToUndirectedGraph(currentAdjMatrix);
    printMatrix(undirectedGraph, "Đồ thị vô hướng tương ứng");
    test_passed = !isDirected(undirectedGraph); // Đảm bảo đồ thị mới là vô hướng
    cout << "Test convertToUndirectedGraph: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test getComplementGraph
    cout << "\n--- Test getComplementGraph ---\n";
    vector<vector<int>> complementGraph = getComplementGraph(currentAdjMatrix);
    printMatrix(complementGraph, "Đồ thị bổ sung");
    // Kiểm tra đơn giản: Đảm bảo cạnh (0,0) không có trong bổ sung
    test_passed = (complementGraph[0][0] == 0);
    cout << "Test getComplementGraph: " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Test findEulerCycle (dùng đồ thị vô hướng)
    cout << "\n--- Test findEulerCycle ---\n";
    vector<int> eulerCycle = findEulerCycle(undirectedGraph); // Sử dụng đồ thị vô hướng
    cout << "Chu trình Euler: ";
    test_passed = eulerCycle.empty(); // Đồ thị của bạn có đỉnh bậc lẻ (ví dụ: đỉnh 0 bậc 3), nên không có chu trình Euler
    if (eulerCycle.empty()) {
        cout << "Không có hoặc không tìm thấy (mong đợi).\n";
    } else {
        for (int v : eulerCycle) {
            cout << v << " ";
        }
        cout << "\n";
    }
    cout << "Test findEulerCycle: " << (test_passed ? "PASSED" : "FAILED") << "\n";


    // Test dfsSpanningTree
    cout << "\n--- Test dfsSpanningTree (bắt đầu từ đỉnh 0) ---\n";
    vector<vector<int>> dfsTree = dfsSpanningTree(currentAdjMatrix, 0);
    printMatrix(dfsTree, "Cây bao trùm DFS");
    // Kiểm tra đơn giản: Đảm bảo có cạnh từ 0 đến 2 và 0 đến 5 trong cây (nếu có trong đồ thị gốc)
    test_passed = (dfsTree[0][2] == 1 || dfsTree[0][5] == 1); // Đảm bảo có ít nhất 1 cạnh từ 0
    cout << "Test dfsSpanningTree: " << (test_passed ? "PASSED" : "FAILED") << "\n";


    // Test bfsSpanningTree
    cout << "\n--- Test bfsSpanningTree (bắt đầu từ đỉnh 0) ---\n";
    vector<vector<int>> bfsTree = bfsSpanningTree(currentAdjMatrix, 0);
    printMatrix(bfsTree, "Cây bao trùm BFS");
    // Kiểm tra đơn giản: Đảm bảo có cạnh từ 0 đến 2 và 0 đến 5 trong cây (nếu có trong đồ thị gốc)
    test_passed = (bfsTree[0][2] == 1 || bfsTree[0][5] == 1); // Đảm bảo có ít nhất 1 cạnh từ 0
    cout << "Test bfsSpanningTree: " << (test_passed ? "PASSED" : "FAILED") << "\n";


    // Test isConnected
    cout << "\n--- Test isConnected ---\n";
    bool connected_0_6 = isConnected(0, 6, currentAdjMatrix); // 0 -> 2 -> 6. Dự kiến CÓ
    cout << "Đỉnh 0 và 6 có liên thông? " << (connected_0_6 ? "Có" : "Không") << "\n";
    bool connected_0_8 = isConnected(0, 8, currentAdjMatrix); // 0 -> 2 -> 6 (không liên thông với 8) hoặc 0 -> 5 -> 7 -> 8. Dự kiến CÓ
    cout << "Đỉnh 0 và 8 có liên thông? " << (connected_0_8 ? "Có" : "Không") << "\n";
    bool connected_6_0 = isConnected(6, 0, currentAdjMatrix); // 6 không có cạnh đi ra. Dự kiến KHÔNG
    cout << "Đỉnh 6 và 0 có liên thông? " << (connected_6_0 ? "Có" : "Không") << "\n"; 
    bool connected_6_7 = isConnected(6, 7, currentAdjMatrix); // 6 không có cạnh đi ra. Dự kiến KHÔNG
    cout << "Đỉnh 6 và 7 có liên thông? " << (connected_6_7 ? "Có" : "Không") << "\n"; 

    test_passed = (connected_0_6 == true && connected_0_8 == true && connected_6_0 == false && connected_6_7 == false);
    cout << "Test isConnected: " << (test_passed ? "PASSED" : "FAILED") << "\n";


    // Để test Dijkstra và Bellman-Ford, chúng ta cần một ma trận trọng số.
    // Dữ liệu input.txt của bạn là ma trận kề (0/1), coi như trọng số là 1 cho các cạnh tồn tại.
    vector<vector<int>> weightedAdjMatrix = currentAdjMatrix;

    cout << "\n--- Test Dijkstra (trọng số mặc định 1) ---\n";
    // Thử tìm đường đi từ 0 đến 6 (0 -> 2 -> 6)
    vector<int> pathDijkstra = dijkstra(0, 6, weightedAdjMatrix);
    cout << "Đường đi ngắn nhất từ 0 đến 6 (Dijkstra): ";
    if (pathDijkstra.empty()) {
        cout << "Không có đường đi hoặc không hợp lệ.\n";
        test_passed = false;
    } else {
        for (int i = 0; i < pathDijkstra.size(); ++i) {
            cout << pathDijkstra[i] << (i == pathDijkstra.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
        // Kiểm tra đường đi mong đợi: 0 -> 2 -> 6
        test_passed = (pathDijkstra.size() == 3 && pathDijkstra[0] == 0 && pathDijkstra[1] == 2 && pathDijkstra[2] == 6);
    }
    cout << "Test Dijkstra (0->6): " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Thử tìm đường đi từ 0 đến 8 (0 -> 5 -> 7 -> 8)
    pathDijkstra = dijkstra(0, 8, weightedAdjMatrix);
    cout << "Đường đi ngắn nhất từ 0 đến 8 (Dijkstra): ";
    if (pathDijkstra.empty()) {
        cout << "Không có đường đi hoặc không hợp lệ.\n";
        test_passed = false;
    } else {
        for (int i = 0; i < pathDijkstra.size(); ++i) {
            cout << pathDijkstra[i] << (i == pathDijkstra.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
        // Kiểm tra đường đi mong đợi: 0 -> 5 -> 7 -> 8
        test_passed = (pathDijkstra.size() == 4 && pathDijkstra[0] == 0 && pathDijkstra[1] == 5 && pathDijkstra[2] == 7 && pathDijkstra[3] == 8);
    }
    cout << "Test Dijkstra (0->8): " << (test_passed ? "PASSED" : "FAILED") << "\n";


    cout << "\n--- Test Bellman-Ford (trọng số mặc định 1) ---\n";
    // Thử tìm đường đi từ 0 đến 6
    vector<int> pathBellmanFord = bellmanFord(0, 6, weightedAdjMatrix);
    cout << "Đường đi ngắn nhất từ 0 đến 6 (Bellman-Ford): ";
    if (pathBellmanFord.empty()) {
        cout << "Không có đường đi hoặc không hợp lệ.\n";
        test_passed = false;
    } else {
        for (int i = 0; i < pathBellmanFord.size(); ++i) {
            cout << pathBellmanFord[i] << (i == pathBellmanFord.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
        // Kiểm tra đường đi mong đợi: 0 -> 2 -> 6
        test_passed = (pathBellmanFord.size() == 3 && pathBellmanFord[0] == 0 && pathBellmanFord[1] == 2 && pathBellmanFord[2] == 6);
    }
    cout << "Test Bellman-Ford (0->6): " << (test_passed ? "PASSED" : "FAILED") << "\n";

    // Thử tìm đường đi từ 0 đến 8
    pathBellmanFord = bellmanFord(0, 8, weightedAdjMatrix);
    cout << "Đường đi ngắn nhất từ 0 đến 8 (Bellman-Ford): ";
    if (pathBellmanFord.empty()) {
        cout << "Không có đường đi hoặc không hợp lệ.\n";
        test_passed = false;
    } else {
        for (int i = 0; i < pathBellmanFord.size(); ++i) {
            cout << pathBellmanFord[i] << (i == pathBellmanFord.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
        // Kiểm tra đường đi mong đợi: 0 -> 5 -> 7 -> 8
        test_passed = (pathBellmanFord.size() == 4 && pathBellmanFord[0] == 0 && pathBellmanFord[1] == 5 && pathBellmanFord[2] == 7 && pathBellmanFord[3] == 8);
    }
    cout << "Test Bellman-Ford (0->8): " << (test_passed ? "PASSED" : "FAILED") << "\n";

    cout << "\n--- Kết thúc Test Cases ---\n";

    return 0;
}
