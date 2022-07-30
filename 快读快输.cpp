namespace io {
	const int N = 1 << 21;
	char bucketR[N], *frontR = bucketR, *backR = bucketR;
	char getchar() {
		return frontR == backR && (backR = bucketR + fread(bucketR, 1, N, stdin)) == (frontR = bucketR) ? EOF : *frontR++;
	}
	template <class type> type read() {
		type res = 0;
		bool f = 0;
		char ch;
		while (!isdigit(ch = getchar()))
			if (ch == '-') f = 1;
		res = ch ^ 48;
		while (isdigit(ch = getchar()))
			res = (res << 3) + (res << 1) + (ch ^ 48);
		return f ? -res : res;
	}
	template <class type> void read(type & x) {x = read<type>();}
	template <class type, class ... args> void read(type & x, args & ... y) {
		read(x);
		read(y ...);
	}
	template <class type> void read(type * x, type * y) {
		for (type * i = x; i != y; ++i) read(*i);
	}
	char bucketW[N], *frontW = bucketW, *backW = bucketW + N;
	void putchar(char ch) {
		if (frontW == backW) {
			fwrite(bucketW, 1, N, stdout);
			frontW = bucketW;
		}
		*frontW++ = ch;
	}
	template <class type> void write(type x) {
		if (x < 0) {
			putchar('-');
			write(-x);
			return;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template <class type, class ... args> void write(type x, args ... y) {
		write(x);
		putchar(' ');
		write(y ...);
	}
	template <class type> void write(type * x, type * y, char c) {
		for (type * i = x; i != y; ++i, putchar(c)) write(*i);
	}
	void flush() {
		fwrite(bucketW, 1, frontW - bucketW, stdout);
	}
}
