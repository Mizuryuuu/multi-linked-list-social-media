#include "sosmed.h"

// DEFINE ID
int nextUserID = 4;
int nextPostID = 104;
int nextCommentID = 204;

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
    adrRelasiComment c, q;

    if (P == Nil) return;

    c = P->firstChild;
    if (c == Nil) {
        cout << "Komentar Kosong.";
        return;
    }

    if (c->child != Nil && c->child->info.idComment == idComment){
        P->firstChild = c->next;
        c->next = Nil;
        deleteComment(L, c->child);
        delete c;
        return;
    }

    q = c;
    while (q->next != Nil) {
        if (q->next->child != Nil &&
            q->next->child->info.idComment == idComment) {
            break;
        }
        q = q->next;
    }

    if (q->next != Nil){
        c = q->next;
        q->next = c->next;
        c->next = Nil;
        deleteComment(L, c->child);
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
void showBeranda(ListUser LU, ListPost LP){
    system("cls");
    cout << "============================" << endl;
    cout << "          BERANDA           " << endl;
    cout << "============================" << endl << endl;

    vector<adrPost> posts = getRandomPost(LP);

    if (posts.empty()) {
        cout << "Belum ada postingan.\n\n";
        return;
    }

    for (adrPost P : posts) {
        adrUser U = findUserByPost(LU, P);

        cout << "[Post ID: " << P->info.idPost << "]" << endl;
        cout << P->info.date << endl;
        cout << P->info.imagePost << endl;

        if (U != Nil)
            cout << U->info.username << ": ";
        else
            cout << "unknown: ";

        cout << P->info.description << endl;
        cout << "comment (" << countCommentPost(P) << ") ->\n\n";
    }

    cout << "==========================" << endl;
    cout << "1. Postingan User" << endl;
    cout << "2. Comment User" << endl;
    cout << "3. Profile" << endl;
    cout << "4. Lihat Comment Postingan" << endl;
    cout << "5. logout" << endl;
    cout << "terminal: ";
}

void showPostinganUser(ListUser &LU, ListPost &LP, ListComment &LC, adrUser currentUser){
    bool running = true;

    while (running) {
        system("cls");
        cout << "============================" << endl;
        cout << "          POSTINGAN         " << endl;
        cout << "============================" << endl << endl;

        if (currentUser->firstChild == Nil) {
            cout << "Belum ada postingan.\n\n";
        } else {
            adrRelasiPost R = currentUser->firstChild;
            while (R != Nil) {
                adrPost P = R->child;

                cout << "[Post ID: " << P->info.idPost << "]" << endl;
                cout << P->info.date << endl;
                cout << P->info.imagePost << endl;
                cout << currentUser->info.username << ": ";
                cout << P->info.description << endl;
                cout << "comment (" << countCommentPost(P) << ") ->\n\n";

                R = R->next;
            }
        }

        cout << "==========================" << endl;
        cout << "1. Tambah Postingan" << endl;
        cout << "2. Edit Postingan" << endl;
        cout << "3. Delete Postingan" << endl;
        cout << "4. Lihat Comment Postingan" << endl;
        cout << "0. Kembali ke Beranda" << endl;
        cout << "terminal: ";

        int menu;
        cin >> menu;

        switch(menu) {
            case 1: {
                    infotypePost post;
                    post.idPost = nextPostID++;
                    post.idUser = currentUser->info.idUser;
                    cout << "Masukkan gambar (image.png/.jpg): ";
                    getline(cin >> ws, post.imagePost);
                    do {
                        cout << "Masukkan tanggal (DD/MM/YYYY): ";
                        getline(cin, post.date);

                        if (!isValidDate(post.date)) {
                            cout << "Format tanggal salah! Contoh: 05/12/2025\n";
                        }

                    } while (!isValidDate(post.date));
                    cout << "Masukkan deskripsi: ";
                    getline(cin, post.description);
                    adrPost newP = newPost(post);
                    insertPost(LP, newP);
                    connectUserPost(currentUser, newP);
                break;
            }
            case 2: {
                int idPost;
                cout << "Masukkan ID Post: ";
                cin >> idPost;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                adrPost P = findPostById(LP, idPost);
                if (P != Nil) {
                    if (findRelasiPost(currentUser, P) != Nil) {
                        cout << "Edit deskripsi: ";
                        getline(cin, P->info.description);
                    } else {
                        cout << "Post bukan milik user\n";
                        cin.get();
                    }
                } else {
                    cout << "Post tidak ditemukan\n";
                    cin.get();
                }
                break;
            }
            case 3: {
                int idPost;
                cout << "Masukkan ID Post: ";
                cin >> idPost;

                adrPost P = findPostById(LP, idPost);
                if (P != Nil && findRelasiPost(currentUser, P) != Nil) {
                    deleteRelationUserPost(currentUser, idPost);
                    deletePost(LC, LP, P);
                } else {
                    cout << "Post tidak ditemukan / bukan milik user\n";
                    cin.ignore();
                    cin.get();
                }
                break;
            }
            case 4: {
                int idPost;
                cout << "Masukkan ID Post: ";
                cin >> idPost;
                adrPost P = findPostById(LP, idPost);
                if (P != Nil) {
                    showCommentByPost(LU, LC, P, currentUser);
                } else {
                    cout << "Post tidak ditemukan\n";
                    cin.ignore();
                    cin.get();
                }
                break;
            }
            case 5: {
                running = false;
                break;
            }

            case 0:
                running = false;
                break;

            default:
                cout << "Menu tidak valid\n";
                cin.ignore();
                cin.get();
                break;
        }
    }
}


void showCommentByPost(ListUser LU, ListComment &LC, adrPost P, adrUser currentUser){
    bool running = true;

    while (running) {
        system("cls");
        cout << "============================" << endl;
        cout << "      COMMENT POSTINGAN     " << endl;
        cout << "============================" << endl << endl;

        adrUser owner = findUserByPost(LU, P);

        cout << P->info.date << endl;
        cout << P->info.imagePost << endl;

        if (owner != Nil)
            cout << owner->info.username << ": ";
        else
            cout << "unknown: ";

        cout << P->info.description << endl << endl;
        
        cout << "Comment Post -> " << endl;

        if (P->firstChild == Nil) {
            cout << "Belum ada komentar.\n\n";
        } else {
            adrRelasiComment R = P->firstChild;
            while (R != Nil) {
                adrComment C = R->child;
                adrUser commenter = findUserById(LU, C->info.idUserComment);

                cout << C->info.date << endl;
                if (commenter != Nil)
                    cout << commenter->info.username << ": ";
                else
                    cout << "unknown: ";

                cout << C->info.comment << endl << endl;

                R = R->next;
            }
        }

        cout << "==========================" << endl;
        cout << "1. Tambah Comment" << endl;
        cout << "0. Kembali ke Beranda" << endl;
        cout << "terminal: ";

        int menu;
        cin >> menu;
        switch (menu) {
            case 1: {
                infotypeComment comment;
                comment.idComment = nextCommentID++;
                comment.idUserComment = currentUser->info.idUser;
                comment.idPost = P->info.idPost;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                do {
                    cout << "Masukkan tanggal (DD/MM/YYYY): ";
                    getline(cin, comment.date);

                    if (!isValidDate(comment.date)) {
                        cout << "Format tanggal salah! Contoh: 05/12/2025\n";
                    }

                } while (!isValidDate(comment.date));

                cout << "Masukkan komentar: ";
                getline(cin, comment.comment);
                adrComment newC = newComment(comment);
                insertComment(LC, newC);
                connectPostComment(P, newC);
                break;
            }
            case 0:
                running = false;
                break;
            default:
                cout << "Menu tidak valid\n";
                cin.ignore();
                cin.get();
                break;
        }
    }
}

 
void showCommentUser(ListUser &LU, ListPost &LP, ListComment &LC, adrUser currentUser){
    bool running = true;

    while (running) {
        system("cls");
        cout << "============================" << endl;
        cout << "        COMMENT USER        " << endl;
        cout << "============================" << endl << endl;

        bool ada = false;

        adrPost P = LP.first;
        while (P != Nil) {
            adrRelasiComment R = P->firstChild;

            while (R != Nil) {
                adrComment C = R->child;

                if (C->info.idUserComment == currentUser->info.idUser) {
                    ada = true;

                    cout << "[Comment ID: " << C->info.idComment << "]" << endl;
                    cout << C->info.date << endl;
                    cout << currentUser->info.username << ": ";
                    cout << C->info.comment << endl << endl;
                }

                R = R->next;
            }

            P = P->nextPost;
        }

        if (!ada) {
            cout << "Belum ada komentar.\n\n";
        }

        cout << "==========================" << endl;
        if(ada) {
            cout << "1. Edit Comment" << endl;
            cout << "2. Delete Comment" << endl;
        }
        cout << "0. Kembali ke Beranda" << endl;
        cout << "terminal: ";
     
        int menu;
        cin >> menu;

        switch (menu)
        {
        case 1:{
            int idComment;
            cout << "Masukkan ID Comment: ";
            cin >> idComment;
            adrComment C = findCommentById(LC, idComment);
            if (C != Nil) {
                if (C->info.idUserComment == currentUser->info.idUser) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Edit komentar: ";
                    getline(cin, C->info.comment);
                } else {
                    cout << "Komentar bukan milik user\n";
                    cin.ignore();
                    cin.get();
                }
            } else {
                cout << "Komentar tidak ditemukan\n";
                cin.ignore();
                cin.get();
            }
            break;
        }

        case 2:{
            int idComment;
            cout << "Masukkan ID Comment: ";
            cin >> idComment;
            adrComment C = findCommentById(LC, idComment);
            if (C != Nil) {
                if (C->info.idUserComment == currentUser->info.idUser) {
                    adrPost postTarget = findPostById(LP, C->info.idPost);
                    deleteRelationPostComment(postTarget, LC, idComment);
                } else {
                    cout << "Komentar bukan milik user\n";
                    cin.ignore();
                    cin.get();
                }
            } else {
                cout << "Komentar tidak ditemukan\n";
                cin.ignore();
                cin.get();
            }
            break;
        }
        case 0:
            running = false;
            break;
        default:
            cout << "Menu tidak valid\n";
            cin.ignore();
            cin.get();
            break;
        }
    }
}

void showProfile(ListUser LU, adrUser &currentUser){
    bool running = true;
    while(running){
        string passwordMasked = currentUser->info.password;
        transform(passwordMasked.begin(), passwordMasked.end(), passwordMasked.begin(), [](char c) { return islower(c) || isdigit(c) ? '*' : c; });
        system("cls");
        cout << "============================" << endl;
        cout << "          PROFILE           " << endl;
        cout << "============================" << endl << endl;

        cout << "Username : " << currentUser->info.username << endl;
        cout << "Email    : " << currentUser->info.email << endl;
        cout << "Password : " << passwordMasked << endl;
        cout << "Jumlah Post : " << countPostUser(currentUser) << endl;
        cout << "============================" << endl;
        cout << "1. Edit Username" << endl;
        cout << "2. Edit Email" << endl;
        cout << "3. Edit Password" << endl;
        cout << "4. Logout" << endl;
        cout << "0. Kembali ke Beranda" << endl;
        cout << "terminal: ";
        int menu;
        cin >> menu;

        switch(menu){
            case 1:{
                cout << "Masukkan username baru: ";
                getline(cin >> ws, currentUser->info.username);
                break;
            }
            case 2:{
                cout << "Masukkan email baru: ";
                getline(cin >> ws, currentUser->info.email);
                break;
            }
            case 3:{
                cout << "Masukkan password baru: ";
                getline(cin >> ws, currentUser->info.password);
                break;
            }
            case 4:{
                running = false;
                break;
            }
            case 0:{
                running = false;
                break;
            }
            default:{
                cout << "Menu tidak valid\n";
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
    
}

void showAllParentAndChild(ListUser LU) {
    system("cls");
    cout << "=============================" << endl;
    cout << " SEMUA DATA PARENT DAN CHILD" << endl;
    cout << "=============================" << endl;
    adrUser U = LU.first;
    while (U != Nil) {
        cout << "Parent User:" << endl;
        cout << "User ID: " << U->info.idUser << endl;
        cout << "Username: " << U->info.username << endl;

        adrRelasiPost R = U->firstChild;
        while (R != Nil) {
            adrPost P = R->child;
            cout << "  Child Post:" << endl;
            cout << "  Post ID: " << P->info.idPost << endl;
            cout << "  Description: " << P->info.description << endl;

            adrRelasiComment RC = P->firstChild;
            while (RC != Nil) {
                adrComment C = RC->child;
                cout << "    Child Lvl 2 Comment:" << endl;
                cout << "    Comment ID: " << C->info.idComment << endl;
                cout << "    Comment: " << C->info.comment << endl;

                RC = RC->next;
            }

            R = R->next;
        }

        cout << "------------------------\n";
        U = U->nextUser;
    }
}

void showCommentWithUser(ListUser LU) {
    system("cls");
    cout << "============================" << endl;
    adrUser U = LU.first;

    while (U != Nil) {
        adrRelasiPost P = U->firstChild;
        while (P != Nil) {
            adrRelasiComment R = P->child->firstChild;

            while (R != Nil) {
                adrComment C = R->child;

                cout << "Comment ID: " << C->info.idComment << endl;
                cout << "Isi Comment: " << C->info.comment << endl;

                cout << "Parent User:" << endl;
                cout << "User ID: " << U->info.idUser << endl;
                cout << "Username: " << U->info.username << endl;
                cout << "------------------------\n";

                R = R->next;
            }

            P = P->next;
        }

        U = U->nextUser;
    }
}

void showPostWithParentUser(ListUser LU) {
    system("cls");
    cout << "============================" << endl;
    adrUser U = LU.first;

    while (U != Nil) {
        adrRelasiPost R = U->firstChild;

        while (R != Nil) {
            adrPost P = R->child;

            cout << "Post ID: " << P->info.idPost << endl;
            cout << "Gambar: " << P->info.imagePost << endl;

            cout << "Parent User:" << endl;
            cout << "User ID: " << U->info.idUser << endl;
            cout << "Username: " << U->info.username << endl;
            cout << "------------------------\n";

            R = R->next;
        }

        U = U->nextUser;
    }
}
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

adrRelasiPost findRelasiPost(adrUser U, adrPost P) {
    adrRelasiPost R = U->firstChild;

    while (R != Nil) {
        if (R->child == P) {
            return R;
        }
        R = R->next;
    }
    return Nil;
}

adrUser findUserByPost(ListUser LU, adrPost P){
    adrUser U = LU.first;

    while (U != Nil) {
        adrRelasiPost R = U->firstChild;
        while (R != Nil) {
            if (R->child == P) {
                return U;
            }
            R = R->next;
        }
        U = U->nextUser;
    }
    return Nil;
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
    int count = 0;
    adrUser U = L.first;

    while (U != Nil) {
        adrRelasiPost R = U->firstChild;
        while (R != Nil) {
            if (R->child == P) {
                count++;
            }
            R = R->next;
        }
        U = U->nextUser;
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

// EDIT RELATION FUNCTION
void editRelationUserPost(adrUser U, adrPost oldPost, adrPost newPost) {
    adrRelasiPost R = U->firstChild;

    while (R != Nil) {
        if (R->child == oldPost) {
            R->child = newPost;
            return;
        }
        R = R->next;
    }

    cout << "Relasi tidak ditemukan\n";
}
void editRelationPostComment(adrPost P, adrComment oldC, adrComment newC) {
    adrRelasiComment R = P->firstChild;

    while (R != Nil) {
        if (R->child == oldC) {
            R->child = newC;
            return;
        }
        R = R->next;
    }

    cout << "Relasi tidak ditemukan\n";
}
// END EDIT RELATION FUNCTION

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

    shuffle(data.begin(), data.end(), mt19937(random_device{}()));

    if (data.size() > 3) {
        data.resize(3);
    }
    return data;    
}

void login(ListUser &LU, adrUser &currentUser){
    string email, password;
    bool found = false;

    while (!found) {
        system("cls");
        cout << "============================" << endl;
        cout << "           LOGIN            " << endl;
        cout << "============================" << endl << endl;

        cout << "Email: ";
        getline(cin >> ws, email);
        cout << "Password: ";
        getline(cin >> ws, password);

        adrUser U = LU.first;
        while (U != Nil) {
            if (U->info.email == email && U->info.password == password) {
                currentUser = U;
                found = true;
                break;
            }
            U = U->nextUser;
        }

        if (!found) {
            cout << "Email atau password salah. Silakan coba lagi.\n";
            cin.ignore();
            cin.get();
        }
    }
}

void registerUser(ListUser &LU){
    infotypeUser newUserInfo;
    newUserInfo.idUser = nextUserID++;

    system("cls");
    cout << "============================" << endl;
    cout << "         REGISTER           " << endl;
    cout << "============================" << endl << endl;

    cout << "Masukkan username: ";
    getline(cin >> ws, newUserInfo.username);

    cout << "Masukkan email: ";
    getline(cin >> ws, newUserInfo.email);

    cout << "Masukkan password: ";
    getline(cin >> ws, newUserInfo.password);

    adrUser newU = newUser(newUserInfo);
    insertUser(LU, newU);

    cout << "Registrasi berhasil! Silakan login dengan akun baru Anda.\n";
    cin.ignore();
    cin.get();
}
// END COMMON FUNCTION
