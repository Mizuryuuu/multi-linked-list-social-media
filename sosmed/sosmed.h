#ifndef SOSMED_H_INCLUDED
#define SOSMED_H_INCLUDED

#define Nil nullptr

#include <bits/stdc++.h>
using namespace std;

// INFOTYPE USER
struct infotypeUser {
    int idUser;
    string username;
    string email;
};

// INFOTYPE POST
struct infotypePost {
    int idPost;
    int idUser;          
    string imagePost;
    string description;
};

// INFOTYPE COMMENT
struct infotypeComment {
    int idComment;
    int idUserComment;   
    string comment;
};

// Id global untuk automisasi id
extern int nextUserID;
extern int nextPostID;
extern int nextCommentID;



#endif // SOSMED_H_INCLUDED
