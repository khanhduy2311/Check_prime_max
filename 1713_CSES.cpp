#include <bits/stdc++.h>
#define int long long
#define task "Divisions_Fermat."

using namespace std;

long long indian_multiplication(long long a, long long b, long long mod)
{
    if (b == 0)
        return 0LL;

    long long half = indian_multiplication(a, b / 2LL, mod) % mod;

    if (b & 1)
        return (half + half + a) % mod;
    else
        return (half + half) % mod;
}

long long modular_exponentiation(long long a, long long b, long long mod)
{
    if (b == 0)
        return 1LL;

    long long half = modular_exponentiation(a, b / 2LL, mod) % mod;
    long long product = indian_multiplication(half, half, mod);

    if (b & 1)
        return indian_multiplication(product, a, mod);
    else
        return product;
}
bool fermat_checking(long long n, int k = 50)
{
    if (n < 4)
        return n == 2 || n == 3;
    
    if (n != 2 && n % 2 == 0)
        return false;
        
    for (int i = 1; i <= k; ++i)
    {
        long long a = 2 + rand() % (n - 3);
        if (modular_exponentiation(a, n - 1, n) != 1)
            return false;
    }
    
    return true;
}

vector < int > eratosthenes_sieve(int max_value)
{
    vector < bool > is_prime(max_value + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= max_value; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= max_value; j += i)
                is_prime[j] = false;

    vector < int > primes;
    for (int i = 2; i <= max_value; ++i)
        if (is_prime[i])
            primes.push_back(i);

    return primes;
}
 vector < int > primes = eratosthenes_sieve(1000000);
void solution(int n)
{

   
    long long res = 1;
    for (int p: primes)
    {
        if (p * p * p > n)
            break;

        int cnt = 0;
        while (n % p == 0)
        {
            n /= p;
            ++cnt;
        }

        res *= (cnt + 1);
    }
    if (fermat_checking(n))
        res *= 2LL;
    else
    {
        int squaroot = sqrt(n);
        if (squaroot * squaroot == n && fermat_checking(squaroot))
            res *= 3;
        else if (n != 1)
            res *= 4;
    }

    cout << res<<endl;
}
void fast(){
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}
signed main()
{
    fast();
	int t;
	cin >> t;
	int n;
	while (t--){
        cin >> n;
		solution(n);
	}
	
    return 0;
}
/* write by kduy in 5/8/2024 */