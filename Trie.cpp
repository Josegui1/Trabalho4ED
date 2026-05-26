#include "Trie.hpp"

TrieNode::TrieNode(){
    isEndOfTitle = false;
    game = nullptr;

    for (int i = 0; i < ALPHABET_SIZE; i++ ){
        children[i] = nullptr;
    }


}


TrieNode::~TrieNode(){

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(children[i] != nullptr){
            delete children[i];
        }
    }
}

Trie::Trie(){
    root = new TrieNode;
}

Trie::~Trie(){
    if(root != nullptr){
        delete root;
    }
}


std::string Trie::toSearchKey(std::string text){
    std::string key = "";
    for (int i = 0; i<text.length(); i++){
        char c  = text[i];
        
        if(c == ' '){
            continue;
        }

        if (c >= 'A' && c <= 'Z'){
            c = c - 'A' + 'a';
        }

        key += c;
    }

    return key;
}