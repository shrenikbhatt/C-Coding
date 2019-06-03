//
// APS105 Lab 9
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: Shrenik Bhatt
// Student Number: 10049992332
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//

//This function creates nodes for the music library and ensures that they are placed in alphabetical order
Node * createNode(char *promptName, char *promptArtist, char *promptGenre, Node *newSong, Node *head);

//This function allows the user to delete a particular node from the linked list by inputting which node they would like to delete
Node * deleteNode (char *prompt, Node *head);

//This function prints all the nodes of the linked list
void printList(Node *head);

//This function allows the user to search if there is a song in the linked list and prints all the values that are in the same node
void searchList(char *prompt, Node *head);

//This function allows the user to quit the program and frees all allocated data
Node * quit(Node *head);

//This function is to check whether an input is already inside of the song library
bool duplicate(Node *head, char *search);


// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

const int MAX_LENGTH = 1024;

int main(void) {
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
	Node *head = NULL;
	
    // Announce the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);
		

        if (response == 'I') {
			char *promptName = "Song name" ;
			char *promptArtist =  "Artist" ;
			char *promptGenre = "Genre" ;
			Node *newSong;

			head = createNode(promptName, promptArtist, promptGenre, newSong, head);

        }
        else if (response == 'D') {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted";
			
			char del[MAX_LENGTH];
			
			inputStringFromUser(prompt, del, MAX_LENGTH);
			head = deleteNode(del, head);

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'S') {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;
			
			char search[MAX_LENGTH];
			inputStringFromUser(prompt, search, MAX_LENGTH);

            //   ADD STATEMENT(S) HERE
			searchList(search, head);

        }
        else if (response == 'P') {
            // Print the music library.

            //   ADD STATEMENT(S) HERE
			printList(head);

        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');

    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE
	head = quit(head);
    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
	printList(head);
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName) {
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
    printf("\nThe song name '%s' was found in the music library.\n",
           songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char *songName) {
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName) {
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE

//This function allocates memory for a node and then for the data contained within each node. After allocating, it will allow the user
//to input data for each node. It then uses an algorithm to insert the node in alphabetical order within the linked list
Node * createNode(char *promptName, char *promptArtist, char *promptGenre, Node *newSong, Node *head){
	// Insert a song into the linked list.
    // Maintain the list in alphabetical order by song name.
    //   ADD STATEMENT(S) HERE
	newSong = (Node*) malloc(sizeof(Node));
	char name[MAX_LENGTH+1];
	char gen[MAX_LENGTH+1];
	char art[MAX_LENGTH+1];
	
	inputStringFromUser(promptName, name, MAX_LENGTH);
	newSong->songName = malloc(strlen(name)+1);
	strcpy(newSong->songName, name);
	
	inputStringFromUser(promptArtist, art, MAX_LENGTH);
	newSong->artist = malloc(strlen(art)+1);
	strcpy(newSong->artist, art);

	inputStringFromUser(promptGenre, gen, MAX_LENGTH);
	newSong->genre = malloc(strlen(gen)+1);
	strcpy(newSong->genre, gen);
		if (duplicate(head, name)){
		songNameDuplicate(name);
		free(newSong->songName);
		free(newSong->artist);
		free(newSong->genre);
		free(newSong);
		return head;
	}
	
	//Insert the node into the linked list
	if (head == NULL){
		newSong->next = head;
		head = newSong;
		return head;
	}

	if (head->next == NULL){
		if (strcmp(head->songName, newSong->songName) < 0){
			head->next = newSong;
			newSong->next = NULL;
		}
		else{
			newSong->next = head;
			head = newSong;
			
		}
		return head;
	}
	
	Node *p = head;
	Node *q = p->next;
	while (strcmp(q->songName, newSong->songName) < 0 && q->next != NULL){
		
		p = q;
		q = q->next;
	}
	
	//Node belongs at the end of the list
	if(strcmp(q->songName, newSong->songName) < 0 && strcmp(p->songName, q->songName) < 0){
		q->next = newSong;
		newSong->next = NULL;
		return head;
	}
	//Node belongs in front of the first Node
	else if (strcmp(newSong->songName, p->songName) < 0 ){
		head = newSong;
		newSong->next = p;
		p->next = q;
		return head;
	}
	//Node belongs in the middle of the list
	else{
		p->next = newSong;
		//p->next = newSong;
		newSong->next = q;
		return head;
	}

}

//This function prompts the user to input a song to delete. It then checks against all the songs in the linked list and if it finds 
//a corresponding value it will delete that node. If the song is not in the list, it will notify the user.
Node * deleteNode(char *del, Node *head){
	if (head == NULL){
		printMusicLibraryEmpty();
		return head;
		
	}
	if (strcmp(head->songName, del) == 0){
		songNameDeleted(del);
		if (head->next == NULL){
			free(head->songName);
			free(head->artist);
			free(head->genre);
			free(head);
			head = NULL;
			
		}
		else{
			free(head);
			head = head->next;
		}
		return head;
	}
	Node *q = head;	
	while (strcmp(q->next->songName, del) != 0 && q->next != NULL){
		q = q->next;
		if (q->next == NULL){
			songNameNotFound(del);
			return head;
		}
	}
	songNameDeleted(del);
	free(q->next->songName);
	free(q->next->artist);
	free(q->next->genre);
	free(q->next);
	q->next = q->next->next;
	return head;
}

//This function prints the list in alphabetical order, if there are elements in the list. If no elements are in the list, it will notify
//the user
void printList(Node *head){
	Node *p = head;
	if (p == NULL){
		printMusicLibraryEmpty();
	}
	else {
		printMusicLibraryTitle();
		printf("\n");
		while (p != NULL){

			printf("%s\n%s\n%s\n\n", p->songName, p->artist, p->genre);
			p = p->next;
		}
	}
}

//This is a check fuction to check if the inputted song already exists within the list
bool duplicate(Node *head, char *input){
	if (head == NULL)
		return false;
	Node *q = head;
	while (strcmp(q->songName, input) != 0){
		if (q->next == NULL){
			return false;
		}
		q = q->next;
	}
	return true;
}

//This function searches for user input within the list and then finds if the input exists within the list. If it does, it will print
//all the details of the song.
void searchList(char *search, Node *head){
	Node *q = head;
	while (strcmp(q->songName, search) != 0){
		if (q->next == NULL){
			songNameNotFound(search);
			return;
		}
		q = q->next;
	}
	songNameFound(search);
	printf("\n%s\n%s\n%s\n", q->songName, q->artist, q->genre);
	
}

//This function allows the user to quit the library and will free all dynamically allocated memory.
Node * quit(Node *head){
	Node *q = head;
	while (q != NULL){
		head = q;
		songNameDeleted(head->songName);
		free(head->songName);
		free(head->genre);
		free(head->artist);
		free(head);
		head = NULL;

		q = q->next;
	}
	free(q);
	return head;
}