// Sourse : https://leetcode.com/problems/longest-palindromic-substring/
// Author : Cecilia Chen
// Date   : 2015-10-28

/***********************************************************************
 *
 * Given a string S, find the longest palindromic substring in S. 
 * You may assume that the maximum length of S is 1000, 
 * and there exists one unique longest palindromic substring.
 *
 **********************************************************************/
 
class Solution {
public:
	// 8ms. O(n). Manacher Algorithm
	string longestPalindrome1(string s) {
		string T = s;
		for(int i=s.size(); i>=0; i--)
			T.insert(i, 1, '#');
		T.insert(0, 1, '>');
		T += '<';
		int P[2001] = {0};
		int c(0), r(0), max(0);
		for(int i = 1; i < T.size() - 1; i++){
			if(r > i) P[i] = min(P[2 * c - i], r - i);	// Mirror
			while(T[i+P[i]+1] == T[i-P[i]-1]) ++P[i];	// Expand
			if(P[i] + i > r) { c = i;  r = P[i] + i; }	// Update current center index
			if(P[i] > P[max]) max = i;
		}
		return s.substr( (max-P[max]-1)/2, P[max] );
	}
	
	// 4ms. Is it O(nlogn)?
	string longestPalindrome2(string s) {
		if (s.size() < 2) return s;
		int begin(0), len(1);
		for (int i = 0; i < s.size();) {
			if (s.size() - i <= len / 2) break;
			int left = i, right = i;
			while (right < s.size()-1 && s[right+1] == s[right]) ++right;	// Skip duplicate characters -> for even substring
			i = right + 1;
			while (right<s.size()-1 && left>0 && s[right+1] == s[left-1]) {	// Expand
				++right; 
				--left; 
			}
			int newLen = right-left+1;  // pre-store (right-left+1)
			if (len < newLen) { 		// >> runtime: 8ms->4ms  【贱人就是矫情(..•˘_˘•..)
				begin = left; 
				len = newLen;
			}
		}
		return s.substr(begin, len);
	}
};