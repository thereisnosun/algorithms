#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "graph.h"
#include "directed_graph.h"
#include "directed_weight_graph.h"
#include "linked_list.h"
#include "general_algos.h"

#include "best_practises.h"
#include "matrix.h"

void MinimumCutTest();
void MinimumPathTest();
void TopologicalOrderTest();

void MergeSortTest();
void QuickSortTest();
void SCCTest();
void DijkstraTest();


//lets assume it is null turminated
void reverseStr(char* str, size_t index, size_t size)
{
	//size_t index = 0;
	//if (str[index] < size)
	//	return;
	
	
	char prev = *str;
	//++str;
	++index;
	reverseStr(str, index, size);
	char tmp = *str;
	//*str = prev;
	std::cout << prev << " ";
	//prev
}

std::string reverseStringRecursively(std::string str) 
{
	if (str.length() == 1) 
	{
		return str;
	}
	else 
	{
		return reverseStringRecursively(str.substr(1, str.length())) + str.at(0);
	}
}


void LL_LoopTest()
{
	LinkedList list;
	list.insertToEnd(1);
	list.insertToEnd(2);
	list.insertToEnd(3);
	list.createLoop();
	std::cout << "Loop existence - " << list.detectAndRemoveLoop() << std::endl;
}

#include "trie_str.h"
void Trie_Test()
{
	std::string keys[] = { "the", "a", "there",
		"answer", "any", "by",
		"bye", "their" };

	int n = sizeof(keys) / sizeof(keys[0]);

	TrieNode trie;
	for (int i = 0; i < n; ++i)
		trie.insert(keys[i]);

	std::cout << "Exists 'any' - " << trie.search("any") << std::endl;
	std::cout << "Exists 'rupert' - " << trie.search("rupert") << std::endl;
}


void treeTest()
{
	tree::treeNode  *root = tree::createNode(1);

	root->left = tree::createNode(2);
	root->right = tree::createNode(3);
	root->left->left = tree::createNode(4);
	root->left->right = tree::createNode(5);

	std::cout << tree::findDepth(root) << std::endl;

	std::cout << tree::checkIfBST(root) << std::endl;

	tree::treeNode  *rootBST = tree::createNode(5);
	rootBST->left = tree::createNode(2);
	rootBST->right = tree::createNode(6);
	rootBST->left->left = tree::createNode(1);
	rootBST->left->right = tree::createNode(3);
	std::cout << tree::checkIfBST(rootBST) << std::endl;
}

int main(int argc, char *argv[])
{
	/*std::cout << string::isInterleave("XY", "X", "XXY") << std::endl;
	std::cout << string::isInterleave("YX", "X", "XXY") << std::endl;*/

	std::cout << "Longest is - " << string::findLongestSubStr("aabbbbbcc", 2) << std::endl;
	//treeTest();
	return 0;

	std::cout << bits::diffBitSumsNaive({ 1,3, 5 }) << std::endl;
	std::cout << bits::diffBitSumsLinear({ 1,3, 5 }) << std::endl;

	//string::getNumericAbreviations("KAK");

	//Trie_Test();
	//LL_LoopTest();
	//std::cout << string::checkIfPalindrome("ROCK") << std::endl;
	//std::cout << string::checkIfPalindrome("ROOR") << std::endl;

	std::string reversed = reverseStringRecursively("ROCK");
	std::cout << "Reversed string is - " << reversed << std::endl;
    Item9AliasDeclaration();
	return 0;
}

void DijkstraTest()
{
    DirectedWeightGraph graph;
    graph.AddEdge(new DirectedWeightEdge{ 1, 2, EdgeDirection::FIRST_TO_SECOND, 1 });
    graph.AddEdge(new DirectedWeightEdge{ 1, 3, EdgeDirection::FIRST_TO_SECOND, 4 });
    graph.AddEdge(new DirectedWeightEdge{ 2, 3, EdgeDirection::FIRST_TO_SECOND, 2 });
    graph.AddEdge(new DirectedWeightEdge{ 2, 4, EdgeDirection::FIRST_TO_SECOND, 6 });
    graph.AddEdge(new DirectedWeightEdge{3, 4, EdgeDirection::FIRST_TO_SECOND, 3});
    auto dikstraPath = graph.FindShortestPath(1, 4);
}

void SCCTest()
{
    DirectedGraph directedGraph;
    directedGraph.AddEdge(new DirectedEdge{ 1, 7, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 1, 4, EdgeDirection::FIRST_TO_SECOND });
    directedGraph.AddEdge(new DirectedEdge{ 4, 7, EdgeDirection::FIRST_TO_SECOND });
    directedGraph.AddEdge(new DirectedEdge{7, 9, EdgeDirection::SECOND_TO_FIRST});
    directedGraph.AddEdge(new DirectedEdge{ 9, 6, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 5, 9, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{8, 3, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{3, 2, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{2, 8, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{ 6, 8, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 6, 5, EdgeDirection::SECOND_TO_FIRST });
    auto compSCC = directedGraph.ComputeSCC();

}

void TopologicalOrderTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    DirectedGraph directedGraph;
    directedGraph.AddEdge(new DirectedEdge{1, 2, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{1, 3, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{2, 4, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{3, 4, EdgeDirection::FIRST_TO_SECOND});
    auto topologicOrder = directedGraph.TopologicalOrder();
    Algo::PrintMap(topologicOrder);
#else
#endif
}

void MergeSortTest()
{
    int test[] = { 1, 23,64, 5, 7, 2, 56, 77, 234, 23,5,6,8,9,34,6,6,546, };
    std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));

    std::cout << "First implementation:\n";
    std::unique_ptr<std::vector<int>> vResVector = Sort::MergeSort(vVector);
    Algo::PrintContainer(vResVector->begin(), vResVector->end());
    
    std::cout << "\nSecond implementation:\n";
    int iSplit = Sort::MergeSort(vVector.begin(), vVector.end());
    std::cout << "Split inversions - " << iSplit << std::endl;
    Algo::PrintContainer(vVector.begin(), vVector.end());
}

void QuickSortTest()
{
    int test[] = { 1, 23,64, 5, 7, 2, 56, 77, 234, 23,5,6,8,9,34,6,6,546, };
    std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));
    Sort::QuickSort(vVector.begin(), vVector.end());

    Algo::PrintContainer(vVector.begin(), vVector.end());
   
}

void MinimumPathTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    Graph graphPath({ {0, 1, 1, 0, 0, 0},
                    {1, 0, 0, 1, 0, 0},
                    {1, 0, 0, 1, 1, 0 },
                    {0, 1, 1, 0, 1, 1 },
                    {0, 0, 1, 1, 0, 1 },
                    {0, 0, 0, 1, 1, 0 }, });
    int iPath = graphPath.FindMinimumPath(1, 4);
    std::cout << iPath;
#else
    Graph graphPath;
    graphPath.AddEdge(new Edge(1, 2));
    graphPath.AddEdge(new Edge(1, 3));
    graphPath.AddEdge(new Edge(2, 4));
    graphPath.AddEdge(new Edge(3, 4));
    graphPath.AddEdge(new Edge(3, 5));
    graphPath.AddEdge(new Edge(4, 5));
    graphPath.AddEdge(new Edge(4, 6));
    graphPath.AddEdge(new Edge(5, 6));
    int iPath = graphPath.FindMinimumPath(1, 4);
    std::cout << iPath;
#endif
}

void MinimumCutTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    Graph graph({ { 0, 1, 0, 0, 1 },
    { 1, 0, 1, 0, 1 },
    { 0, 1, 0, 1, 1 },
    { 0, 0, 1, 0, 1 },
    { 1, 1, 1, 1, 0 } });
    auto minimumCut = graph.FindMinimumCut();
    std::cout << minimumCut;
#else
    Graph graph;
    graph.AddEdge(new Edge(1, 2));
    graph.AddEdge(new Edge(1, 5));
    graph.AddEdge(new Edge(2, 3));
    graph.AddEdge(new Edge(4, 5));
    graph.AddEdge(new Edge(3, 4));
    graph.AddEdge(new Edge(2, 5));
    auto minimumCut = graph.FindMinimumCut();
    std::cout << minimumCut;
#endif
}