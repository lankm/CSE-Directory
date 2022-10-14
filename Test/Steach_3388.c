#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


struct thread_args{
	int numOfThreads;
	long *values;
	int subArraySize;
	int firstElement;
	int finalElement;
	int fileSize;
	char **text;
	
};



////start of functions that sort without forks and stuff
void bubbleSort(long *values, int x, char text[][30]){
	long temp;
	char tempc[30];

	for(int j = 0; j < x; j++){
		for(int k = 0; k < x-j; k++){
			if(values[k] > values[k+1]){
				temp = values[k];
				values[k] = values[k+1];
				values[k+1] = temp;

				strcpy(tempc, text[k]);
				strcpy(text[k], text[k+1]);
				strcpy(text[k+1], tempc);
			}	
		}
	}
}

void sortNormal()
{
	int fileSize = 20000;	//******CHANGE THIS TO CHANGE THE AMOUNT OF DATA IN CSV FILE*******//
	char filename[256];
	char text[fileSize][30];	
	memset(text,' ', (fileSize * 30));	//initializing array 
	long values[fileSize];
	memset(values,0,fileSize);			//initializing array
	char input[100];
	int i = -1; //counter
	time_t cTime;

	

	//opens file for reading
	strcpy(filename,"data.csv");

	FILE *file;
	file = fopen(filename, "r");

	if(file == NULL){
		printf("Error opening %s\n",filename);
		return;
	}

	//reads data from file
	while(fgets(input,100, file) != NULL)
	{
		char* token;
		char* endptr; //this is for strtol 
		i++;

		token = strtok(input, ",");
		strcpy(text[i], token);
		token = strtok(NULL,"\n");
		values[i] = strtol(token, &endptr, 10);
		//printf("%s, %ld, %d\n",text[i],values[i], i);		
	} 	
	fclose(file);

	time(&cTime);
	printf("Time before sorting without forks %s\n",ctime(&cTime));

	bubbleSort(values, i, text);	//sorts
	
	time(&cTime);
	printf("Time after sorting without forks %s\n",ctime(&cTime));

	//writes sorted arrays back to a new file
	file = fopen("output1.txt","w");
	for(int b = 0; b < i; b++)
		fprintf(file,"%s %ld\n",text[b],values[b]);
	fclose(file);
}
//////end of functions related to sorting without forks and stuff

void Merge(char (*text)[30], long *array, int a1, int a2, int sizeA, int sizeB, int fileSize){//a1 and a2 are the start of each subarray that is getting merged
	long count1 = array[a1];	//holds the next value for one of the split arrays
	long count2 = array[a2];	//holds the next value for one of the split arrays
	char text1[30] = {" "};		//holds the next string for one of the split arrays
	char text2[30] = {" "};		//holds the next string for one of the split arrays
	int size1 = a1 + sizeA;     //tells the function, when to stop moving through the array
	int size2 = a2 + sizeB;		//tells the function, when to stop moving through the array
	int arrayHead = a1;			//points to the next location in the array

	//a1 and a2 also serve as a pointer to the next value to grab once replacement happens
	strcpy(text1,text[a1]);		//setting the first value for text1
	strcpy(text2,text[a2]);		//setting the first value for text2

	//filling out copy arrays, so that original values can still be referenced
	long copyArray[fileSize];
	char copyText[fileSize][30];
	memset(copyText, ' ', (fileSize * 30));
	for(int i = 0; i < fileSize; i++){
		copyArray[i] = array[i];
		strcpy(copyText[i], text[i]);
	}	

	//checks whether a1 or a2 has gone past where it's repective array ends
	while((a1 < size1)|| (a2 < size2)){
		if(count2 < count1){				//these check which value needs to go in the array next
			strcpy(text[arrayHead],text2);
			array[arrayHead++] = count2;

			if((a2 + 1) < size2){
				count2 = copyArray[++a2];		//grab next value in original array
				strcpy(text2, copyText[a2]);	//grab next value in original array
			}
			else{
				count2 = 999999999;
				a2++;
			}
		}
		else if(count1 < count2){			//these check which value needs to go in the array next
			strcpy(text[arrayHead],text1);	
			array[arrayHead++] = count1;

			if((a1 + 1) < size1){
				count1 = copyArray[++a1];		//grab next value in original array
				strcpy(text1, copyText[a1]);	//grab next value in original array
			}
			else{
				count1 = 999999999;
				a1++;
			}
		}
		else{	//for some reason if these are the same then we'll put both in the next spots
			if((a1 != 999999999) && (a2 != 999999999)){
				strcpy(text[arrayHead],text1);
				array[arrayHead++] = count1;
				strcpy(text[arrayHead],text2);
				array[arrayHead++] = count2;
				
				count1 = copyArray[++a1];
				strcpy(text1, copyText[a1]);
				count2 = copyArray[++a2];
				strcpy(text2, copyText[a2]);
			}
		}
	}
}

void MergeAllFiles(char (*text)[30],long *values, int numOfForks, int sizeOfSubArrays, int fileSize){

	int numOfSortedArrays = numOfForks;	//sets the number of arrays that are sorted, each time through the loop will cut the number in half
	int arrayHead = 0;
	int oddArray = 0;
	int oddArraySize;

	while(numOfSortedArrays != 1){	//checks if all arrays are merged
		Merge(text, values,arrayHead, arrayHead+sizeOfSubArrays, sizeOfSubArrays, sizeOfSubArrays, fileSize);
		arrayHead = sizeOfSubArrays*2;

		//if head, still has room in the array to merge & checks for an uneven amount of arrays left(second condtion), cant merge 5 arrays equally
		while((arrayHead < fileSize) && ((arrayHead + (sizeOfSubArrays *2)) <= fileSize)){	
			Merge(text, values,arrayHead, arrayHead+sizeOfSubArrays, sizeOfSubArrays, sizeOfSubArrays, fileSize);
			arrayHead = arrayHead + (sizeOfSubArrays*2);
		}
		if((numOfSortedArrays) % 2 != 0){	//checking if there is not an even amount of arrays left
			oddArray = 1;
			oddArraySize = sizeOfSubArrays;
		}
		numOfSortedArrays = numOfSortedArrays/2; 	//cuts the number of arrays in half
		sizeOfSubArrays = sizeOfSubArrays * 2;		//the size of each array doubles
		arrayHead = 0;								//head resets to the beginning of the array

		if(numOfSortedArrays == 1 && oddArray)	//if there is uneven amount of arrays at some point, combine the last one with the big array
			Merge(text,values,arrayHead, (fileSize - oddArraySize), (fileSize - oddArraySize), oddArraySize, fileSize);
	}
}

void *threadBubbleSort(void *_args){
	long temp;
	char tempc[30];
	struct thread_args *args = (struct thread_args *) _args;
	int x = args->finalElement;
	int k;

	for(int j = 0; j < x; j++){
		for(k = args->firstElement; k < x-j; k++){
			if((args->values[k] > args->values[k+1]) && ((k+1) < args->fileSize)){	
				//second condition prevents k from going out of array

				temp = args->values[k];
				args->values[k] = args->values[k+1];
				args->values[k+1] = temp;

				strcpy(tempc, args->text[k]);
				strcpy(args->text[k], args->text[k+1]);
				strcpy(args->text[k+1], tempc);
			}	
		}
	}
	//for(int i = 0; i < args->finalElement; i++){
		printf("%ld %d\n", args->values[args->firstElement], args->firstElement);
	//}


	return NULL;
}

void sortSubArrays(int numOfForks, long *values, int fileSize, char text[][30], struct thread_args *args[]){
	pthread_t thread[numOfForks];
	int sortSize = ceil(fileSize/numOfForks);

	for(int i = 0; i < numOfForks; i++){
		args[i]->numOfThreads = numOfForks;
		args[i]->subArraySize = sortSize;
		args[i]->firstElement = 0;
		args[i]->finalElement = sortSize;
		args[i]->fileSize = fileSize;

		//args->finalElement = args->finalElement + sortSize;
		pthread_create(&thread[i], NULL, &threadBubbleSort, args[i]);

	}

	for(int i = 0; i < numOfForks; i++){
		if(pthread_join(thread[i],NULL) != 0){
			printf("ERROR : pthread join falied.\n");
			return;
		}

	}
	//for(int i =0; i < fileSize; i++)
		//printf("%ld, %d\n",values[i], i);
	/*char filename[8] = "";
	int subArraysize = fileSize/numOfForks;	
	char subArraySizeString[10];
	sprintf(subArraySizeString,"%d",subArraysize);
	for(int i = 0; i < numOfForks; i++)
	{
		int p = fork(); // child
		if(p == 0)
		{
			sprintf(filename, "%d.txt",i+1);
			char *args[] = {"./sort", filename, subArraySizeString, NULL};	// sort => sorting function
			execv("./sort", args);
		}
	}*/

	//for(int i=0; i < fileSize; i++)
		//strcpy(text[i],args->text[i]);

		
	int b = 0;
	for(int z = 0; z < numOfForks; z++){
		for(int y = 0; y < sortSize && b < fileSize; y++){
			//strcpy(text[b], args[z]->text[y]);
			values[b++] = args[z]->values[y];
		}
	}

}

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("incorrect parameters\n");
		return -1;
	}
	else{

		sortNormal();

		time_t cTime;
		int fileSize = 20000; //******CHANGE THIS TO CHANGE THE AMOUNT OF DATA IN CSV FILE*******//
		char filename[256];
		char text[fileSize][30];	
		memset(text,' ', (fileSize * 30));	//initializing array 
		long values[fileSize];
		memset(values,0,fileSize);			//initializing array
		char input[100];					//buffer to read data from csv file
		int i = -1; 						//counter
		int numOfForks= atoi(argv[1]);		//saving the number of forks

		strcpy(filename,"data.csv");	//static filename for reading data
		FILE *file;
		file = fopen(filename, "r");	//opens file for reading
		if(file == NULL){			//checking to make sure file opens
			printf("Error opening %s\n",filename);
			return 1;
		}

		while(fgets(input,100, file) != NULL)	//reads data on line at a time
		{
			char* token;
			char* endptr; 
			i++;

			token = strtok(input, ",");
			strcpy(text[i], token);
			token = strtok(NULL,"\n");
			values[i] = strtol(token, &endptr, 10);	
		} 	
		fclose(file);

		//break up array
		//breakArray(numOfForks, values, text,fileSize);
		int sizeOfSubArrays = ceil(fileSize/numOfForks);
		int iterator = 0;
		long valuesShared[numOfForks][sizeOfSubArrays];		//seperates array into groups for each fork to sort
		char textShared[numOfForks][sizeOfSubArrays][30];	//seperates array into groups for each fork to sort

		//seperates array into groups for each fork to sort
		for(int k = 0; k < numOfForks; k++){				
			for(int j =0; j < sizeOfSubArrays; j++){
				valuesShared[k][j] = values[iterator];
				strcpy(textShared[k][j],text[iterator]);
				iterator++;
			}
		}
		struct thread_args *args[numOfForks];
		for(int i = 0; i < numOfForks; i++){
			args[i] = malloc(/*sizeof(char[numOfForks][sizeOfSubArrays]) + */sizeof(struct thread_args));
			//args[i]->text = malloc(numOfForks * sizeof(char *));
			//for(int j = 0; j < sizeOfSubArrays; j++)
			//	args[i]->text[j] = malloc(30 * sizeof(char));
		}

		for(int i = 0; i < numOfForks; i++){
			args[i]->values = &valuesShared[i][0];
			args[i]->text[0] = textShared[i][0];
			//strcpy(args[i]->text, textShared[i][0]); //make sure to pass address to first location
			//for(int j = 0; j < sizeOfSubArrays; j++)
				//sprintf(args[i]->text, "%s", textShared[i][j]);
				//args[i]->text[j] = textShared[i][j];
				//strcpy(args[i]->text, textShared[i][j]);
		}
		


		/**print time***/
		time(&cTime);
		printf("Time before starting fork processes and merging %s\n",ctime(&cTime));

		//fork/sort arrays

		sortSubArrays(numOfForks, values, fileSize, text, args);

		//waiting for all child processes
		
		//for(int z=0; z < numOfForks; z++)
		//	wait(NULL);
		
		//re-grabs sorted arrays and saves each one individually
		//int sizeOfSubArrays = ceil(fileSize/numOfForks);
		//char splitArrayText[numOfForks][sizeOfSubArrays][30];
		//long splitArrayLong[numOfForks][sizeOfSubArrays];

		/*
		for(int a = 0; a < numOfForks; a++){
			sprintf(filename,"%d.txt",a+1);
			file = fopen(filename,"r");
			if(file == NULL)
				printf("error opening %s\n",filename);
			else{
				int i = 0;
				fgets(input, 100, file);

				while(!feof(file)){
					sscanf(input, "%s %ld\n", splitArrayText[a][i],&splitArrayLong[a][i]);
					fgets(input, 100, file);
					i++;
				}	 
				fclose(file);
			}
		}
		*/

		//rewrites split arrays back into original arrays
		//probably could've just done this when reading the files, but ran out of time
		/*
		int b = 0;
		for(int z = 0; z < numOfForks; z++){
			for(int y = 0; y < sizeOfSubArrays; y++){
				strcpy(text[b], splitArrayText[z][y]);
				values[b++] = splitArrayLong[z][y];
			}
		}*/
		//merges all the data into one sorted array
		//MergeAllFiles(text,values, numOfForks, sizeOfSubArrays,fileSize);
		
		//	for(int i =0 ; i < fileSize; i++)
		//printf("%ld\n",values[i]);

		/**print time***/
		time(&cTime);
		printf("Time after sorting and merging using forks %s\n",ctime(&cTime));
		//writes output to a file to validate the sorting
		file = fopen("output2.txt","w");
		for(int b = 0; b < i; b++)
			fprintf(file,"%s %ld\n",text[b],values[b]);
		fclose(file);

		for(int i = 0; i < numOfForks; i++){
			for(int j = 0; j < sizeOfSubArrays; j++)
				free(args[i]->text[j]);
			
			//free(args[i]->text);
			free(args[i]);
		}
	}
	
	return 0;
}

