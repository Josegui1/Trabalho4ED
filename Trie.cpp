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
        return 26 + (c - '0');
    }
    return -1;
}

// Funcao auxiliar para pegar jogos abaixo de um prefixo
void Trie::collectGames(TrieNode* node, std::vector<Game*>& results){
    if (node == nullptr){
        return;
    }

    if (node->isEndOfTitle){
        results.push_back(node->game);
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(node->children[i] != nullptr){
            collectGames(node->children[i], results);
        }
    }
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

bool Trie::contains(std::string title){
    std::string key = toSearchKey(title);

    TrieNode* current = root;
    for (int i = 0; i < key.length(); i++){
        int index = charToIndex(key[i]);

        if (index == -1){
            return false;
        }

        if (current->children[index] == nullptr){
            return false;
        }

        current = current->children[index];
    }

    return current->isEndOfTitle;
}


void Trie::sortResults(std::vector<Game*>& games){
  int n = games.size();

  for(int i = 0; i < n-1; i++){
    for (int j = 0; j < n - i - 1; j++){
        if(!comesBefore(games[j], games[j+1])){
            Game* temp = games[j];
            games[j] = games[j+1];
            games[j+1] = temp;
        }
    }
  }
}

std::vector<Game*> Trie:: autocomplete(std::string prefix, int k){
    std::vector<Game*> results;

    if (k<=0){
        return results;
    }

    std::string key = toSearchKey(prefix);
    TrieNode* current = root;

    // Fazendo a busca do prefixo dentro da Trie
    for(int i = 0; i < key.length(); i++){
        int index = charToIndex(key[i]);

        if (index == -1){
            return results;
        }

        if (current->children[index] == nullptr){
            return results;
        }

        current = current->children[index];
    }

    // Coleta os jogos abaixo desse no e ordema
    collectGames(current, results);
    sortResults(results);

    // Filtra os primeiros k jogos caso k seja menor que o tamanho dos results
    std::vector<Game*> limitedResults;
    for(int i = 0; i < k && i < results.size(); i++){
        limitedResults.push_back(results[i]);
    }

    return limitedResults;
}