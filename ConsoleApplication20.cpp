#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

Queue* createQueue(unsigned capacity) {
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = new int[(queue->capacity * sizeof(int))];
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

vector<vector<int>> generateRandomGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int random = rand() % 2;
            graph[i][j] = random;
            graph[j][i] = random;
        }
    }

    return graph;
}

void printMatrix(vector<vector<int>>& matrix) {
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void BFSUsingMatrix(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < graph[currentVertex].size(); i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void BFSUsingMatrixWithTime(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    auto start = high_resolution_clock::now();
    BFSUsingMatrix(graph, visited, startVertex);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nВремя обхода через матрицу смежности (стандартная queue): " << duration.count() << " микросекунд" << endl;
}

void BFSUsingCustomQueue(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    int n = graph.size();
    Queue* q = createQueue(n);
    enqueue(q, startVertex);
    visited[startVertex] = true;

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        cout << currentVertex << " ";

        for (int i = 0; i < n; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                enqueue(q, i);
                visited[i] = true;
            }
        }
    }
}

void BFSUsingCustomQueueWithTime(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    auto start = high_resolution_clock::now();
    BFSUsingCustomQueue(graph, visited, startVertex);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nВремя обхода через матрицу смежности (структура данных): " << duration.count() << " микросекунд" << endl;
}

void printAdjacencyList(vector<vector<int>>& graph) {
    cout << "Список смежности:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}


void BFSUsingLists(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;


    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";


        for (int i = 0; i < graph[currentVertex].size(); i++) {
            int adjacentVertex = graph[currentVertex][i];
            if (!visited[adjacentVertex]) {
                q.push(adjacentVertex);
                visited[adjacentVertex] = true;
            }
        }
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество вершин : ";
    cin >> n;


    vector<vector<int>> adjacencyMatrix = generateRandomGraph(n);
    printMatrix(adjacencyMatrix);

    vector<bool> visited(n, false);
    int startVertex;
    cout << "Введите вершину, с которой начать обход: ";
    cin >> startVertex;

    if (startVertex < 0 || startVertex >= n) {
        cout << "Некорректная вершина. Пожалуйста, введите вершину от 0 до " << n - 1 << "." << endl;
        return 0;
    }

    cout << "Обход в ширину через матрицу смежности: ";
    BFSUsingMatrixWithTime(adjacencyMatrix, visited, startVertex);

    vector<vector<int>> adjacencyList(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    visited.assign(n, false);
    cout << "\nОбход в ширину через кастомную очередь: ";
    BFSUsingCustomQueueWithTime(adjacencyMatrix, visited, startVertex);
    cout << endl;


    printAdjacencyList(adjacencyList);


    visited.assign(n, false);
    cout << "Обход в ширину через список смежности: ";
    BFSUsingLists(adjacencyList, visited, startVertex);
    cout << endl;


    return 0;
}
