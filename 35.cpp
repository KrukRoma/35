#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class TreeNode 
{
public:
    string name;
    vector<unique_ptr<TreeNode>> children;

    TreeNode(const string& name) : name(name) 
    {
        cout << "Node " << name << " created.\n";
    }

    ~TreeNode() 
    {
        cout << "Node " << name << " destroyed.\n";
    }

    void addChild(const string& childName) 
    {
        children.emplace_back(make_unique<TreeNode>(childName));
    }

    TreeNode* findNode(const string& nodeName) 
    {
        if (name == nodeName) 
        {
            return this;
        }
        for (auto& child : children) 
        {
            TreeNode* result = child->findNode(nodeName);
            if (result) 
            {
                return result;
            }
        }
        return nullptr;
    }

    void removeChild(const string& childName) 
    {
        auto it = children.begin();
        while (it != children.end()) 
        {
            if ((*it)->name == childName) 
            {
                it = children.erase(it);
            }
            else 
            {
                ++it;
            }
        }
    }

    void preOrderTraversal() const 
    {
        cout << name << " ";
        for (const auto& child : children) 
        {
            child->preOrderTraversal();
        }
    }

    void postOrderTraversal() const 
    {
        for (const auto& child : children) 
        {
            child->postOrderTraversal();
        }
        cout << name << " ";
    }

    void inOrderTraversal() const 
    {
        if (!children.empty()) 
        {
            children.front()->inOrderTraversal();
        }
        cout << name << " ";
        for (size_t i = 1; i < children.size(); ++i) 
        {
            children[i]->inOrderTraversal();
        }
    }
};

int main() 
{
    TreeNode root("root");

    root.addChild("child1");
    root.addChild("child2");
    root.addChild("child3");

    root.findNode("child1")->addChild("child1.1");
    root.findNode("child1")->addChild("child1.2");

    root.findNode("child2")->addChild("child2.1");

    cout << "Pre-order Traversal:\n";
    root.preOrderTraversal();
    cout << "\n";

    cout << "Post-order Traversal:\n";
    root.postOrderTraversal();
    cout << "\n";

    cout << "In-order Traversal:\n";
    root.inOrderTraversal();
    cout << "\n";

    cout << "Removing child2...\n";
    root.removeChild("child2");

    cout << "Pre-order Traversal after removal:\n";
    root.preOrderTraversal();
    cout << "\n";
}
