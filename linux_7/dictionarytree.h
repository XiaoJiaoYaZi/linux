#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H
//#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
using namespace std;
class DictinaryTree
{

public:
    DictinaryTree()
    {
        root = new Node();
    }
    ~ DictinaryTree() {
        delete root;
    }
private:
    class Node
    {
    public:
        typedef map<string,Node> ChildNode;
        Node()
        {
            isWord = false;
            count = 0;
            str = "";
            parent = NULL;
            childs = new ChildNode();
        }
        Node(bool isWord,int count,string &str)
        {
            this->childs = new ChildNode();
            this->isWord = isWord;
            this->count= count;
            this->str = str;
        }
        Node &operator = (const Node& thr)
        {
            this->childs = thr.childs;
            this->isWord = thr.isWord;
            this->count = thr.count;
            this->str = thr.str;
            return *this;

        }
        Node(const Node& thr)
        {
            this->childs = thr.childs;
            this->isWord = thr.isWord;
            this->count = thr.count;
            this->str = thr.str;
            this->parent = thr.parent;
        }
        void addChild(string &key,Node &node)
        {
            node.parent = this;
            this->childs->insert(make_pair<string,Node>(key,node));
        }
        void removeChild(string &key)
        {
            childs->erase(key);
        }
        string toString()
        {
            char s[128];
            sprintf(s,"str:5s, isWord:%d, cout:%d\n",str.c_str(),isWord,count);
            return string(s);
        }
    public:
        bool isWord;
        int count;
        string str;
        ChildNode *childs;
        Node *parent;
    };
private:
    Node *root;

public:
    void addStr(string &word,Node &node)
    {
        node.count++;
        string str = node.str;
        if(str.empty())
        {
            if(node.childs->size()>0){
                searchChild(word,node);
            }
            else{
                Node newNode(true,1,word);
                node.addChild(word,newNode);
            }
        }
        else{
            string commonwords = "";
            for(int i=0;i<word.length();i++)
            {//find the same word
                if(i<str.length() && str.at(i) == word.at(i)){
                    commonwords += word.at(i);
                }
                else
                {
                    break;
                }
            }
            if(commonwords.length()>0)
            {
                if(commonwords.length() == str.length() &&
                        commonwords.length() == word.length()){
                    //same word do nothing
                    ;
                }
                else if (commonwords.length() == str.length() &&
                         commonwords.length() < word.length()) {
                    //continue to search and insert
                    string leftword = word.substr(commonwords.length());
                    searchChild(leftword,node);
                }
                else if (commonwords.length()<str.length()) {
                    //
                    Node splitNode(true,node.count,commonwords);
                    node.parent->removeChild(node.str);
                    splitNode.parent->addChild(commonwords,splitNode);

                    if(commonwords.length()<word.length()){
                        splitNode.isWord = false;
                        string wordLeft = word.substr(commonwords.length());
                        Node leftNode(true,1,wordLeft);
                        splitNode.addChild(wordLeft,leftNode);
                        splitNode.count++;
                    }

                    string strLeft = str.substr(commonwords.length());
                    node.str = strLeft;
                    splitNode.parent = node.parent;
                    splitNode.addChild(strLeft,node);
                    splitNode.count++;
                    //splitNode.parent = node.parent;
                    splitNode.parent->addChild(commonwords,splitNode);


                }

            }
            else {
                Node newNode(true,1,word);
                node.addChild(word,newNode);
            }
        }
    }
    void searchChild(string &key,Node &node)
    {
        bool isFind = false;
        if(node.childs->size()>0)
        {
            Node::ChildNode::iterator p = node.childs->begin();
            while (p!=node.childs->end()) {
                Node childNode = p->second;
                if(key.at(0) == childNode.str.at(0))
                {
                    isFind = true;
                    addStr(key,p->second);
                    break;
                }
                p++;
            }
        }
        if(!isFind)
        {
            Node newNode(true,1,key);
            node.addChild(key,newNode);
        }

    }

    void add(string &word)
    {
        addStr(word,*root);
    }
    bool findStr(string &word,Node &node)
    {
        bool isMatch = true;
        string wordLeft = word;
        string str = node.str;
        if(!str.empty())
        {
            if(word.find(str)<0){
                isMatch = false;
            }
            else {
                wordLeft = word.substr(str.length());
            }
        }
        if(isMatch){
            if(wordLeft.length()>0)
            {
                Node::ChildNode::const_iterator p = node.childs->begin();
                while (p!=node.childs->end())
                {
                    Node childNode = p->second;
                    bool isChildFind = findStr(wordLeft,childNode);
                    if(isChildFind) return true;
                    p++;
                }
                return false;
            }
            else
            {
                return node.isWord;
            }
        }
        return false;
    }
    bool find(string &word)
    {
        return findStr(word,*root);
    }

    int countChildStr(string &prefix,Node &node)
    {
        Node::ChildNode::const_iterator p = node.childs->begin();
        while (p!=node.childs->end()) {
            Node childNode = p->second;
            int childCount = countChildStr(prefix,childNode);
            if(childCount!=0){
                return childCount;
            }
            p++;
        }
        return 0;
    }
    int countStr(string &prefix,Node &node)
    {
        string str = node.str;
        if(!str.empty())
        {
            if(prefix.find(str)<0 && str.find(prefix)<0)
            {
                return 0;
            }
            else if (str.find(prefix)>0) {
                return node.count;
            }
            else if (prefix.find(str)>0) {
                string prefixLeft = prefix.substr(str.length());
                if(prefixLeft.length()>0)
                {
                    return countChildStr(prefixLeft,node);
                }
            }
        }
        else{
            return countChildStr(prefix,node);
        }
        return 0;
    }
    int count(string &word)
    {
        if(word.empty())
        {
            return root->count;
        }
        return countStr(word,*root);
    }
    void printNode(Node &node,int layer)
    {
        for(int i=0;i<layer;i++)
        {
            printf("\t");
        }
        printf("%s",node.toString().c_str());
        Node::ChildNode::const_iterator p = node.childs->begin();
        while (p!=node.childs->end()) {
            Node childNode = p->second;
            printNode(childNode,layer+1);
            p++;
        }

    }
    void print(){
        printNode(*root,0);
    }

};

#endif // DICTIONARYTREE_H























