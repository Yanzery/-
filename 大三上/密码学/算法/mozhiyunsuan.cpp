int ModExp(int x, int y, int mod)
{    int res = 1;    
		 while(y)   
	  {        
						 if(y & 1) 
						 res =  res * x % mod;        
						 x = x * x % mod;       
					  y = y / 2;   
		}    
		return res;
} 




