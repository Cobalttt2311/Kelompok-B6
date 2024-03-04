//Aes_descrypt, mendekripsi blok data menggunakan kunci yang telah diberikan.
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
    // keySize yang diperluas
    int expandedKeySize;

    // jumlah putaran
    int nbrRounds;

    // kunci yang diperluas
    unsigned char *expandedKey;

    // blok 128 bit untuk memecahkan kode
    unsigned char block[16];

    int i, j;

    // set the number of rounds
    switch (size)
    {
    case SIZE_16:
        nbrRounds = 10;
        break;
    case SIZE_24:
        nbrRounds = 12;
        break;
    case SIZE_32:
        nbrRounds = 14;
        break;
    default:
        return ERROR_AES_UNKNOWN_KEYSIZE;
        break;
    }

    expandedKeySize = (16 * (nbrRounds + 1));

    expandedKey = (unsigned char *)malloc(expandedKeySize * sizeof(unsigned char));

    if (expandedKey == NULL)
    {
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }
    else
    {
        /* Mengatur nilai blok, untuk blok tersebut:
         * a0,0 a0,1 a0,2 a0,3
         * a1,0 a1,1 a1,2 a1,3
         * a2,0 a2,1 a2,2 a2,3
         * a3,0 a3,1 a3,2 a3,3
         * urutan pemetaan adalah a0,0 a1,0 a2,0 a3,0 a0,1 a1,1 ... a2,3 a3,3
         */

        // melakukan iterasi pada kolom-kolom
        for (i = 0; i < 4; i++)
        {
            // melakukan iterasi pada baris
            for (j = 0; j < 4; j++)
                block[(i + (j * 4))] = input[(i * 4) + j];
        }

        // memperluas kunci menjadi kunci 176, 208, 240 byte
        expandKey(expandedKey, key, size, expandedKeySize);

        // mendekripsi blok menggunakan expandedKey
        aes_invMain(block, expandedKey, nbrRounds);

        // membuka kembali peta blok kedalam output
        for (i = 0; i < 4; i++)
        {
            // melakukan iterasi pada baris
            for (j = 0; j < 4; j++)
                output[(i * 4) + j] = block[(i + (j * 4))];
        }

        // Dealokasi memori
        free(expandedKey);
        expandedKey = NULL;
    }

    return SUCCESS;
}
