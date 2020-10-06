#include "reducer.h"
finalKeyValueDS* fkvds;

// create a key value node
finalKeyValueDS *createFinalKeyValueNode(char *word, int count){
	finalKeyValueDS *newNode = (finalKeyValueDS *)malloc (sizeof(finalKeyValueDS));
	strcpy(newNode -> key, word);
	newNode -> value = count;
	newNode -> next = NULL;
	return newNode;
}

// insert or update an key value
finalKeyValueDS *insertNewKeyValue(finalKeyValueDS *root, char *word, int count){
	finalKeyValueDS *tempNode = root;
	if(root == NULL)
		return createFinalKeyValueNode(word, count);
	while(tempNode -> next != NULL){
		if(strcmp(tempNode -> key, word) == 0){
			tempNode -> value += count;
			return root;
		}
		tempNode = tempNode -> next;
	}
	if(strcmp(tempNode -> key, word) == 0){
		tempNode -> value += count;
	} else{
		tempNode -> next = createFinalKeyValueNode(word, count);
	}
	return root;
}

// free the DS after usage. Call this once you are done with the writing of DS into file
void freeFinalDS(finalKeyValueDS *root) {
	if(root == NULL) return;

	finalKeyValueDS *tempNode = root -> next;;
	while (tempNode != NULL){
		free(root);
		root = tempNode;
		tempNode = tempNode -> next;
	}
}

// reduce function
void reduce(char *key) {
	char filename[256];
	int temp; //,count;
	//count = 0;
	int count = 0;
	FILE* fp = fopen(key, "r");
	fscanf(fp, "%s", filename);
	
	while(temp = fgetc(fp) != EOF){
		if(temp == 1){
			count++;
		}
	}
	fkvds = insertNewKeyValue(fkvds, filename, count);
	fclose(fp);
	
}

// write the contents of the final intermediate structure
// to output/ReduceOut/Reduce_reducerID.txt
void writeFinalDS(int reducerID){
	if (fkvds == NULL){
		return;
	}
	
	finalKeyValueDS* temp = fkvds -> next;
	
	char filename[256];
	char* word = temp -> key;
	
	sprintf(filename, "output/ReduceOut/Reducer_%d.txt", reducerID);
	FILE* fp = fopen(filename, "w");
	
	while(temp != NULL){
		fprintf(fp, "%s ", temp -> key);
		fprintf(fp, "%d ", temp -> value);
		fputs("\n", fp);
		fkvds = temp;
		temp = temp -> next;
	}
	fclose(fp);
}

int main(int argc, char *argv[]) {

	if(argc < 2){
		printf("Less number of arguments.\n");
		printf("./reducer reducerID");
	}

	// ###### DO NOT REMOVE ######
	// initialize 
	int reducerID = strtol(argv[1], NULL, 10);

	// ###### DO NOT REMOVE ######
	// master will continuously send the word.txt files
	// alloted to the reducer
	char key[MAXKEYSZ];
	while(getInterData(key, reducerID))
		reduce(key);

	// You may write this logic. You can somehow store the
	// <key, value> count and write to Reduce_reducerID.txt file
	// So you may delete this function and add your logic
	writeFinalDS(reducerID);

	return 0;
}
