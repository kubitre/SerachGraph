#include <iostream>
#include <vector>
#include <queue>

/*
 *
 * */
std::vector<std::vector<int>>* breadthFirstSearch(
        std::vector<std::vector<int>> &graph,
        int countVertex,
        int startVertex
        ){
    std::queue<int> passedVertex;
    passedVertex.push(startVertex);

    std::vector<bool> isPassed(countVertex);

    std::vector<int> lengthShortRoute (countVertex),
                     vertexFromPassed (countVertex);

    isPassed[startVertex] = true;
    lengthShortRoute[startVertex] = -1;

    while(!passedVertex.empty()){
        int currentVertex = passedVertex.front();
        passedVertex.pop();

        for(size_t i =0; i < graph[currentVertex].size(); ++i){
            int toVertex = graph[currentVertex][i];
            if(!isPassed[toVertex]){
                isPassed[toVertex] = true;
                passedVertex.push(toVertex);

                lengthShortRoute[toVertex] = lengthShortRoute[currentVertex] + 1;
                vertexFromPassed[toVertex] = currentVertex;
            }
        }
    }
    std::vector<std::vector<int>>* results = new std::vector<std::vector<int>>{lengthShortRoute, vertexFromPassed};

    return results;
}
/*
 *
 * */
void inCycle(
        std::vector<std::vector<int>> &graph,
        std::vector<int> &passedVertexs,
        std::vector<int> &wayVertex,
        int startVertex){
    for(std::vector<int>::iterator i = graph[startVertex].begin(); i != graph[startVertex].end(); i++){
        if(!(passedVertexs[*i])){
            passedVertexs[*i] = 1;
            wayVertex.push_back(*i);
            inCycle(
                    graph,
                    passedVertexs,
                    wayVertex,
                    *i
            );
        }
    }
}

std::vector<std::vector<int>> *DepthFirstSearch(
        std::vector<std::vector<int>> &graph,
        int countVertex,
        int startVertex
        ){
    std::vector<int> passedVertexs(countVertex);
    std::vector<int> wayVertex;

    inCycle(graph, passedVertexs, wayVertex, startVertex);

    std::vector<std::vector<int>> *result = new std::vector<std::vector<int>> {passedVertexs, wayVertex};
    return result;
}




void TestFunc(
        std::vector<std::vector<int>> graph,
        std::string nameFunction,
        std::vector<std::vector<int>> *(*Func)(
                std::vector<std::vector<int>> &,
                int,
                int
                ),
        std::vector<std::vector<int>> expectedResult,
        std::vector<std::vector<int>> *resultFromFunc,
        int countVertex,
        int startVertex
        ){
    resultFromFunc = Func(
            graph,
            countVertex,
            startVertex
            );

    std::cout<<"Test result of the function ["<<nameFunction<<"]: "<< (*resultFromFunc == expectedResult)<<std::endl;
}

void TestData_BFS(std::vector<std::vector<int>>*result){
    std::vector<std::vector<int>> graph = {{1, 2}, {0, 2, 3}, {0, 1, 3},{0, 1}};
    std::vector<std::vector<int>> expectedResult = {{-1,0,0,1}, {0,0,0,1}};

    int countVertex = 4;
    int startVertex = 0;


    TestFunc(
            graph,
            "Breadth-first search",
            breadthFirstSearch,
            expectedResult,
            result,
            countVertex,
            startVertex
    );

}

void TestData_DFS(std::vector<std::vector<int>>*result){
    std::vector<std::vector<int>> graph = {{1, 2}, {0, 2, 3}, {0, 1, 3},{0, 1}};
    std::vector<std::vector<int>> expectedResult = {{1,1,1,1}, {1,0,2,3}};

    int countVertex = 4;
    int startVertex = 0;


    TestFunc(
            graph,
            "Depth-first search",
            DepthFirstSearch,
            expectedResult,
            result,
            countVertex,
            startVertex
    );
}

int main() {
    std::vector<std::vector<int>> *result;
    TestData_BFS(result);
    TestData_DFS(result);
    return 0;
}