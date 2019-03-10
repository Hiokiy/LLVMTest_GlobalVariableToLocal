
int main(void);
inline void sub1(void);
inline void sub2(void);

int giData;

int main(void) {

	sub1();
	sub2();

    return 0;
}

inline void sub1(void) {
	
	int liData;

	liData = 5;
	giData = 6;

}

inline void sub2(void) {
	
	int liData;

	liData = 7;
	giData = 8;

}

