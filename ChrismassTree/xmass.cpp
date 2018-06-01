/*
    create XTree<Type>
    
    init root:
    ...
        tree.PushIter(new Type);
    ...

    use Goto-functions to navigate
        Uber, Prev, Next, Down

    ...
        tree.GotoNext() <==> iter = iter->next
    ...

    use Push-functions to add elements
        Prev, Next, Down
    ...
        tree.PushPrev(new element) // push before iter
    ...

        tree.PushDown(element) <==> GotoDown, PushPrev, GotoUber
*/


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
    PNod self = tree.Iter();
    if (!self)
    {
        std::cout.width(5);
        std::cout << "{}" << std::endl;
        return;
    }
    PNod uber, prev, next, down;
    {
        uber = nullptr;
        prev = nullptr;
        next = nullptr;
        down = nullptr;
    }
    if (self->uber)
        uber = self->uber;
    if (self->down)
        down = self->down;
    if (uber)
    {
        std::cout.width(5);
        std::cout << (uber ? std::to_string(uber->GetVal()) : "{}") << std::endl;
    }
    std::cout.width(5);
    std::cout << std::to_string(self->GetVal()) << " ";
    for (next = self->next; next != self; next = next->next)
    {
        std::cout.width(5);
        std::cout << std::to_string(next->GetVal()) << " ";
    }
    std::cout << std::endl;
    std::cout.width(5);
    std::cout << (down ? std::to_string(down->GetVal()) : "{}") << std::endl;

}

void TestGotoNext(Tree&);
void TestGotoPrev(Tree&);
void TestGotoUber(Tree&);
void TestGotoDown(Tree&);

void TestPushIter(Tree&);
void TestPushNext(Tree&);
void TestPushPrev(Tree&);
void TestPushDown(Tree&);

int MainTest()
{
    {
        Tree tree;

        std::cout << "MainTest()" << std::endl;

        while (true)
        {
            std::string str;
            std::cin >> str;

            if (str == "quit")
            {
                break;
            }

            if (str == "show") {
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

                if (str == "next") {
                    TestGotoNext(tree);
                    continue;
                }
                if (str == "prev") {
                    TestGotoPrev(tree);
                    continue;
                }
                if (str == "uber")
                {
                    TestGotoUber(tree);
                    continue;
                }
                if (str == "down")
                {
                    TestGotoDown(tree);
                    continue;
                }
            }

            if (str == "push")
            {
                std::cin >> str;


                if (str == "iter")
                {
                    TestPushIter(tree);
                    continue;
                }
                if (str == "next")
                {
                    TestPushNext(tree);
                    continue;
                }
                if (str == "prev")
                {
                    TestPushPrev(tree);
                    continue;
                }
                if (str == "down")
                {
                    TestPushDown(tree);
                    continue;
                }
            }

            std::cout << "unknown command, try:" << std::endl;
            std::cout << "show, go, push, iter, prev, uber, next, down" << std::endl;
        }
    }
    std::cout << "finish" << std::endl;
    return 0;
}


void TestGotoNext(Tree& tree)
{
    std::cout << "Going next from: " << std::endl;
    ShowCurrentNode(tree);

    if (tree.GotoNext())
    {
        std::cout << "to" << std::endl;
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "to nowhere" << std::endl;
    }
}
void TestGotoPrev(Tree& tree)
{
    std::cout << "Going prev from: " << std::endl;
    ShowCurrentNode(tree);

    if (tree.GotoPrev())
    {
        std::cout << "to" << std::endl;
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "to nowhere" << std::endl;
    }
}
void TestGotoUber(Tree& tree)
{
    std::cout << "Going uber from: " << std::endl;
    ShowCurrentNode(tree);

    if (tree.GotoUber())
    {
        std::cout << "to" << std::endl;
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "to nowhere" << std::endl;
    }
}
void TestGotoDown(Tree& tree)
{
    std::cout << "Going down from: " << std::endl;
    ShowCurrentNode(tree);

    if (tree.GotoDown())
    {
        std::cout << "to" << std::endl;
        ShowCurrentNode(tree);
    }
    else
    {
        std::cout << "to nowhere" << std::endl;
    }
}

int* GonnaPush(std::string what)
{
    int *p = new int;
    std::cin >> *p;
    return p;

}
void TestPushIter(Tree& tree)
{
    int* p = GonnaPush("iter");
    bool result = tree.PushIter(p);
    std::cout << (result ? "ok" : "fail") << std::endl;
}
void TestPushNext(Tree& tree)
{
    int* p = GonnaPush("next");
    bool result = tree.PushNext(p);
    std::cout << (result ? "ok" : "fail") << std::endl;
}
void TestPushPrev(Tree& tree)
{
    int* p = GonnaPush("prev");
    bool result = tree.PushPrev(p);
    std::cout << (result ? "ok" : "fail") << std::endl;
}
void TestPushDown(Tree& tree)
{
    int* p = GonnaPush("down");
    bool result = tree.PushDown(p);
    std::cout << (result ? "ok" : "fail") << std::endl;
}


#endif