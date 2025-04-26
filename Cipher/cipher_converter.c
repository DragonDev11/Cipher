char** generate_cipher_pattern(char* string, int size){
    int checker[256] = {0};
    for (int i=0; i<size; i++){
        unsigned char ch = string[i];

        if (checker[ch]){
            return;
        }

        checker[ch] = 1;
    }

    
}