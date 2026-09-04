extern int D_0054C92C[];
extern int _decodeOrSkipFrame(void);
extern int _decodeOrSkipField(void);

int _decodeOrSkip(void) {
    if (D_0054C92C[0] == 3) {
        return _decodeOrSkipFrame();
    }
    return _decodeOrSkipField();
}
