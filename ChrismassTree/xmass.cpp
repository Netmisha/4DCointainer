#ifdef _DEBUG
#define MainTest main
#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"

using PNod = Node<int>*;
using Tree = XTree<int>;

void ShowCurrentNode(Tree const& tree)
{
    auto ToStr = [](PNod node)
    {
        if (node)
        {
            return std::to_string(node->GetVal());
        }
        else
        {
            return std::string("{}");
        }
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
        {
            prev = tree.Iter()->prev;
        }
        if (self->next != self)
        {
            next = tree.Iter()->next;
        }
        down = tree.Iter()->down;
    }

    if (uber)
    {
        for (const auto& str : { std::string{}, ToStr(uber), std::string{}})
        {
            std::cout.width(5);
            std::cout << str;
        }
        std::cout << std::endl;
    }

    if (self)
    {
        for (const auto& str : { ToStr(prev), ToStr(self), ToStr(next) })
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
        for (const auto& str : { std::string{}, ToStr(down), std::string{} })
        {
            std::cout.width(5);
            std::cout << str;
        }
        std::cout << std::endl;
    }
}
void ShowCurrentRing(Tree const& tree)
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

enum class Way{Next = 1, Prev, Down, Uber, Root, Iter};
std::string WayToStr(Way way)
{
    switch (way)
    {
        case Way::Next: return "next";
        case Way::Prev: return "prev";
        case Way::Down: return "down";
        case Way::Uber: return "uber";
        case Way::Root: return "root";
        case Way::Iter: return "iter";
    }
}

void TestPush(Way way, Tree& tree)
{
    int* p = GetInt();
    bool result = false;
    switch (way)
    {
        case Way::Down: result = tree.PushDown(p); break;
        case Way::Next: result = tree.PushNext(p); break;
        case Way::Prev: result = tree.PushPrev(p); break;
        case Way::Iter: result = tree.PushIter(p); break;
    }
    std::cout << (result ? "ok" : "fail") << std::endl;
}

void TestGoTo(Way way, Tree& tree)
{
    std::cout << "Going " << WayToStr(way) << " from: " << std::endl;
    ShowCurrentNode(tree);
    bool result = false;
    switch (way)
    {
        case Way::Next: result = tree.GoToNext(); break;
        case Way::Prev: result = tree.GoToPrev(); break;
        case Way::Down: result = tree.GoToDown(); break;
        case Way::Uber: result = tree.GoToUber(); break;
        case Way::Root: result = tree.GoToRoot(); break;
    }
    if (result)
    {
        std::cout << "to" << std::endl; 
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "to nowhere" << std::endl;
    }
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
                TestGoTo(Way::Next, tree);
                continue;
            }
            if (str == "prev")
            {
                TestGoTo(Way::Prev, tree);
                continue;
            }
            if (str == "uber")
            {
                TestGoTo(Way::Uber, tree);
                continue;
            }
            if (str == "down")
            {
                TestGoTo(Way::Down, tree);
                continue;
            }
            if (str == "root")
            {
                TestGoTo(Way::Root, tree);
                continue;
            }
        }

        if (str == "push")
        {
            std::cin >> str;


            if (str == "iter")
            {
                TestPush(Way::Iter, tree);
                continue;
            }
            if (str == "next")
            {
                TestPush(Way::Next, tree);
                continue;
            }
            if (str == "prev")
            {
                TestPush(Way::Prev, tree);
                continue;
            }
            if (str == "down")
            {
                TestPush(Way::Down, tree);
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
        std::cout << "push  iter|prev|next|down" << std::endl;
        std::cout << "goto  iter|prev|uber|next|down" << std::endl;
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