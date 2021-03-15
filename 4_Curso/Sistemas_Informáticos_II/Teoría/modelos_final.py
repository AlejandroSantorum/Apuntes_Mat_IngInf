import math

def binom(n, k):
    return math.factorial(n) / (math.factorial(k) * math.factorial(n-k))

# Modelo MM1
class MM1:
    def __init__(self, lam, mu, rho=None, L=None, Lq=None, W=None, Wq=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.rho = round(rho, 4) if rho else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None

    def get_rho(self):
        if self.rho is None:
            self.rho = round((self.lam/self.mu), 4)
        return self.rho

    def get_pn(self, n):
        if self.rho is None:
            self.get_rho()
        return round((1-self.rho)*(self.rho)**n, 4)

    def get_L(self):
        if self.L is None:
            if self.rho is None:
                self.get_rho()
            self.L = round(self.rho/(1-self.rho), 4)
        return self.L

    def get_Lq(self):
        if self.Lq is None:
            self.Lq = round(self.lam**2 / (self.mu * (self.mu - self.lam)), 4)
        return self.Lq

    def get_W(self):
        if self.W is None:
            if self.L is None:
                self.get_L()
            self.W = round(self.L/self.lam, 4)
        return self.W

    def get_Wq(self):
        if self.Wq is None:
            if self.Lq is None:
                self.get_Lq()
            self.Wq = round(self.Lq/self.lam, 4)
        return self.Wq

    def get_percentil(self, t):
        return round(1 - math.exp(-(self.mu - self.lam) * t ), 4)

    def get_tiempo(self, perc):
        if self.W is None:
            self.get_W()
        return round(-self.W * math.log(1 - perc), 4)

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_rho()
        self.get_L()
        self.get_Lq()
        self.get_W()
        self.get_Wq()


# Modelo MMc
class MMc:
    def __init__(self, lam, mu, c, rho=None, L=None, Lq=None, W=None, Wq=None, p0=None, Pq=None, pc=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.c = c
        self.rho = round(rho, 4) if rho else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None
        self.p0 = round(p0, 4) if p0 else None
        self.Pq = round(Pq, 4) if Pq else None
        self.pc = round(pc, 4) if pc else None

    def get_rho(self):
        if self.rho is None:
            self.rho = round(self.lam/(self.c*self.mu), 4)
        return self.rho

    def get_p0(self):
        if self.p0 is None:
            last_term = ((self.lam/self.mu)**self.c)/(math.factorial(self.c)*(1-self.rho))
            partial = 0
            for n in range(self.c):
                partial += ((self.lam/self.mu)**n)/(math.factorial(n))
            self.p0 =  round((last_term + partial)**(-1), 4)
        return self.p0

    def get_pn(self, n):
        c = self.c
        lam = self.lam
        mu = self.mu
        p0 = self.get_p0()
        if n < c:
            return round(p0 * ((lam/mu)**n)/(math.factorial(n)), 4)
        else:
            return round(p0 * (((c)**c)/(math.factorial(c))) * (( lam/(c*mu))**n), 4)

    def get_pc(self):
        if self.pc is None:
            self.pc = self.get_pn(self.c)
        return self.pc

    def get_Pq(self):
        if self.Pq is None:
            pc = self.get_pc()
            rho = self.get_rho()
            self.Pq = round(pc/(1-rho), 4)
        return self.Pq

    def get_L(self):
        if self.L is None:
            c = self.c
            rho = self.get_rho()
            Pq = self.get_Pq()
            self.L = round((Pq * rho) / (1 - rho) + c * rho, 4)
        return self.L

    def get_Lq(self):
        if self.Lq is None:
            rho = self.get_rho()
            Pq = self.get_Pq()
            self.Lq = round( Pq * (rho)/(1-rho) , 4)
        return self.Lq

    def get_W(self):
        if self.W is None:
            mu = self.mu
            c = self.c
            lam = self.lam
            Pq = self.get_Pq()
            self.W = round(Pq / (c * mu - lam) + 1/mu, 4)
        return self.W

    def get_Wq(self):
        if self.Wq is None:
            mu = self.mu
            c = self.c
            lam = self.lam
            Pq = self.get_Pq()
            self.Wq = round(Pq / (c * mu - lam), 4)
        return self.Wq

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_rho()
        self.get_p0()
        self.get_pc()
        self.get_Pq()
        self.get_L()
        self.get_Lq()
        self.get_W()
        self.get_Wq()


# Modelo MMcc
class MMcc:

    def __init__(self, lam, mu, c, lamEff=None, pc=None, rho=None, p0=None, L=None, W=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.c = c
        self.p0 = round(p0, 4) if p0 else None
        self.pc = round(pc, 4) if pc else None
        self.rho = round(rho, 4) if rho else None
        self.lamEff = round(lamEff, 4) if lamEff else None
        self.L = round(L, 4) if L else None
        self.Lq = 0
        self.W = round(W, 4) if W else None
        self.Wq = 0

    def get_p0(self):
        if self.p0 is None:
            p0 = 0
            lam = self.lam
            mu = self.mu
            c = self.c
            for n in range(0, c+1):
                p0 += ((lam/mu)**n) * (1 / math.factorial(n))
            self.p0 = round(p0**(-1), 4)
        return self.p0

    def get_pn(self, n):
        if (n > self.c):
            print('Esto no tiene sentido')
            return None
        p0 = self.get_p0()
        lam = self.lam
        mu = self.mu
        return round(p0 * ((lam/mu)**n) * (1/math.factorial(n)), 4)

    def get_pc(self):
        if self.pc is None:
            self.pc = self.get_pn(self.c)
        return self.pc

    def get_lamEff(self):
        if self.lamEff is None:
            lam = self.lam
            pc = self.get_pc()
            self.lamEff = round(lam * (1 - pc), 4)
        return self.lamEff

    def get_rho(self):
        if self.rho is None:
            lam = self.lam
            mu = self.mu
            c = self.c
            pc = self.get_pc()
            self.rho = round( (lam/(c*mu)) * (1 - pc), 4)
        return self.rho

    def get_L(self):
        if self.L is None:
            c = self.c
            rho = self.get_rho()
            self.L = round(c * rho, 4)
        return self.L

    def get_W(self):
        if self.W is None:
            mu = self.mu
            self.W = round(1/mu, 4)
        return self.W

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_p0()
        self.get_pc()
        self.get_lamEff()
        self.get_rho()
        self.get_L()
        self.get_W()


# Modelo MM1K
class MM1K:

    def __init__(self, lam, mu, K, p0=None, pK=None, rho=None, lamEff=None, L=None, Lq=None, W=None, Wq=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.K = K
        self.p0 = round(p0, 4) if p0 else None
        self.pK = round(pK, 4) if pK else None
        self.rho = round(rho, 4) if rho else None
        self.lamEff = round(lamEff, 4) if lamEff else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None

    def get_p0(self):
        if self.p0 is None:
            lam = self.lam
            mu = self.mu
            K = self.K
            if lam == mu:
                self.p0 = round(1/(K+1), 4)
            else:
                quo = lam/mu
                self.p0 = round((1-quo)/(1-(quo)**(K+1)), 4)
        return self.p0

    def get_pn(self, n):
        if n > self.K:
            print('Esto no tiene sentido')
            return None
        lam = self.lam
        mu = self.mu
        p0 = self.get_p0()
        return round(p0 * ((lam/mu)**n), 4)

    def get_pK(self):
        if self.pK is None:
            self.pK = self.get_pn(self.K)
        return self.pK

    def get_lamEff(self):
        if self.lamEff is None:
            lam = self.lam
            pK = self.get_pK()
            self.lamEff = round(lam * (1 - pK), 4)
        return self.lamEff

    def get_rho(self):
        if self.rho is None:
            p0 = self.get_p0()
            self.rho = round(1 - p0, 4)
        return self.rho

    def get_L(self):
        if self.L is None:
            lam = self.lam
            mu = self.mu
            K = self.K
            p0 = self.get_p0()
            if lam == mu:
                self.L = round(K/2, 4)
            else:
                quo = lam/mu
                self.L = round(quo/(1-quo) * ( (1 - (K+1)*(quo)**K + K*(quo)**(K+1)  )  / (1 - (quo)**(K+1)) ), 4)
        return self.L

    def get_Lq(self):
        if self.Lq is None:
            L = self.get_L()
            rho = self.get_rho()
            self.Lq = round(L - rho, 4)
        return self.Lq

    def get_W(self):
        if self.W is None:
            lam = self.lam
            L = self.get_L()
            pK = self.get_pK()
            self.W = round(L / (lam * (1 - pK)), 4)
        return self.W

    def get_Wq(self):
        if self.Wq is None:
            mu = self.mu
            W = self.get_W()
            self.Wq = round(W - 1/mu, 4)
        return self.Wq

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_p0()
        self.get_pK()
        self.get_lamEff()
        self.get_rho()
        self.get_L()
        self.get_Lq()
        self.get_W()
        self.get_Wq()


# Modelo M/M/1/Infinito/M
class MM1InfM():
    def __init__(self, lam, mu, M, p0=None, rho=None, lamEff=None, L=None, W=None, Lq=None, Wq=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.M = M
        self.p0 = round(p0, 4) if p0 else None
        self.rho = round(rho, 4) if rho else None
        self.lamEff = round(lamEff, 4) if lamEff else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None

    def get_p0(self):
        if self.p0 is None:
            M = self.M
            lam = self.lam
            mu = self.mu
            sum = 0
            for n in range(0, M+1):
                sum += (math.factorial(M))/(math.factorial(M-n)) * ((lam/mu)**n)
            self.p0 = round(sum**(-1), 4)
        return self.p0

    def get_pn(self, n):
        p0 = self.get_p0()
        M = self.M
        lam = self.lam
        mu = self.mu
        return round( p0 * (math.factorial(M)/math.factorial(M-n)) * ((lam/mu)**n) , 4)

    def get_rho(self):
        if self.rho is None:
            p0 = self.get_p0()
            self.rho = round(1 - p0, 4)
        return self.rho

    def get_lamEff(self):
        if self.lamEff is None:
            mu = self.mu
            p0 = self.get_p0()
            self.lamEff = round(mu*(1 - p0), 4)
        return self.lamEff

    def get_L(self):
        if self.L is None:
            M = self.M
            mu = self.mu
            lam = self.lam
            rho = self.get_rho()
            self.L = round(M - (mu/lam) * rho , 4)
        return self.L

    def get_Lq(self):
        if self.Lq is None:
            M = self.M
            mu = self.mu
            lam = self.lam
            rho = self.get_rho()
            self.Lq = round(M - (mu/lam) * rho - rho, 4)
        return self.Lq

    def get_W(self):
        if self.W is None:
            M = self.M
            mu = self.mu
            lam = self.lam
            rho = self.get_rho()
            self.W = round(M/(mu * rho) - 1/lam, 4)
        return self.W

    def get_Wq(self):
        if self.Wq is None:
            mu = self.mu
            W = self.get_W()
            self.Wq = round(W - 1/mu, 4)
        return self.Wq

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_p0()
        self.get_rho()
        self.get_lamEff()
        self.get_L()
        self.get_Lq()
        self.get_W()
        self.get_Wq()


# Modelo M/M/c/Infinito/M
class MMcInfM:
    def __init__(self, lam, mu, c, M, p0=None, rho=None, lamEff=None, L=None, Lq=None, W=None, Wq=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4)
        self.c = c
        self.M = M
        self.p0 = round(p0, 4) if p0 else None
        self.rho = round(rho, 4) if rho else None
        self.lamEff = round(lamEff, 4) if lamEff else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None

    def get_p0(self):
        if self.p0 is None:
            c = self.c
            M = self.M
            mu = self.mu
            lam = self.lam
            firstSum = 0
            for n in range(0, c):
                firstSum += binom(M, n) * (lam/mu)**n
            lastSum = 0
            for n in range(c, M+1):
                lastSum += binom(M, n) * (math.factorial(n))/(c**(n-c) * math.factorial(c)) * (lam/mu)**n
            self.p0 = round( (firstSum + lastSum)**(-1) , 4)
        return self.p0

    def get_pn(self, n):
        c = self.c
        M = self.M
        mu = self.mu
        lam = self.lam
        p0 = self.get_p0()
        if n < c and n >= 0:
            return round(p0 * binom(M, n) * (lam/mu)**n , 4)
        elif c < M and c >= n:
            return round(p0 * binom(M, n) * (math.factorial(n))/(c**(n-c) * math.factorial(c)) *(lam/mu)**n , 4)
        else:
            print('Esto no tiene sentido')
            return None

    def get_free(self):
        prob = 0
        c = self.c
        for n in range(0, c):
            prob += (c-n)/(c) * self.get_pn(n)
        return round(prob, 4)

    def get_rho(self):
        if self.rho is None:
            prob = 1
            c = self.c
            for n in range(0, c):
                prob -= (c-n)/(c) * self.get_pn(n)
            self.rho = round(prob, 4)
        return self.rho

    def get_lamEff(self):
        if self.lamEff is None:
            c = self.c
            mu = self.mu
            rho = self.get_rho()
            self.lamEff = round(c * mu * rho, 4)
        return self.lamEff

    def get_L(self):
        if self.L is None:
            M = self.M
            c = self.c
            lam = self.lam
            mu = self.mu
            rho = self.get_rho()
            self.L = round(M - (c * mu/lam) * rho, 4)
        return self.L

    def get_W(self):
        if self.W is None:
            M = self.M
            Ts = 1/self.mu
            c = self.c
            rho = self.get_rho()
            Tc = 1/self.lam
            self.W = round(M * Ts / (c * rho) - Tc, 4)
        return self.W

    def get_Wq(self):
        if self.Wq is None:
            mu = self.mu
            W = self.get_W()
            self.Wq = round(W - 1/mu, 4)
        return self.Wq

    def get_Lq(self):
        if self.Lq is None:
            Wq = self.get_Wq()
            lamEff = self.get_lamEff()
            self.Lq = round(Wq*lamEff, 4)
        return self.Lq

    def __str__(self):
        return str(vars(self))

    def calculate(self):
       self.get_p0()
       self.get_rho()
       self.get_lamEff()
       self.get_L()
       self.get_W()
       self.get_Wq()
       self.get_Lq()


# Modelo M/G/1
class MG1:

    def __init__(self, lam, ES, ES2, mu = None, rho=None, L=None, Lq=None, W=None, Wq=None):
        self.lam = round(lam, 4)
        self.mu = round(mu, 4) if mu else None
        self.ES = round(ES, 4)
        self.ES2 = round(ES2, 4)
        self.rho = round(rho, 4) if rho else None
        self.L = round(L, 4) if L else None
        self.Lq = round(Lq, 4) if Lq else None
        self.W = round(W, 4) if W else None
        self.Wq = round(Wq, 4) if Wq else None

    def get_mu(self):
        if self.mu is None:
            self.mu = round(1/self.ES, 4)
        return self.mu

    def get_rho(self):
        if self.rho is None:
            self.rho = round(self.lam / self.get_mu(), 4)
        return self.rho

    def get_Wq(self):
        if self.Wq is None:
            lam = self.lam
            ES2 = self.ES2
            rho = self.get_rho()
            self.Wq = round(lam * ES2/(2 * (1-rho)), 4)
        return self.Wq

    def get_Lq(self):
        if self.Lq is None:
            lam = self.lam
            ES2 = self.ES2
            rho = self.get_rho()
            self.Lq = round(lam * lam * ES2/(2 * (1-rho)), 4)
        return self.Lq

    def get_W(self):
        if self.W is None:
            lam = self.lam
            ES = self.ES
            ES2 = self.ES2
            rho = self.get_rho()
            self.W = round(lam * ES2/(2 * (1-rho)) + ES, 4)
        return self.W

    def get_L(self):
        if self.L is None:
            lam = self.lam
            ES2 = self.ES2
            rho = self.get_rho()
            self.L = round(lam * lam * ES2/(2 * (1-rho)) + rho, 4)
        return self.L

    def __str__(self):
        return str(vars(self))

    def calculate(self):
        self.get_mu()
        self.get_rho()
        self.get_L()
        self.get_Lq()
        self.get_W()
        self.get_Wq()
