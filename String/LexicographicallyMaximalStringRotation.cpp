vector<int> maxLex(vector<int> s) {
	s.insert(s.end(), s.begin(), s.end());
	s.push_back(numeric_limits<int>::min());
	int i = 0, j = 1, n = s.size();
	while(j < n) {
		int k = 0;
		while(j + k < n - 1 && s[i + k] == s[j + k]) ++k;
		if(s[i + k] < s[j + k]) i += k + 1;
		else j += k + 1;
		if(i == j) ++j;
	}
	return vector<int>(s.begin() + i, s.begin() + i + n / 2);
}
