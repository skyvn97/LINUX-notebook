int phi[n];
for (int i = 0; i < n; i++) phi[i] = i;	
for (int i = 1; i < n; i++) 
	for (int j = 2 * i; j < n; j += i)
		phi[j] -= phi[i];
