// Read each word in the file
    while(fscanf(source, '%s', buffer) == 1)

        // Add each word to the hash table
        {
            node *newWord = malloc(sizeof(node));
            if (newWord == NULL)
            {
                printf("Memory allocation failed\n");
                return false;
            }

            strcpy(newWord.word, buffer);
            int index = hash(buffer);
            newWord->next = table[index];
            table[index] = newWord;
        }
