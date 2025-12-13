#include "sosmed/sosmed.h"

// CREATE LIST
void createListUser(ListUser &L){
    L.first = Nil;
}
void createListPost(ListPost &L){
    L.first = Nil;
}
void createLisComment(ListComment &L){
    L.first = Nil;
}
// END CREATE LIST

// INSERT FUNCTION
adrUser newUser(infotypeUser x){
    adrUser P = new elmUser;
    P->info = x;
    P->nextUser = Nil;
    P->firstChild = Nil;
    return P;
}
adrPost newPost(infotypePost x){
    adrPost P = new elmPost;
    P->info = x;
    P->firstChild = Nil;
    P->nextPost = Nil;
    return P;
}
adrComment newComment(infotypeComment x){
    adrComment P = new elmComment;
    P->info = x;
    P->nextComment = Nil;
    return P;
}
void insertUser(ListUser &L, adrUser P){
    if(L.first == Nil){
        L.first = P;
    } else {
        P->nextUser = L.first;
        L.first = P;
    }
}
void insertPost(ListPost &L, adrPost P){
    if(L.first == Nil){
        L.first = P;
    } else {
        P->nextPost = L.first;
        L.first = P;
    }
}
void insertComment(ListComment &L, adrComment P){
    if(L.first == Nil){
        L.first = P;
    } else {
        P->nextComment = L.first;
        L.first = P;
    }
}
void connectUserPost(adrUser &U, adrPost P){
    adrRelasiPost R = new elmRelasiPost;
    R->child = P;
    R->next = U->firstChild;
    U->firstChild = R;
}
void connectPostComment(adrPost &P, adrComment C){
    adrRelasiComment R = new elmRelasiComment;
    R->child = C;
    R->next = P->firstChild;
    P->firstChild = R;
}
// END INSERT FUNCTION

// DELETE FUNCITON
void deleteRelationUserPost(adrUser &U, int idPost){
    adrRelasiPost p, q;

    p = U->firstChild;
    if (p == Nil) {
        cout << "Postingan Kosong" << endl;
        return;
    }

    if (p->child->info.idPost == idPost) {
        U->firstChild = p->next;
        p->next = Nil;
        delete p;
        return;
    }

    q = U->firstChild;
    while (q->next != Nil && q->next->child->info.idPost != idPost) {
        q = q->next;
    }

    if (q->next != Nil) {
        p = q->next;
        q->next = p->next;
        p->next = Nil;
        delete p;
    }

    cout << "Postingan ngga ketemu.";
}
void deleteRelationPostComment(adrPost &P ,ListComment &L, int idComment){
    adrRelasiComment c,q;

    c = P->firstChild;
    if (c == Nil) {
        cout << "Komentar Kosong.";
    }
    
    if (c->child->info.idComment == idComment){
        P->firstChild = c->next;
        c->next = Nil;
        deleteComment(L,c->child);
        delete c;
        return;
    }

    q = P->firstChild;
    while (q->next != Nil && q->next->child->info.idComment != idComment){
        q = q->next;
    }

    if (q->next != Nil){
        c = q->next;
        q->next = c->next;
        c->next = Nil;
        deleteComment(L,c->child);
        delete c;
        return;
    }

    cout << "Komentar ngga ketemu.";
}

void deleteFirstComment(ListComment &L, adrComment C){
    L.first = C->nextComment;
    C->nextComment = Nil;
    delete C;
}

void deleteAfterComment(ListComment &L,adrComment prec, adrComment C){
    prec->nextComment = C->nextComment;
    C->nextComment = Nil;
    delete C;
}
void deleteComment(ListComment &L, adrComment C){
    adrComment p;
    
    if (L.first == C) {
        deleteFirstComment(L,C);
    } else {
        p = L.first;
        while (p != Nil && p->nextComment != C){
            p = p->nextComment;
        }
        if (p != Nil) {
            deleteAfterComment(L,p,C);
        } else {
            cout << "Komen Tidak ada" << endl;
        }
    }
}

void deleteFirstPost(ListPost &LP){
    adrPost P;

    P = LP.first;
    LP.first = P->nextPost;
    P->nextPost = Nil;
    delete P;
}

void deleteAfterPost(ListPost &LP, adrPost prec){
    adrPost P; 

    P = prec->nextPost;
    prec->nextPost = P->nextPost;
    P->nextPost = Nil;
    delete P;
}

void deletePost(ListComment &LC,ListPost &LP, adrPost P){
    adrRelasiComment c;
    adrPost prec;

    
    while (P->firstChild != Nil) {
        deleteRelationPostComment(P,LC,P->firstChild->child->info.idComment);
    }

    
    if (LP.first == P) {
        deleteFirstPost(LP);
    } else {
        prec = LP.first;
        while (prec->nextPost != Nil && prec->nextPost != P) {
            prec = prec->nextPost;
        }
        if (prec->nextPost == P) {
            deleteAfterPost(LP, prec);
        }
    }

}

void deleteFirstUser(ListUser &LU){
    adrUser U;
    
    U = LU.first;
    LU.first = U->nextUser;
    U->nextUser = Nil;
    delete U;
}

void deleteAfterUser(ListUser &LU, adrUser prec){
    adrUser U;
    
    U = prec->nextUser;
    prec->nextUser = U->nextUser;
    U->nextUser = Nil;
    delete U;
}

void deleteUser(ListUser &LU, ListPost &LP,ListComment &LC,adrUser U){
    adrRelasiPost r;
    adrPost P;

    while (U->firstChild != Nil) {
        r = U->firstChild;
        P = r->child;
        
        deleteRelationUserPost(U, P->info.idPost);
        deletePost(LC, LP, P);
    }

    if (LU.first == U) {
        deleteFirstUser(LU);
    } else {
        adrUser prec = LU.first;
        while (prec->nextUser != Nil && prec->nextUser != U) {
            prec = prec->nextUser;
        }
        if (prec->nextUser == U) {
            deleteAfterUser(LU, prec);
        }
    }

}
// END DELETE FUNCTION

// EDIT DATA FUNCTION
// END EDIT DATA FUNCTION

// SHOW DATA FUNCTION

// END SHOW DATA FUNCTION

// FIND FUNCTION
adrUser findUserById(ListUser L, int idUser){
    adrUser P = L.first;
    while (P != Nil) {
        if(P->info.idUser == idUser) return P;
        P = P->nextUser;
    }
    return Nil;
}

adrPost findPostById(ListPost L, int idPost){
    adrPost P = L.first;
    while(P != Nil){
        if(P->info.idPost == idPost) return P;
        P = P->nextPost;
    }
    return Nil;
}

adrComment findCommentById(ListComment L, int idComment){
    adrComment P = L.first;
    while(P != Nil){
        if(P->info.idComment == idComment) return P;
        P = P->nextComment;
    }
    return Nil;
}

adrComment findPostById(ListComment L, int idComment){
    adrComment P = L.first;
    while(P != Nil){
        if(P->info.idComment == idComment) return P;
        P = P->nextComment;
    }
    return Nil;
}

adrRelasiPost findRelasiPost(adrUser U, adrPost P) {
    adrRelasiPost R = U->firstChild;

    while (R != Nil) {
        if (R->child == P) {
            return R;      // relasi ditemukan
        }
        R = R->next;
    }
    return Nil;            // relasi tidak ada
}
// END FIND FUNCTION

// COUNT FUNCTION
int countCommentPost(adrPost P){
    adrRelasiComment C = P->firstChild;
    int count = 0;
    while (C != Nil) {
        count++;
        C = C->next;
    }
    return count;
}

int countPostUser(adrUser U){
    adrRelasiPost P = U->firstChild;
    int count = 0;
    while (P != Nil) {
        count++;
        P = P->next;
    }
    return count;
}


int countUser(ListUser L){
    adrUser P = L.first;
    int count = 0;
    while(P != Nil){
        count++;
        P = P->nextUser;
    }
    return count;
}

int countRelationPost(ListUser L, adrPost P){
    adrUser Q = L.first;
    adrRelasiPost R;
    int count = 0;
    while(Q != Nil){
        R = Q->firstChild;
        while(R != Nil){
            if(R->child == P){
                count++;
            }
            R = R->next;
        }
        Q = Q->nextUser;
    }
    return count;
}

int countNoRelationPost(ListUser LU, ListPost LP) {
    int count = 0;
    adrPost P = LP.first;

    while (P != Nil) {
        bool found = false;
        adrUser U = LU.first;

        // cek di semua user
        while (U != Nil && !found) {
            adrRelasiPost R = U->firstChild;

            while (R != Nil) {
                if (R->child == P) {
                    found = true; // post ini sudah punya relasi
                    break;
                }
                R = R->next;
            }

            U = U->nextUser;
        }

        if (!found) {
            count++; // post tidak punya relasi dari user manapun
        }

        P = P->nextPost;
    }

    return count;
}
int countNoRelationComment(ListPost LP, ListComment LC){
    int count = 0;
    adrComment C = LC.first;

    while (C != Nil) {
        bool found = false;
        adrPost P = LP.first;

        // cek di semua user
        while (P != Nil && !found) {
            adrRelasiComment R = P->firstChild;

            while (R != Nil) {
                if (R->child == C) {
                    found = true; // post ini sudah punya relasi
                    break;
                }
                R = R->next;
            }

            P = P->nextPost;
        }

        if (!found) {
            count++; // post tidak punya relasi dari user manapun
        }

        C = C->nextComment;
    }

    return count;
}
// END COUNT FUNCTION

// COMMON FUNCTION
bool isValidDate(string date) {
    if (date.length() != 10 ) return false;
    if (date[2] != '/' || date[5] != '/') return false;

    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if (month == 2) {
        bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        if(leap && day > 29) return  false;
        if(!leap && day > 28) return false;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }

    return true;
}

vector<adrPost> getRandomPost(ListPost L){
    vector<adrPost> data;
    adrPost P = L.first;
    while (P != Nil) {
        data.push_back(P);
        P = P->nextPost;
    }

    random_shuffle(data.begin(), data.end());

    if (data.size() > 3) {
        data.resize(3);
    }
    return data;    
}
// END COMMON FUNCTION
