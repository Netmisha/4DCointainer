#pragma once

template<class Type>
struct Node
{
    Node(Type const* ptr) 
    {
        pval = const_cast<int*>(ptr);
    }
    ~Node()
    {
        delete pval;
    }
    Type const& GetVal() const
    {
        return *pval;
    }
    void        SetVal(Type const* ptr)
    {
        delete pval;
        pval = const_cast<int*>(ptr);
    }
    void        SetVal(Type const& value) const
    {
        *pval = value;
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
    XTree()
    {}
    ~XTree()
    {
        RecursiveDestruction(root);
    }
    using XNode = Node<Type>;
    // returns current in-tree position
    XNode* Iter() const { return iter; }

    
    // change in-tree position by 1 hop 
    // returns false on fail
    bool GotoNext() { return GoPlaces(+1, 0); }
    bool GotoPrev() { return GoPlaces(-1, 0); }
    bool GotoUber() { return GoPlaces(0, -1); }
    bool GotoDown() { return GoPlaces(0, +1); }

    // push item into tree in relation to current position

    // changes value of iter (sets if empty tree)
    bool PushIter(Type const* p)
    {
        if (! iter)
        {
            XNode* node = new XNode(p);
            root = iter = node;
            
            iter->next = iter;
            iter->prev = iter;
        }

        else
        {
            iter->SetVal(p);
        }

        return true;
    }
    
    // result: this->prev == new
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
    bool PushNext(Type const* p) // result: this->next == new
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
    bool PushDown(Type const* p) // result: this->down == new, down->next = down_old
    {
        bool pushResult = false;

        if (iter)
        {
            if (GotoDown())
            {
                PushPrev(p);
                GotoUber();
            }
            else
            {
                XNode* node = new XNode(p);
                
                node->next = node;
                node->prev = node;

                iter->down = node; // INVEST
                node->uber = iter;
            }

            pushResult = true;
        }

        return pushResult;
    }

    bool PopIter()
    {
        if (!iter)
            return false;

        if (iter == root)
        {
            RecursiveDestruction(iter);
            iter = nullptr;
            return true;
        }

        if (iter->next == iter)
        {
            GotoUber();
            RecursiveDestruction(iter->down);
            iter->down = nullptr;
            return true;
        }

        if (iter->uber->down == iter)
        {
            iter->uber->down = iter->next;

            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;

            XNode* kill = iter;
            iter = iter->next;

            RecursiveDestruction(kill);
            return true;
        }
    }
protected:
    XNode* root = nullptr; // always points at top el
    XNode* iter = nullptr; // points at current element

    bool GoPlaces(int x, int y)
    {
        if (iter)
        {
            switch (x)
            {
                case +1: 
                    if (iter->next)
                    {
                        iter = iter->next;
                        return true;
                    }
                    break;
                case -1:
                    if (iter->prev)
                    {
                        iter = iter->prev;
                        return true;
                    }
                    break;
            }
            switch (y)
            {
                case -1:
                    if (iter->uber)
                    {
                        iter = iter->uber;
                        return true;
                    }
                    break;
                case +1:
                    if (iter->down)
                    {
                        iter = iter->down;
                        return true;
                    }
                    break;
            }
            
        }
        return false;
    }

    void RecursiveDestruction(XNode* node)
    {
        if (!node)
            return;

        RecursiveDestruction(node->down);
        
        node->prev->next = nullptr;

        RecursiveDestruction(node->next);

        std::cout << "killing " << node->GetVal() << std::endl;

        delete node;
    }
};