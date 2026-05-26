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

// Funcao auxiliar para converter caracteres em numeros
int Trie::charToIndex(char c){
    if(c >= 'a' && c <= 'z'){
        return c - 'a';
    }

    if(c >= '0' && c <= '9'){
        return 26 + (c - 'a');
    }
    return -1;
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