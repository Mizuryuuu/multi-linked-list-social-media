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
    adrRelasiPost p,q;

    p = U->firstChild;
    if (p == Nil) {
        cout << "Postingan Kosong.";
    }
    
    if (p->child->info.idPost == idPost){
        U->firstChild = p->next;
        p->next = Nil;
        delete p;
        return;
    }

    q = U->firstChild;
    while (q->next != Nil && q->next->child->info.idPost != idPost){
        q = q->next;
    }

    if (q->next != Nil){
        p = q->next;
        q->next = p->next;
        p->next = Nil;
        delete p;
        return;
    }

    cout << "Postingan ngga ketemu.";
}
void deleteRelationPostComment(adrPost &P, int idComment){
    adrRelasiComment c,q;

    c = P->firstChild;
    if (c == Nil) {
        cout << "Komentar Kosong.";
    }
    
    if (c->child->info.idComment == idComment){
        P->firstChild = c->next;
        c->next = Nil;
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
        delete c;
        return;
    }

    cout << "Komentar ngga ketemu.";
}
void deleteComment(ListComment &L, adrComment C){
    adrComment p;
    
    if (L.first == C) {
        L.first = C->nextComment;
        C->nextComment = Nil;
        delete C;
    } else {
        p = L.first;
        while (p != Nil && p->nextComment != C){
            p = p->nextComment;
        }
        if (p != Nil) {
            p->nextComment = C->nextComment;
            C->nextComment = Nil;
            delete C;
        } else {
            cout << "Komen Tidak ada" << endl;
        }
    }
}

void deletePost(ListPost &L, int idPost){
    ListComment LC;
    adrPost P;
    adrRelasiComment c;
    adrComment C;

    P = L.first;
    while (P != Nil && P->info.idPost != idPost){
        P = P->nextPost;
    }

    c = P->firstChild;

}

void deleteUser(ListPost &L, int idPost){

}
// END DELETE FUNCTION

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
// END COMMON FUNCTION
