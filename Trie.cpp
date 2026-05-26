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
    root = new TrieNode();
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

// Funcao auxiliar para ver se o jogo a vem antes do b
bool Trie::comesBefore(Game* a, Game* b){
    if (a->getPopularity() > b->getPopularity()){
        return true;
    }
    
    if (a->getPopularity() < b->getPopularity()){
        return false;
    }

    std::string keyA = toSearchKey(a->getTitle());
    std::string keyB = toSearchKey(b->getTitle());

    return keyA < keyB;
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

bool Trie::insert(Game* game){
    if(game == nullptr){
        return false;
    }

    std::string key = toSearchKey(game->getTitle());

    TrieNode* current = root;

    for(int i = 0; i < key.length(); i++){
        int index = charToIndex(key[i]);
        
        if (index == -1){
            return false;
        }

        if (current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->isEndOfTitle = true;
    current->game = game;

    return true;
}