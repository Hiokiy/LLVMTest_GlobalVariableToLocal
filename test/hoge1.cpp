int main(int argc, char **argv);
int add(int a, int b);

int main(int argc, char **argv)
{
	int ret = 1;
	int temp1 = 2;
	int temp2 = 3;
	int temp3 = 4;

	if (argc==0) {
		ret = 5;
		temp1 = 7;
	}else{
		ret = 6;
		temp2 = 8;
	}
	temp3 = 5 + 4;
		
	return ret;
}

int add(int a, int b)
{
	return (a+b);
}

