typedef unsigned short ushort;
typedef unsigned long ulong;


ushort DevMem[0x100] = {1,2,3,4,5};
ushort HSTK;

void InstSTMLD(ulong DevAdr) {
	HSTK = DevMem[DevAdr];
}

void InstSTOUT(ulong DevAdr) {
	DevMem[DevAdr] = HSTK;
}

