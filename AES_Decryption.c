void aes_invRound(unsigned char *state, unsigned char *roundKey)
{

    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
    invMixColumns(state);
}

void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    int i = 0;

    unsigned char roundKey[16];

    createRoundKey(expandedKey + 16 * nbrRounds, roundKey);
    addRoundKey(state, roundKey);

    for (i = nbrRounds - 1; i > 0; i--)
    {
        createRoundKey(expandedKey + 16 * i, roundKey);
        aes_invRound(state, roundKey);
    }

    createRoundKey(expandedKey, roundKey);
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
}
