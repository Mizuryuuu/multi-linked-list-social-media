#include <iostream>
#include "sosmed/sosmed.h"
using namespace std;

int main() {
    // ===== INIT LIST =====
    ListUser LU;
    ListPost LP;
    ListComment LC;

    createListUser(LU);
    createListPost(LP);
    createLisComment(LC);

    // ===== DUMMY USER =====
    adrUser u1 = newUser({1, "andi", "andi@mail.com", "123"});
    adrUser u2 = newUser({2, "budi", "budi@mail.com", "123"});
    adrUser u3 = newUser({3, "cici", "cici@mail.com", "123"});

    insertUser(LU, u1);
    insertUser(LU, u2);
    insertUser(LU, u3);

    // ===== DUMMY POST =====
    adrPost p1 = newPost({101, 1, "12/12/2025", "Gunung.png", "Pemandangan indah"});
    adrPost p2 = newPost({102, 1, "13/12/2025", "Pantai.png", "Laut biru"});
    adrPost p3 = newPost({103, 3, "14/12/2025", "Hutan.png", "Hijau dan sejuk"});

    insertPost(LP, p1);
    insertPost(LP, p2);
    insertPost(LP, p3);

    // ===== RELASI USER - POST =====
    connectUserPost(u1, p1);
    connectUserPost(u2, p2);
    connectUserPost(u3, p3);

    // ===== DUMMY COMMENT =====
    
    adrComment c1 = newComment({201, 2, "12/12/2025", "keren banget"});
    adrComment c2 = newComment({202, 2, "13/12/2025", "mantap"});
    adrComment c3 = newComment({203, 3, "14/12/2025", "suka ini"});

    insertComment(LC, c1);
    insertComment(LC, c2);
    insertComment(LC, c3);

    // ===== RELASI POST - COMMENT =====
    connectPostComment(p1, c1);
    connectPostComment(p1, c2);
    connectPostComment(p3, c3);

    adrUser currentUser = u1; // simulasi login
    bool running = true;
    int menu;

    while (running) {
        showBeranda(LU, LP);
        cin >> menu;

        switch (menu) {
        case 1:
            showPostinganUser(LU, LP, LC, currentUser);
            break;

        case 2:
            showCommentUser(LU, LP, LC, currentUser);
            break;

        case 3:
            system("cls");
            cout << "Username : " << currentUser->info.username << endl;
            cout << "Jumlah Post : " << countPostUser(currentUser) << endl;
            cout << "\nTekan apa saja...";
            cin.ignore();
            cin.get();
            break;

        case 4: {
            int idPost;
            cout << "Masukkan ID Post: ";
            cin >> idPost;
            adrPost P = findPostById(LP, idPost);
            if (P != Nil) {
                showCommentByPost(LU, LC, P, currentUser);\
            } else {
                cout << "Post tidak ditemukan\n";
                cin.ignore();
                cin.get();
            }
            break;
        }

        case 5:
            system("cls");
            cout << "ADMIN MODE\n";
            cout << "Total User : " << countUser(LU) << endl;
            cout << "Post tanpa user : " << countNoRelationPost(LU, LP) << endl;
            cout << "Comment tanpa post : " << countNoRelationComment(LP, LC) << endl;
            cin.ignore();
            cin.get();
            break;

        case 0:
            running = false;
            break;

        default:
            cout << "Menu tidak valid\n";
            cin.ignore();
            cin.get();
        }
    }

    cout << "Logout berhasil.\n";
    return 0;
}