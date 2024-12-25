#include <iostream>
#include <vector>
using namespace std;

vector<string> colors = {
        "\033[0;31m", // Red
        "\033[0;32m", // Green
        "\033[0;33m", // Yellow
        "\033[0;34m", // Blue
        "\033[0;35m", // Magenta
        "\033[0;36m"  // Cyan
    };

vector<vector<char>> getPuzzle() {
    vector<vector<char>> p = {
        {'W', 'N', 'C', 'U', 'P', 'S', 'Y', 'L', 'O', 'C', 'K', 'E', 'N', 'K'},
        {'S', 'C', 'A', 'R', 'L', 'E', 'T', 'W', 'I', 'T', 'C', 'H', 'Y', 'O'},
        {'R', 'O', 'C', 'K', 'E', 'T', 'R', 'A', 'C', 'C', 'O', 'O', 'N', 'T'},
        {'O', 'H', 'A', 'W', 'K', 'E', 'Y', 'E', 'N', 'P', 'C', 'W', 'N', 'T'},
        {'A', 'W', 'L', 'U', 'N', 'A', 'S', 'N', 'O', 'W', 'I', 'F', 'R', 'P'},
        {'O', 'J', 'R', 'A', 'P', 'R', 'V', 'T', 'I', 'O', 'W', 'F', 'O', 'I'},
        {'N', 'S', 'N', 'C', 'Y', 'I', 'O', 'L', 'A', 'K', 'M', 'E', 'N', 'S'},
        {'M', 'T', 'E', 'M', 'M', 'U', 'L', 'K', 'E', 'N', 'A', 'J', 'F', 'S'},
        {'R', 'S', 'C', 'O', 'T', 'G', 'U', 'E', 'O', 'W', 'G', 'A', 'I', 'E'},
        {'C', 'E', 'Y', 'N', 'J', 'R', 'E', 'S', 'R', 'E', 'I', 'N', 'S', 'N'},
        {'E', 'F', 'O', 'E', 'T', 'O', 'K', 'E', 'E', 'N', 'K', 'C', 'T', 'L'},
        {'C', 'R', 'H', 'V', 'A', 'O', 'N', 'P', 'U', 'Y', 'W', 'A', 'R', 'E'},
        {'W', 'E', 'N', 'N', 'N', 'T', 'J', 'O', 'L', 'A', 'K', 'T', 'N', 'Y'},
        {'E', 'E', 'W', 'W', 'O', 'L', 'V', 'E', 'R', 'I', 'N', 'E', 'N', 'R'}
    };

    return p;
}

vector<string> targetWords() {
    vector<string> words = {
        "PSYLOCKE", 
        "SCARLETWITCH", 
        "ROCKETRACCOON", 
        "HAWKEYE", 
        "LUNASNOW", 
        "WOLVERINE", 
        "VENOM", 
        "GROOT",
        "MAGIK", 
        "JEFF"
    };

    return words;
}

void printPuzzle(vector<vector<char>> &puzzle) {
    for (size_t i = 0; i < puzzle.size(); i++) {
        for (size_t j = 0; j < puzzle[i].size(); j++) {
            cout << "\033[32m" << puzzle[i][j] << "\033[0m" << " ";
        }
        cout << "\n";
    }
}


bool inbound(vector<vector<char>> &grid, string &word, int i, int j) {
    if (i < 0
        || j < 0
        || i > grid.size() - 1
        || j > grid[0].size() - 1)
        return false;

    return true;
}

bool dfs(vector<vector<char>>& grid, string& word, int i, int j, int n, vector<pair<int, int>>& path) {
    if (n == word.size())
        return true;

    if (!inbound(grid, word, i, j) || grid[i][j] != word[n]) {
        return false;
    }

    grid[i][j] = '*';
    path.emplace_back(i, j);

    bool found = dfs(grid, word, i + 1, j, n + 1, path) 
        || dfs(grid, word, i - 1, j, n + 1, path)
        || dfs(grid, word, i, j + 1, n + 1, path)
        || dfs(grid, word, i, j - 1, n + 1, path);


    // backtrack
    if (!found) 
        path.pop_back();

    grid[i][j] = word[n];

    return found;
}

void highlight(vector<vector<char>>& puzzle, vector<pair<int, int>>& path) {
    int colorIndex = 0;
    for (size_t i = 0; i < puzzle.size(); i++) {
        for (size_t j = 0; j < puzzle[i].size(); j++) {
            bool isPartOfWord = false;
            for (const auto &[x, y] : path) {
                if (x == i && y == j) {
                    isPartOfWord = true;
                    break;
                }
            }

            if (isPartOfWord) {
                cout << "\033[1;31m" << puzzle[i][j] << "\033[0m" << " ";
            } else {
                cout << "\033[32m" << puzzle[i][j] << "\033[0m" << " ";
            }
        }
        colorIndex++;
        cout << "\n";
    }
}

int main() {
    vector<vector<char>> puzzle = getPuzzle();
    string word = targetWords()[0];
    vector<pair<int, int>> path;

    for (auto word : targetWords()) {
        for (int i = 0; i < puzzle.size(); i++) {
            for (int j = 0; j < puzzle[i].size(); j++) {
                if (puzzle[i][j] == word[0] && dfs(puzzle, word, i, j, 0, path)) 
                    continue;
            }
        }
    }
    highlight(puzzle, path);
    
    return 0;
}