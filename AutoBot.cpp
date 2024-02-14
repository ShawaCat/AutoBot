#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void keydown(int vk, bool dwn) {
	if (dwn) {
		keybd_event(vk, 0, 0, 0);
	} else { keybd_event(vk, 0, KEYEVENTF_KEYUP, 0); }
}


void delayy(int to) {
	Sleep(to);
}

void mclick(bool left, bool dwn) {
	if (left) {
		if (dwn) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		}
		else {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
	else {
		if (dwn) {
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		}
		else {
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}
	}
}

void mouse(int x, int y, bool abso) {
	if (abso) {
		SetCursorPos(x, y);
	} else {
		POINT cp;
		GetCursorPos(&cp);
		SetCursorPos(cp.x + x, cp.y + y);
	}
}

int chkbutt(int kkey) {
	if (GetAsyncKeyState(kkey) == -32767) {
		return 1;
	}
	else { return 0; }
}


int main()
{
	int alp[500] = { 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 
	49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 13, 27, 8, 9, 32, 189, 187, 219, 221, 220, 0, 186, 222, 192, 188, 190, 191, 20, 
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123};
	string coma, nameof, temp, lib[900];
	int arg1, arg2, i=0, iter;
	cout << "Input 2 to use midi or Input 1 to use library or 0 to input name manually: ";
	cin >> i;
	

	if (i == 2) {
		system("start midi\\pmidi.exe");
	}
	else if (i == 1) {
		i = 0;
		ifstream fin("files.txt");
		if (fin.fail()) {
			cout << "Lib is corrupted";
			return 0;
		}
		while (!fin.eof()) {
			fin >> lib[i];
			cout << i + 1 << ". " << lib[i]<<"\n";
			i++;
		}
		fin.close();
		cout << "input Num of file: ";
		cin >> i;
		nameof = lib[i-1];
	}
	else {
		cout << "Input name of file: ";
		cin >> nameof;
	}
	ifstream fin("lib//"+nameof);
	if (fin.fail()) {
		cout << "file could not be opened";
		return 0;
	}
	cout << "How many repats (or -1 for inf): ";
	cin >> iter;
	cout << "For exit press R_Control\n";
	cout << "For start press R_Alt\n";
	while (chkbutt(VK_RMENU) == 0) {
		i = i + 1 - 1;
	}
	i = 0;
	cout << "Start work\n";
	while (i < iter) {
		while (!fin.eof()) {
			if (chkbutt(VK_RCONTROL) == 1) {
				return 0;
			} 
			fin >> coma;
			arg1 = 0;
			arg2 = 0;
			if (coma == "KeyDown") {
				fin >> arg1 >> arg2;
				keydown(alp[arg1 - 4], 1);
			}
			else if (coma == "KeyUp") {
				fin >> arg1 >> arg2;
				keydown(alp[arg1 - 4], 0);
			}
			else if (coma == "Delay") {
				fin >> arg1 >> temp;
				delayy(arg1);
			}
			else if (coma == "MoveTo") {
				fin >> arg1 >> arg2;
				mouse(arg1, arg2, 1);
			}
			else if (coma == "MoveR") {
				fin >> arg1 >> arg2;
				mouse(arg1, arg2, 0);
			}
			else if (coma == "LeftDown") {
				fin >> arg1;
				mclick(1, 1);
			}
			else if (coma == "LeftUp") {
				fin >> arg1;
				mclick(1, 0);
			}
			else if (coma == "RightDown") {
				fin >> arg1;
				mclick(0, 1);
			}
			else if (coma == "RightUp") {
				fin >> arg1;
				mclick(0, 0);
			}
		}
		if (iter != -1) { iter++; }
		fin.clear();
		fin.seekg(0, ios::beg);

	}
}

