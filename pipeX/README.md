
>>so it is not feasible to allocate array of string? Should I extract full path with helper and then free_str_vec inside the helper AND heturn only one full_path string AND then free it inside fork before exit()< not sharing it with parent?<<	...
>>I still donot understand how branches work. Prisiecely: how to use them? Just if(pid > OR < 0)?<<	👉 You don’t “use branches with fork” — you interpret fork’s return value and let each process naturally fall into its own branch.
>>why not 644?<<	https://quickref.me/chmod.html
	 https://gist.github.com/juanarbol/c44e736be70279c1fd5d68aa24f9d8be
👉 Because 0644 is an octal literal in C, while 644 would be treated as a decimal number and produce the wrong permission bits.