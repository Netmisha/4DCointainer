#ifndef __X__TREE__INCLUDED__
#define __X__TREE__INCLUDED__

#include <ciso646>

template<class Type>
struct Node
{
    Node(Type const* ptr) {
        pval = const_cast<Type*>(ptr);
    }
    ~Node() {
        delete pval;
    }
    Type const& GetVal() const {
        return *pval;
    }
    void        SetVal(Type const* ptr) {
        delete pval;
        pval = const_cast<Type*>(ptr);
    }
    Node* uber = nullptr;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node* down = nullptr;
protected:
    Type* pval;
};

template<class Type>
class XTree
{
public:
    XTree() {}
    ~XTree() 
    {
        RecursiveDestruction(root);
    }

    using XNode = Node<Type>;

    XNode* Iter() const { return iter; }
    XNode* Root() const { return root; }

    bool GoToNext() 
    { 
        if (iter)
        {
            if (iter->next)
            {
                iter = iter->next;
                return true;
            }
        }
        return false;
    }
    bool GoToPrev() 
    { 
        if (iter)
        {
            if (iter->prev)
            {
                iter = iter->prev;
                return true;
            }
        }
        return false;
    }
    bool GoToUber() 
    { 
        if (iter)
        {
            if (iter->uber)
            {
                iter = iter->uber;
                return true;
            }
        }
        return false;
    }
    bool GoToDown() 
    { 
        if (iter)
        {
            if (iter->down)
            {
                iter = iter->down;
                return true;
            }
        }
        return false;
    }
    bool GoToRoot()
    {
        if (root)
        {
            iter = root;
            return true;
        }
        return false;
    }

    bool PushIter(Type const* p)
    {
        if (not iter)
        {
            XNode* node = new XNode(p);
            root = iter = node;

            iter->next = iter;
            iter->prev = iter;
        }
        else {
            iter->SetVal(p);
        }

        return true;
    }
    bool PushPrev(Type const* p)
    {
        bool pushResult = false;

        if (iter)
        {
            XNode* node = new XNode(p);
            XNode* prev = iter->prev;

            node->prev = prev;
            prev->next = node;

            node->next = iter;
            iter->prev = node;

            if (iter->uber)
            {
                node->uber = iter->uber;
            }

            pushResult = true;;
        }

        return pushResult;
    }
    bool PushNext(Type const* p)
    {
        bool pushResult = false;

        if (iter)
        {
            XNode* node = new XNode(p);
            XNode* next = iter->next;

            node->next = next;
            next->prev = node;

            node->prev = iter;
            iter->next = node;

            if (iter->uber)
            {
                node->uber = iter->uber;
            }

            pushResult = true;
        }

        return pushResult;
    }
    bool PushDown(Type const* p)
    {
        bool pushResult = false;

        if (iter)
        {
            if (GoToDown())
            {
                PushPrev(p);
                GoToUber();
            }
            else
            {
                XNode* node = new XNode(p);

                node->next = node;
                node->prev = node;

                iter->down = node;
                node->uber = iter;
            }

            pushResult = true;
        }

        return pushResult;
    }

    bool PopIter()
    {
        if (!iter)
        {
            return false;
        }

        if (iter == root)
        {
            RecursiveDestruction(iter);
            iter = nullptr;
            return true;
        }

        if (iter->next == iter)
        {
            GoToUber();
            RecursiveDestruction(iter->down);
            iter->down = nullptr;
            return true;
        }

        XNode* kill = iter;

        if (iter->uber)
        {
            auto uber = iter->uber;
            if (uber->down == iter)
            {
                uber->down = iter->next;
            }
        }
        auto prev = iter->prev;
        prev->next = iter->next;
        auto next = iter->next;
        next->prev = iter->prev;

        iter = iter->next;

        RecursiveDestruction(kill->down);
        delete kill;

        return true;
    }

    /**
    Get array representing current ring
    Keeps last iter copy and last return result

    Tracks 
        if iter was changed
        if ring size has changed
    Checks if memory obtained from last call needs being set free
    */
    Type* RingToArr() const
    {
        static Type* ptr = nullptr;
        //static XNode* rter = iter;

        if (iter)
        {
            if (not ptr)
            {
                ptr = GetIterRing();
            }
            else
            {
                delete[] ptr;
                ptr = GetIterRing();
                //rter = iter;
            }
        }

        return ptr;
    }
    size_t GetRingLen() const
    {
        size_t len = 0;
        if (iter)
        {
            ++len;
            for (XNode* it = iter->next; it != iter; it = it->next)
            {
                ++len;
            }
        }
        return len;
    }
private:
    XNode* root = nullptr;
    XNode* iter = nullptr;

    Type* GetIterRing() const
    {
        size_t len = GetRingLen();

        Type* ptr = new Type[len];

        XNode* it = iter;
        for (int i = 0; i< len; ++i)
        {
            ptr[i] = it->GetVal();
            it = it->next;
        }

        return ptr;
    }

    void RecursiveDestruction(XNode* node)
    {
        if (!node)
        {
            return;
        }

        RecursiveDestruction(node->down);

        node->prev->next = nullptr;
        RecursiveDestruction(node->next);

        delete node;
    }
};
#endif // __X__TREE__INCLUDED__