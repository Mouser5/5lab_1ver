#include "conio.h"
#include <iostream>
#include <windows.h>
#include <sstream> 
#include <fstream>
#include <string>

using namespace std;

#include "windows.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Tree {
    string word;
    string number;
    Tree* left;
    Tree* right;
};

Tree* FillTree(Tree* tree, string word, string number) {
    if (tree == NULL) {
        tree = new Tree;
        tree->left = NULL;
        tree->right = NULL;
        tree->word = word;
        tree->number = number;
    }
    else
    {
        if (tree->word > word)
            tree->left = FillTree(tree->left, word, number);
        if (tree->word < word)
            tree->right = FillTree(tree->right, word, number);
        if (tree->word == word)
            tree->number =tree->number+number;
    }
    return (tree);
}

int x = 0, temp = 0;
int PrintTree(Tree* tree, int y)
{
    int size;
    if (tree != NULL)
    {
        PrintTree(tree->left, y + 1);
        if (y > temp)
            temp = y;
        gotoxy(x, y);
        cout << tree->word << " " << tree->number;
        size = tree->word.length() + tree->number.length();
        x+=size+2;
        PrintTree(tree->right, y + 1);
    }
    return(temp);
}

void Program() {
    Tree* tree = NULL;
    int temp = 0,row=1;
    string word,line,number;
    ifstream inFile("input.txt", ios::in);
    while (!inFile.eof()) {
        getline(inFile, line);
        stringstream ss;
        ss << row;
        number = "";
        number = ss.str();
        istringstream iss(line);
        while (iss >> word) {
            tree = FillTree(tree, word, number);
        }
        row++;
    }
    cout << "This is your tree:" << endl;
    temp=PrintTree(tree, 1);
    gotoxy(0, temp);
}

int main()
{
    Program();
}