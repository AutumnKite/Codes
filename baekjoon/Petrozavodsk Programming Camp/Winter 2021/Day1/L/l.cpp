// O((N+M+max_XY})^2)

#include <bits/stdc++.h>
using namespace std;

int N, M;
int CX, CY, X, Y;
deque<int> D;
deque<int> D2;

vector<int> ANS;
int VALUE;
vector<int> ANS2;
int VALUE2;

bool DEBUG = false;

void PRINTD(){
    for(int i = 0; i < D.size(); i++){
        cout << D.front();
        int d = D.front();
        D.pop_front();
        D.push_back(d);
    }
    cout << endl;
}

int opposite(int dir){
    if(dir <= 1){
        return dir + 2;
    }
    return dir - 2;
}

void input_vector(deque<int> *V){
    string s;
    cin >> s;
    for(int j = 0; j < s.size(); j++){
        if(s[j] == 'N'){
            (*V).push_back(0);
        } else if(s[j] == 'E'){
            (*V).push_back(1);
        } else if(s[j] == 'S'){
            (*V).push_back(2);
        } else if(s[j] == 'W'){
            (*V).push_back(3);
        }
    }
}

void input(){
    cin >> CX >> CY;
    cin >> N >> M;
    D.clear();
    D2.clear();
    ANS.clear();
    ANS2.clear();
    input_vector(&D);
    input_vector(&D2);
}

void inversion(){
    vector<int> temp;
    while(!D2.empty()){
        temp.push_back(D2.front());
        D2.pop_front();
    }
    for(int i = 0; i < temp.size(); i++){
        D2.push_front(opposite(temp[i]));
    }
}

void swap_ALL(){
    swap(D, D2);
    swap(ANS, ANS2);
    swap(VALUE, VALUE2);
}

void rotate(){
    swap(X, Y);
    Y = -Y;
    for(int i = 0; i < D.size(); i++){
        int d = D.front();
        d++;
        if(d == 4) d = 0;
        D.pop_front();
        D.push_back(d);
    }
    for(int i = 0; i < ANS.size(); i++){
        if(ANS[i] >= 0 && ANS[i] <= 3){
            ANS[i]++;
            if(ANS[i] == 4){
                ANS[i] = 0;
            }
        } else if(ANS[i] >= 4 && ANS[i] <= 7){
            ANS[i]++;
            if(ANS[i] == 8){
                ANS[i] = 4;
            }
        }
    }
}

void MOVE(int *x, int *y){
    if(D.empty()) return;
    int d = D.front();
    D.pop_front();
    if(d == 0){
        (*y)++;
    } else if(d == 1){
        (*x)++;
    } else if(d == 2){
        (*y)--;
    } else {
        (*x)--;
    }
    D.push_back(d);
}

bool clear_rows(){
    if(D.empty()) return false;
    int MAXY = Y;
    int MINY = Y;
    for(int i = 0; i < D.size(); i++){
        MOVE(&X, &Y);
        MAXY = max(MAXY, Y);
        MINY = min(MINY, Y);
    }
    if(MAXY <= 1 || MAXY == MINY){
        return false;
    }
    while(Y == MAXY){
        ANS.push_back(-1);
        MOVE(&X, &Y);
    }
    if(DEBUG){
        cout << "MAXY = " << MAXY << "   MINY = " << MINY << endl;
        cout << "X = " << X << "   Y = " << Y << endl;
        PRINTD();
    }
    int amt = D.size();
    for(; amt > 0; amt--){
        if(D.size() == 0) return false;
        while(true){
            if(D.size() == 0) return false;
            if(Y < MAXY - 1 || D.front() != 0){
                MOVE(&X, &Y);
                ANS.push_back(-1);
                break;
            }
            D.pop_front();
            if(D.front() == 2){
                D.pop_front();
                ANS.push_back(4);
            } else {
                int e = D.front();
                D.pop_front();
                D.push_front(0);
                D.push_front(e);
                ANS.push_back(-2);
                break;
            }
        }
    }
    return true;
}

void clear_rest(){
    while(D.size() != 0){
        if(DEBUG) PRINTD();
        int amt = D.size();
        bool END = true;
        for(; amt > 0; amt--){
            if(DEBUG) cout << "Size: " << D.size() << "  " << amt << endl;
            int d = D.front();
            D.pop_front();
            if(D.front() == opposite(d)){
                D.pop_front();
                ANS.push_back(4 + d);
                END = false;
                break;
            } else {
                D.push_front(d);
                MOVE(&X, &Y);
                ANS.push_back(-1);
            }
        }
        if(END) break;
    }
    if(DEBUG) cout << "leftovers: " << D.size() << endl;
    if(D.size() != 0){
        while(X != 1 || Y != 0){
            MOVE(&X, &Y);
            ANS.push_back(-1);
        }
        VALUE = D.size()/8;
        if(D.front() == 2) VALUE = -VALUE;
    } else {
        // getting to point (1, 0).
        if(Y == 0){
            ANS.push_back(0);
            ANS.push_back(-1);
            ANS.push_back(6);
            Y++;
        }
        if(X > 1){
            while(X != 1){
                ANS.push_back(3);
                ANS.push_back(-1);
                ANS.push_back(5);
                X--;
            }
        } else if(X < 1){
            while(X != 1){
                ANS.push_back(1);
                ANS.push_back(-1);
                ANS.push_back(7);
                X++;
            }
        }
        if(Y > 0){
            while(Y != 0){
                ANS.push_back(2);
                ANS.push_back(-1);
                ANS.push_back(4);
                Y--;
            }
        } else {
            while(Y != 0){
                ANS.push_back(0);
                ANS.push_back(-1);
                ANS.push_back(6);
                Y++;
            }
        }
        VALUE = 0;
    }
}

void make_ANS(){
    X = CX;
    Y = CY;
    MOVE(&X, &Y);
    ANS.push_back(-1);
    for(int i = 0; i < 4; i++){
        if(DEBUG) cout << "init row clearing" << endl;
        while(clear_rows()){
            if(DEBUG) cout << "row clearing" << endl;
        }
        if(DEBUG) cout << "rotating" << endl;
        rotate();
    }
    if(DEBUG) cout << "clearing rest" << endl;
    clear_rest();
}

void mergeANS(){
    for(int i = ANS2.size() - 1; i >= 0; i--){
        if(ANS2[i] >= 0 && ANS2[i] <= 3){
            ANS.push_back(ANS2[i + 2] - 4);
            ANS.push_back(-1);
            ANS.push_back(ANS2[i] + 4);
            ANS2.pop_back();
            ANS2.pop_back();
            ANS2.pop_back();
            i -= 2;
        }
    }
    // There are no ADD operations in ANS2 anymore.
    for(int i = ANS2.size() - 1; i >= 0; i--){
        if(ANS2[i] == -1){
            ANS.push_back(-1);
        } else if(ANS2[i] == -2){
            ANS[ANS.size() - 2] = -2;
            ANS.push_back(-1);
        } else {
            ANS.push_back(ANS2[i] - 4);
            ANS.push_back(-1);
            ANS.push_back(-1);
        }
    }
}

void output(){
    cout << "YES\n";
    for(int i = 0; i < ANS.size(); i++){
        if(ANS[i] == -2) {
            cout << 'C';
        } else if(ANS[i] == -1){
            cout << '-';
        } else if(ANS[i] == 0) {
            cout << 'N';
        } else if(ANS[i] == 1) {
            cout << 'E';
        } else if(ANS[i] == 2) {
            cout << 'S';
        } else if(ANS[i] == 3) {
            cout << 'W';
        } else {
            cout << 'R';
        }
    }
    cout << '\n';
}

void process(){
    inversion();
    make_ANS();
    if(DEBUG) cout << "ANS1" << endl;
    swap_ALL();
    make_ANS();
    if(DEBUG) cout << "ANS2" << endl;
    swap_ALL();
    if(VALUE + VALUE2 != 0){
        cout << "NO\n";
        return;
    }
    mergeANS();
    output();
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    for(int v = 0; v < T; v++){
        input();
        process();
    }
}