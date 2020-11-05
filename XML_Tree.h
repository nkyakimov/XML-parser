#ifndef XML_TREE_H_INCLUDED
#define XML_TREE_H_INCLUDED
#include "Node.h"


class Tree
{
private:
    Node* root=nullptr;
public:
    void set_root(Node*);
    Node* get_root() const;
    void print() const;
    void print_by_id(const string id_val) const;
    void load_tree(const char* f_name);
    ~Tree();
    Tree& operator = (const Tree& t);
    int size() const;
    const Node* get_by(const bool,const string) const;
    void add_new_element();
    void get_prop_by_id(string,string) const;
    void print_to_file(const char* f_name) const;
    void delete_by_tag_and_id(const string,const string);
};


#endif // XML_TREE_H_INCLUDED
