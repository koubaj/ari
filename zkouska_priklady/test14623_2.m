A = [1, 3;
    0 0]
B = [2; -3]

poly = [1, 18, 9];
poles = roots(poly)

K = acker(A, B, poles)