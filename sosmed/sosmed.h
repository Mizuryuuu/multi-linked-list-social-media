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
    string password;
};

// INFOTYPE POST
struct infotypePost {
    int idPost;
    int idUser;          
    string date;
    string imagePost;
    string description;
};

// INFOTYPE COMMENT
struct infotypeComment {
    int idComment;
    int idUserComment;   
    string date;
    string comment;
};

// ADDRESS
typedef struct elmUser *adrUser; // Parent
typedef struct elmPost *adrPost; // Child lvl 1
typedef struct elmComment *adrComment; // Child lvl 2
// END ADDRESS

// RELATION
typedef struct elmRelasiPost* adrRelasiPost;
typedef struct elmRelasiComment* adrRelasiComment;
// END RELATION

// STRUCTURE
struct elmUser // User
{
    infotypeUser info;
    adrUser nextUser;
    adrRelasiPost firstChild;
};

struct elmPost // Post (child lvl 2)
{
    infotypePost info;
    adrPost nextPost;
    adrRelasiComment firstChild;
};

struct elmComment // Comment (child lvl 2)
{
    infotypeComment info;
    adrComment nextComment;
};

struct elmRelasiPost // Relation Post and User
{
    adrPost child;
    adrRelasiPost next;
};

struct elmRelasiComment // Relation Comment and Post
{
    adrComment child;
    adrRelasiComment next;
};
// END STRUCTURE

// MAIN LIST
struct ListUser
{
    adrUser first;
};

struct ListPost
{
    adrPost first;
};

struct ListComment
{
    adrComment first;
};
// END MAIN LIST

// Main Function
void createListUser(ListUser &L);
void createListPost(ListPost &L);
void createLisComment(ListComment &L);
// End Main Function

// Id global untuk automisasi id
extern int nextUserID;
extern int nextPostID;
extern int nextCommentID;


#endif // SOSMED_H_INCLUDED
