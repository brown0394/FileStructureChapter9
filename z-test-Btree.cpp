//data file에 가변길이 레코드를 저장하고 index로서 btree를 사용한다.
#include <iostream>
#include <string>
#include "btree.h"
#include "recording.h"
#include "length.h"
#include "strclass.h"
using namespace std;

//const char** keys;

const int BTreeSize = 4;

char* getKey(char* targetKey, int keyLength) {//make all of the key length same.
	char* key = new char[keyLength+1];
	int i = 0;
	for (; i < strlen(targetKey); ++i) {
		key[i] = targetKey[i];
		if (i == keyLength && strlen(targetKey) >= keyLength) 
			break;
	}
	for (; i < keyLength; ++i) {
		key[i] = '0';
	}
	key[i] = '\0';
	delete[] targetKey;
	return key;
}

template <class recordType>
void readDataFile(RecordFile<recordType>& dataFile) {
	int result;
	recordType record;
	dataFile.Rewind();
	while (true) {
		result = dataFile.Read(record);
		if (result == -1) break;
		cout << record << endl;
	}
}

template <class BTreeType, class RecordType>
void writeFile(BTree<BTreeType>& bt, RecordFile<RecordType>& dataFile) {
	int recAddr;
	//write records
	Recording* R[20];

	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	R[10] = new Recording("1LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[11] = new Recording("1RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[12] = new Recording("1WAR", "23699", "Touchstone", "Corea", "Corea");
	R[13] = new Recording("1ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[14] = new Recording("1COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[15] = new Recording("1DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[16] = new Recording("1MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[17] = new Recording("1COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[18] = new Recording("1DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[19] = new Recording("1FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");

	int result;
	//keys = new const char* [20];
	for (int i = 0; i < 20; i++)
	{
		recAddr = dataFile.Append(*R[i]);//data file에 가변길이 record를 저장
		//keys[i] = (*R[i]).Key();//getKey((*R[i]).Key(), 7);//sizeof keyType is 8 using String class.
		char* key = (*R[i]).Key();
		result = bt.Insert(key, recAddr);
		bt.Print(cout);
		delete[] key;
	}

	for (int i = 0; i < 20; ++i) {
		delete[] R[i];
		//delete[] keys[i];
	}
	//delete[] keys;
	//keys = nullptr;
}

template <class BTreeType, class RecordType>
void readFile(BTree<BTreeType>& bt, RecordFile<RecordType>& dataFile) {
	cout << "\nRead File in Entry Sequenced Order" << endl;
	readDataFile(dataFile);
	cout << "\nRead File in Sorted Order" << endl;
	bt.PrintSorted(dataFile);
}

int processFile() {
	LengthFieldBuffer Buffer;
	BTree <String> bt(BTreeSize, 10);
	RecordFile<Recording> dataFile(Buffer);
	
	int result = dataFile.Create("btreedata.dat", ios::out | ios::in);
	if (result == -1) {
		cout << "Please delete btreedata.dat" << endl;
		system("pause");
		return 0;
	}
	result = bt.Create("btree.dat", ios::out | ios::in);
	if (!result) {
		cout << "Please delete btree.dat" << endl;
		system("pause");
		return 0;
	}

	writeFile(bt, dataFile);
	readFile(bt, dataFile);
	dataFile.Close();
	bt.Close();
}

int main(int argc, char* argv) {
	processFile();
	system("pause");
	return 1;
}