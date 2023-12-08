#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct rightNode{
	char rname[10];
	struct rightNode* rnext;
};

struct production{
	char lname;	
	char** terminalFirst;
	
	char first[15];
	int firstCount;
	int isFirstCalculated;
	
	char follow[15];
	int followCount;
	int isFollowCalculated;
	
	struct rightNode* rnode;
	struct production* prodNext;
};

struct production* productionFront = NULL;
struct production* productionRear = NULL;
struct production* productionNow = NULL;

struct rightNode* rightTop = NULL;

struct production* isNonTerminal(char ch){ //Whether a character is a Terminal or Not
	struct production* tempProd = productionFront;
	while(tempProd != NULL){
		if(tempProd->lname == ch) return tempProd;
		tempProd = tempProd->prodNext;
	}
	return NULL;
}

int isPresent(char* string, char ch){ //Whether a character present in the String or Not
	int i = 0;
	while(string[i] != '\0'){
		if(string[i] == ch) return 1;
		i++;
	}
	return 0;
}

void calculatingFirst(struct production* tempProd){
	if(!tempProd->isFirstCalculated){
		tempProd->isFirstCalculated = 1;
		struct rightNode* tempNode = tempProd->rnode;
		while(tempNode != NULL){
			int i, count = 0;
			while(1){
				int flag = 0;
				struct production* tempProd2 = isNonTerminal(tempNode->rname[count]);
				if(tempProd2 != NULL){
					calculatingFirst(tempProd2);
					for(i=0;i<tempProd2->firstCount;i++){
						if(tempProd2->first[i] == '#' && tempNode->rname[count+1] != '\0'){
							count++; flag = 1;
						} else if(!isPresent(tempProd->first, tempProd2->first[i])){
							strncat(tempProd->first, tempProd2->first+i, 1);
							tempProd->firstCount++;
						}
					}
					if(!flag) break;
				} else {
					if(tempNode->rname[count] == '#' && tempNode->rname[count+1] != '\0'){
							count++; flag = 1;
					} else if(!isPresent(tempProd->first, tempNode->rname[count])){
						strncat(tempProd->first, tempNode->rname+count, 1);
						tempProd->firstCount++;
					}
					if(!flag) break;
				}
			}
		tempNode = tempNode->rnext;
		}
	}
}

void calculatingFollow(struct production* tempProd){
	if(!tempProd->isFollowCalculated){
		tempProd->isFollowCalculated = 1;
		int i, j;
		struct production* tempProd2 = productionFront;
		while(tempProd2 != NULL){
			struct rightNode* tempNode = tempProd2->rnode;
			while(tempNode != NULL){
				for(i=0;i<strlen(tempNode->rname);i++){
					if(tempProd->lname == tempNode->rname[i]){
						int count = 1;
						char temp[15] = "";
						while(1){
							if(tempNode->rname[i+count] == '\0'){
								calculatingFollow(tempProd2);
								for(j=0;j<tempProd2->followCount;j++){
									if(!isPresent(tempProd->follow, tempProd2->follow[j])){
										strncat(tempProd->follow, tempProd2->follow+j, 1);
										tempProd->followCount++;
									}
								}
								break;
							} else {
								int flag = 0;
								struct production* tempProd3 = isNonTerminal(tempNode->rname[i+count]);
								if(tempProd3 != NULL){
									for(j=0;j<tempProd3->firstCount;j++){
										if(tempProd3->first[j] == '#'){
											count++; flag = 1;
										} else if(!isPresent(tempProd->follow, tempProd3->first[j])){
											strncat(tempProd->follow, tempProd3->first+j, 1);
											tempProd->followCount++;
										}
									}
									if(!flag) break;
								} else {
									if(tempNode->rname[i+count] == '#'){
										count++; flag = 1;
									} else if(!isPresent(tempProd->follow, tempNode->rname[i+count])){
										strncat(tempProd->follow, tempNode->rname+i+count, 1);
										tempProd->followCount++;
									}
									if(!flag) break;
								}
							}
						}
					}
				}
				tempNode = tempNode->rnext;
			}
			tempProd2 = tempProd2->prodNext;
		}
	}
}

//Terminals List
char terminals[20]; 
int sizeofTerminals = 0;

int isExist(char ch){ //Whether a char is a terminal or Not
	int i = 0;
	while(terminals[i] != '\0'){
		if(terminals[i] == ch) return 1;
		i++;
	}
	return 0;
}
void gatherTerminal(char ch){ //Collecting the terminals
	if(ch != '\0' && ch != '#' && !isExist(ch) && !isNonTerminal(ch)){
		terminals[sizeofTerminals] = ch;
		sizeofTerminals++;
	}
}

int main(){
	int size;// termSize, nonTermSize;
	char input[10];

	printf("Enter Size: ");
	scanf("%d",&size);
	fflush(stdin);

	{//Taking Grammer For Input
		int i;
		printf("Enter Production:\n");
		while(size--){
			scanf("%s",input);
	
			productionNow = (struct production*)malloc(sizeof(struct production));
			productionNow->rnode = NULL;
			productionNow->prodNext = NULL;
			
			productionNow->first[0] = '\0';
			productionNow->follow[0] = '\0';
			
			productionNow->firstCount = 0;
			productionNow->followCount = 0;
			
			productionNow->isFirstCalculated = 0;
			productionNow->isFollowCalculated = 0;
			
			rightTop = (struct rightNode*)malloc(sizeof(struct rightNode));
			rightTop->rnext = NULL;
			
			//Collecting Left Side
			productionNow->lname = input[0];
			
			//Collecting Right Side
			for(i=2;i<=strlen(input);i++) rightTop->rname[i-2] = input[i];
			
			//Storing Production
			struct production* tempProd = isNonTerminal(productionNow->lname);
			if(tempProd == NULL){
				productionNow->rnode = rightTop;
				if(productionFront == NULL && productionRear == NULL){
					productionFront = productionRear = productionNow;	
				} else {
					productionRear->prodNext = productionNow;
					productionRear = productionRear->prodNext;
				}
			} else {
				struct rightNode* tempNode = tempProd->rnode;
				tempProd->rnode = rightTop;
				tempProd->rnode->rnext = tempNode;
			}
		}
	}
	system("cls");
	
	{//Calculating Firsts
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			calculatingFirst(tempProd);
			tempProd = tempProd->prodNext;
		}
	}

	productionFront->follow[0] = '$';
	productionFront->follow[1] = '\0';
	productionFront->followCount = 1;
	
	{//Calculating Follow
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			calculatingFollow(tempProd);
			tempProd = tempProd->prodNext;
		}
	}
	
	{//Printing the Grammer
		int i;
		struct production* tempProd = productionFront;
		printf("----------------------------------------Productions----------------------------------------\n");
		while(tempProd != NULL){
			//Printing eft Side
			printf("%c->",tempProd->lname);
			struct rightNode* tempNode = tempProd->rnode;
			//Printing Right Side
			while(tempNode != NULL){
				printf(" %s",tempNode->rname);
				tempNode = tempNode->rnext;
				if(tempNode != NULL) printf(" |");
			}
			//Printing Firsts
			printf("\nFirst: {");
			for(i=0;i<tempProd->firstCount;i++) printf(" %c",tempProd->first[i]);
			printf(" }\t"); 
			//Printing Follow
			printf("Follow: {");
			for(i=0;i<tempProd->followCount;i++) printf(" %c",tempProd->follow[i]);
			printf(" }\n");
			tempProd = tempProd->prodNext;
		}	
	}
	
	{//Storing Terminals
		int i;
		gatherTerminal('$');
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			struct rightNode* tempNode = tempProd->rnode;
			while(tempNode != NULL){
				for(i=0;i<strlen(tempNode->rname);i++){
					gatherTerminal(tempNode->rname[i]);
				}
				tempNode = tempNode->rnext;
			}
			tempProd = tempProd->prodNext;
		}
	}
	
	{//Initializing Space
		int i;
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			tempProd->terminalFirst = (char**)malloc(sizeofTerminals*sizeof(char*));
			for(i=0;i<sizeofTerminals;i++){
				tempProd->terminalFirst[i] = (char*)malloc(15);
				strcpy(tempProd->terminalFirst[i], "NAN");
			} 
			tempProd = tempProd->prodNext;
		}
	}
	
	{//LL1 Parsing Table
		int i, j;
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			struct rightNode* tempNode = tempProd->rnode;
			while(tempNode != NULL){
				char temp[20] = "";
				char prod[15] = "";
				strncat(prod, &tempProd->lname, 1);
				strcat(prod, "=");
				strcat(prod, tempNode->rname);
				int count = 0;
				while(1){
					int flag = 0;
					struct production* tempProd2 = isNonTerminal(tempNode->rname[count]);
					if(tempProd2 != NULL){
						for(i=0;i<tempProd2->firstCount;i++){
							if(tempProd2->first[i] == '#' && tempNode->rname[count+1] != '\0'){
								count++; flag = 1;
							} else{
								if(tempProd2->first[i] == '#'){
									for(j=0; j<tempProd->followCount;j++){
										if(!isPresent(temp, tempProd->follow[j])){
											strncat(temp, tempProd->follow+j, 1);
										}
									}
								} else if(!isPresent(temp, tempProd2->first[i])){
									strncat(temp, tempProd2->first+i, 1);
								}
							}
						}
						if(!flag) break;
					} else{
						if(tempNode->rname[count] == '#'){
							for(j=0; j<tempProd->followCount;j++){
								if(!isPresent(temp, tempProd->follow[j])){
									strncat(temp, tempProd->follow+j, 1);
								}
							}
						} else {
							strncat(temp, tempNode->rname+count, 1);
						}
						break;
					}
				}
				
				for(i=0;i<strlen(temp);i++){
					for(j=0;j<sizeofTerminals;j++){
						if(temp[i] == terminals[j]){
							if(strcmp(tempProd->terminalFirst[j], "NAN")){
								strcpy(tempProd->terminalFirst[j], "ERROR");
							}
							else strcpy(tempProd->terminalFirst[j], prod);
						}
					}
				}
				tempNode = tempNode->rnext;
			}
			tempProd = tempProd->prodNext;
		}	
	}
	
	{//Printing The Table
		int i;
		printf("\n----------------------------------------LL1 Parsing Table----------------------------------------");
		printf("\nT\t\t");
		for(i=0;i<sizeofTerminals;i++) printf("|\t%c\t",terminals[i]);
		printf("\nNT");
		
		struct production* tempProd = productionFront;
		while(tempProd != NULL){
			printf("\n%c\t\t",tempProd->lname);
			for(i=0;i<sizeofTerminals;i++){
				if(strcmp(tempProd->terminalFirst[i], "") == 0) printf("|\t\t",tempProd->lname);
				else printf("|\t%s\t",tempProd->terminalFirst[i]);
			}
			tempProd = tempProd->prodNext;
		}	
	}
	return 0;
}
