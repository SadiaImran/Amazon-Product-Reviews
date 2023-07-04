#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <cfloat>
#include<stack>
#define V 20
using namespace std;
//----------------------------------------
struct Products {
	int productId ; 
	
	Products * next = NULL ; 
};
//----------------------------------------
struct Id { 
	Products * products = NULL ; 
};
Id * myHash[20] ; 
//----------------------------------------
struct Review
{
    string id;
    string productId;
    string userId;
    string profilerName;
    string helpfulnessNumerator;
    string helpfulnessDenominator;
    int score;
   
    string summary;
    string text;
    double price ; 

    Review *prev = NULL;
    Review *next = NULL;
};

Review *first = NULL;
Review *last = NULL;
Review * front = NULL ;
Review * rear = NULL ; 
//------------------------------------------
static int rating1 = 0 ; 
static int sum = 0 ; 
static int count = 0 ;
static int totalReviews = 0 ; 
const int MAX_HEAP_SIZE = 7292;
static int heapSize = -1;
Review *heap[MAX_HEAP_SIZE];


int bfsGraph[V][V];
int dfsGraph[V][V];
double graph[V][V];
//------------------------------------------
struct BST{
	BST * right = NULL ; 
	BST * left = NULL ; 

    string productId;
    string userId;
    string profilerName;
    int score;
    int id ; 
    double price ; 
	
};
BST * root = NULL ; 
//---------------------------------------
void printScore(){
	Review * curr = first ; 
	while(curr!=NULL){
		if(curr->score==5){
			cout << curr->profilerName << " , " << curr->productId << " , "
             << curr->score << " , " << curr->summary << endl;
		}
		curr=curr->next ;
	}
}

//--------------------------------------------
int height(BST * p ){
	if(p==NULL){
		return 0 ; 
	}
	else{
		int lheight = height(p->left)  ;
		int rheight = height(p->right)  ; 
		
		return max(lheight,rheight) + 1 ;
	}
}
//--------------------------------------------
int balancedFactor(BST * p ){
	return height(p->left) - height(p->right);
}
//--------------------------------------------
BST * rotateLeft(BST * y){
	BST * x = y->right ; 
	y->right = x->left ;
	x->left = y ;
	return x ; 
}
//--------------------------------------------
BST * rotateRight(BST * y){
	BST * x = y->left ; 
	y->left = x->right ;
	x->right = y ; 
	return x ;  
}
//--------------------------------------------
BST * rotateLeftRight(BST * x ){
	 x->left = rotateLeft(x->left);
	 x = rotateRight(x);
	 return x ;
}
//--------------------------------------------
BST * rotateRightLeft(BST * x){
	x->right = rotateRight(x->right);
	x = rotateLeft(x);
	return x ;
}
//--------------------------------------------
BST * insertAVL(BST * p ,int id ,  string productId , string userId , string profilerName , int score ,  double price ){
	if(p==NULL){
		 p = new BST ; 
	
    p->productId = productId;
    p->userId = userId;
    p->profilerName = profilerName;
    p->score = score;

    p->id = id ; 
    p->price = price ; 
	}
	else{
		if(id > p->id){
			p->right = insertAVL(p->right ,  id ,productId ,  userId ,  profilerName ,  score ,  price);
			if(balancedFactor(p)==-2){
				if(id>p->right->id){
					p = rotateLeft(p);
				}
				else{
					p=rotateRightLeft(p);
				}
			}
		}
		else{
			if(id<p->id){
				p->left = insertAVL(p->left, id , productId ,  userId ,  profilerName ,  score , price);
				if(balancedFactor(p)==2){
					if(id<p->left->id){
						p=rotateRight(p);
					}
					else{
						p=rotateLeftRight(p);
					}
				}
			}
		}
	}
	return p ; 
}
//------------------------------------------

// Add nodes to the linked list
void addNode(string id, string productId, string userId, string profilerName,
             string helpfulnessNumerator, string helpfulnessDenominator, int score, double price,
             string summary, string text)
{
    Review *newNode = new Review;
    newNode->id = id;
    newNode->productId = productId;
    newNode->userId = userId;
    newNode->profilerName = profilerName;
    newNode->helpfulnessNumerator = helpfulnessNumerator;
    newNode->helpfulnessDenominator = helpfulnessDenominator;
    newNode->score = score;
   
    newNode->price = price ; 
    newNode->summary = summary;
    newNode->text = text;

    // If the list is empty, make the new node the first and last node
    if (first == NULL)
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        // Add the new node at the end of the list
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
}
//------------------------------------------
void preOrder(BST * myRoot){
	if (myRoot != NULL) {
        cout << myRoot->id<<" ";
        preOrder(myRoot->left);
        preOrder(myRoot->right);
    }
}
//------------------------------------------
void inOrder(BST *myRoot) {
    if (myRoot != NULL) {
        inOrder(myRoot->left);
        cout << myRoot->id<<" ";
        inOrder(myRoot->right);
    }
}
//----------------------------------------
// Print information about all reviews
void printReviews()
{
    Review *current = first;
    cout << "Profiler , Product Id , Score , Summary" << endl;
    while (current != NULL)
    {
        cout << current->profilerName << " , " << current->productId << " , "
             << current->score << " , " << current->summary << " , " << current->price<< endl;
        current = current->next;
    }
}
//------------------------------------------
void swapReviews(Review* ptr1, Review* ptr2) {
    Review temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
//------------------------------------------
void insertHeap(string id, string productId, string userId, string profilerName,
             string helpfulnessNumerator, string helpfulnessDenominator, int score, double price,
             string summary, string text ){

	Review * p = new Review ; 
	 p->id = id;
    p->productId = productId;
    p->userId = userId;
    p->profilerName = profilerName;
    p->helpfulnessNumerator = helpfulnessNumerator;
    p->helpfulnessDenominator = helpfulnessDenominator; 
    p->score = score;
    p->price = price;
    p->summary = summary;
    p->text = text;
	
	if(heapSize==MAX_HEAP_SIZE){
	
		cout<<"No space \n";
		return ; 
	}
	else{

		heapSize ++ ;
		int parent ; 

		heap[heapSize] = p ; 
	
		int tlast = heapSize ; 
		bool adjusted = false ; 
		while((!adjusted)&&tlast>=0){

			if(tlast%2!=0){
				//odd child 
	
				parent = (tlast-1)/2 ;
			}
			else{
				//even child 

				parent = (tlast-1)/2 ; 
			}
	
            
            int currentId = heap[tlast]->score; 
			int parentId = heap[parent]->score;
  
            
            if (currentId > parentId) {
                swapReviews(heap[parent], heap[tlast]);
                tlast = parent;
            }
			else{

				adjusted = true ; 
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
void displayHeap()
{
    cout << "Heap-wise Sorted Data:\n";
    for (int i = 0; i <= heapSize; i++)
    {
        cout << heap[i]->id << " , " << heap[i]->profilerName << " , " << heap[i]->productId << " , "
             << heap[i]->score << " , " << heap[i]->summary  << " , " <<heap[i]->price<< endl;
    }
}
//---------------------------------------------------------------------------------------------------------
void init( int MAX_HEAP_SIZE ){
	for(int i = 0 ; i<MAX_HEAP_SIZE ; i++){
		for(int j = 0 ; j<MAX_HEAP_SIZE ; j++){
			graph[i][j] = 0 ;
		}
	}
}
//--------------------------------------------------------------------------------------------------------
void printAdjMatrix(int size){
	cout<<"  | ";
	for(int i = 0 ; i<size;i++){
		cout<<i<<" | ";
	}
	cout<<endl;
	for(int i =0 ; i<size ; i++){
		cout<<i<<" | ";
		for(int j = 0; j<size ; j++){
			cout<<graph[i][j]<<"   ";
		}
		cout<<endl;
	}
	cout<<endl;
}
//------------------------------------------
void addEdge(int i , int j , int edge ){

		graph[i][j] = edge ;
		graph[j][i] = edge ;
	
}
//------------------------------------------------------------------
bool searchHash(string s ){
	bool ans = false ; 
	int id = 0;
	 for (int c = 0 ; c<s.length() ; c++) {
        id += static_cast<int>(s[c]);
    }
    
	int index = id%20;

	if(myHash[index]->products==NULL){
		return false ; 
	}
	else{
		Products * p = myHash[index]->products;
		while (p != NULL && p->productId != id) {
    		p = p->next;
			}
		if(p==NULL){
			return false ; 
		}
		else{
			return true;
		}
	}
}
//-------------------------------------------------------------------------
void insertHash(string s) {
	
    int id = 0;

    for (int c = 0; c < s.length(); c++) {
        id += static_cast<int>(s[c]);
    }
    

    if (searchHash(s)) {

        return;
    }

    int index = id % 20;

    if (myHash[index]->products == NULL) {
        myHash[index]->products = new Products;
        myHash[index]->products->productId = id;
    } else {
        Products *p = myHash[index]->products;
        while (p->next != NULL) {
            p = p->next;
        }
        Products *newProduct = new Products;
		newProduct->productId = id;
		newProduct->next = NULL;
		p->next = newProduct;
		    }
}
//--------------------------------------------------------------------
void displayHash() {
    for (int i = 0; i < V; i++) {
        if (myHash[i]->products == NULL) {
            cout << "No product saved for index value: " << i << endl;
        } else {
            Products *p = myHash[i]->products;
            cout << "Products saved at index value " << i << ": ";
            while (p != NULL) {
                cout << p->productId << ", ";
                p = p->next;
            }
            cout << endl;
        }
    }
}

//-------------------------------------------------------------------------
int minDist(double dist[], bool visited[])
{
    double min = DBL_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}
//-----------------------------------------------------
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    cout << j << "  ";
}
//------------------------------------------------------
void printSolution(double dist[], int parent[], int src)
{
    std::cout << "Vertex\t\tDistance\tPath\n";
    for (int i = 0; i < V; i++)
    {
        cout << src << " -> " << i << "\t\t" << dist[i] << "\t\t";
        printPath(parent, i);
        cout << std::endl;
    }
}
//-------------------------------------------------------
void dijkstra(double graph[V][V], int src)
{
    double dist[V];
    bool visited[V];
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = DBL_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < 20; count++)
    {
        int u = minDist(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] > 0 && dist[u] != DBL_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, src);
}
//--------------------------------------------------------
void dijkstraCall(){

    Review* p = first;
    Review* q = first;
    double priceDifference;
    for (int i = 0; i < V; i++) {

        Review* q = first;
        for (int j = 0; j < V; j++) {

            if (p->price >= q->price) {
                priceDifference = p->price - q->price;
            } else {
                priceDifference = q->price - p->price;
            }

            graph[i][j] = priceDifference;

            q = q->next;
            
        }

        p = p->next;
    }

    dijkstra(graph, 0);
}
//------------------------------------------
int extractMin(bool visited[], double distances[], int vertices) {
    double minDistance = DBL_MAX;
    int minVertex = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minVertex = i;
        }
    }
    return minVertex;
}
//------------------------------------------
#include <iomanip> // Include this header for setw() function
void prims(int source, int vertices) {
    bool visited[vertices];
    double distances[vertices];
    int parent[vertices];
    int path[vertices];

    // Initialize distances and visited array
    for (int i = 0; i < vertices; i++) {
        distances[i] = DBL_MAX;
        visited[i] = false;
    }
    distances[source] = 0;
    parent[source] = -1;
	
    for (int i = 0; i < vertices ; i++) {
        int u = extractMin(visited, distances, vertices);
        
        visited[u] = true;
        path[i] = u ;
        

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < distances[v]) {
                distances[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Display Prim's result
    cout << "Vertices\tVisited\t\tDistance\t\tParent" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << i << "\t\t" << visited[i] << "\t\t";
        if (distances[i] == DBL_MAX)
            cout << "INF\t\t";
        else
            cout << fixed << setprecision(2) << distances[i] << "\t\t\t";
        cout << parent[i] << endl;
    }
    
    //Displaying Path 
    cout << "\nSpanning Tree Path\n\n";
    for (int i = 0; i < vertices ; i++) {
        cout << path[i] << " -> ";
    }
    cout << " X\n\n";
   
}
//--------------------------------------------------------------------------
double calculateReviewSimilarity(Review* review1, Review* review2) {
    double rating1 = review1->score;
    double rating2 = review2->score;
    
    double similarity = 1.0 / (1.0 + abs(rating1 - rating2));

    return similarity;
}
//-----------------------------------------------------------------
void bfs(int bfsGraph[V][V], int start)
{
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        
        cout<<current<<" ";


        for (int neighbor = 0; neighbor < V; ++neighbor)
        {
            if (bfsGraph[current][neighbor] && !visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    delete[] visited;
}
//----------------------------------------------------------------------------------
void bfsImplementation(){
	Review* p = first;
	Review* q = first;
	double weight;
	for (int i = 0; i < V; i++) {

    	Review* q = first;
   		for (int j = 0; j < V; j++) {

        	double similarity = calculateReviewSimilarity(p, q);

        	if(similarity >= (1/2)){
        		bfsGraph[i][j] = 1;
			}
			else{
				bfsGraph[i][j] = 0;
			}

        	q = q->next;
        
    	}
   		p = p->next;
	}
	
	bfs(bfsGraph,0);
}
//-----------------------------------------------
void initializeGraph(){
	Review* p = first;
	Review* q = first;
	double priceDifference;
	for (int i = 0; i < V; i++) {

		Review* q = first;
		for (int j = 0; j < V; j++) {

			if (p->price >= q->price) {
				priceDifference = p->price - q->price;
			} else {
				priceDifference = q->price - p->price;
			}

			graph[i][j] = priceDifference;
		//	cout<<q->price<<endl;
			q = q->next;

		 }
	
	 p = p->next;

	}
}
//---------------------------------------------------------
void doHashing(){
	Review * p = first ;
		int c = 0 ;  
		while(p!=NULL){
			insertHash(p->productId);	
			p=p->next  ; 
		}
		displayHash();
}
//---------------------------------------------------------


//START OF PROGRAM
int main()
{
	for (int i = 0; i < 20; i++) {
        myHash[i] = new Id ;
    }

    ifstream fin("Amazon.csv");
    if (!fin)
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line, word;
    vector<string> lineData;
    int lines = 0;

    // Read the file line by line
    while (getline(fin, line))
    {
        stringstream ss(line);
        while (getline(ss, word, ','))
        {
            lineData.push_back(word);
        
        }
		stringstream s2(lineData[6]);
        int score;
        s2>>score;
        
		stringstream s3(lineData[0]);
        int id;
        s3>>id;
        
        stringstream s4(lineData[7]);
        double price;
        s4>>price;
        
        // Process the data and add it to the linked list
        if (lines != 0)
        {
            addNode(lineData[0], lineData[1], lineData[2], lineData[3], lineData[4],
                    lineData[5], score, price, lineData[8], lineData[9]);

            root = insertAVL(root,id,lineData[1], lineData[2], lineData[3],score,price);
	
		    insertHeap(lineData[0], lineData[1], lineData[2], lineData[3], lineData[4],
                    lineData[5], score, price, lineData[8], lineData[9]);
		
		
        }
		
        // Clear the vector for the next line
        lineData.clear();
        totalReviews++;
        lines++;
        
    }

	cout<<endl ; 
	

   
    int choice ; 
    do
    {
    	cout<<"-------------------<<<WELCOME TO AMAZON PRODUCT REVIEWS>>>---------------\n";
        cout<<"| 		1. Print information about all reviews               	|"<<endl;
        cout<<"| 		2. Print information about reviews having score 5     	|"<<endl;
        cout<<"| 		3. Display in AVL                                     	|\n";
        cout<<"| 		4. Display in HEAP                                    	|\n";
        cout<<"| 		5. Dijkastra Implementation                           	|\n";
        cout<<"| 		6. Prims Implementation                              	|\n";
        cout<<"| 		7. Hashing                                            	|\n";
        cout<<"| 		8. BFS                                                	|\n";
        cout<<"| 		Select an option or 0 to exit:                        	|\n";
        cout<<"-------------------------------------------------------------------------\n";
        cin>>choice;
        switch(choice)
        {
            case 1 :
            {
                printReviews();
                break;
            }
            case 2 :
            {
               printScore();
                break;
            }
			case 3 :{
				cout<<"------------------------------------------------------------------------------\n";
				inOrder(root);
				cout<<"\n------------------------------------------------------------------------------\n";
				break;
			}
			case 4 : {
				displayHeap();
				break;
			}
			case  5 : { 
			
				dijkstraCall();
				break;
			}
			case 6 : {
				initializeGraph();
				prims(0,V);
				break ; 
			}
			case 7 : {
				cout<<"a. Insert a product\nb. Search for a product\n";
				char ans ; 
				cin>>ans;
				if(ans == 'a'){
					doHashing();
				}
				else{
					string productId ; 
					cout<<"Enter Product Id to search : \n";
					cin>>productId;
					cout<<"----------------------------------\n";
					std::cout << (searchHash(productId) ? "Product Found" : "Product Not Found") << std::endl;
					cout<<"----------------------------------\n";
				}
				
				
				break;
			}
			case 8 : {
				cout<<"Traversing In BFS is as Follow : \n\n";
				bfsImplementation();
				cout<<endl<<"\n";
				
				break;
			}
            default :
            {
                cout<<"Invalid choice!"<<endl;
            }
        }
    }
    while(choice!=0);

   
    fin.close();
    return 0;
}

