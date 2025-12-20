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
    adrUser admin = newUser({0, "admin", "admin@mail.com", "admin123"});
    adrUser u1 = newUser({1, "andi", "andi@mail.com", "123"});
    adrUser u2 = newUser({2, "budi", "budi@mail.com", "123"});
    adrUser u3 = newUser({3, "cici", "cici@mail.com", "123"});

    insertUser(LU, admin);
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
    connectUserPost(u1, p2);
    connectUserPost(u3, p3);

    // ===== DUMMY COMMENT =====
    adrComment c1 = newComment({201, 101, 2, "12/12/2025", "keren banget"});
    adrComment c2 = newComment({202, 101, 2, "13/12/2025", "mantap"});
    adrComment c3 = newComment({203, 103, 3, "14/12/2025", "suka ini"});

    insertComment(LC, c1);
    insertComment(LC, c2);
    insertComment(LC, c3);

    // ===== RELASI POST - COMMENT =====
    connectPostComment(p1, c1);
    connectPostComment(p1, c2);
    connectPostComment(p3, c3);

    // ===== LOGIN =====
    bool mainRunning = true;
    adrUser currentUser = Nil;
    while (mainRunning)
    {
        system("cls");
        cout << "============================" << endl;
        cout << "           MENU             " << endl;
        cout << "============================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Exit" << endl;
        cout << "============================" << endl;
        cout << "Pilih menu: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                login(LU, currentUser);
                mainRunning = false;
                break;

            case 2:
                registerUser(LU);
                break;

            case 0:
                mainRunning = false;
                break;

            default:
                cout << "Menu tidak valid\n";
                cin.ignore();
                cin.get();
        }
    }

    if (currentUser->info.username == "admin") {
        bool running = true;
        int menu;

        while(running){
            system("cls");
            cout << "============================" << endl;
            cout << "          ADMIN MODE        " << endl;
            cout << "============================" << endl;
            cout << "1. Lihat Semua User" << endl;
            cout << "2. Lihat Semua Postingan" << endl;
            cout << "3. Lihat Semua Komentar" << endl;
            cout << "4. Lihat Data User -> Postingan -> Komentar" << endl;
            cout << "5. Lihat Data Postingan <- User" << endl;
            cout << "6. Edit Relasi User - Postingan" << endl;
            cout << "7. Edit Relasi Postingan - Komentar" << endl;
            cout << "8. Count Element dari Parent User" << endl;
            cout << "9. Count Relasi yang dimiliki oleh Child Postingan" << endl;
            cout << "10. Count Element Child Postingan tanpa Relasi" << endl;
            cout << "11. Count Element Child Komentar tanpa Relasi" << endl;
            cout << "0. Logout" << endl;
            cout << "terminal: ";
            cin >> menu;
            switch (menu) {
                case 1:
                    {
                        system("cls");
                        cout << "============================" << endl;
                        cout << "         DAFTAR USER        " << endl;
                        cout << "============================" << endl << endl;

                        adrUser U = LU.first;
                        while (U != Nil) {
                            cout << "ID User: " << U->info.idUser << endl;
                            cout << "Username: " << U->info.username << endl;
                            cout << "Email: " << U->info.email << endl;
                            cout << "----------------------------" << endl;
                            U = U->nextUser;
                        }
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 2:
                    {
                        system("cls");
                        cout << "============================" << endl;
                        cout << "       DAFTAR POSTINGAN     " << endl;
                        cout << "============================" << endl << endl;

                        adrPost P = LP.first;
                        while (P != Nil) {
                            cout << "ID Post: " << P->info.idPost << endl;
                            cout << "ID User: " << P->info.idUser << endl;
                            cout << "Date: " << P->info.date << endl;
                            cout << "Image: " << P->info.imagePost << endl;
                            cout << "Description: " << P->info.description << endl;
                            cout << "----------------------------" << endl;
                            P = P->nextPost;
                        }
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 3:
                    {
                        system("cls");
                        cout << "============================" << endl;
                        cout << "       DAFTAR KOMENTAR      " << endl;
                        cout << "============================" << endl << endl;

                        adrComment C = LC.first;
                        while (C != Nil) {
                            cout << "ID Comment: " << C->info.idComment << endl;
                            cout << "ID Post: " << C->info.idPost << endl;
                            cout << "ID User Comment: " << C->info.idUserComment << endl;
                            cout << "Date: " << C->info.date << endl;
                            cout << "Comment: " << C->info.comment << endl;
                            cout << "----------------------------" << endl;
                            C = C->nextComment;
                        }
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 4:
                    showAllParentAndChild(LU);
                    cin.ignore();
                    cin.get();
                    break;
                case 5:
                    showPostWithParentUser(LU);
                    cin.ignore();
                    cin.get();
                    break;
                case 6:
                    {
                        int idUser, oldPostID, newPostID;
                        cout << "Masukkan ID User: ";
                        cin >> idUser;
                        cout << "Masukkan ID Postingan lama: ";
                        cin >> oldPostID;
                        cout << "Masukkan ID Postingan baru: ";
                        cin >> newPostID;

                        adrUser U = findUserById(LU, idUser);
                        adrPost oldPost = findPostById(LP, oldPostID);
                        adrPost newPost = findPostById(LP, newPostID);
                        if (U != Nil && oldPost != Nil && newPost != Nil) {
                            editRelationUserPost(U, oldPost, newPost);
                            cout << "Relasi berhasil diubah.\n";
                        } else {
                            cout << "Data tidak ditemukan.\n";
                        }
                        cin.ignore();
                        cin.get();  
                    }
                    break;
                case 7:
                    {
                        int idPost, oldCommentID, newCommentID;
                        cout << "Masukkan ID Postingan: ";
                        cin >> idPost;
                        cout << "Masukkan ID Komentar lama: ";
                        cin >> oldCommentID;
                        cout << "Masukkan ID Komentar baru: ";
                        cin >> newCommentID;

                        adrPost P = findPostById(LP, idPost);
                        adrComment oldC = findCommentById(LC, oldCommentID);
                        adrComment newC = findCommentById(LC, newCommentID);
                        if (P != Nil && oldC != Nil && newC != Nil) {
                            editRelationPostComment(P, oldC, newC);
                            cout << "Relasi berhasil diubah.\n";
                        } else {
                            cout << "Data tidak ditemukan.\n";
                        }
                        cin.ignore();
                        cin.get();  
                    }
                    break;
                case 8:
                    {
                        int idUser;
                        cout << "Masukkan ID User: ";
                        cin >> idUser;
                        adrUser U = findUserById(LU, idUser);
                        if (U != Nil) {
                            int count = countPostUser(U);
                            cout << "Jumlah Postingan oleh User ID " << idUser << ": " << count << endl;
                        } else {
                            cout << "User tidak ditemukan.\n";
                        }
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 9:
                    {
                        int idPost;
                        cout << "Masukkan ID Postingan: ";
                        cin >> idPost;
                        adrPost P = findPostById(LP, idPost);
                        if (P != Nil) {
                            int count = countCommentPost(P);
                            cout << "Jumlah Komentar pada Postingan ID " << idPost << ": " << count << endl;
                        } else {
                            cout << "Postingan tidak ditemukan.\n";
                        }
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 10:
                    {
                        int count = countNoRelationPost(LU, LP);
                        cout << "Jumlah Postingan tanpa Relasi User: " << count << endl;
                        cin.ignore();
                        cin.get();
                    }
                    break;
                case 11:
                    {
                        int count = countNoRelationComment(LP, LC);
                        cout << "Jumlah Komentar tanpa Relasi Postingan: " << count << endl;
                        cin.ignore();
                        cin.get();
                    }
                    break;
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

    } else {
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
                showProfile(LU, currentUser);
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
                running = false;
                break;
                
            default:
                cout << "Menu tidak valid\n";
                cin.ignore();
                cin.get();
            }
        }
    }

    cout << "Logout berhasil.\n";
    return 0;
}