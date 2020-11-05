#include "XML_Tree.h"

const Node* Tree::get_by(const bool type_to_search,const string arg) const
{
    return root->get_by(type_to_search,arg);
}

void Tree::get_prop_by_id(string id,string key) const
{
    if(root->get_prop_by_id(id,key)==false)
        cout<<"No such entry\n";
}

Tree::~Tree()
{
    if(root!=nullptr)
    {
        root->del();
        root=nullptr;
    }
}

Tree& Tree::operator = (const Tree& t)
{
    if (this != &t)
    {
        Node* root = new Node;
        *root=*t.root;
        this->root=root;
    }
    return *this;
}

int Tree::size() const
{
    return (root!=nullptr) ? root->size()+1 : 0;
}

void Tree::set_root(Node* r)
{
    root=r;
}
Node* Tree::get_root() const
{
    return root;
}
void Tree::print() const
{
    if(root!=nullptr)
    {
        root->print(0);
    }
    else
    {
        cout<<"Nothing to print\n";
    }
}

void Tree::print_by_id(const string id) const
{
    if(root==nullptr)
        return;
    root->print_by_id(id);
}

void id_checker(vector<Node*> created)
{
    int v=1;
    for(int i=0; i<created.size()-1; i++)
    {
        for(int j=i+1; j<created.size(); j++)
        {
            if(created[i]->get_id_val()==created[j]->get_id_val()&&created[j]->get_id_val()!="")
            {
                string new_id=created[j]->get_id_val();
                new_id+='_';
                new_id+=(char)(48+v);
                v++;
                created[j]->set_id_val(new_id);
            }
        }
    }
}

void prop_fixer(vector<Node*> created)
{
    for(int i=0; i<created.size(); i++)
    {
        if(created[i]->get_prop()!="")
        {
            created[i]->prettyfy_prop();
        }
    }
}

void Tree::load_tree(const char* f_name)
{
    vector<string>fields;
    vector<Node*>created;
    ifstream file(f_name);

    if (file.is_open())
    {
        Node* a = new Node;
        a->fill_up(file,fields,created);
        root=a;
        if(fields.size()!=0)
        {
            cout<<"Something is wrong with file"<<endl;
            a->del();
            root=nullptr;
        }
        if(created.size()>0)
        {
            id_checker(created);
            prop_fixer(created);
        }

        file.close();
    }
}

void Tree::add_new_element()
{
    if(root==nullptr)
        return;
    cout<<"Choose to add new element to which tag and id of tag"<<endl;
    string tag,id;
    cin>>tag>>id;
    if(id=="n")
        id="";
    Node* current = root->get_by_tag_and_id(tag,id);
    if(current==nullptr)
        return;
    Node* a = new Node;
    *a=*current->get_child(0);
    current->add_child(a);
    a->console_fill();
    vector<Node*>all;
    root->get_all(all);
    id_checker(all);
    prop_fixer(all);
}

void Tree::print_to_file(const char* f_name) const
{
    if(root==nullptr)
        return;
    ofstream file(f_name);

    if (file.is_open())
    {
        root->print_in_file(file,0);

        file.close();
    }
}

void Tree::delete_by_tag_and_id(const string tag,const string id)
{
    if(root==nullptr)
        return;
    const Node* current = root->get_by_tag_and_id(tag,id);
    if(current!=nullptr)
    {
        if(current==root)
        {
            root->del();
            root=nullptr;
        }
        else
        {
            if(root->remove(current))
                cout<<"Deleted successfully\n";
        }
    }
}
