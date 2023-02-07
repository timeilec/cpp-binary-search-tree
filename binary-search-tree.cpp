#include <iostream>
#include <vector>
#include <iomanip>

class Cell
{
    public:
        int getValue() { return cellValue; }
        void setValue(int value) { cellValue = value; }
        bool getExists() { return exists; }
        void setExists(bool value) { exists = value; }
    private:
        int cellValue;
        bool exists = false;
};

class Node
{
    public:
        Node(int value, int height)
        {
            nodeValue = value;
            nodeHeight = height;
        }
        ~Node()
        {
            delete leftTree;
            delete rightTree;
        }
        int getValue() { return nodeValue; }
        int getHeight() { return nodeHeight; }
        void makeLeftTree(int value) { leftTree = new Node(value,nodeHeight+1); }
        void makeRightTree(int value) { rightTree = new Node(value,nodeHeight+1); }
        Node* getLeftTree() { return leftTree; }
        Node* getRightTree() { return rightTree; }
    private:
        int nodeValue;
        int nodeHeight;
        Node* leftTree = nullptr;
        Node* rightTree = nullptr;
};

class BST
{
    public:
        BST() {  }
        ~BST() { delete rootNode; }
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder()
        {
            recursiveSort(rootNode);
            return sortedList;
        }
        int getHeight() { return treeHeight; }
        void prettyPrint();
    private:
        Node* rootNode = nullptr;
        int treeHeight = 0;
        int numNodes = 0;
        std::vector<int> sortedList;
        std::vector<int> sortedListHeights;
        std::vector<std::vector<Cell>> printVector;

        void recursiveSort(Node* node);
        void fillPrintVector();
        void outputPrintVector();
};

void BST::insertKey(int newKey)
{
    if (rootNode == nullptr)
    {
        rootNode = new Node(newKey, 1);
        numNodes += 1;
    }
    else
    {
        bool inserted = false;
        Node* currNode = rootNode;

        while (!inserted)
        {
            if ( newKey < currNode->getValue() )               // Key is smaller than current node value
            {
                if ( currNode->getLeftTree() == nullptr )    // There is no left child
                {
                    currNode->makeLeftTree(newKey);
                    inserted = true;
                    numNodes += 1;
                }
                else                                        // There is a left child      
                {
                    currNode = currNode->getLeftTree();
                }
            }

            if ( newKey > currNode->getValue() )               // Key is greater than current node value
            {
                if ( currNode->getRightTree() == nullptr )    // There is no right child
                {
                    currNode->makeRightTree(newKey);
                    inserted = true;
                    numNodes += 1;
                }
                else                                        // There is a right child      
                {
                    currNode = currNode->getRightTree();
                }
            }
        }
    }
}

bool BST::hasKey(int searchKey)
{
    if (rootNode == nullptr)
    {
        return false;
    }

    Node* currNode = rootNode;
    while (true)
    {
        if (currNode->getValue() == searchKey)
        {
            return true;
        }
        if ( searchKey < currNode->getValue() )               // Key is smaller than current node value
        {
            if ( currNode->getLeftTree() == nullptr )
            {
                return false;
            }
            currNode = currNode->getLeftTree();
        }
        if ( searchKey > currNode->getValue() )               // Key is bigger than current node value
        {
            if ( currNode->getRightTree() == nullptr )
            {
                return false;
            }
            currNode = currNode->getRightTree();
        }
    }
}

void BST::recursiveSort(Node* node)
{
    if (node != nullptr)
    {
        recursiveSort(node->getLeftTree());
        if (node->getHeight() > treeHeight)
        {
            treeHeight = node->getHeight();
        }
        sortedList.push_back(node->getValue());
        sortedListHeights.push_back(node->getHeight());
        recursiveSort(node->getRightTree());
    }
}

void BST::fillPrintVector()
{
    int insertRow;
    for (int i = 0; i < sortedList.size(); ++i)
    {
        for (int j = 0; j < printVector.size(); ++j)
        {
            insertRow = sortedListHeights.at(i) - 1;
            if (j == insertRow)
            {
                Cell cellToInsert;
                cellToInsert.setValue(sortedList.at(i));
                cellToInsert.setExists(true);
                printVector.at(j).push_back(cellToInsert);
            }
            else
            {
                Cell cellToInsert;
                printVector.at(j).push_back(cellToInsert);
            }
        }
    }
}

void BST::outputPrintVector()
{
    int numRows = printVector.size();
    int numColumns = printVector.at(0).size();
    Cell currentCell;

    for (int i = 0; i < numRows; ++i)
    {
        // Top row of output
        for (int j = 0; j < numColumns; ++j)
        {
            std::cout << "-----";
        }
        std::cout << "-";

        std::cout << std::endl;

        // Bottom row of output
        for (int j = 0; j < numColumns; ++j)
        {
            currentCell = printVector.at(i).at(j);
            std::cout << "|";
            if (currentCell.getExists() == true)
            {
                std::cout << std::setw(4) << currentCell.getValue();
            }
            else
            {
                std::cout << std::setw(4) << " ";
            }
        }
        std::cout << "|";

        std::cout << std::endl;
    }
    for (int j = 0; j < numColumns; ++j)
    {
        std::cout << "-----";
    }
    std::cout << "-";
}

void BST::prettyPrint()
{
    if (sortedList.size() > 0)
    {
        printVector.resize(treeHeight);
        fillPrintVector();
        outputPrintVector();
    }
}

int main()
{
    BST tree;

    // Insert integers into tree from user input
    std::cout << "Enter the numbers to be stored: ";
    int valueToStore;
    while (std::cin >> valueToStore)
    {
        tree.insertKey(valueToStore);
    }
    std::cin.clear();
    std::cin.ignore();

    // Print in sorted order
    std::vector<int> sortedList = tree.inOrder();
    std::cout << "The numbers in sorted order: ";
    for (int i = 0; i < sortedList.size(); ++i)
    {
        std::cout << sortedList.at(i) << " ";
    }
    std::cout << std::endl;

    // Pretty Print
    tree.prettyPrint();

    return 0;
}