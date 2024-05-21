#include <stdio.h>
#include <stdlib.h>
// SAVMPIZELIZWAVUYAERIJCXCSPYFZCX

/* function converts all alphabets to uppercase and
   removes characters except alphabets and white space */
char * filter(char *inp_txt){

    /* removes characters except alphabets and white spaces */
    for(int i = 0; i < strlen(inp_txt); i++){
        inp_txt[i] = toupper(inp_txt[i]);
        if(!(isalpha(inp_txt[i]) || inp_txt[i] == ' ')){
           strcpy(&inp_txt[i], &inp_txt[i+1]);
           i--;
        }
    }
/* returns the input after removing unwanted characters
   and converting to uppercase */
    return inp_txt;
}

/* function finds the index of input characters from alphabet_arr */
char * alpha_index(int *indx_arr, char *inp_txt, char *alphabet_arr){

    for(int i = 0; i < strlen(inp_txt); i++){
        for(int j = 0; j < strlen(alphabet_arr); j++){
            if(inp_txt[i] == alphabet_arr[j]){
                indx_arr[i] = j;
                break;
            }
        }
    }

    /* returns the indexes */
    return indx_arr;
}


/* function encrypts the plain text */
char encrypt(int *indx_arr, char *alphabet_arr, char *inp_txt, int key1, int key2){
/* numerical  shifting*/
    for(int i = 0; i < strlen(inp_txt); i++){
        indx_arr[i] = (indx_arr[i] * key1) + key2;
        if(indx_arr[i] > 25){
            indx_arr[i] = indx_arr[i] % 26;
        }
    }

/* assigning corresponding alphabets */
    char output[strlen(inp_txt)];
    for(int i = 0; i < strlen(inp_txt); i++){
        for(int j = 0; j < strlen(alphabet_arr); j++){
            if(indx_arr[i] == j){
                output[i] = alphabet_arr[j];
            }
        }
    }


/* output text */
    printf("\nYour Encrypted Message is: %s", output);
}

/* function decrypts the cipher text */
char decrypt(int *indx_arr, char *alphabet_arr, char *inp_txt, int key1, int key2){

    int a_inv = 0;
    int flag = 0;

    //Find a^-1 (the multiplicative inverse of a
        //in the group of integers modulo m.)
    for (int i = 0; i < 26; i++)
    {
        flag = (key1 * i) % 26;

        //Check if (a*i)%26 == 1,
                //then i will be the multiplicative inverse of a
        if (flag == 1)
        {
            a_inv = i;
            printf("a inverse: %d\n", i);
        }
    }

/* numerical  shifting*/
    for(int i = 0; i < strlen(inp_txt); i++){

        printf("\nindex of E before: %d, key2: %d", indx_arr[i], key2);

        indx_arr[i] = a_inv * (indx_arr[i] - key2) % 26;
        printf("\nind - k2: %d,\n(ind - k2) * a-inv: %d,\nafter mod: %d", (indx_arr[i] - key2), a_inv * (indx_arr[i] - key2), indx_arr[i]);
		}


/* assigning corresponding alphabets */
    char output[strlen(inp_txt)];
    for(int i = 0; i < strlen(inp_txt); i++){
        for(int j = 0; j < strlen(alphabet_arr); j++){
            if(indx_arr[i] == j){
                output[i] = alphabet_arr[j];
            }
        }
    }

/* output text */
    printf("\nYour Decrypted Message is: %s", output);
}


int main(){
    char flag;
    do{

        /* prompt user: encrypt or decrypt */
        printf("\n\nSelect option:\n Encrypt = 1\n Decrypt = 2\nSelection:  ");
        int x;
        scanf("%d", &x);
        getchar();

        /* Alphabet array */
        char alphabet_arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                               'H', 'I', 'J', 'K', 'L', 'M', 'N',
                               'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                               'V', 'W', 'X', 'Y', 'Z' };

        /* Variables to store user input */
        char inp_txt[100];

        int key1, key2;

        /* Encryption: User input and encryption function call */
        if(x == 1){
            printf("\nEnter message to encrypt: ");
            fgets(inp_txt, 100, stdin);

            printf("\nEnter first encryption key: ");
            scanf("%d", &key1);

            printf("\nEnter second encryption key: ");
            scanf("%d", &key2);

            /* array declared with input message size to store indexes */
            int indx_arr[strlen(inp_txt)];
            /* function encrypt passed user inputs and alphabet array */
            encrypt(alpha_index(indx_arr, inp_txt, alphabet_arr), alphabet_arr, filter(inp_txt), key1, key2);
        }

        /* Decryption: User input and decryption function call */
        else if(x == 2){
            printf("\nEnter message to decrypt: ");
            fgets(inp_txt, 100, stdin);

            printf("\nEnter first decryption key: ");
            scanf("%d", &key1);

            printf("\nEnter second decryption key: ");
            scanf("%d", &key2);

            /* array declared with input message size to store indexes */
            int indx_arr[strlen(inp_txt)];
            /* function decrypt passed user inputs and alphabet array */
            decrypt(alpha_index(indx_arr, inp_txt, alphabet_arr), alphabet_arr, filter(inp_txt), key1, key2);
        }

        getchar();
        printf("\n\n\nRun the program again?(Y/N): ");
        scanf("%c", &flag);

    }while(flag == 'y' || flag == 'Y');

    return 0;
}


