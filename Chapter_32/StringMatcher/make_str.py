import numpy as np

def make_str(txt_size=None):
    alphabet = np.array([chr(i) for i in range(65, 65 + 26)])
    char_set_size = np.random.randint(4, 9)
    char_set = np.random.choice(alphabet, char_set_size, replace=False)
    if txt_size is None:
        txt_size = np.random.randint(1000, 5000)
    print("Text length:", txt_size)
    txt = ""
    for i in range(txt_size):
        if((i + 1) % (txt_size / 5) == 0):
            print("[{}/{}] generated...".format(i + 1, txt_size))
        txt += np.random.choice(char_set)
    pat_size = np.random.randint(5, 11)
    txt_idx = np.random.randint(0, txt_size - pat_size)
    pat = txt[txt_idx:txt_idx + pat_size]
    return txt, pat, char_set