# -------[1. Naive String Matcher]--------

def NaiveStringMatcher(txt, pat, char_set, output):
    n = len(txt)
    m = len(pat)
    for s in range(0, n - m + 1):
        if pat == txt[s:s+m]:
            if output == True:
                print("pattern occurs with shift", s)
            
# -------[2. Rabin Karp Matcher]--------
def get_num(c):
    return ord(c.upper()) - ord('A') + 1

def RabinKarp(txt, pat, char_set, output):
    set_size = len(char_set)
    # cd = make_dict(char_set)
    PRIME = 13 # const prime number
    n = len(txt)
    m = len(pat)
    h = set_size ** (m - 1) % PRIME
    pat_num = 0
    txt_num = 0
    for i in range(0, m):
        pat_num = (set_size * pat_num + get_num(pat[i])) % PRIME
        txt_num = (set_size * txt_num + get_num(txt[i])) % PRIME
    for s in range(0, n - m + 1):
        if pat_num == txt_num:
            if pat == txt[s:s+m]:
                if output == True:
                    print("pattern occurs with shift", s)
        if s < n - m:
            txt_num = (set_size * (txt_num - get_num(txt[s]) * h) 
                       + get_num(txt[s + m])) % PRIME
            
# -------[3. Finite Automaton Matcher]--------
def is_prefix(pat, k, q, a):
    s1 = pat[:q] + a
    s2 = pat[:k]
    len_s2 = len(s2)
    f = s1[-len_s2:] == s2
    # print(k, q, a, s1, "<->", s2, "=>", f)
    return f

def ComputeTransitionFunction(pat, char_set):
    # print("k q a")
    func = {}
    m = len(pat)
    for q in range(0, m + 1):
        char_func = {}
        for a in char_set:
            k = min(m, q + 1)
            while(k > 0 and not is_prefix(pat, k, q, a)):
                k = k - 1
            char_func[a] = k
        func[q] = char_func
    return func

def FiniteAutomatonMatcher(txt, pat, char_set, output):
    tf = ComputeTransitionFunction(pat, char_set)
    n = len(txt)
    m = len(pat)
    q = 0 # State, indicats how many chars are matched
    for i in range(n):
        q = tf[q][txt[i]]
        if q == m:
            if output == True:
                print("pattern occurs with shift", i - m + 1)