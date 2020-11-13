#pragma once
int fact(int n)
{
    int i, fact = 1;
    for (i = 1; i <= n; i++)
    {
        fact = fact * i;  
        std::cout << i << " " << fact << "\n";
           
    }
return fact;

}

