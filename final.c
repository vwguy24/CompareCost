//Luke Reimnitz's Program
/*This program takes two lists of items from stores and compares them to give you a list of where to get
the best deals. It uses File I/O with the command line so you need to enter the files, string manipulation
to compare strings,and change them, structures to build the items, sorting and recursion to sort the items.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 20
//initialize struct, functions and global variables
struct item_def
{
    int items;
    char item[N];
    double cost;
    char store[N];
};
typedef struct item_def item;
int readItems(FILE *ifp, item O[], int items);
int cheapPrice(item store1[], item store2[], item cheapest[], int items, int item2);
int alphabetical(item cheapest[], int items);
int recursion(item one, item two);
void printItems(item one[], int items);
FILE *ifp;
FILE *ifp2;
FILE *ofp;

int main(int argc, char* argv[])
{
    //make sure there are 2 input files and an output file entered
    if (argc != 4)
	{
		printf("Syntax Error: ./a.out <infile> <infile> <outfile>\n");
		exit(1);
	}
	//open necessary files
	ifp = fopen(argv[1], "r");
	ifp2 = fopen(argv[2], "r");
	ofp = fopen(argv[3], "w");
	//initialize struct and items
    struct item_def store1[N];
    struct item_def store2[N];
    int items, item2;
    //read files for items
    readItems(ifp, store1, items);
    readItems(ifp2, store2, item2);
    struct item_def cheapest[N];
    //find cheapest item
    cheapPrice(store1, store2, cheapest, items, item2);
    //sort alphabetically
    alphabetical(cheapest, items);
    //print items to file
    printItems(cheapest, items);
    //close files
	fclose(ofp);
	fclose(ifp);
	fclose(ifp2);


	return 0;
}
int readItems(FILE *ifp, item O[], int items)
{
    //read how many items there are
    fscanf(ifp, "%d", items);
    //put items into struct
    for(int i = 0; i < items; i++){
        fscanf(ifp, "%s", &O[i].item);
        fscanf(ifp, "%lf", &O[i].cost);
    }
}

int cheapPrice(item store1[], item store2[], item cheapest[], int items, int item2){
    //for loop to look through all items and choose cheapest, also says what store
    for(int i = 0; i < items; i++){
        for(int j = 0; j < item2; j++){
            if (store1[i].item == store2[j].item){
                if (store1[i].cost < store2[j].cost){
                    strcpy(cheapest[i].item, store1[i].item);
                    strcpy(cheapest[i].store, "Store 1");
                }
                else{
                    strcpy(cheapest[i].item, store2[j].item);
                    strcpy(cheapest[i].store, "Store 2");
                }
            }
            else{
                strcpy(cheapest[i].store, "Store 1");
            }
        }
    }
}
int alphabetical(item cheapest[], int items){
    //sorts items alphabetically
    for(int i = 0; i < items; i++){
        for(int j = 0; j < items; j++){
            recursion(cheapest[i], cheapest[j]);
        }
    }
}
int recursion(item one, item two){
    //used to execute sorting
    struct item_def temp;
    if(strcmp(one.item,two.item) > 0){
        strcpy(temp.item, one.item);
        strcpy(temp.store, one.store);
        strcpy(one.item, two.item);
        strcpy(one.store, two.store);
        strcpy(two.item, temp.item);
        strcpy(two.store, temp.store);
    }
}
void printItems(item one[], int items){
    //print to file
    for (int i = 0; i < items; i++){
        fprintf(ofp, "%s has the best price on %s\n", one[i].store, one[i].item);
    }
}
