class IComponent
{
public:
    IComponent(/* args */);
    ~IComponent();
    virtual void Execute() = 0;
    virtual void AddChild(IComponent *ele) {}
    virtual void RemoveChild(IComponent *ele) {}
};

class Leaf : public IComponent
{
public:
    virtual void Execute() {
        cout << "leaf exxcute" << endl;
    }
};

class Composite : public IComponent
{
private:
    std::list<IComponent*> _list;
public:
    virtual void AddChild(IComponent *ele) {
        // ...
    }
    virtual void RemoveChild(IComponent *ele) {
        // ...
    }
    virtual void Execute() {
        for (auto iter = _list.begin(); iter != _list.end(); iter++) {
            iter->Execute();
        }
    }
};


