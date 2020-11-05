#include "Node.h"

void Node::del()
{
    for(int i=0; i<children.size(); i++)
    {
        children[i]->del();
    }
    delete this;
}

string pretty(string arg)
{
    if(arg.size()==1)
    {
        return arg;
    }
    else if(arg[0]==' '&&arg[1]==' ')
    {
        arg.erase(0,1);
        return pretty(arg);
    }
    else
    {
        string result;
        result+=arg[0];
        arg.erase(0,1);
        result+=pretty(arg);
        return result;
    }
}

void Node::prettyfy_prop()
{
    string result;
    result=pretty(this->get_prop());
    if(result[0]==' ')
    {
        result.erase(0,1);
    }
    if(result[result.size()-1]==' ')
    {
        result.erase(result.size()-1,result.size());
    }
    this->set_prop(result);
}

int Node::size() const
{
    if(children.size()==0)
    {
        return 1;
    }
    else
    {
        int s=0;
        for(int i=0; i<children.size(); i++)
        {
            s+=children[i]->size();
        }
        return s;
    }
}

Node::~Node()
{
    children.erase(children.begin(),children.end());
    field_name.erase(field_name.begin(),field_name.end());
    id_name.erase(id_name.begin(),id_name.end());
    id_value.erase(id_value.begin(),id_value.end());
    property.erase(property.begin(),property.end());
}

Node::Node():Node((string)"",(string)"",(string)"",(string)""){};

Node::Node(const string f,const string id_n,const string id_v,const string prop)
{
    field_name=f;
    id_name=id_n;
    id_value=id_v;
    property=prop;
}

string Node::get_id_name() const
{
    return id_name;
}
void Node::set_id_name(const string n)
{
    id_name=n;
}
void Node::set_id_val(const string v)
{
    id_value=v;
}
string Node::get_id_val() const
{
    return id_value;
}
void Node::set_prop(const string p)
{
    property=p;
}
string Node::get_prop() const
{
    return property;
}

string Node::get_field_name() const
{
    return field_name;
}
void Node::set_field_name(const string f)
{
    field_name=f;
}

void Node::print(int padding) const
{
    /*
    if(this==nullptr)
        return;
    */
    cout<<string(padding,' ');
    cout<<'<'<<get_field_name();
    if(id_value!="")
    {
        cout<<" "<<get_id_name()<<'='<<get_id_val();
    }
    cout<<'>';
    if(property!="")
    {
        cout<<" "<<get_prop()<<" </"<<get_field_name()<<'>'<<endl;
    }
    else
    {
        cout<<endl;
        for(int i=0; i<children.size(); i++)
        {
            children[i]->print(padding+3);
        }
        cout<<string(padding,' ');
        cout<<"</"<<get_field_name()<<'>'<<endl;
    }
}

void Node::print_in_file(ofstream& file,int padding) const
{
    file<<string(padding,' ');
    file<<'<'<<get_field_name();
    if(id_value!="")
    {
        file<<" "<<get_id_name()<<'='<<get_id_val();
    }
    file<<'>';
    if(property!="")
    {
        file<<" "<<get_prop()<<" </"<<get_field_name()<<">\n";
    }
    else
    {
        file<<"\n";
        for(int i=0; i<children.size(); i++)
        {
            children[i]->print_in_file(file,padding+5);
        }
        file<<string(padding,' ');
        file<<"</"<<get_field_name()<<">\n";
    }
}

void Node::add_child(Node* a)
{
    children.push_back(a);
}

void Node::print_by_id(const string id) const
{
    if(id_value==id)
    {
        print(0);
        return;
    }
    else
    {
        for(int i=0; i<children.size(); i++)
        {
            children[i]->print_by_id(id);
        }
    }
}

bool is_letter(char a)
{
    return (a>='A'&&a<='Z')||(a>='a'&&a<='z')||(a>='0'&&a<='9');
}

void Node::fill_up(ifstream& file,vector<string>& fields,vector<Node*>&created)
{
    string reader="";
    char curr;
    file.get(curr);
    while(curr!='<'&&!file.eof())
    {
        file.get(curr);
    }
    file.get(curr);
    while(curr!='>'&&!file.eof())
    {
        reader+=curr;
        file.get(curr);
    }
    fill_data(reader,fields);
fil_again:
    while(curr!='<'&&![](char a)
            {
                return (a>='A'&&a<='Z')||(a>='a'&&a<='z')||(a>='0'&&a<='9');
            }(curr)
    &&!file.eof())
    {
        file.get(curr);
    }

    if(curr=='<')
    {
        file.get(curr);
        if(curr=='/')
        {
            reader="";
            file.get(curr);
            while(curr!='>'&&!file.eof())
            {
                reader+=curr;
                file.get(curr);
            }
            if(fields[fields.size()-1]==reader)
            {
                fields.pop_back();
            }
            else
            {
                fields.push_back("Error");
            }

            if(fields.size()==0)
            {
                while(!file.eof()&&!is_letter(curr))
                {
                    file.get(curr);
                }
                if(!file.eof())
                {
                    fields.push_back("Error");
                }
            }
        }
        else
        {
            file.putback(curr);
            Node* a = new Node;
            created.push_back(a);
            file.putback('<');
            children.push_back(a);
            a->fill_up(file,fields,created);
            file.get(curr);
            goto fil_again;
        }
    }
    else if(is_letter(curr))
    {
        reader="";
        while(curr!='<'&&!file.eof())
        {
            reader+=curr;
            file.get(curr);
        }
        this->set_prop(reader);

        file.get(curr);
        if(curr=='/')
        {
            reader="";
            file.get(curr);
            while(curr!='>'&&!file.eof())
            {
                reader+=curr;
                file.get(curr);
            }
            if(fields[fields.size()-1]==reader)
            {
                fields.pop_back();
            }
            else
            {
                fields.push_back("Error");
            }
            if(fields.size()==0)
            {
                while(!file.eof()&&!is_letter(curr))
                {
                    file.get(curr);
                }
                if(!file.eof())
                {
                    fields.push_back("Error");
                }
            }

        }
        else
        {
            fields.push_back("Error");
        }
    }
    else
    {
        fields.push_back("Error");
    }
}

void Node::fill_data(const string data,vector<string>& fields)
{
    string f="";
    string id="";
    string val="";
    for(int i=0; i<data.size(); i++)
    {
        if(data[i]=='=')
        {
            f="";
            for(int j=0; j<data.size(); j++)
            {
                if(data[j]==' ')
                {
                    while(data[j]==' ')
                    {
                        j++;
                    }
                    while(data[j]!='=')
                    {
                        id+=data[j];
                        j++;
                    }
                    j++;
                    while(j<data.size())
                    {
                        val+=data[j];
                        j++;
                    }
                    i=data.size();
                    break;
                }
                else
                {
                    f+=data[j];
                }
            }
        }
        else
        {
            f+=data[i];
        }

    }
    for(int i=0; i<val.size(); i++)
    {
        if(val[i]=='"')
        {
            val.erase(val.begin()+i);
        }
    }
    fields.push_back(f);
    field_name=f;
    id_name=id;
    id_value=val;
}

const Node* Node::get_by(const bool type,const string arg) const
{
    if(type==false)
    {
        //search by id
        if(this->id_value==arg)
        {
            cout<<this->id_value<<endl;
            return this;
        }
        else
        {
            for(int i=0; i<children.size(); i++)
            {
                const Node* res=children[i]->get_by(type,arg);
                if(res!=nullptr)
                    return res;
            }

            return nullptr;
        }

    }
    else
    {
        //search by tag
        for(int i=0; i<children.size(); i++)
            if(children[i]->field_name==arg)
                return children[i];

        return nullptr;
    }
}



Node* Node::get_by_tag_and_id(const string tag,const string id)
{
    if(get_field_name()==tag&&get_id_val()==id)
    {
        return this;
    }
    else
    {
        for(int i=0; i<children.size(); i++)
        {
            Node* result=children[i]->get_by_tag_and_id(tag,id);
            if(result!=nullptr)
                return result;
        }
        return nullptr;
    }
}

Node* Node::get_child(unsigned int i)
{
    return children[i];
}

Node& Node::operator = (const Node& t)
{
    if (this != &t)
    {
        set_id_name(t.get_id_name());
        set_id_val(t.get_id_val());
        set_prop(t.get_prop());
        set_field_name(t.get_field_name());

        for(int i=0; i<t.children.size(); i++)
        {
            Node* a = new Node;
            *a=*t.children[i];
            add_child(a);
        }

    }
    return *this;
}

void Node::console_fill()
{
    cout<<"Do you want a property for "<<get_field_name()<<endl<<"y/n"<<endl;
    char opt;
    cin>>opt;
    if(opt=='y')
    {
        cout<<"Choose new prop"<<endl;
        string prop="";
        cin.ignore();
        getline(cin,prop);
        set_prop(prop);
    }
    else
    {
        set_prop("");
    }

    for(int i=0; i<children.size(); i++)
    {
        children[i]->console_fill();
    }
}

void Node::get_all(vector<Node*>& all)
{
    all.push_back(this);
    for(int i=0; i<children.size(); i++)
        children[i]->get_all(all);
}

bool Node::get_prop_by_id(string id,string key) const
{
    if(get_id_val()==id)
    {
        for(int i=0;i<children.size();i++)
        {
            if(children[i]->get_field_name()==key)
            {
                string result = children[i]->get_prop();
                if(result!=""){cout<<result<<endl;}else{cout<<"No entry\n";}
                return true;
            }
        }
        return false;
    }
    else
    {
        for(int i=0;i<children.size();i++)
        {
            if(children[i]->get_prop_by_id(id,key))
            {
                return true;
            }
        }
        return false;
    }
}

bool Node::remove(const Node* current)
{
    for(int i=0;i<children.size();i++)
    {
        if(children[i]==current)
        {
            delete children[i];
            children.erase(children.begin()+i);
            return true;
        }
        else
        {
            if(children[i]->remove(current)) return true;
        }
    }
}


