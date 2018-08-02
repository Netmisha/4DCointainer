#ifdef _DEBUG
#define MainTest main
#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"

using PNod = Node<int>*;
using Tree = XTree<int>;

void ShowCurrentNode(Tree& tree)
{
    auto ToStr = [](PNod node)
    {
        if (node)
            return std::to_string(node->GetVal());
        else
            return std::string("{}");
    };

    PNod self = tree.Iter();
    PNod uber, prev, next, down;
    {
        uber = nullptr;
        prev = nullptr;
        next = nullptr;
        down = nullptr;
    }
    if (self)
    {
        uber = tree.Iter()->uber;
        if (self->prev != self)
            prev = tree.Iter()->prev;
        if (self->next !=self)
            next = tree.Iter()->next;
        down = tree.Iter()->down;
    }

    if (uber)
    {
        for (std::string str : { std::string{}, ToStr(uber), std::string{}})
        {
            std::cout.width(5);
            std::cout << str;
        }
        std::cout << std::endl;
    }

    if (self)
    {
        for (std::string str : { ToStr(prev), ToStr(self), ToStr(next) })
        {
            std::cout.width(5);
            std::cout << str;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout.width(5);
        std::cout << "{}" << std::endl;
    }
    
    if (down)
    {
        for (std::string str : { std::string{}, ToStr(down), std::string{} })
        {
            std::cout.width(5);
            std::cout << str;
        }
        std::cout << std::endl;
    }
}
void ShowCurrentRing(Tree& tree)
{
    size_t size = tree.GetRingLen();
    int*   ptr  = tree.RingToArr();

    std::cout << "ring of " << size << " elements: ";

    for (int i = 0; i < size; ++i)
    {
        std::cout.width(5);
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;

    delete[] ptr;
}


int* GetInt();

#define TestPush(Way, tree) \
{\
    int* p = GetInt();\
    bool result = tree.Push##Way (p);\
    std::cout << (result ? "ok" : "fail") << std::endl;\
}

#define TestGoto(Way, tree)\
{\
    std::cout << "Going " #Way " from: " << std::endl;\
    ShowCurrentNode(tree);\
    if (tree.Goto##Way())\
    {\
        std::cout << "to" << std::endl;\
        ShowCurrentNode(tree);\
    }\
    else\
    {\
        std::cout << "to nowhere" << std::endl;\
    }\
}

void TestPopIter(Tree&);


int MainTest()
{
    std::cout << "MainTest():" << std::endl;

    Tree tree;

    while (true)
    {
        std::string str;
        std::cin >> str;

        if (str == "quit")
        {
            break;
        }

        if (str == "show")
        {
            std::cin >> str;

            if (str == "elem")
            {
                ShowCurrentNode(tree);
                continue;
            }

            if (str == "ring")
            {
                ShowCurrentRing(tree);
                continue;
            }
        }

        if (str == "goto")
        {
            std::cin >> str;

            if (str == "next")
            {
                TestGoto(Next, tree);
                continue;
            }
            if (str == "prev")
            {
                TestGoto(Prev, tree);
                continue;
            }
            if (str == "uber")
            {
                TestGoto(Uber, tree);
                continue;
            }
            if (str == "down")
            {
                TestGoto(Down, tree);
                continue;
            }
            if (str == "root")
            {
                TestGoto(Root, tree);
                continue;
            }
        }

        if (str == "push")
        {
            std::cin >> str;


            if (str == "iter")
            {
                TestPush(Iter, tree);
                continue;
            }
            if (str == "next")
            {
                TestPush(Next, tree);
                continue;
            }
            if (str == "prev")
            {
                TestPush(Prev, tree);
                continue;
            }
            if (str == "down")
            {
                TestPush(Down, tree);
                continue;
            }
        }
        if (str == "pop")
        {
            TestPopIter(tree);
            continue;
        }

        std::cout << "unknown command, try:" << std::endl;
        std::cout << "show  elem|ring" << std::endl;
        std::cout << "push|goto  iter|prev|uber|next|down" << std::endl;
        std::cout << "pop" << std::endl;
        std::cout << "quit" << std::endl;
    }

    std::cout << "finish" << std::endl;
    return 0;
}

int* GetInt()
{
    int *p = new int;
    std::cin >> *p;
    return p;
}

void TestPopIter(Tree& tree)
{
    std::cout << "trying to pop: " << std::endl;
    ShowCurrentNode(tree);

    if (tree.PopIter())
    {
        std::cout << "success!" << std::endl;
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "fail" << std::endl;
    }
}

#endif